# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mortega- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/31 09:21:58 by mortega-          #+#    #+#              #
#    Updated: 2021/12/11 16:45:52 by mortega-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_BONUS	=	philosophers_bonus.c\
				table_bonus.c\
				processes_bonus.c\
				threads_bonus.c\
				utils_bonus.c

OBJS_BONUS	=	${SRCS_BONUS:.c=.o}

NAME_BONUS	=	philo_bonus

CFLAGS	=	-Wall -Werror -Wextra -pthread

.c.o:
			@gcc ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME_BONUS):	${OBJS_BONUS}
				@gcc -o ${NAME_BONUS} ${OBJS_BONUS}

all:		${NAME_BONUS}

clean:
			@rm -f ${OBJS_BONUS}

fclean:		clean
			rm -f ${NAME_BONUS}

re:			fclean all

.PHONY:		all clean fclean re
