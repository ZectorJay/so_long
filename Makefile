# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/03 15:52:53 by hmickey           #+#    #+#              #
#    Updated: 2021/12/10 16:49:37 by hmickey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:			all clean fclean re

NAME		=	so_long

INCLUDE		=	./include/

SRCS		=	src/parsing.c\
				main.c\
				src/draw.c\
				src/movement.c\
				./gnl/get_next_line.c\
				./gnl/get_next_line_utils.c\
				./src/draw_map.c\
				./src/move_functions.c\
				./src/move_functions2.c\

OBJS		= ${SRCS:.c=.o}

CC			= gcc -g

RM			= rm -f

CFLAGS		= 

FRAME		= ./mlx/libmlx.a -framework OpenGL -framework AppKit ./libft/libft.a -MMD -pthread

%.o:			%.c $(INCLUDE)
				$(CC) -I${INCLUDE} $(CFLAGS) -c $< -o $@

$(NAME):		${OBJS} ${INCLUDE}
				${MAKE} -C ./libft/
				${CC} ${FRAME} ${OBJS} -o so_long

all:			${NAME}

clean:
				${RM} ${OBJS}

fclean:			clean
				${RM} ${NAME}

-include		${OBJ:.o=.d}

re:				fclean all
