/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:17:46 by dberger           #+#    #+#             */
/*   Updated: 2020/02/07 12:58:58 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

/*
** "hash" takes the value of the ascii number of each letter of the name of the
** room. By applying binary shift on it, we makes sure that it has a random
** value in binary writing, so that "lemin"and "nimel" won't result to the same
** index. The values we choose for xor and addition are just random.
*/

int		ft_hashage(char *name, int hash_size)
{
	size_t	i;
	size_t	hash;

	i = 0;
	hash = 0;
	while (i != ft_strlen(name))
	{
		hash += name[i++];
		hash += hash << 10;
		hash ^= hash >> 6;
	}
	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;
	return (hash % hash_size);
}

/*
** The bigger is the tab, the less probability we have to encounter
** collisions. We define the amplifier of the tab size in "SIZE_HASH"
*/

t_room	*ft_init_tab(t_info *info)
{
	int		i;
	t_room	*room;

	i = 0;
	info->size_tab = info->room_nb * SIZE_HASH;
	if (!(info->tab = malloc(sizeof(info->tab) * info->size_tab)))
		return (NULL);
	room = info->first;
	while (i < info->size_tab)
	{
		info->tab[i] = NULL;
		i++;
	}
	return (room);
}

/*
** In this tab, we add a pointer to the room we are storing once we made
** sure it's index wasn't in collision with any other room already in the
** tab. We initiate "room->link" which is a tab or rooms, that can be as big
** as they are rooms.
*/

BOOL	ft_init_links_tab(t_info *info, t_room *room, int i)
{
	int	j;

	j = 0;
	info->tab[i] = room;
	if (!(room->link = malloc(sizeof(room->link) * info->room_nb)))
		return (FALSE);
	while (j < info->room_nb)
	{
		room->link[j] = NULL;
		j++;
	}
	return (TRUE);
}

/*
** If a name, with the hashing function result in the same index as
** another name, we simply increase the number of index we found until
** the tab of this index is empty ("tab[i]");
*/

int		ft_coll(t_info *info, char *name, int i, int s)
{
	while (i < s && info->tab[i] != NULL
		&& ft_strcmp(name, info->tab[i]->name))
	{
		i++;
		if (i == s)
			i = 0;
	}
	return (i);
}

/*
** We use a "hash" function to transform the names of rooms to an
** index number, to store it in a tab (10 times bigger than the actual
** number of rooms we need ("size_tab"), so we avoid collisions).
*/

BOOL	ft_hashtab(t_info *info, t_room *room, int i)
{
	i = 0;
	if ((room = ft_init_tab(info)) == NULL)
		return (FALSE);
	while (room)
	{
		i = ft_hashage(room->name, info->size_tab);
		if (i < info->size_tab && info->tab[i] == NULL)
		{
			if (ft_init_links_tab(info, room, i) == FALSE)
				return (FALSE);
		}
		else
		{
			i = ft_coll(info, room->name, i, info->size_tab);
			if (info->tab[i] != NULL
			&& !(ft_strcmp(room->name, info->tab[i]->name)))
				return (FALSE);
			else if (info->tab[i] == NULL)
				if (ft_init_links_tab(info, room, i) == FALSE)
					return (FALSE);
		}
		room = room->next;
	}
	return (TRUE);
}
