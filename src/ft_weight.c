/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_weight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:50:55 by dberger           #+#    #+#             */
/*   Updated: 2019/12/06 19:00:37 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

/*
** If we are crossing an UNSUDED link, then the weight of the neighbour will
** be the weight of it's possible mum + 1 (since we are moving forward).
** But if it is a link that we are crossing back up, we use substraction since
** we are going backwards, so we are potentially "less" far from start.
*/

int		ft_calc_weight(t_room *room, int i)
{
	int	weight;

	weight = 0;
	if (room->link[i]->status == BACKWARD)
		weight = room->weight - 1;
	else if (room->link[i]->status == UNUSED)
		weight = room->weight + 1;
	return (weight);
}

void	ft_new_in(t_room *room, t_room **queue, t_room **ngb, int weight)
{
	if ((*ngb)->in_q == NOT_IN_QUEUE)
	{
		if (VISU == 1)
			ft_printf("%s-", (*ngb)->name);
		(*ngb)->in_q = IN_QUEUE;
		(*ngb)->next = NULL;
		(*queue)->next = *ngb;
		(*queue) = *ngb;
	}
	(*ngb)->weight = weight;
	(*ngb)->mum = room;
}

/*
** To be able to add a new room to the queue (ngb), we want to make sure
** that the room it comes from is not start or that the ngb is not the mum
** of the room. We need to check if the link from (room) to (ngb) is CLEAN.
** However if we are on a room used in a path we found previously (opti)
** we are only allowed to use a link BACKWARD (== already used by a path,
** that would go from end to start), except if we already came from a
** BACKWARD link.
** We can never use a link if it is FORWARD.
*/

BOOL	ft_check_link(t_room *ngb, t_info *info, t_room *room, int i)
{
	t_link	*link;
	int		mum;
	int		k;
	int		m;

	mum = 0;
	k = 0;
	m = 0;
	while (room->mum && room->link[m]->dest != room->mum)
		m++;
	link = room->link[i];
	if (ngb == room->mum)
		mum = i;
	if (ngb != room->mum && ngb != info->start)
		k = k + GOOD_PATH;
	if (room->opti == 0 && link->status == UNUSED)
		k = k + CLEAN;
	if (room->opti == 1 && link->status == BACKWARD
		&& room->link[m]->status == UNUSED)
		k = k + REVERSE;
	if (room->opti == 1 && room->link[m]->status == FORWARD)
		k = k + OUT;
	return ((k == GOOD_PATH + CLEAN) || (k == GOOD_PATH + REVERSE)
			|| (k == GOOD_PATH + OUT) ? TRUE : FALSE);
}

/*
** We only add a room to the queue if it is not already in. However, if it is in
** the queue but the new weight we could assign it is inferior to the one it had
** we will change it's "mum".
*/

void	ft_add_to_queue(t_room *room, t_room **queue, t_room **ngb, int i)
{
	int new_weight;

	new_weight = 0;
	if ((*ngb)->in_q == NOT_IN_QUEUE)
		ft_new_in(room, queue, ngb, ft_calc_weight(room, i));
	else if ((*ngb)->in_q == IN_QUEUE)
	{
		new_weight = ft_calc_weight(room, i);
		if (new_weight < (*ngb)->weight)
			ft_new_in(room, queue, ngb, new_weight);
	}
}

/*
** ngb stands for "neighbour". The room we are on is the current "head" of queue
** we check all it's ngb and add them or not to the queue if it is possible.
*/

t_room	*ft_weight(t_info *info, t_room *room, t_room *queue)
{
	t_room	*ngb;
	int		i;

	i = 0;
	ngb = NULL;
	if (queue == NULL)
		queue = room;
	if (VISU == 1)
		ft_printf("%s:", room->name);
	while (i < room->nbl)
	{
		ngb = room->link[i]->dest;
		if (ft_check_link(ngb, info, room, i) == TRUE)
			ft_add_to_queue(room, &queue, &ngb, i);
		i++;
	}
	if (VISU == 1)
		ft_printf("\n");
	return (queue);
}
