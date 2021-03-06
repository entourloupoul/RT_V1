# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmasson <pmasson@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/07 18:54:45 by pmasson           #+#    #+#              #
#    Updated: 2019/09/10 14:25:05 by pmasson          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	:= rtv1

CC		?= gcc
CFLAGS	?= -Wall -Werror -Wextra

CPPFLAGS	:= -I includes/ -I libft/includes/
CPPFLAGS	+= -I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers
CPPFLAGS	+= -F ~/Library/Frameworks/

LDFLAGS	:= -framework SDL2

SRCS	:= \
	main.c						\
	rtv1_atoi.c					\
	rtv1_free.c					\
	rtv1_get_scene.c			\
	rtv1_get_light.c			\
	rtv1_get_obj.c				\
	rtv1_get_coord_obj.c		\
	rtv1_set_cam_vec.c			\
	rtv1_create_final.c			\
	rtv1_get_color.c			\
	rtv1_check_inter_sphere.c	\
	rtv1_check_inter_plane.c	\
	rtv1_get_shade.c			\
	rtv1_check_inter_cylinder.c	\
	rtv1_check_inter_cone.c		\
	rtv1_solve_2_deg.c			\
	rtv1_matrix.c				\
	rtv1_calc_obj.c				\
	rtv1_shade_cone.c			\
	rtv1_check_inter.c			\
	rtv1_check_plane_side.c		\
	rtv1_shade_cylinder.c

SRCSDIR	:= ./srcs
OBJSDIR	:= ./objs

OBJS	:= $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))

LIBFT	:= libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) --no-print-directory -C libft/ > /dev/null
	$(CC) $(CPPFLAGS) $(LDFLAGS) $^ $(LIBFT) -o $@

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c includes/rtv1.h | $(OBJSDIR)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJSDIR):
	@mkdir -p $@

debug: CFLAGS := -g3
debug: re

test: CFLAGS := -Wall
test: $(NAME)

clean:
	rm -Rf $(OBJS)
	rm -Rf $(OBJSDIR)
	@$(MAKE) --no-print-directory -C libft/ clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) --no-print-directory -C libft/ fclean

re: fclean $(NAME)

.PHONY: clean fclean re all
