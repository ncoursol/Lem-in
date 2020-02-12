/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:59:22 by dberger           #+#    #+#             */
/*   Updated: 2019/12/06 18:47:19 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

/*
** We reuse the link-chained created in ft_storage to create or queue for BFS
** We will need for each room : a "weight" (defining the distance of the room
** from start), a "mum" (the room that will add another room to the queue - so
** start will never have a mum), finally "in_q" notifies us if a room has been
** added to the queue or not.
*/

t_room	*ft_init_var(t_info *info, t_room *room, t_room *queue)
{
	t_room	*save;

	room = info->start;
	queue = room;
	save = queue;
	while (queue)
	{
		room = queue;
		room->in_q = NOT_IN_QUEUE;
		room->weight = 0;
		room->mum = NULL;
		queue = (queue)->next;
	}
	queue = save;
	queue->next = NULL;
	queue = NULL;
	return (queue);
}

/*
** Initialisation of steps (a tab of paths with pointers on rooms)
** Path_info will stock the length of these paths, the steps necessary
** to cross them depending on the number of ants.
*/

t_ways	ft_init_steps(int size)
{
	t_ways	ways;

	if (!(ways.steps = ft_memalloc(sizeof(t_room*) * size)))
		return (ways);
	ways.nb_ways = NEVER_FILLED;
	if (!(ways.path_info = ft_memalloc(sizeof(long*) * size)))
		return (ways);
	return (ways);
}

/*
** In Finish queue, we check if there is no more optimal mum for end. If we
** still haven't explored rooms left in the queue, thanks to the system of
** substracting weight when we cross a "REVERSED PATH", we might be able to
** reach "end" with an inferior weight in which case we would change it's mum.
*/

void	ft_finish_queue(t_info *info, t_room **room, t_room **queue)
{
	while (*room && info->end->in_q == IN_QUEUE)
	{
		if ((*room) == info->end && (*room)->next)
			*room = (*room)->next;
		if ((*room)->weight <= info->end->weight - 1)
			*queue = ft_weight(info, *room, *queue);
		else
			return ;
		*room = (*room)->next;
	}
}

/*
** In ft_weight we had a "weight" to each room until we reach "end". if "end"
** is not in queue at the end, it means there is no possible connection
** between start and end.
*/

BOOL	ft_shorter_way(t_info *info, t_room **room, t_room **queue, t_ways comp)
{
	*room = info->start;
	(*room)->in_q = IN_QUEUE;
	while (info->end->in_q == NOT_IN_QUEUE && *room)
	{
		*queue = ft_weight(info, *room, *queue);
		*room = (*room)->next;
	}
	if (info->end->in_q == NOT_IN_QUEUE)
	{
		ft_clean_steps(&comp, FINAL_FREE);
		return (STOP);
	}
	ft_finish_queue(info, room, queue);
	return (KEEP_SEARCHING);
}

/*
** BFS will find the shorter path from start to end given the accessible links
** (to start they are all accessible). KARP will update those links and stock
** in a tab (best or comp) all the possible paths after this new iteration of
** BFS. We compare "comp" to "best" to see if it is more efficient and if we
** should keep looking for a new combination of paths.
*/

t_ways	ft_bfs(t_info *info, t_room *room, t_ways best)
{
	t_room	*queue;
	t_ways	comp;
	int		i;

	i = 0;
	queue = NULL;
	best = ft_init_steps(info->max_paths);
	comp = ft_init_steps(info->max_paths);
	if (!best.steps || !comp.steps)
		return (best);
	while (i < info->max_paths && i < info->ant_nb)
	{
		if (VISU == 1)
			ft_printf("#B\n");
		if (queue != NULL)
			queue = ft_init_var(info, room, queue);
		if (ft_shorter_way(info, &room, &queue, comp) == STOP)
			return (best);
		if (ft_karp(info, room, &best, &comp) == STOP)
			return (best);
		i++;
	}
	ft_clean_steps(&comp, FINAL_FREE);
	return (best);
}
