/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:29:31 by dberger           #+#    #+#             */
/*   Updated: 2019/12/10 11:53:28 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

/*
** MINI_FREE corresponds to when we want to free comp after we have given its
** values to the new best. But we want to keep the structure to store the next
** combination of paths we will find. "opti" is when a room belongs to one of
** "best" paths.
*/

void	ft_free_steps(t_ways *ways, int mode)
{
	int j;
	int k;

	j = 0;
	k = 0;
	while (ways->steps && j < ways->nb_ways && ways->steps[j] != NULL)
	{
		while (ways->steps[j][k] != NULL)
		{
			if (mode != MINI_FREE)
				ways->steps[j][k]->opti = 0;
			ways->steps[j][k] = NULL;
			k++;
		}
		free(ways->steps[j]);
		ways->steps[j] = NULL;
		k = 0;
		j++;
	}
}

/*
** We can only clean steps after we have allocated space for them: so
** after at least one iteration of bfs and karp. We use this function also
** everytime we find a better combination of paths than the last one and
** we want to erase "best" and create a new one with the values of "comp".
*/

void	ft_clean_steps(t_ways *ways, int mode)
{
	int i;

	i = 0;
	ft_free_steps(ways, mode);
	while (i < ways->nb_ways && ways->path_info && ways->path_info[i])
	{
		free(ways->path_info[i]);
		i++;
	}
	ways->nb_ways = 0;
	ways->tot_max = 0;
	if (mode == FINAL_FREE && ways->steps != NULL)
		free(ways->steps);
	if (mode == FINAL_FREE && ways->path_info != NULL)
		free(ways->path_info);
}

/*
** If we encounter an error in ft_storrage, it means we only have a list
** chained of rooms, and not a hashtab yet. Same thing happens if we find an
** error in the first link we encounter.
*/

void	ft_clean_list(t_info *info, t_room *room)
{
	t_room	*save;
	int		i;

	save = room;
	i = 0;
	while (room != NULL)
	{
		save = (room->next != NULL ? room->next : NULL);
		if (room->link)
		{
			while (room->link[i])
			{
				free(room->link[i]);
				i++;
			}
			i = 0;
			free(room->link);
		}
		free(room->name);
		free(room);
		room = save;
	}
	info->room_nb = 0;
	if (info->line != NULL && info->line[0])
		free(info->line);
}

/*
** For each room we have in our hashtab, we need to free their links
** (if they have any) - but not what is stock in the links since it is
** simply other rooms that we are about to free in this same function.
** Finally we free the rooms names.
*/

int		ft_free_rooms(t_info *info, int i)
{
	t_room	*room;
	int		j;
	int		k;

	room = NULL;
	j = 0;
	k = 0;
	if (info->tab && info->tab[i] != NULL && info->room_nb != 0)
	{
		room = info->tab[i];
		while (j <= info->room_nb && room->link && room->link[j])
		{
			free(room->link[j]);
			j++;
		}
		if (room->name)
			free(room->name);
		if (room->link)
			free(room->link);
		if (room)
			free(room);
		j = 0;
	}
	i++;
	return (i);
}

/*
** What we free depends on where we are in the process. Maybe we have
** encounter an error during program, so there are only a few things we
** have allocated in memory yet.
** "coord" are the coordinates of the rooms (we use it for the visualisator)
*/

void	ft_clean_free(t_info *info)
{
	int	i;

	i = 0;
	if (info->room_nb == -1)
		ft_clean_list(info, info->first);
	while (i < info->room_nb * 10)
		i = ft_free_rooms(info, i);
	i = 0;
	while (i <= info->xmax && info->coord != NULL && info->coord[i])
	{
		free(info->coord[i]);
		i++;
	}
	if (info->coord)
		free(info->coord);
	if (info->tab)
		free(info->tab);
}
