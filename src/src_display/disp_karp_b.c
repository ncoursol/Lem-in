/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_karp_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 15:21:15 by dberger           #+#    #+#             */
/*   Updated: 2019/12/05 15:21:17 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/display.h"

void			disp_b4(t_disp *d, t_input *t, t_room **s, int *j)
{
	if (SDL_RenderCopy(d->rend, d->pils_r, NULL, &d->rback) < 0)
		error("(disp_karp.c) SDL_RenderCopy : ", d);
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(disp_karp.c) SDL_SetRenderTarget : ", d);
	d->rback.x = 0;
	d->rback.y = 0;
	if (SDL_QueryTexture(d->txt2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
		error("(disp_karp.c) SDL_QueryTexture : ", d);
	if (SDL_RenderCopy(d->rend, d->txt2, NULL, &d->rback) < 0)
		error("(disp_karp.c) SDL_RenderCopy : ", d);
	SDL_RenderPresent(d->rend);
	*j = 0;
	*s = t->first;
	SDL_Delay(d->delay);
	event(d, 0, 1);
}

void			disp_b3(t_disp *d, t_input *t, t_room **s, t_room **nb_one)
{
	if (SDL_RenderDrawLine(d->rend, (*nb_one)->x * t->coefx + 100,
				(*nb_one)->y * t->coefy + 100, (*s)->x * t->coefx + 100,
				(*s)->y * t->coefy + 100) < 0)
		error("(disp_karp.c) SDL_RenderDrawLine : ", d);
	if (SDL_RenderDrawLine(d->rend, (*nb_one)->x * t->coefx + 101,
				(*nb_one)->y * t->coefy + 100, (*s)->x * t->coefx + 101,
				(*s)->y * t->coefy + 100) < 0)
		error("(disp_karp.c) SDL_RenderDrawLine : ", d);
	if (SDL_RenderDrawLine(d->rend, (*nb_one)->x * t->coefx + 99,
				(*nb_one)->y * t->coefy + 100, (*s)->x * t->coefx + 99,
				(*s)->y * t->coefy + 100) < 0)
		error("(disp_karp.c) SDL_RenderDrawLine : ", d);
	if (SDL_RenderDrawLine(d->rend, (*nb_one)->x * t->coefx + 100,
				(*nb_one)->y * t->coefy + 101, (*s)->x * t->coefx + 100,
				(*s)->y * t->coefy + 101) < 0)
		error("(disp_karp.c) SDL_RenderDrawLine : ", d);
	if (SDL_RenderDrawLine(d->rend, (*nb_one)->x * t->coefx + 100,
				(*nb_one)->y * t->coefy + 99, (*s)->x * t->coefx + 100,
				(*s)->y * t->coefy + 99) < 0)
		error("(disp_karp.c) SDL_RenderDrawLine : ", d);
	d->rback.x = (*s)->x * t->coefx + 50;
	d->rback.y = (*s)->y * t->coefy + 24;
	d->rback.w = 27;
	d->rback.h = 64;
}

int				disp_b2(t_disp *d, t_input *t, t_room **s, t_room **nb_one)
{
	int		i;

	i = 0;
	*s = t->first;
	while (t->line[i] != ':')
		i++;
	while (ft_strncmp((*s)->name, t->line, i))
		*s = (*s)->next;
	*nb_one = *s;
	*s = t->first;
	if (SDL_SetRenderTarget(d->rend, d->txt2) < 0)
		error("(disp_karp.c) SDL_SetRenderTarget : ", d);
	d->rback.x = (*nb_one)->x * t->coefx + 50;
	d->rback.y = (*nb_one)->y * t->coefy + 24;
	d->rback.w = 27;
	d->rback.h = 64;
	if (SDL_RenderCopy(d->rend, d->pils_b, NULL, &d->rback) < 0)
		error("(disp_karp.c) SDL_RenderCopy : ", d);
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(disp_karp.c) SDL_SetRenderTarget : ", d);
	d->rback.x = 0;
	d->rback.y = 0;
	if (SDL_QueryTexture(d->txt2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
		error("(disp_karp.c) SDL_QueryTexture : ", d);
	return (i);
}

void			disp_b5(t_disp *d, t_input *t, t_room *s, int i)
{
	int		j;
	t_room	*nb_one;

	i = disp_b2(d, t, &s, &nb_one);
	if (SDL_RenderCopy(d->rend, d->txt2, NULL, &d->rback) < 0)
		error("(disp_karp.c) SDL_RenderCopy : ", d);
	SDL_RenderPresent(d->rend);
	SDL_Delay(d->delay);
	j = 0;
	while (t->line[i])
	{
		j++;
		i++;
		if (t->line[i] == '-')
		{
			j--;
			if (SDL_SetRenderTarget(d->rend, d->txt2) < 0)
				error("(disp_karp.c) SDL_SetRenderTarget : ", d);
			while (ft_strncmp(s->name, t->line + (i - j), j))
				s = s->next;
			disp_b3(d, t, &s, &nb_one);
			disp_b4(d, t, &s, &j);
		}
	}
}

void			disp_b(t_disp *d, t_input *t, t_room *s, int i)
{
	if (SDL_SetRenderDrawColor(d->rend, 255, 255, 255, 250) < 0)
		error("(disp_karp.c) SDL_SetRenderDrawColor : ", d);
	get_next_line(0, &t->line);
	while (t->line[0] != '#')
	{
		disp_b5(d, t, s, i);
		free(t->line);
		get_next_line(0, &t->line);
	}
}
