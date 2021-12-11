# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mortega- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/31 09:21:58 by mortega-          #+#    #+#              #
#    Updated: 2021/12/08 10:39:19 by mortega-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	srcs/philosophers.c\
			srcs/table.c\
			srcs/threads.c\
			srcs/utils.c

SRCS_BONUS	=	bonus/philosophers_bonus.c\
				bonus/table_bonus.c\
				bonus/processes_bonus.c\
				bonus/threads_bonus.c\
				bonus/utils_bonus.c

OBJS	=	${SRCS:.c=.o}

OBJS_BONUS	=	${SRCS_BONUS:.c=.o}

NAME	=	philo

NAME_BONUS	=	philo_bonus

CFLAGS	=	-Wall -Werror -Wextra -pthread

.c.o:
			@gcc ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			@gcc -o ${NAME} ${OBJS}

bonus:		${OBJS_BONUS}
			@gcc -o ${NAME_BONUS} ${OBJS_BONUS}

all:		${NAME}

clean:
			@rm -f ${OBJS}
			@rm -f ${OBJS_BONUS}

fclean:		clean
			rm -f ${NAME}
			rm -f ${NAME_BONUS}

re:			fclean all

.PHONY:		all clean fclean re
