/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 13:58:04 by ncoursol          #+#    #+#             */
/*   Updated: 2019/11/19 16:54:24 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/display.h"

void	ft_fill_pix(t_input *t, t_disp *d, int c)
{
	d->rback.x = t->xmax - 50;
	d->rback.y = t->ymax - 52;
	d->rback.w = 100;
	d->rback.h = 100;
	if (c == 3)
	{
		if (SDL_RenderCopy(d->rend, d->neo, NULL, &d->rback) < 0)
			error("(trace_line.c) SDL_RenderCopy : ", d);
	}
	else if (c == 4)
	{
		if (SDL_RenderCopy(d->rend, d->trini, NULL, &d->rback) < 0)
			error("(trace_line.c) SDL_RenderCopy : ", d);
	}
	else if (c == 5)
	{
		if (SDL_RenderCopy(d->rend, d->morph, NULL, &d->rback) < 0)
			error("(trace_line.c) SDL_RenderCopy : ", d);
	}
	else
	{
		if (SDL_RenderCopy(d->rend, d->smith, NULL, &d->rback) < 0)
			error("(trace_line.c) SDL_RenderCopy : ", d);
	}
}

void	ft_case_two(t_input *t, t_disp *d, int i, int c)
{
	int		cumul;
	int		x;
	int		y;
	int		dx;
	int		dy;

	dx = t->xmin - t->xmax;
	dy = t->ymin - t->ymax;
	x = (dx > 0 ? 1 : -1);
	y = (dy > 0 ? 1 : -1);
	dx = (dx < 0 ? -dx : dx);
	dy = (dy < 0 ? -dy : dy);
	cumul = dy / 2;
	while (i <= d->delay && (t->xmax != t->xmin || t->ymax != t->ymin))
	{
		t->ymax += y;
		cumul += dx;
		if (cumul >= dy)
		{
			cumul -= dy;
			t->xmax += x;
		}
		i++;
	}
	ft_fill_pix(t, d, c);
}

void	ft_case_one(t_input *t, t_disp *d, int i, int c)
{
	int		cumul;
	int		x;
	int		y;
	int		dx;
	int		dy;

	dx = t->xmin - t->xmax;
	dy = t->ymin - t->ymax;
	x = (dx > 0 ? 1 : -1);
	y = (dy > 0 ? 1 : -1);
	dx = (dx < 0 ? -dx : dx);
	dy = (dy < 0 ? -dy : dy);
	cumul = dx / 2;
	while (i <= d->delay && (t->xmax != t->xmin || t->ymax != t->ymin))
	{
		t->xmax += x;
		cumul += dy;
		if (cumul >= dx)
		{
			cumul -= dx;
			t->ymax += y;
		}
		i++;
	}
	ft_fill_pix(t, d, c);
}

void	ft_trace_line(t_input *t, t_disp *d, int c)
{
	int		i;
	int		dx;
	int		dy;

	dx = t->xmin - t->xmax;
	dy = t->ymin - t->ymax;
	dx = (dx < 0 ? -dx : dx);
	dy = (dy < 0 ? -dy : dy);
	i = 1;
	if (dx > dy)
		ft_case_one(t, d, i, c);
	else
		ft_case_two(t, d, i, c);
}
