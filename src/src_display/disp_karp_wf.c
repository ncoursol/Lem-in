/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_karp_wf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 15:21:36 by dberger           #+#    #+#             */
/*   Updated: 2019/12/05 15:21:38 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/display.h"

void			disp_w5(t_input *t, t_room **s, int *i, int *j)
{
	*s = t->first;
	*i += 1;
	while (t->line[*i] && t->line[*i] != '-')
		*i += 1;
	while (ft_strncmp((*s)->name, t->line + *j + 1, *i - *j - 1))
		*s = (*s)->next;
}

void			disp_w4(t_disp *d, t_room **s, t_room **nb_one)
{
	if (SDL_QueryTexture(d->txt2, NULL, NULL,
				&d->rback.w, &d->rback.h) < 0)
		error("(disp_karp.c) SDL_QueryTexture : ", d);
	if (SDL_RenderCopy(d->rend, d->txt2, NULL, &d->rback) < 0)
		error("(disp_karp.c) SDL_RenderCopy : ", d);
	*nb_one = *s;
	SDL_RenderPresent(d->rend);
	SDL_Delay(d->delay == -1 ? 0 : d->delay);
	event(d, 0, 1);
}

void			disp_w3(t_disp *d, t_input *t, t_room **s, t_room **nb_one)
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
	d->rback.x = 0;
	d->rback.y = 0;
}

void			disp_w2(t_disp *d, t_input *t)
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
	if (SDL_SetRenderDrawColor(d->rend, 255, 170, 0, 250) < 0)
		error("(disp_karp.c) SDL_SetRenderDrawColor : ", d);
	get_next_line(0, &t->line);
}

void			disp_w(t_disp *d, t_input *t, t_room *s, int i)
{
	t_room		*nb_one;
	int			j;

	disp_w2(d, t);
	while (t->line[0] != '#')
	{
		i = 0;
		while (t->line[i])
		{
			j = 0;
			if (t->line[i] == '-')
			{
				if (SDL_SetRenderTarget(d->rend, d->txt2) < 0)
					error("(disp_karp.c) SDL_SetRenderTarget : ", d);
				j = i;
				disp_w6(t, &s, &nb_one, &i);
				disp_w5(t, &s, &i, &j);
				disp_w3(d, t, &s, &nb_one);
				disp_w4(d, &s, &nb_one);
			}
		}
		free(t->line);
		get_next_line(0, &t->line);
	}
}
