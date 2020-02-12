/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_storage2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 15:19:58 by dberger           #+#    #+#             */
/*   Updated: 2019/12/10 11:58:52 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int			ft_check2(t_info *info, int i, int *j)
{
	if (!ft_max_min(info, 2, i))
		return (3);
	while (info->line[i] != ' ' && info->line[i])
	{
		if (info->line[i] < '0' || info->line[i] > '9')
			return (3);
		i++;
	}
	i = -1;
	while (info->line[++i])
		if (info->line[i] == ' ')
			*j += 1;
	return (1);
}

BOOL		ft_storage2(t_info *info, char **str)
{
	int		type;
	int		ret;

	type = -1;
	ret = get_next_line(0, &info->line);
	if (ret == -1 || ret == 0 || info->line == NULL)
		return (FALSE);
	if (info->line[0] == 0)
	{
		free(info->line);
		info->line = NULL;
		return (FALSE);
	}
	if (!(*str = ft_strjoin_nf(*str, info->line, 1, info)))
		return (FALSE);
	while (info->line[++type])
		if (!ft_isdigit(info->line[type]))
			return (FALSE);
	info->ant_nb = ft_atol(info->line);
	if (info->ant_nb <= 0 || info->ant_nb > 2147483647)
		return (FALSE);
	free(info->line);
	return (TRUE);
}

BOOL		ft_storage3(t_info *info, int *start, int *end, int *type)
{
	if (ft_strcmp(info->line, "##start") == 0)
	{
		*type = ROOM_START;
		if (*start == 0)
			*start = 1;
		else
			return (FALSE);
	}
	else if (ft_strcmp(info->line, "##end") == 0)
	{
		*type = ROOM_END;
		if (*end == 0)
			*end = 1;
		else
			return (FALSE);
	}
	else if (info->line[0] != '#')
		*type = ROOM_NORMAL;
	return (TRUE);
}

BOOL		ft_storage4(t_info *info, int start, int end)
{
	if (start == 0 || end == 0)
		return (FALSE);
	if (info->xmax == -1 || info->ymax == -1)
		return (FALSE);
	return (TRUE);
}
