/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 11:26:01 by ncoursol          #+#    #+#             */
/*   Updated: 2019/12/03 13:10:28 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "SDL2/SDL.h"
# include "SDL2/SDL_image.h"
# include "SDL2/SDL_mixer.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"

typedef struct		s_disp
{
	int				w;
	int				h;
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Event		event;
	SDL_Surface		*img;
	SDL_Texture		*back;
	SDL_Texture		*back2;
	SDL_Texture		*black;
	SDL_Texture		*fail;
	SDL_Texture		*toss;
	SDL_Texture		*r_start;
	SDL_Texture		*r_end;
	SDL_Texture		*title;
	SDL_Texture		*start;
	SDL_Texture		*leave;
	SDL_Texture		*made;
	SDL_Texture		*arrow;
	SDL_Texture		*start_w;
	SDL_Texture		*leave_w;
	SDL_Texture		*txt;
	SDL_Texture		*txt2;
	SDL_Texture		*morph;
	SDL_Texture		*smith;
	SDL_Texture		*neo;
	SDL_Texture		*trini;
	SDL_Texture		*morph_b;
	SDL_Texture		*neo_b;
	SDL_Texture		*trini_b;
	SDL_Texture		*morph_c;
	SDL_Texture		*neo_c;
	SDL_Texture		*trini_c;
	SDL_Texture		*morph_t;
	SDL_Texture		*neo_t;
	SDL_Texture		*trini_t;
	SDL_Texture		*pils_b;
	SDL_Texture		*pils_r;
	SDL_Texture		*sub;
	Mix_Music		*spy;
	Mix_Music		*wake;
	Mix_Music		*deft;
	Mix_Chunk		*menu1;
	Mix_Chunk		*menu2;
	SDL_Rect		rback;
	SDL_Rect		menu;
	int				delay;
	struct s_room	*first;
}					t_disp;

typedef struct		s_input
{
	char			*line;
	int				ant_nb;
	int				room_nb;
	int				link_nb;
	int				xmax;
	int				ymax;
	int				xmin;
	int				ymin;
	int				running;
	float			coefx;
	float			coefy;
	struct s_room	*first;
}					t_input;

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				type;
	struct s_room	*next;
}					t_room;

void				init_img(t_disp *d);
void				init(t_disp *d);
void				menu(t_disp *d, int *running, int cursor, int i);
void				error(char *src, t_disp *d);
void				disp(t_disp *d, t_input *t);
void				init_img_load(t_disp *d, SDL_Texture **tex, char *filename);
int					get_info(t_input *t, t_room *r, t_disp *d);
void				ft_trace_line(t_input *t, t_disp *d, int c);
void				disp_karp(t_disp *d, t_input *t);
void				disp_b(t_disp *d, t_input *t, t_room *s, int i);
void				disp_k(t_disp *d, t_input *t, t_room *s, int i);
void				disp_w(t_disp *d, t_input *t, t_room *s, int i);
void				disp_links(t_disp *d, t_input *t);
void				disp_room(t_disp *d, t_input *t);
void				disp_choice(t_disp *d, t_input *t, int *c, int i);
int					lem(t_disp *d, t_input *t, int c);
void				event(t_disp *d, int i, int running);
void				disp_w6(t_input *t, t_room **s, t_room **nb_one, int *i);
int					disp_choice6(t_disp *d, t_input *t, int *c, int i);
void				disp_links6(t_disp *d);
void				lem6(t_disp *d, t_input *t, int **ant, int i);
void				init_menu(t_disp *d, int cursor);
void				error3(t_disp *d);
void				error2(t_disp *d);

#endif
