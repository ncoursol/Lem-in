/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_karp_k.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 15:21:24 by dberger           #+#    #+#             */
/*   Updated: 2019/12/05 15:21:25 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/display.h"

void			error2(t_disp *d)
{
	SDL_DestroyTexture(d->back);
	SDL_DestroyTexture(d->back2);
	SDL_DestroyTexture(d->black);
	SDL_DestroyTexture(d->fail);
	SDL_DestroyTexture(d->toss);
	SDL_DestroyTexture(d->r_start);
	SDL_DestroyTexture(d->r_end);
	SDL_DestroyTexture(d->title);
	SDL_DestroyTexture(d->start);
	SDL_DestroyTexture(d->leave);
	SDL_DestroyTexture(d->made);
	SDL_DestroyTexture(d->arrow);
	SDL_DestroyTexture(d->start_w);
	SDL_DestroyTexture(d->leave_w);
	SDL_DestroyTexture(d->txt);
	SDL_DestroyTexture(d->txt2);
	SDL_DestroyTexture(d->morph);
	SDL_DestroyTexture(d->smith);
	SDL_DestroyTexture(d->neo);
	SDL_DestroyTexture(d->trini);
	SDL_DestroyTexture(d->morph_b);
	SDL_DestroyTexture(d->neo_b);
	SDL_DestroyTexture(d->trini_b);
	error3(d);
}

void			disp_k3(t_disp *d, t_input *t, t_room **s, t_room **nb_one)
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
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(disp_karp.c) SDL_SetRenderTarget : ", d);
}

int				disp_k2(t_disp *d, t_input *t, t_room **s, t_room **nb_one)
{
	int		j;
	int		i;

	i = 0;
	while (t->line[i] != '-')
		i++;
	while (ft_strncmp((*s)->name, t->line, i))
		*s = (*s)->next;
	*nb_one = *s;
	*s = t->first;
	j = i;
	while (t->line[i] != ':')
		i++;
	while (ft_strncmp((*s)->name, t->line + j + 1, i - j - 1))
		*s = (*s)->next;
	if (t->line[i + 1] == '1')
	{
		if (SDL_SetRenderDrawColor(d->rend, 25, 152, 227, 250) < 0)
			error("(disp_karp.c) SDL_SetRenderDrawColor : ", d);
	}
	else if (SDL_SetRenderDrawColor(d->rend, 127, 14, 78, 250) < 0)
		error("(disp_karp.c) SDL_SetRenderDrawColor : ", d);
	return (i);
}

void			disp_k(t_disp *d, t_input *t, t_room *s, int i)
{
	t_room		*nb_one;

	get_next_line(0, &t->line);
	while (t->line[0] != '#')
	{
		if (SDL_SetRenderTarget(d->rend, d->txt2) < 0)
			error("(disp_karp.c) SDL_SetRenderTarget : ", d);
		s = t->first;
		i = disp_k2(d, t, &s, &nb_one);
		disp_k3(d, t, &s, &nb_one);
		d->rback.x = 0;
		d->rback.y = 0;
		if (SDL_QueryTexture(d->txt2, NULL, NULL, &d->rback.w, &d->rback.h) < 0)
			error("(disp_karp.c) SDL_QueryTexture : ", d);
		if (SDL_RenderCopy(d->rend, d->txt2, NULL, &d->rback) < 0)
			error("(disp_karp.c) SDL_RenderCopy : ", d);
		SDL_RenderPresent(d->rend);
		SDL_Delay(d->delay);
		event(d, 0, 1);
		free(t->line);
		get_next_line(0, &t->line);
	}
}
