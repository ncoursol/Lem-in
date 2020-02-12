/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 14:45:56 by dberger           #+#    #+#             */
/*   Updated: 2020/02/07 13:08:13 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

/*
** Info has all the general informations about our anthill: number of ants,
** rooms, links, the pointer to the rooms start and end, line and str will help
** us read the map and stock it for the final print.
*/

t_info	init_info(int argc, char **argv)
{
	t_info	info;

	info.line = NULL;
	info.stop_str = 0;
	info.len_str = BUF;
	info.start = NULL;
	info.end = NULL;
	info.ant_nb = 0;
	info.room_nb = 0;
	info.size_tab = 0;
	info.link_nb = 0;
	info.lines_rqd = 0;
	info.max_paths = 0;
	info.coord = NULL;
	info.xmax = -1;
	info.ymax = -1;
	info.xmin = 2147483647;
	info.ymin = 2147483647;
	info.option = 0;
	if (argc == 2)
		if (!ft_strcmp(argv[1], "-c"))
			info.option = 1;
	return (info);
}

/*
** For each rooms, we need to know to what other rooms they are linked to,
** "nbl" is the number of links, the rest will help us during the algorithm.
*/

t_room	*init_room(void)
{
	t_room *room;

	if (!(room = ft_memalloc(sizeof(t_room*))))
		return (NULL);
	room->link = NULL;
	room->mum = NULL;
	room->name = NULL;
	room->next = NULL;
	room->nbl = 0;
	room->in_q = 0;
	room->weight = 0;
	room->opti = 0;
	room->ant_index = 0;
	return (room);
}

/*
** This function frees the necessary data before printing the message error.
*/

BOOL	ft_error(t_info info, char *str, t_ways best, int mode)
{
	free(str);
	if (mode == FAIL_HASH && info.link_nb == 0)
		ft_clean_list(&info, info.first);
	if (mode == FAIL_HASH && info.link_nb != 0 && info.max_paths != IMPOSSIBLE)
		free(info.line);
	if (mode == FAIL_BFS)
		ft_clean_steps(&best, 1);
	ft_clean_free(&info);
	ft_printf("ERROR\n");
	return (FALSE);
}

/*
** To use the visualisator, we need to change the variable "VISU" in lem-in.h
** from 0 to 1. Before that we check if there is both start and end have links,
** otherwise we don't even need to move forward since there won't be any path
** possible. In "max_path" we reduce the number of iteration we will need to do
** in our BFS, since we can't have more ways than start and end have links.
*/

BOOL	ft_visu(t_info *info, char *str, t_ways best, int mode)
{
	if ((info->start->link[0] == NULL || info->end->link[0] == NULL)
		&& (info->max_paths = IMPOSSIBLE) == IMPOSSIBLE)
		return (FALSE);
	info->max_paths = (info->start->nbl <= info->end->nbl ?
						info->start->nbl : info->end->nbl);
	if (VISU == 1 && mode == 1 && best.steps == NULL)
	{
		info->link_nb = info->link_nb / 2;
		ft_printf("#%d %d %d ", info->room_nb, info->xmax, info->ymax);
		ft_printf("%d %d %d\n%s\n", info->xmin, info->ymin, info->link_nb, str);
	}
	if (VISU == 1 && mode == 2)
	{
		ft_printf("#F\n");
		ft_print_ways(&best);
		ft_printf("#0\n\n");
	}
	return (TRUE);
}

/*
** In our Lem-in we first store the map and check if it is correct
** (hastab and links), then we find the optimal number of possible ways
** with ft_bfs, and then we "send" and print the ants moving in the rooms
** from start to end, finally we free everything we have allocated in memory.
*/

int		main(int argc, char **argv)
{
	t_info	info;
	t_room	*room;
	t_ways	best;
	char	*str;

	str = ft_memalloc(BUF);
	info = init_info(argc, argv);
	best.steps = NULL;
	if (!(room = init_room()) || !str)
		return (FALSE);
	info.first = room;
	if (ft_storage(&info, room, &str) == FALSE && ((info.room_nb = BAD) == BAD))
		return (ft_error(info, str, best, FAIL_STOR));
	if (ft_hashtab(&info, room, 0) == FALSE || ft_links(&info, &str) == FALSE
		|| ft_visu(&info, str, best, 1) == FALSE)
		return (ft_error(info, str, best, FAIL_HASH));
	best = ft_bfs(&info, room, best);
	if (best.steps == NULL || best.nb_ways == NONE)
		return (ft_error(info, str, best, FAIL_BFS));
	ft_visu(&info, str, best, 2);
	ft_result(str, info, &best, 0);
	free(str);
	ft_clean_steps(&best, 1);
	ft_clean_free(&info);
	return (TRUE);
}

/*
** __attribute__((destructor))
**	void	end()
** {
**	while (1);
** }
*/
