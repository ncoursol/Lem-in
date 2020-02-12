/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 15:21:53 by dberger           #+#    #+#             */
/*   Updated: 2019/12/09 15:16:47 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/display.h"

void		disp_links5(t_disp *d, t_input *t, t_room **s, int *i)
{
	d->rback.x = ((*s)->x * t->coefx) + 75;
	d->rback.y = ((*s)->y * t->coefy) + 75;
	d->rback.w = 50;
	d->rback.h = 50;
	if ((*s)->type == 1)
	{
		if (SDL_RenderCopy(d->rend, d->r_start, NULL, &d->rback) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
		t->xmax = (*s)->x;
		t->ymax = (*s)->y;
	}
	else if ((*s)->type == 2)
	{
		if (SDL_RenderCopy(d->rend, d->r_end, NULL, &d->rback) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
	}
	else
	{
		if (SDL_RenderCopy(d->rend, d->toss, NULL, &d->rback) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
	}
	*s = (*s)->next;
	*i += 1;
	disp_links6(d);
}

void		disp_links4(t_disp *d, SDL_Point *pts, int *j)
{
	if (SDL_SetRenderTarget(d->rend, d->txt) < 0)
		error("(disp.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderDrawLine(d->rend, pts[*j].x,
				pts[*j].y, pts[*j + 1].x, pts[*j + 1].y) < 0)
		error("(disp.c) SDL_RenderDrawLine : ", d);
	if (SDL_RenderDrawLine(d->rend, pts[*j].x + 1,
				pts[*j].y, pts[*j + 1].x + 1, pts[*j + 1].y) < 0)
		error("(disp.c) SDL_RenderDrawLine : ", d);
	if (SDL_RenderDrawLine(d->rend, pts[*j].x - 1,
				pts[*j].y, pts[*j + 1].x - 1, pts[*j + 1].y) < 0)
		error("(disp.c) SDL_RenderDrawLine : ", d);
	if (SDL_RenderDrawLine(d->rend, pts[*j].x,
				pts[*j].y + 1, pts[*j + 1].x, pts[*j + 1].y + 1) < 0)
		error("(disp.c) SDL_RenderDrawLine : ", d);
	if (SDL_RenderDrawLine(d->rend, pts[*j].x,
				pts[*j].y - 1, pts[*j + 1].x, pts[*j + 1].y - 1) < 0)
		error("(disp.c) SDL_RenderDrawLine : ", d);
	*j += 2;
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(disp.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->txt, NULL, &d->rback) < 0)
		error("(disp.c) SDL_RenderCopy : ", d);
	SDL_RenderPresent(d->rend);
	SDL_Delay(d->delay);
	event(d, 0, 1);
}

void		disp_links3(t_disp *d, t_input *t, SDL_Point *pts, int j)
{
	while (j != t->link_nb * 2)
	{
		if (SDL_RenderCopy(d->rend, d->txt, NULL, &d->rback) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
		if (SDL_RenderDrawLine(d->rend, pts[j].x,
					pts[j].y, pts[j + 1].x, pts[j + 1].y) < 0)
			error("(disp.c) SDL_RenderDrawLine : ", d);
		if (SDL_RenderDrawLine(d->rend, pts[j].x + 1,
					pts[j].y, pts[j + 1].x + 1, pts[j + 1].y) < 0)
			error("(disp.c) SDL_RenderDrawLine : ", d);
		if (SDL_RenderDrawLine(d->rend, pts[j].x - 1,
					pts[j].y, pts[j + 1].x - 1, pts[j + 1].y) < 0)
			error("(disp.c) SDL_RenderDrawLine : ", d);
		if (SDL_RenderDrawLine(d->rend, pts[j].x,
					pts[j].y + 1, pts[j + 1].x, pts[j + 1].y + 1) < 0)
			error("(disp.c) SDL_RenderDrawLine : ", d);
		if (SDL_RenderDrawLine(d->rend, pts[j].x,
					pts[j].y - 1, pts[j + 1].x, pts[j + 1].y - 1) < 0)
			error("(disp.c) SDL_RenderDrawLine : ", d);
		j += 2;
		SDL_RenderPresent(d->rend);
		SDL_Delay(d->delay);
		event(d, 0, 1);
	}
}

int			disp_links2(t_input *t, t_room *s, SDL_Point *pts, int *j)
{
	int		i;

	i = 0;
	s = t->first;
	get_next_line(0, &t->line);
	if (t->line[0] == 0)
		return (0);
	if (t->line[0] != '#' && *j < t->link_nb * 2)
	{
		while (t->line[i] != '-')
			i++;
		while (ft_strncmp(s->name, t->line, i))
			s = s->next;
		pts[*j].x = (s->x * t->coefx) + 100;
		pts[*j].y = (s->y * t->coefy) + 100;
		*j += 1;
		s = t->first;
		while (ft_strncmp(s->name, t->line + i + 1, ft_strlen(t->line) - i + 1))
			s = s->next;
		pts[*j].x = (s->x * t->coefx) + 100;
		pts[*j].y = (s->y * t->coefy) + 100;
	}
	*j = (t->line[0] == '#' ? *j : *j + 1);
	free(t->line);
	return (1);
}

void		disp_links(t_disp *d, t_input *t)
{
	t_room		*s;
	SDL_Point	pts[t->link_nb * 2];
	int			i;
	int			j;

	j = 0;
	while (t->line[0] != '\n')
		if (!disp_links2(t, s, pts, &j))
			break ;
	if (SDL_SetRenderDrawColor(d->rend, 29, 128, 22, 250) < 0)
		error("(disp.c) SDL_SetRenderDrawColor : ", d);
	disp_links3(d, t, pts, 0);
	j = 0;
	while (j != t->link_nb * 2)
		disp_links4(d, pts, &j);
	i = 0;
	s = t->first;
	if (SDL_SetRenderTarget(d->rend, d->txt) < 0)
		error("(disp.c) SDL_SetRenderTarget : ", d);
	while (i < t->room_nb)
		disp_links5(d, t, &s, &i);
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(disp.c) SDL_SetRenderTarget", d);
}
