/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_lem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 15:21:45 by dberger           #+#    #+#             */
/*   Updated: 2019/12/09 21:03:11 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/display.h"

void		lem3(t_disp *d, t_input *t, int *i)
{
	while (SDL_PollEvent(&d->event))
	{
		if (d->event.type == SDL_QUIT)
			error("(disp.c) SDL_QUIT : ", d);
		if (d->event.key.keysym.sym == SDLK_ESCAPE)
		{
			d->delay = -1;
			error("\n", d);
		}
		if (d->event.key.keysym.sym == SDLK_KP_PLUS)
			d->delay = (d->delay == 40 ? 40 : d->delay + 1);
		if (d->event.key.keysym.sym == SDLK_KP_MINUS)
			d->delay = (d->delay == 0 ? 0 : d->delay - 1);
		if (d->event.key.keysym.sym == SDLK_SPACE)
			d->delay = 0;
	}
	if (t->line[*i])
		*i += 1;
}

void		lem5(t_input *t, t_room *s, int *i)
{
	int		j;

	while (t->line[*i - 1] != '-')
		*i += 1;
	j = *i;
	while (t->line[*i] && t->line[*i] != ' ')
		*i += 1;
	s = t->first;
	while (ft_strncmp(s->name, t->line + j, *i - j))
		s = s->next;
	t->xmin = (s->x * t->coefx) + 100;
	t->ymin = (s->y * t->coefy) + 100;
}

void		lem2(t_disp *d, t_input *t, int **ant, int *c)
{
	int		k;
	int		i;
	t_room	*s;

	i = 0;
	while (t->line[i])
	{
		if (t->line[i] == 'L')
		{
			k = ft_atoi(t->line + i + 1) - 1;
			t->xmax = ant[k][0];
			t->ymax = ant[k][1];
			lem5(t, s, &i);
			ft_trace_line(t, d, (k == 0 ? *c : 0));
			ant[k][0] = t->xmax;
			ant[k][1] = t->ymax;
			if (t->xmax != t->xmin || t->ymax != t->ymin)
				t->link_nb = 0;
		}
		lem3(d, t, &i);
	}
	SDL_RenderPresent(d->rend);
}

void		lem4(t_disp *d, t_input *t, int **ant, int *c)
{
	d->delay = 6;
	while (t->line[0] == 'L')
	{
		t->link_nb = 0;
		while (t->link_nb == 0)
		{
			t->link_nb = 1;
			d->rback.x = 0;
			d->rback.y = 0;
			if (SDL_QueryTexture(d->txt, NULL, NULL,
			&d->rback.w, &d->rback.h) < 0)
				error("(disp.c) SDL_QueryTexture : ", d);
			if (SDL_RenderCopy(d->rend, d->txt, NULL, &d->rback) < 0)
				error("(disp.c) SDL_RenderCopy : ", d);
			lem2(d, t, ant, c);
		}
		free(t->line);
		get_next_line(0, &t->line);
	}
	if (t->line[0] == 'L')
		free(t->line);
	d->rback.x = 0;
	d->rback.y = 0;
	if (SDL_QueryTexture(d->txt, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
		error("(disp.c) SDL_QueryTexture : ", d);
}

int			lem(t_disp *d, t_input *t, int c)
{
	int		**ant;
	int		i;

	i = 0;
	if (!(ant = (int**)malloc(sizeof(int*) * t->ant_nb)))
		return (0);
	while (i < t->ant_nb)
	{
		if (!(ant[i] = (int*)malloc(sizeof(int) * 2)))
			return (0);
		ant[i][0] = (t->xmax * t->coefx) + 100;
		ant[i][1] = (t->ymax * t->coefy) + 100;
		i++;
	}
	while (t->line[0] != 'L' || strchr(t->line, '-') == NULL
	|| t->line[1] > '9' || t->line[1] < '0')
	{
		get_next_line(0, &t->line);
		if (t->line[0] != 'L')
			free(t->line);
	}
	lem4(d, t, ant, &c);
	lem6(d, t, ant, i);
	return (1);
}
