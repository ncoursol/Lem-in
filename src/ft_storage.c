/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_storage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 15:13:04 by ncoursol          #+#    #+#             */
/*   Updated: 2020/01/17 11:27:33 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		ft_max_min(t_info *info, int mode, int i)
{
	long		a;

	a = ft_atol(info->line + i);
	if (a > 2147483647)
		return (FALSE);
	if (mode == 1)
	{
		if (info->xmax < a)
			info->xmax = a;
		if (info->xmin > a)
			info->xmin = a;
	}
	if (mode == 2)
	{
		if (info->ymax < a)
			info->ymax = a;
		if (info->ymin > a)
			info->ymin = a;
	}
	return (TRUE);
}

int		ft_check(t_info *info, int type, int i)
{
	int		j;

	j = 0;
	if (info->line[i - 1] != ' ' || info->line[i] < '0' || info->line[i] > '9')
		return (3);
	if (!ft_max_min(info, 1, i))
		return (3);
	if (info->line[0] == 'L')
		return (3);
	while (info->line[i] != ' ' && info->line[i])
	{
		if (info->line[i] < '0' || info->line[i] > '9')
			return (3);
		i++;
	}
	if (info->line[i] != ' ' || info->line[i + 1] < '0'
			|| info->line[i + 1] > '9')
		return (3);
	i++;
	if (ft_check2(info, i, &j) != 1)
		return (3);
	return (j != 2 ? 3 : type);
}

BOOL	ft_store(t_info *info, t_room **room, int type, int i)
{
	t_room	*new;

	if ((*room)->name != NULL)
	{
		new = init_room();
		(*room)->next = new;
		(*room) = new;
	}
	while (info->line[i] != ' ' && info->line[i])
	{
		if (info->line[i] == '-')
			return (FALSE);
		i++;
	}
	if (!((*room)->name = (char*)malloc(sizeof(char) * i + 1)))
		return (FALSE);
	(*room)->name[i] = '\0';
	(*room)->name = ft_strncpy((*room)->name, info->line, i);
	i = ft_check(info, type, i + 1);
	if (i == ROOM_START)
		info->start = (*room);
	if (i == ROOM_END)
		info->end = (*room);
	info->room_nb++;
	return (i == 3 ? FALSE : TRUE);
}

BOOL	ft_space(t_info *info)
{
	if (ft_strchr(info->line, ' ') == NULL && info->line[0] != '#')
	{
		if (info->line[0] == '\0')
		{
			free(info->line);
			info->line = NULL;
		}
		return (FALSE);
	}
	return (TRUE);
}

BOOL	ft_storage(t_info *info, t_room *room, char **str)
{
	int	type;
	int	start;
	int	end;

	start = 0;
	end = 0;
	if (!ft_storage2(info, str))
		return (FALSE);
	type = -1;
	while (get_next_line(0, &info->line))
	{
		if (ft_space(info) == FALSE)
			break ;
		if (info->line[0] != '#')
			if (!ft_store(info, &room, type, 0))
				return (FALSE);
		if (!ft_storage3(info, &start, &end, &type))
			return (FALSE);
		if (!(*str = ft_strjoin_nf(*str, info->line, 1, info)))
			return (FALSE);
		free(info->line);
	}
	if (!ft_storage4(info, start, end) || info->line == NULL)
		return (FALSE);
	return (ft_strcmp("", info->line) == 0 ? FALSE : TRUE);
}
