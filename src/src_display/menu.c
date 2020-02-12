/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 13:39:28 by ncoursol          #+#    #+#             */
/*   Updated: 2019/11/28 16:45:38 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/display.h"

void		menu2(t_disp *d, int cursor)
{
	if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_BLEND) < 0)
		error("(menu.c) SDL_SetRenderDrawBlendMode error : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 0, 0, 0, 120) < 0)
		error("(menu.c) SDL_SetRenderDrawColor error : ", d);
	if (SDL_RenderFillRect(d->rend, NULL) < 0)
		error("(menu.c) SDL_RenderFillRect error : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 138, 138, 138, 50) < 0)
		error("(menu.c) SDL_SetRenderDrawColor error : ", d);
	if (SDL_RenderFillRect(d->rend, &d->menu) < 0)
		error("(menu.c) SDL_RenderFillRect error : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 29, 128, 22, 250) < 0)
		error("(menu.c) SDL_SetRenderDrawColor error : ", d);
	if (SDL_RenderDrawRect(d->rend, &d->menu) < 0)
		error("(menu.c) SDL_RenderDrawRect error : ", d);
	d->rback.x = 879;
	d->rback.y = 0;
	if (SDL_QueryTexture(d->title, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
		error("(menu.c) SDL_QueryTexture : ", d);
	if (SDL_RenderCopy(d->rend, d->title, NULL, &d->rback) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	init_menu(d, cursor);
}

void		cursor_choice(t_disp *d, int cursor)
{
	if (cursor != 1)
	{
		if (SDL_QueryTexture(d->leave_w, NULL, NULL,
		&d->rback.w, &d->rback.h) < 0)
			error("(menu.c) SDL_QueryTexture : ", d);
		if (SDL_RenderCopy(d->rend, d->leave_w, NULL, &d->rback) < 0)
			error("(menu.c) SDL_RenderCopy : ", d);
		d->rback.x = 1450;
		d->rback.y = 990;
		if (SDL_QueryTexture(d->arrow, NULL, NULL,
		&d->rback.w, &d->rback.h) < 0)
			error("(menu.c) SDL_QueryTexture : ", d);
		if (SDL_RenderCopy(d->rend, d->arrow, NULL, &d->rback) < 0)
			error("(menu.c) SDL_RenderCopy : ", d);
	}
	d->rback.x = 890;
	d->rback.y = 420;
	if (SDL_QueryTexture(d->made, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
		error("(menu.c) SDL_QueryTexture : ", d);
	if (SDL_RenderCopy(d->rend, d->made, NULL, &d->rback) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	if (SDL_RenderDrawLine(d->rend, 1020, 720, 1550, 720) < 0)
		error("(menu.c) SDL_RenderDrawLine error : ", d);
	SDL_RenderPresent(d->rend);
}

void		menu3(t_disp *d, int cursor)
{
	d->rback.x = 900;
	d->rback.y = 980;
	if (cursor == 1)
	{
		if (SDL_QueryTexture(d->leave, NULL, NULL,
		&d->rback.w, &d->rback.h) < 0)
			error("(menu.c) SDL_QueryTexture : ", d);
		if (SDL_RenderCopy(d->rend, d->leave, NULL, &d->rback) < 0)
			error("(menu.c) SDL_RenderCopy : ", d);
		d->rback.x = 1450;
		d->rback.y = 790;
		if (SDL_QueryTexture(d->arrow, NULL, NULL,
		&d->rback.w, &d->rback.h) < 0)
			error("(menu.c) SDL_QueryTexture : ", d);
		if (SDL_RenderCopy(d->rend, d->arrow, NULL, &d->rback) < 0)
			error("(menu.c) SDL_RenderCopy : ", d);
	}
	cursor_choice(d, cursor);
}

int			input_case(t_disp *d, int *running, int cursor, int i)
{
	if (d->event.type == SDL_QUIT)
		error("(menu.c) SDL_QUIT : ", d);
	if ((d->event.key.keysym.sym == SDLK_DOWN
				|| d->event.key.keysym.sym == SDLK_UP)
			&& d->event.type == SDL_KEYDOWN && i == 0)
	{
		if ((cursor == 1 && d->event.key.keysym.sym == SDLK_DOWN)
				|| (cursor == 0 && d->event.key.keysym.sym == SDLK_UP))
			if (Mix_PlayChannel(-1, d->menu1, 0) == -1)
				error("(menu.c) Mix_PlayChannel : ", d);
		d->rback.x = 0;
		d->rback.y = 0;
		if (SDL_QueryTexture(d->back, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
			error("(menu.c) SDL_QueryTexture : ", d);
		if (SDL_RenderCopy(d->rend, d->back, NULL, &d->rback) < 0)
			error("(menu.c) SDL_RenderCopy : ", d);
		if (d->event.key.keysym.sym == SDLK_DOWN)
			cursor = (cursor == 1 ? 0 : 0);
		if (d->event.key.keysym.sym == SDLK_UP)
			cursor = (cursor == 0 ? 1 : 1);
		menu(d, running, cursor, 1);
		return (0);
	}
	return (1);
}

void		menu(t_disp *d, int *running, int cursor, int i)
{
	if ((d->menu1 = Mix_LoadWAV("img/low.wav")) == NULL)
		error("(menu.c) Mix_LoadWAV : ", d);
	if ((d->menu2 = Mix_LoadWAV("img/scratch.wav")) == NULL)
		error("(menu.c) Mix_LoadWAV : ", d);
	Mix_VolumeChunk(d->menu1, 20);
	Mix_VolumeChunk(d->menu2, 20);
	menu2(d, cursor);
	menu3(d, cursor);
	while (*running == 2)
	{
		while (SDL_PollEvent(&d->event))
		{
			if (!input_case(d, running, cursor, i))
				break ;
			if (d->event.key.keysym.sym == SDLK_RETURN)
			{
				if (Mix_PlayChannel(-1, d->menu2, 0) == -1)
					error("(menu.c) Mix_PLayChannel : ", d);
				*running = (cursor == 0 ? 0 : 1);
				break ;
			}
			if (d->event.type == SDL_KEYUP)
				i = 0;
		}
	}
}
