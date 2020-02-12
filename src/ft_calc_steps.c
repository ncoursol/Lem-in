/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_steps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 13:05:16 by dberger           #+#    #+#             */
/*   Updated: 2019/12/07 17:24:34 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

/*
** The number of ants we can send in one path ("a") will depend on the total
** number of ants in the anthill ("ants"), the sum of the length of all paths
** found ("tpl"), the number of paths ("nb_ways"), the length of the path we
** are on ("len").
*/

long	ft_calc_ants(t_info *info, t_ways **ways, int i)
{
	long len;
	long ants;
	long a;
	long tpl;
	long nb_w;

	ants = info->ant_nb;
	tpl = (*ways)->tot_pl;
	len = (*ways)->path_info[i][LENGTH];
	nb_w = (*ways)->nb_ways;
	a = ((ants + tpl - (nb_w * len)) / nb_w);
	(*ways)->path_info[i][ANTS] = a;
	return (a);
}

/*
** We want to know which path is the shorter one so we can send more ants
** in this path. "tot_max" stock the length of the longest path since
** it corresponds to the number of total number of steps we will have when
** sending all our ants.
*/

void	ft_min_max(t_ways **ways, int i)
{
	long steps;

	steps = (*ways)->path_info[i][STEPS];
	if (steps > (*ways)->tot_max)
		(*ways)->tot_max = steps;
	if (steps < (*ways)->min)
		(*ways)->min = steps;
}

/*
** Steps corresponds to number of steps necessary to move in one path,
** X number of ants (calculated in ft_calc_ants).
*/

void	ft_one_path_steps(t_ways **ways, int i, long a)
{
	long len;
	long steps;

	len = (*ways)->path_info[i][LENGTH];
	steps = len + a - 1;
	(*ways)->path_info[i][STEPS] = steps;
}

/*
** We are doing divisions of "int" so the numbers are rounded to
** decimal and might not match the final number of ants.
*/

void	ft_left_over(t_info *info, t_ways **ways, long nb)
{
	long i;
	long a;
	long left;

	i = 0;
	a = 0;
	left = info->ant_nb - nb;
	while (left > 0)
	{
		i = 0;
		while (i < (*ways)->nb_ways
				&& (*ways)->path_info[i][STEPS] != (*ways)->min)
			i++;
		(*ways)->path_info[i][ANTS] += 1;
		a = (*ways)->path_info[i][ANTS];
		ft_one_path_steps(ways, i, a);
		ft_min_max(ways, i);
		left--;
	}
}

/*
** this function will help us, in BFS, to choose between the combinasion
** of paths stock in "BEST" and the new one we have found in "COMP". Maybe
** "COMP" proposes more different paths, but maybe they are way longer than
** those of "BEST" and it would take much longer to move all our ants from
** start to end.
*/

t_ways	*ft_calc_steps(t_ways *ways, t_info *info, int j)
{
	int		i;
	long	nb;
	long	a;

	i = 0;
	nb = 0;
	a = 0;
	ways->nb_ways = j + 1;
	while (i < ways->nb_ways)
	{
		a = ft_calc_ants(info, &ways, i);
		if (a < 0)
		{
			ways->tot_max = -1;
			return (ways);
		}
		nb = nb + a;
		ft_one_path_steps(&ways, i, a);
		ft_min_max(&ways, i);
		i++;
	}
	if (nb < info->ant_nb)
		ft_left_over(info, &ways, nb);
	return (ways);
}
