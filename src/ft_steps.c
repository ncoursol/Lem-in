/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_steps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:36:09 by dberger           #+#    #+#             */
/*   Updated: 2019/12/07 17:00:29 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

/*
** Info->end->weight gives us the final lenght of the path we are trying to
** create. And in path_info, we need 5 info: LENGTH (how long is the path)
** ANTS : how many ants will be sent in these paths once we have done our
** repartition in function ft_calc_steps. STEPS will be our final info on how
** many steps are necessary to send those ants from start to end.
** ANTS SENT and ANT_ARRIVED will be used in the display to print the output.
*/

int		ft_create_space(t_ways **ways, t_info *info, int j)
{
	while ((*ways)->steps[j] != NULL && j < info->max_paths)
		j++;
	if (!((*ways)->steps[j] = ft_memalloc(sizeof(t_room) * info->end->weight)))
		return (BAD);
	if (!((*ways)->path_info[j] = ft_memalloc(sizeof(long) * 5)))
		return (BAD);
	(*ways)->path_info[j][LENGTH] = NONE;
	(*ways)->path_info[j][ANTS] = NONE;
	(*ways)->path_info[j][STEPS] = NONE;
	(*ways)->path_info[j][ANTS_SENT] = INIT;
	(*ways)->path_info[j][ANT_ARRIVED] = INIT;
	(*ways)->steps[j + 1] = NULL;
	return (j);
}

/*
** We are looking for the neighbour of our room that is accessible with a
** FORWARD link.
*/

void	ft_find_room(t_room **room, int m)
{
	while ((*room)->link[m]->status != FORWARD)
		m++;
	(*room) = (*room)->link[m]->dest;
	(*room)->opti = 1;
}

/*
** "j" correspond to the number of paths, "k" corresponds to its length.
** in path_info we stock information corresponding to each paths.
** in steps[2][0] : there is the pointer on the first room of the 3rd path.
** so in path_info[2][LENGTH] there will be the final length of the 3rd path.
*/

int		ft_fill_space(t_room **room, t_info *info, t_ways **ways, int i)
{
	int	m;
	int	j;
	int	k;

	m = i;
	j = 0;
	k = 0;
	j = ft_create_space(ways, info, j);
	if (j == BAD)
		return (BAD);
	while (*room != info->end)
	{
		ft_find_room(room, m);
		(*ways)->steps[j][k] = *room;
		k++;
		(*ways)->steps[j][k] = NULL;
		m = 0;
	}
	(*ways)->path_info[j][LENGTH] = k;
	(*ways)->tot_pl = (*ways)->tot_pl + k;
	k = 0;
	*room = info->start;
	return (j);
}

/*
** "tot_pl" stands for total path length. if they are two paths detected
** by this new karp iteration, tot_pl is the addition of both path length.
*/

void	ft_init_ways(t_ways **ways)
{
	(*ways)->tot_max = -2147483648;
	(*ways)->min = 2147483647;
	(*ways)->tot_pl = 0;
}

/*
** Starting from the room "start" we are crossing all the links whom
** status is "FORWARD". If starts has 2 links forward, it means we
** will have to store 2 differents paths in "ways" (it could be "best"
** or "comp"). Finally in "calc_steps" we calculate how many steps
** our necessary to move X ants from start to end with N number of paths
** stock in "ways".
*/

t_ways	*ft_steps(t_info *info, t_room *room, t_ways *ways)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_init_ways(&ways);
	while (i < info->start->nbl && ways->steps)
	{
		if (room->link[i]->status == FORWARD)
			j = ft_fill_space(&room, info, &ways, i);
		if (j == BAD)
			return (NULL);
		if (j == info->max_paths)
			return (ft_calc_steps(ways, info, j));
		i++;
	}
	ways = ft_calc_steps(ways, info, j);
	if (VISU == 1)
	{
		ft_printf("#W\n");
		ft_print_ways(ways);
	}
	return (ways);
}
