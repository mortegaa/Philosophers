# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mortega- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/31 09:21:58 by mortega-          #+#    #+#              #
#    Updated: 2021/12/11 16:46:12 by mortega-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	philosophers.c\
			table.c\
			threads.c\
			utils.c

OBJS	=	${SRCS:.c=.o}

NAME	=	philo

CFLAGS	=	-Wall -Werror -Wextra -pthread

.c.o:
			@gcc ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			@gcc -o ${NAME} ${OBJS}

all:		${NAME}

clean:
			@rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
