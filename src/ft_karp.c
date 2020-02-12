/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_karp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:00:23 by dberger           #+#    #+#             */
/*   Updated: 2019/12/06 19:26:31 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

t_ways	*ft_copy_comp(int j, t_ways *best, t_ways *comp)
{
	int k;

	k = 0;
	best->nb_ways = comp->nb_ways;
	best->tot_max = comp->tot_max;
	best->tot_pl = comp->tot_pl;
	best->min = comp->min;
	while (comp->steps[j][k])
	{
		if (k < 5)
			best->path_info[j][k] = comp->path_info[j][k];
		comp->steps[j][k]->opti = 1;
		best->steps[j][k] = comp->steps[j][k];
		k++;
	}
	return (best);
}

/*
** We have found a more optimal "set of paths", so we erase our old "best"
** option, create a new one that will have the values of our 'compare' option.
*/

BOOL	ft_new_best(t_ways *best, t_ways *comp)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (comp->steps[j] && j <= comp->nb_ways)
	{
		k = comp->path_info[j][LENGTH];
		if (!(best->steps[j] = ft_memalloc(sizeof(t_room) * k)))
			return (FALSE);
		if (!(best->path_info[j] = ft_memalloc(sizeof(int) * 5)))
			return (FALSE);
		best = ft_copy_comp(j, best, comp);
		j++;
	}
	return (TRUE);
}

/*
** It is simple: we go from end to start through the mum of each rooms.
** if the link between one room and it's mum is unused, we change it's
** status to "used" : so from the room to it's mum it is now a "backward" link
** and from the mum to this room it is a "forward" link.
*/

void	ft_update_status(t_room *room)
{
	t_link	*link;
	int		i;

	i = 0;
	link = NULL;
	while (room->link[i] && room->link[i]->dest != room->mum)
		i++;
	link = room->link[i];
	if (VISU == 1)
		ft_printf("%s-%s:", room->name, room->link[i]->dest->name);
	if (link->status == UNUSED && link->rev->status == UNUSED)
	{
		if (VISU == 1)
			ft_printf("1\n");
		link->status = BACKWARD;
		link->rev->status = FORWARD;
	}
	else if (link->status == FORWARD && link->rev->status == BACKWARD)
	{
		if (VISU == 1)
			ft_printf("0\n");
		link->status = CANCELED;
		link->rev->status = CANCELED;
	}
}

/*
** Here we update the status and then fill the steps in best or comp.
*/

BOOL	ft_fill_ways(t_info *info, t_room *room, t_ways *best, t_ways *comp)
{
	room = info->end;
	if (VISU == 1)
		ft_printf("#K\n");
	while (room != info->start)
	{
		ft_update_status(room);
		room = room->mum;
	}
	if (best->nb_ways == NEVER_FILLED)
	{
		if (!(best = ft_steps(info, room, best)))
			return (STOP);
	}
	else
	{
		if (!(comp = ft_steps(info, room, comp)))
		{
			ft_clean_steps(comp, FINAL_FREE);
			return (STOP);
		}
	}
	return (TRUE);
}

/*
** In KARP we first update the status of "flows", of our links. Then we cross
** all the links from start that are going forward and stock the corresponding
** rooms in a structure ("best" if it is the first time, "comp" to compare it to
** "best"). If "best" is still better in terms of total steps than "comp", we
** stop our search and erase comp. On the contrary, if "comp" allow us to send
** our ants from start to end in less steps, then "comp" becomes the new "best",
** and we continue our BFS for a possible optimisation.
*/

BOOL	ft_karp(t_info *info, t_room *room, t_ways *best, t_ways *comp)
{
	if (ft_fill_ways(info, room, best, comp) == STOP)
		return (STOP);
	if (comp->nb_ways != NEVER_FILLED
		&& comp->tot_max < best->tot_max && comp->tot_max != -1)
	{
		ft_clean_steps(best, FREE_FOR_REPLACE);
		if (ft_new_best(best, comp) == FALSE)
		{
			ft_clean_steps(comp, FINAL_FREE);
			return (STOP);
		}
		ft_clean_steps(comp, MINI_FREE);
		return (KEEP_SEARCHING);
	}
	else if (comp->nb_ways != NEVER_FILLED
		&& (comp->tot_max > best->tot_max || comp->tot_max == -1))
	{
		ft_clean_steps(comp, FINAL_FREE);
		return (STOP);
	}
	return (KEEP_SEARCHING);
}
