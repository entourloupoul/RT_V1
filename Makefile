# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmasson <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/07 18:54:45 by pmasson           #+#    #+#              #
#    Updated: 2019/07/24 13:40:16 by pmasson          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		rtv1

SRCSDIR		=		./srcs

OBJSDIR		=		./objs

SRCS		=		main.c				rtv1_atoi.c			rtv1_free.c			\
					get_next_line.c		rtv1_get_scene.c	rtv1_get_light.c	\
					rtv1_get_obj.c		rtv1_get_coord_obj.c					\
					rtv1_set_cam_vec.c	rtv1_set_cam_vec2.c	rtv1_create_final.c	\
					rtv1_get_color.c	rtv1_check_inter_sphere.c				\
					rtv1_check_inter_plane.c				rtv1_get_shade.c	\
					rtv1_check_inter_cylinder.c				rtv1_solve_2_deg.c

OBJS		=		$(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))

CC			=		gcc -g

CFLAG		=		-Wall -Werror -Wextra

INCL		=		-I includes/ -I libft/includes/ -I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers

FRAMEWORK1	=		-F ~/Library/Frameworks/

FRAMEWORK2	=		-framework SDL2

RM			=		rm -f

LIB			=		libft/libft.a

all			:		mlibft $(NAME)

$(NAME)		:		$(OBJS) $(LIB) includes/rtv1.h
					$(CC) $(CFLAG) $(FRAMEWORK1) $(FRAMEWORK2) $(INCL) $(OBJS) $(LIB) -o $(NAME)

mlibft		:	
					@make -C libft/

$(OBJSDIR)/%.o	:	$(SRCSDIR)/%.c includes/rtv1.h
					@mkdir -p $(OBJSDIR)
					$(CC) -c $(CFLAG) $(FRAMEWORK1) $(INCL) -c $< -o $@

clean		:		
					$(RM) $(OBJS)
					make -C libft/ clean

fclean		:		clean
					$(RM) $(NAME)
					make -C libft/ fclean

re			:		
					@make fclean
					@make all

.PHONY		:		clean fclean re mlibft all
