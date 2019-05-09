# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmasson <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/07 18:54:45 by pmasson           #+#    #+#              #
#    Updated: 2019/05/09 15:18:50 by pmasson          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		rtv1

SRCSDIR		=		./srcs

OBJSDIR		=		./objs

SRCS		=		main.c				rtv1_atoi.c			rtv1_free.c			\
					get_next_line.c		rtv1_get_scene.c	rtv1_get_light.c	\
					rtv1_get_obj.c		rtv1_get_coord_obj.c

OBJS		=		$(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))

CC			=		gcc -g

CFLAG		=		-Wall -Werror -Wextra

INCL		=		-I includes/ -I libft/includes/

RM			=		rm -f

LIB			=		libft/libft.a

all			:		libft $(NAME)

$(NAME)		:		$(OBJS) $(LIB) includes/rtv1.h
					$(CC) $(CFLAG) $(INCL) $(OBJS) $(LIB) -o $(NAME)

libft		:		
					@make -C libft/

$(OBJSDIR)/%.o	:	$(SRCSDIR)/%.c includes/rtv1.h
					@mkdir -p $(OBJSDIR)
					$(CC) -c $(CFLAG) $(INCL) -c $< -o $@

clean		:		
					$(RM) $(OBJS)
					make -C libft/ clean

fclean		:		clean
					$(RM) $(NAME)
					make -C libft/ fclean

re			:		
					@make fclean
					@make all

.PHONY		:		clean fclean re libft
