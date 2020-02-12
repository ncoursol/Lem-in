/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_karp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 15:21:04 by dberger           #+#    #+#             */
/*   Updated: 2019/12/05 15:21:06 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/display.h"

void		init_menu(t_disp *d, int cursor)
{
	d->rback.x = 900;
	d->rback.y = 780;
	if (cursor == 1)
	{
		if (SDL_QueryTexture(d->start_w, NULL, NULL,
					&d->rback.w, &d->rback.h) < 0)
			error("(menu.c) SDL_QueryTexture : ", d);
		if (SDL_RenderCopy(d->rend, d->start_w, NULL, &d->rback) < 0)
			error("(menu.c) SDL_RenderCopy : ", d);
	}
	else
	{
		if (SDL_QueryTexture(d->start, NULL, NULL,
					&d->rback.w, &d->rback.h) < 0)
			error("(menu.c) SDL_QueryTexture : ", d);
		if (SDL_RenderCopy(d->rend, d->start, NULL, &d->rback) < 0)
			error("(menu.c) SDL_RenderCopy : ", d);
	}
	if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_NONE) < 0)
		error("(menu.c) SDL_SetRenderDrawBlendMode error : ", d);
}

void		disp_links6(t_disp *d)
{
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(disp.c) SDL_SetRenderTarget", d);
	d->rback.x = 0;
	d->rback.y = 0;
	if (SDL_QueryTexture(d->back2, NULL, NULL,
				&d->rback.w, &d->rback.h) < 0)
		error("(disp.c) SDL_QueryTexture : ", d);
	if (SDL_RenderCopy(d->rend, d->txt, NULL, &d->rback) < 0)
		error("(disp.c) SDL_RenderCopy : ", d);
	SDL_RenderPresent(d->rend);
	SDL_Delay(d->delay);
	if (SDL_SetRenderTarget(d->rend, d->txt) < 0)
		error("(disp.c) SDL_SetRenderTarget", d);
	event(d, 0, 1);
}

void		disp_karp3(t_disp *d, t_input *t, t_room *s)
{
	if (t->line[1] == 'F')
		d->delay = -1;
	free(t->line);
	disp_w(d, t, s, 0);
	if (d->delay == -1)
	{
		if (SDL_SetRenderTarget(d->rend, d->txt) < 0)
			error("(disp_karp.c) SDL_SetRenderTarget : ", d);
		d->rback.x = 0;
		d->rback.y = 0;
		if (SDL_QueryTexture(d->txt2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
			error("(disp_karp.c) SDL_QueryTexture : ", d);
		if (SDL_RenderCopy(d->rend, d->txt2, NULL, &d->rback) < 0)
			error("(disp_karp.c) SDL_RenderCopy : ", d);
		if (SDL_SetRenderTarget(d->rend, NULL) < 0)
			error("(disp_karp.c) SDL_SetRenderTarget : ", d);
	}
}

void		disp_karp2(t_disp *d, t_input *t)
{
	if (SDL_SetRenderTarget(d->rend, d->txt2) < 0)
		error("(disp_karp.c) SDL_SetRenderTarget : ", d);
	d->rback.x = 0;
	d->rback.y = 0;
	if (SDL_QueryTexture(d->txt, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
		error("(disp_karp.c) SDL_QueryTexture : ", d);
	if (SDL_RenderCopy(d->rend, d->txt, NULL, &d->rback) < 0)
		error("(disp_karp.c) SDL_RenderCopy : ", d);
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(disp_karp.c) SDL_SetRenderTarget : ", d);
	while (t->line[0] != '#')
	{
		free(t->line);
		get_next_line(0, &t->line);
	}
	d->delay = d->delay * 8;
	t->running = 1;
}

void		disp_karp(t_disp *d, t_input *t)
{
	t_room		*s;

	disp_karp2(d, t);
	while (t->line[0] != '#' || t->line[1] != '0')
	{
		if (t->line[0] == '#' && t->line[1] == 'B')
		{
			free(t->line);
			disp_b(d, t, s, 0);
		}
		else if (t->line[0] == '#' && t->line[1] == 'K')
		{
			free(t->line);
			disp_k(d, t, s, 0);
		}
		else if ((t->line[0] == '#' && t->line[1] == 'W')
				|| (t->line[0] == '#' && t->line[1] == 'F'))
			disp_karp3(d, t, s);
		if (t->line[0] != '#')
		{
			free(t->line);
			get_next_line(0, &t->line);
		}
	}
	free(t->line);
}
