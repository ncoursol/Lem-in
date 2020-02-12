/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_result.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 18:17:03 by dberger           #+#    #+#             */
/*   Updated: 2019/12/07 18:13:56 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		ft_last_ant_in_path(t_ways *best, int i, int j)
{
	if (best->path_info[i][ANTS_SENT] == best->path_info[i][ANTS])
		j = best->path_info[i][LENGTH] - 1;
	else
	{
		while (best->steps[i][j]->ant_index != 0)
			j++;
		if (j > 0)
			j--;
	}
	return (j);
}

t_ways	*ft_move_ants(t_info info, t_ways *best, int i, int *j)
{
	int		a;

	a = 0;
	while (*j >= 0)
	{
		if (best->steps[i][*j] == info.end)
			*j -= 1;
		if (best->steps[i][*j + 1] && best->steps[i][*j]->ant_index != 0)
		{
			a = best->steps[i][*j]->ant_index;
			if (best->steps[i][*j + 1] != info.end)
				best->steps[i][*j + 1]->ant_index = a;
			else
				best->path_info[i][ANT_ARRIVED] = a;
			best->steps[i][*j]->ant_index = 0;
		}
		*j -= 1;
	}
	if (*j < 0)
		*j += 1;
	return (best);
}

t_ways	*ft_new_ants(t_ways *best, int *a, int *i, int j)
{
	t_room	*room;

	room = NULL;
	if (best->path_info[*i][ANTS_SENT] < best->path_info[*i][ANTS])
	{
		room = best->steps[*i][j];
		room->ant_index = *a;
		best->path_info[*i][ANTS_SENT] += 1;
		*a += 1;
	}
	*i += 1;
	return (best);
}

/*
** "ant index" is the index of the ant we have sent in a room: it goes from 1
** to the total number of ants "ant_nb". "ANT ARRIVED" is the number of ants
** we have sent in one path since we started.
*/

void	ft_print_result(t_info *info, t_ways **best, int i, int j)
{
	t_room	*room;
	int		arr;

	room = NULL;
	arr = 0;
	while (i < (*best)->nb_ways && info->end->ant_index != info->ant_nb)
	{
		j = 0;
		while (j < (*best)->path_info[i][LENGTH])
		{
			room = (*best)->steps[i][j];
			arr = (*best)->path_info[i][ANT_ARRIVED];
			if (room->ant_index != 0)
				ft_printf("L%d-%s ", room->ant_index, room->name);
			else if (room == info->end && arr != 0)
			{
				ft_printf("L%d-%s ", arr, room->name);
				if (arr == info->ant_nb)
					info->end->ant_index = info->ant_nb;
				(*best)->path_info[i][ANT_ARRIVED] = 0;
			}
			j++;
		}
		i++;
	}
}

/*
** In "str" we have stock the map we got in the first place. We check in
** ft_particular if start is not link to end, if not we move forward for the
** final output: we move our ants from one room to the other, then add a new one
** to the party ;)
** We reused the int "info_max_paths" that is no longer useful, to stock the
** total of iteration we are doing (corresponding to the final number of steps).
*/

void	ft_result(char *str, t_info info, t_ways *best, int i)
{
	int	j;
	int	a;

	j = 0;
	a = 1;
	info.max_paths = 0;
	if (VISU == 0)
		ft_printf("%s\n", str);
	if (ft_particular(best, info) == FALSE)
		return ;
	while (info.end->ant_index != info.ant_nb)
	{
		while (i < best->nb_ways)
		{
			j = ft_last_ant_in_path(best, i, j);
			best = ft_move_ants(info, best, i, &j);
			best = ft_new_ants(best, &a, &i, j);
		}
		i = 0;
		j = 0;
		ft_print_result(&info, &best, i, j);
		ft_printf("\n");
		info.max_paths = info.max_paths + 1;
	}
	ft_lines_rqd(info, info.max_paths);
}
