/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_choice.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 15:20:53 by dberger           #+#    #+#             */
/*   Updated: 2019/12/05 15:20:56 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/display.h"

void		disp_choice5(t_disp *d, int *c)
{
	if (*c == 0)
	{
		if (SDL_RenderCopy(d->rend, d->neo_t, NULL, &d->menu) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
	}
	else if (*c == 1)
	{
		if (SDL_RenderCopy(d->rend, d->trini_t, NULL, &d->menu) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
	}
	else
	{
		if (SDL_RenderCopy(d->rend, d->morph_t, NULL, &d->menu) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
	}
	if (SDL_SetRenderDrawColor(d->rend, 29, 128, 22, 250) < 0)
		error("(disp.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderDrawRect(d->rend, &d->menu) < 0)
		error("(disp.c) SDL_RenderDrawRect : ", d);
	SDL_RenderPresent(d->rend);
}

void		disp_choice4(t_disp *d, int *c)
{
	d->rback.x = d->menu.x + 460;
	if (*c == 2)
	{
		if (SDL_RenderCopy(d->rend, d->morph_c, NULL, &d->rback) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
	}
	else
	{
		if (SDL_RenderCopy(d->rend, d->morph_b, NULL, &d->rback) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
	}
	d->menu.w -= 24;
	d->menu.h = 60;
	d->menu.x += 12;
	d->menu.y += 12;
	if (SDL_RenderCopy(d->rend, d->sub, NULL, &d->menu) < 0)
		error("(disp.c) SDL_RenderCopy : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 29, 128, 22, 250) < 0)
		error("(disp.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderDrawRect(d->rend, &d->menu) < 0)
		error("(disp.c) SDL_RenderDrawRect : ", d);
	d->menu.h = 400;
	d->menu.y += 72;
}

void		disp_choice3(t_disp *d, int *c)
{
	d->rback.w = 200;
	d->rback.h = 200;
	d->rback.y = (d->menu.h + d->menu.y) - 220;
	d->rback.x = d->menu.x + 20;
	if (*c == 0)
	{
		if (SDL_RenderCopy(d->rend, d->neo_c, NULL, &d->rback) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
	}
	else
	{
		if (SDL_RenderCopy(d->rend, d->neo_b, NULL, &d->rback) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
	}
	d->rback.x = d->menu.x + 240;
	if (*c == 1)
	{
		if (SDL_RenderCopy(d->rend, d->trini_c, NULL, &d->rback) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
	}
	else
	{
		if (SDL_RenderCopy(d->rend, d->trini_b, NULL, &d->rback) < 0)
			error("(disp.c) SDL_RenderCopy : ", d);
	}
}

void		disp_choice2(t_disp *d, int *c)
{
	d->rback.y = 0;
	d->rback.x = 0;
	if (SDL_QueryTexture(d->back2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
		error("(disp.c) SDL_QueryTexture : ", d);
	if (SDL_RenderCopy(d->rend, d->txt, NULL, &d->rback) < 0)
		error("(disp.c) SDL_RenderCopy : ", d);
	d->menu.w = (d->rback.w / 4) * 2;
	d->menu.h = (d->rback.h / 4) * 2;
	d->menu.x = (d->rback.w / 2) - (d->menu.w / 2);
	d->menu.y = (d->rback.h / 2) - (d->menu.h / 2);
	if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_BLEND) < 0)
		error("(disp.c) SDL_SetRenderDrawBlendMode : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 0, 0, 0, 250) < 0)
		error("(disp.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderFillRect(d->rend, &d->menu) < 0)
		error("(disp.c) SDL_RenderFillRect : ", d);
	if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_NONE) < 0)
		error("(disp.c) SDL_SetRenderDrawBlendMode : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 29, 128, 22, 250) < 0)
		error("(disp.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderDrawRect(d->rend, &d->menu) < 0)
		error("(disp.c) SDL_RenderDrawRect : ", d);
	disp_choice3(d, c);
	disp_choice4(d, c);
	disp_choice5(d, c);
}

void		disp_choice(t_disp *d, t_input *t, int *c, int i)
{
	disp_choice2(d, c);
	while (*c < 3)
	{
		while (SDL_PollEvent(&d->event))
		{
			if (!disp_choice6(d, t, c, i))
				break ;
			if (d->event.key.keysym.sym == SDLK_RETURN)
			{
				d->rback.y = 0;
				d->rback.x = 0;
				if (SDL_QueryTexture(d->back2, NULL, NULL,
				&d->rback.w, &d->rback.h) < 0)
					error("(disp.c) SDL_QueryTexture : ", d);
				if (Mix_PlayChannel(-1, d->menu2, 0) == -1)
					error("(disp.c) Mix_PlayChannel : ", d);
				if (SDL_RenderCopy(d->rend, d->txt, NULL, &d->rback) < 0)
					error("(disp.c) SDL_RenderCopy : ", d);
				SDL_RenderPresent(d->rend);
				*c += 3;
				break ;
			}
		}
	}
}
