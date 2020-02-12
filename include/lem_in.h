/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:59:41 by dberger           #+#    #+#             */
/*   Updated: 2020/01/31 16:26:19 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"
# include <unistd.h>

# define VISU 1
# define SIZE_HASH 10
# define IMPOSSIBLE -2
# define GOOD_PATH 1
# define CLEAN 256
# define REVERSE -7
# define OUT 98
# define BOOL int
# define BUF 200
# define TRUE 1
# define FALSE 0
# define BAD -1
# define FAIL_STOR 0
# define FAIL_HASH 1
# define FAIL_BFS 2
# define FREE_FOR_REPLACE 0
# define FINAL_FREE 1
# define MINI_FREE 2
# define COMPARE 0
# define ROOM_START 1
# define ROOM_END 2
# define ROOM_NORMAL 0
# define UNUSED 0
# define BACKWARD -1
# define FORWARD 1
# define CANCELED 0
# define INIT 0
# define FINISH 1
# define LENGTH 0
# define ANTS 1
# define STEPS 2
# define ANTS_SENT 3
# define ANT_ARRIVED 4
# define NONE -1
# define NEVER_FILLED -1
# define KEEP_SEARCHING 1
# define STOP 0
# define NOT_IN_QUEUE 0
# define IN_QUEUE 1

typedef struct		s_info
{
	char			*line;
	struct s_room	**tab;
	struct s_room	*first;
	struct s_room	*start;
	struct s_room	*end;
	int				**coord;
	int				stop_str;
	int				old_stop;
	int				len_str;
	int				lines_rqd;
	int				ant_nb;
	int				max_paths;
	int				room_nb;
	int				size_tab;
	int				link_nb;
	int				xmax;
	int				ymax;
	int				xmin;
	int				ymin;
	int				option;
}					t_info;

typedef struct		s_room
{
	char			*name;
	struct s_link	**link;
	struct s_room	*next;
	struct s_room	*mum;
	int				weight;
	int				ant_index;
	int				nbl;
	size_t			opti;
	size_t			in_q;
}					t_room;

typedef struct		s_link
{
	struct s_room	*dest;
	struct s_link	*rev;
	int8_t			status;
}					t_link;

typedef struct		s_ways
{
	struct s_room	***steps;
	int				**path_info;
	int				tot_max;
	int				min;
	int				nb_ways;
	int				tot_pl;
}					t_ways;

char				*ft_strjoin_nf(char *s1, char *s2, int a, t_info *info);
BOOL				ft_particular(t_ways *best, t_info info);
void				ft_print_ways(t_ways *ways);
t_room				*init_room(void);
BOOL				ft_storage(t_info *t, t_room *r, char **str);
int					ft_coll(t_info *info, char *name, int i, int s);
int					ft_hashage(char *name, int hash_size);
BOOL				ft_hashtab(t_info *t, t_room *r, int i);
BOOL				ft_links(t_info *t, char **str);
t_room				*ft_weight(t_info *t, t_room *r, t_room *queue);
void				ft_init_ways(t_ways **ways);
void				ft_clean_list(t_info *info, t_room *room);
void				ft_clean_steps(t_ways *ways, int mode);
void				ft_clean_free(t_info *info);
t_ways				*ft_calc_steps(t_ways *ways, t_info *info, int j);
t_ways				*ft_steps(t_info *t, t_room *r, t_ways *comp);
t_ways				ft_bfs(t_info *t, t_room *r, t_ways best);
BOOL				ft_karp(t_info *t, t_room *r, t_ways *best, t_ways *comp);
void				ft_lines_rqd(t_info info, int total);
void				ft_result(char *str, t_info info, t_ways *best, int i);
int					ft_check2(t_info *info, int i, int *j);
BOOL				ft_storage2(t_info *info, char **str);
BOOL				ft_storage3(t_info *info, int *start, int *end, int *type);
BOOL				ft_storage4(t_info *info, int start, int end);
int					ft_max_min(t_info *info, int mode, int i);

#endif
