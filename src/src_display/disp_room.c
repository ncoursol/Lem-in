/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 15:22:07 by dberger           #+#    #+#             */
/*   Updated: 2019/12/05 15:22:09 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/display.h"

void		error3(t_disp *d)
{
	SDL_DestroyTexture(d->morph_c);
	SDL_DestroyTexture(d->neo_c);
	SDL_DestroyTexture(d->trini_c);
	SDL_DestroyTexture(d->morph_t);
	SDL_DestroyTexture(d->neo_t);
	SDL_DestroyTexture(d->trini_t);
	SDL_DestroyTexture(d->pils_b);
	SDL_DestroyTexture(d->pils_r);
	SDL_DestroyTexture(d->sub);
	SDL_DestroyRenderer(d->rend);
	SDL_DestroyWindow(d->win);
}

void		lem6(t_disp *d, t_input *t, int **ant, int i)
{
	if (SDL_RenderCopy(d->rend, d->txt, NULL, &d->rback) < 0)
		error("(disp.c) SDL_RenderCopy : ", d);
	SDL_RenderPresent(d->rend);
	i = 0;
	while (i < t->ant_nb)
	{
		free(ant[i]);
		i++;
	}
	free(ant);
}

void		disp_room3(t_disp *d, t_input *t, t_room **s)
{
	d->rback.x = ((*s)->x * t->coefx) + 75;
	d->rback.y = ((*s)->y * t->coefy) + 75;
	d->rback.w = 50;
	d->rback.h = 50;
	if (SDL_RenderCopy(d->rend, d->toss, NULL, &d->rback) < 0)
		error("(disp.c) SDL_RenderCopy : ", d);
	*s = (*s)->next;
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(disp.c) SDL_SetRenderTarget", d);
	d->rback.x = 0;
	d->rback.y = 0;
	if (SDL_QueryTexture(d->back2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
		error("(disp.c) SDL_QueryTexture : ", d);
	if (SDL_RenderCopy(d->rend, d->txt, NULL, &d->rback) < 0)
		error("(disp.c) SDL_RenderCopy : ", d);
	SDL_RenderPresent(d->rend);
	SDL_Delay(d->delay);
	if (SDL_SetRenderTarget(d->rend, d->txt) < 0)
		error("(disp.c) SDL_SetRenderTarget", d);
}

void		disp_room2(t_disp *d, t_input *t, t_room **s)
{
	if (SDL_QueryTexture(d->back2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
		error("(disp.c) SDL_QueryTexture : ", d);
	if (SDL_RenderCopy(d->rend, d->back2, NULL, &d->rback) < 0)
		error("(disp.c) SDL_RenderCopy : ", d);
	d->rback.x = ((*s)->x * t->coefx) + 75;
	d->rback.y = ((*s)->y * t->coefy) + 75;
	d->rback.w = 50;
	d->rback.h = 50;
	if (SDL_RenderCopy(d->rend, d->toss, NULL, &d->rback) < 0)
		error("(disp.c) SDL_RenderCopy : ", d);
	d->rback.x = 0;
	d->rback.y = 0;
	*s = (*s)->next;
	SDL_RenderPresent(d->rend);
	SDL_Delay(d->delay);
	event(d, 0, 1);
}

void		disp_room(t_disp *d, t_input *t)
{
	int		i;
	t_room	*s;

	i = 0;
	s = t->first;
	while (i++ < t->room_nb)
		disp_room2(d, t, &s);
	i = 0;
	s = t->first;
	if (SDL_SetRenderTarget(d->rend, d->txt) < 0)
		error("(disp.c) SDL_SetRenderTarget", d);
	if (SDL_QueryTexture(d->back2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
		error("(disp.c) SDL_QueryTexture : ", d);
	if (SDL_RenderCopy(d->rend, d->back2, NULL, &d->rback) < 0)
		error("(disp.c) SDL_RenderCopy : ", d);
	while (i++ < t->room_nb)
	{
		disp_room3(d, t, &s);
		event(d, 0, 1);
	}
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(disp.c) SDL_SetRenderTarget", d);
}
