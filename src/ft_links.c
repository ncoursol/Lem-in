/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_links.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 13:16:59 by dberger           #+#    #+#             */
/*   Updated: 2020/02/07 13:02:22 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

/*
** Link will be a simple structure, with a pointer to a destination room (dest)
** a status: 0 since the links haven't yet been crossed or used by any path.
** nbl stands for number of links (stock in one room), link_nb for number total
** of links (stock in info).
*/

t_link	*ft_create_ways(t_room *from, t_room *dest, t_info *info)
{
	t_link	*link;

	if (!(link = (t_link*)malloc(sizeof(t_link) * info->room_nb)))
		return (NULL);
	link->dest = dest;
	link->status = 0;
	from->nbl += 1;
	info->link_nb = info->link_nb + 1;
	return (link);
}

/*
** If we receive: A-B: in A we will have a link to the room B, in A we will
** have a link to the room A.
*/

BOOL	ft_fill_links(t_room *one, t_room *two, t_info *info, int i)
{
	int	j;

	j = 0;
	if (one->link[i] == NULL)
	{
		if (!(one->link[i] = ft_create_ways(one, two, info)))
			return (FALSE);
	}
	else if (one->link[i]->dest == two)
		return (FALSE);
	while (two->link[j] != NULL
			&& j < info->room_nb && two->link[j]->dest != one)
		j++;
	if (two->link[j] == NULL)
	{
		if (!(two->link[j] = ft_create_ways(two, one, info)))
			return (FALSE);
	}
	else if (two->link[j]->dest == one)
		return (FALSE);
	one->link[i]->rev = two->link[j];
	two->link[j]->rev = one->link[i];
	return (TRUE);
}

/*
** When a room is link to another one, we first need to check if the room
** exist in our hashtab (ft_coll), then if we already linked those two rooms
** together we want to ignore this information to not have twice the same link
*/

BOOL	ft_calc_links(char *room1, char *room2, int s, t_info *info)
{
	int		i;
	int		h1;
	int		h2;
	t_room	*one;
	t_room	*two;

	i = 0;
	h1 = ft_coll(info, room1, ft_hashage(room1, s), s);
	h2 = ft_coll(info, room2, ft_hashage(room2, s), s);
	if (info->tab[h1] == NULL || info->tab[h2] == NULL)
		return (FALSE);
	one = info->tab[h1];
	two = info->tab[h2];
	while (one->link[i] != NULL
			&& i < info->room_nb && one->link[i]->dest != two)
		i++;
	ft_fill_links(one, two, info, i);
	free(info->line);
	return (TRUE);
}

/*
** In ft_cut_room we should receive a string like "room1-room2"
** Instead of allocating memory to check the validity of each name of rooms
** we just change the pointer on the string or it's end:
** Room2 becomes the string after the sign "-", and Room1 becomes the string
** before the sign "-".
*/

BOOL	ft_cut_room(t_info *info)
{
	char	*room1;
	char	*room2;
	int		s;

	s = 0;
	room1 = info->line;
	room2 = info->line;
	while (*room2 != '-' && *room2)
		room2++;
	room2++;
	while (room1[s] != '-' && room1[s])
		s++;
	room1[s] = '\0';
	s = info->room_nb * 10;
	if (!room2 || !room1)
		return (FALSE);
	if (!(ft_calc_links(room1, room2, s, info)))
		return (FALSE);
	return (TRUE);
}

/*
** When we arrive in ft_links, what is stock in info->line should be the first
** link we found while reading the map in ft_storage. Then we need to continue
** the reading of our map with get_next_line. We ignore any comment or command,
** except the one that gives us the number of lines required that we will stock
** in "info->line_rqd".
*/

BOOL	ft_links(t_info *info, char **str)
{
	if (!(*str = ft_strjoin_nf(*str, info->line, 1, info))
		|| !(ft_cut_room(info)))
	{
		(*str)[info->old_stop] = '\0';
		return (FALSE);
	}
	while (get_next_line(0, &info->line))
	{
		if (!(*str = ft_strjoin_nf(*str, info->line, 1, info)))
			return (FALSE);
		if (info->line[0] == '#')
		{
			if (!ft_strncmp(info->line,
				"#Here is the number of lines required: ", 39))
				info->lines_rqd = ft_atoi(info->line + 39);
			free(info->line);
		}
		else if (info->line[0] != '#')
			if (!(ft_cut_room(info)) && ((*str)[info->old_stop] = '\0') == '\0')
			{
				free(info->line);
				return (BAD);
			}
	}
	return (TRUE);
}
