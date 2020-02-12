# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dberger <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/24 14:43:37 by dberger           #+#    #+#              #
#    Updated: 2019/12/05 18:38:40 by dberger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NO_COLOR = \033[0m
YELLOW = \033[33m
GREEN = \033[32m
BLUE = \033[36m
PINK = \033[35m

NAME = lem-in
NAME_DISP = display
CC = gcc
CFLAGS = -Wall -Wextra -Werror
HFILE = ./include/lem_in.h
HFILE_DISP = ./include/display.h
LIB_DIR = ./lib
OBJ_DIR = ./obj

LIBC = $(LIB_DIR)/libft
FT_PRINTF = $(LIB_DIR)/ft_printf
MINILIBX = $(LIB_DIR)/minilibx

NAME_PTF = libftprintf.a
NAME_LIBC = libft.a

SRC = src/main.c \
	src/ft_storage.c \
	src/ft_storage2.c \
	src/ft_print_ways.c \
	src/ft_hashtab.c \
	src/ft_bfs.c \
	src/ft_weight.c \
	src/ft_links.c \
	src/ft_karp.c \
	src/ft_steps.c \
	src/ft_clean_free.c \
	src/ft_calc_steps.c \
	src/ft_strjoin_nf.c \
	src/ft_result.c

SRC_DISP = src/src_display/main.c \
		   src/src_display/menu.c \
           src/src_display/disp.c \
           src/src_display/input.c \
           src/src_display/trace_line.c \
           src/src_display/ft_init.c \
           src/src_display/disp_karp.c \
           src/src_display/disp_karp_b.c \
           src/src_display/disp_karp_k.c \
           src/src_display/disp_karp_wf.c \
           src/src_display/disp_choice.c \
           src/src_display/disp_room.c \
           src/src_display/disp_links.c \
           src/src_display/disp_lem.c


OBJ = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRC))
OBJ_DISP = $(patsubst src/src_display/%.c,$(OBJ_DIR)/obj_disp/%.o,$(SRC_DISP))


LIB = $(FT_PRINTF)/$(NAME_PTF) \
	  $(LIBC)/$(NAME_LIBC)

.PHONY: all clean fclean re

all: mkdir $(NAME) $(NAME_DISP)

mkdir:
		mkdir -p $(OBJ_DIR)
		mkdir -p $(OBJ_DIR)/obj_disp

disp: $(NAME_DISP)

$(LIB): FORCE
	$(MAKE) -C $(LIBC)
	$(MAKE) -C $(FT_PRINTF)

$(NAME): $(LIB) $(OBJ) Makefile $(HFILE)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)
	echo "$(YELLOW)	--- $(GREEN)lem-in$(YELLOW) Compiled ! ---	$(NO_COLOR)"

$(NAME_DISP): $(LIB) $(OBJ_DISP) Makefile $(HFILE_DISP)
	$(CC) -o $(NAME_DISP) $(OBJ_DISP) $(LIB) -L lib/sdl -l SDL2-2.0.0 -l SDL2_image -l SDL2_mixer
	echo "$(YELLOW)	--- $(GREEN)lem-in display$(YELLOW) Compiled ! ---	$(NO_COLOR)"


$(OBJ_DIR)/%.o:src/%.c $(HFILE)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)/obj_disp/%.o:src/src_display/%.c $(HFILE_DISP)
	$(CC) -o $@ -c $<

clean:
	$(MAKE) $@ -C $(LIBC)
	$(MAKE) $@ -C $(FT_PRINTF)
	rm -rf $(OBJ_DIR)/$(OBJ)
	rm -rf $(OBJ_DIR)/obj_disp/$(OBJ_DISP)
	rm -rf $(OBJ_DIR)
	echo "$(BLUE)	--- Binary deleted ! ---	$(NO_COLOR)"

fclean: clean
	$(MAKE) $@ -C $(LIBC)
	$(MAKE) $@ -C $(FT_PRINTF)
	rm -rf $(NAME)
	rm -rf $(NAME_DISP)
	echo "$(PINK)	--- Programm deleted ! ---	$(NO_COLOR)"

re: fclean all disp

.SILENT:

FORCE:
