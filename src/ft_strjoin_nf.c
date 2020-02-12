/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_nf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:58:05 by dberger           #+#    #+#             */
/*   Updated: 2019/12/07 18:15:54 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	ft_free_old(const char *s1, const char *s2, int *a)
{
	if (*a == 1 || *a == 3)
		free((char*)s1);
	if (*a == 2 || *a == 3)
		free((char*)s2);
}

char	*ft_strcat_from_n(char *dest, const char *src, int stop)
{
	int i;
	int j;

	j = 0;
	i = stop;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\n';
	dest[i + j + 1] = '\0';
	return (dest);
}

/*
** This function copies s2 in s1, and create a new string if s1 is not big
** enough while freeing the old s1. It also adds a "\n" to each line we add.
*/

char	*ft_strjoin_nf(char *s1, char *s2, int a, t_info *info)
{
	char	*str;
	int		save;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = NULL;
	save = info->stop_str + ft_strlen(s2) + 1;
	if (save < info->len_str)
		ft_strcat_from_n(s1, s2, info->stop_str);
	else if (save >= info->len_str)
	{
		info->len_str += BUF;
		if (!(str = ft_memalloc(info->len_str)))
			return (NULL);
		ft_strcpy(str, s1);
		ft_strcat_from_n(str, s2, info->stop_str);
		info->old_stop = info->stop_str;
		info->stop_str += ft_strlen(s2) + 1;
		ft_free_old(s1, s2, &a);
		return (str);
	}
	info->old_stop = info->stop_str;
	info->stop_str += ft_strlen(s2) + 1;
	return (s1);
}
