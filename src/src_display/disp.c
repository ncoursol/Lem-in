/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 12:12:20 by ncoursol          #+#    #+#             */
/*   Updated: 2019/12/09 15:15:42 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/display.h"

void		event(t_disp *d, int i, int running)
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
		if (d->event.key.keysym.sym == SDLK_KP_MINUS)
		{
			d->delay += (d->delay / 4);
			d->delay = (d->delay > 1500 ? 1500 : d->delay);
		}
		if (d->event.key.keysym.sym == SDLK_KP_PLUS)
		{
			d->delay -= (d->delay / 4);
			d->delay = (d->delay < 20 ? 20 : d->delay);
		}
		while (d->event.key.keysym.sym == SDLK_SPACE)
			SDL_PollEvent(&d->event);
	}
}

int			disp_choice6(t_disp *d, t_input *t, int *c, int i)
{
	if (d->event.type == SDL_KEYUP)
		i = 0;
	if (d->event.type == SDL_QUIT)
		error("(disp.c) SDL_QUIT : ", d);
	if ((d->event.key.keysym.sym == SDLK_LEFT
				|| d->event.key.keysym.sym == SDLK_RIGHT)
			&& d->event.type == SDL_KEYDOWN && i == 0)
	{
		if ((*c == 0 && d->event.key.keysym.sym == SDLK_RIGHT)
				|| (*c == 2 && d->event.key.keysym.sym == SDLK_LEFT) || *c == 1)
			Mix_PlayChannel(-1, d->menu1, 0);
		if (d->event.key.keysym.sym == SDLK_RIGHT)
			*c += (*c == 2 ? 0 : 1);
		if (d->event.key.keysym.sym == SDLK_LEFT)
			*c -= (*c == 0 ? 0 : 1);
		disp_choice(d, t, c, i);
		return (0);
	}
	return (1);
}

void		disp_w6(t_input *t, t_room **s, t_room **nb_one, int *i)
{
	if (*i == 0)
	{
		*s = t->first;
		while ((*s)->type != 1)
			*s = (*s)->next;
		*nb_one = *s;
	}
}

void		replace_room(t_disp *d, t_input *t)
{
	t_room		*s;

	if (SDL_SetRenderTarget(d->rend, d->txt) < 0)
		error("(disp.c) SDL_SetRenderTarget", d);
	s = t->first;
	while (s->type != 1)
		s = s->next;
	d->rback.x = (s->x * t->coefx) + 75;
	d->rback.y = (s->y * t->coefy) + 75;
	d->rback.w = 50;
	d->rback.h = 50;
	if (SDL_RenderCopy(d->rend, d->r_start, NULL, &d->rback) < 0)
		error("(disp.c) SDL_RenderCopy : ", d);
	s = t->first;
	while (s->type != 2)
		s = s->next;
	d->rback.x = (s->x * t->coefx) + 75;
	d->rback.y = (s->y * t->coefy) + 75;
	d->rback.w = 50;
	d->rback.h = 50;
	if (SDL_RenderCopy(d->rend, d->r_end, NULL, &d->rback) < 0)
		error("(disp.c) SDL_RenderCopy : ", d);
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(disp.c) SDL_SetRenderTarget", d);
	SDL_RenderPresent(d->rend);
}

void		disp(t_disp *d, t_input *t)
{
	int		w;
	int		h;
	int		c;
	char	*line;

	c = 0;
	SDL_GetWindowSize(d->win, &w, &h);
	t->coefx = (t->xmax <= 1 ? w - 200 : t->coefx);
	t->coefy = (t->xmax <= 1 ? h - 200 : t->coefy);
	if (t->xmax > 1 && t->ymax > 1)
	{
		t->coefx = (((float)w - 200) / (float)t->xmax);
		t->coefy = (((float)h - 200) / (float)t->ymax);
	}
	disp_room(d, t);
	disp_links(d, t);
	disp_karp(d, t);
	replace_room(d, t);
	SDL_Delay(1500);
	disp_choice(d, t, &c, 0);
	lem(d, t, c);
}
