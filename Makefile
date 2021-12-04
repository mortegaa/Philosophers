# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mortega- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/31 09:21:58 by mortega-          #+#    #+#              #
#    Updated: 2021/12/04 17:29:12 by mortega-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	srcs/philosophers.c\
			srcs/utils.c

SRCS_BONUS	=	bonus/philosophers_bonus.c \
				bonus/utils_bonus.c

OBJS	=	${SRCS:.c=.o}

OBJS_BONUS	=	${SRCS_BONUS:.c=.o}

NAME	=	philo

NAME_BONUS	=	philobonus

CFLAGS	=	-Wall -Werror -Wextra -pthread

.c.o:
			@gcc ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS} ${Lib} ${Gnl} ${Mlx}
			@gcc -o ${NAME} ${OBJS} ${Lib} ${Gnl} ${Mlx}

bonus:		${OBJS_BONUS} ${Lib} ${Gnl} ${Mlx}
			@gcc -o ${NAME_BONUS} ${OBJS_BONUS} ${Lib} ${Gnl} ${Mlx}

all:		${NAME}

clean:
			@rm -f ${OBJS}
			@rm -f ${OBJS_BONUS}

fclean:		clean
			rm -f ${NAME}
			rm -f ${NAME_BONUS}

re:			fclean all

.PHONY:		all clean fclean re
