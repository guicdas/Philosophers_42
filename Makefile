# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/20 17:26:30 by gcatarin          #+#    #+#              #
#    Updated: 2023/11/05 17:28:04 by gcatarin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -I./ #fsanitize=address
RM				= rm -fr

NAME			= philo
HEADER			= ../philo.h

SOURCES			= srcs/philo.c srcs/ft_utils.c srcs/ft_thread.c \
				 srcs/ft_routines.c srcs/ft_master.c srcs/ft_init.c srcs/ft_time.c

SOURCES_O		= $(SOURCES:srcs/%.c=objs/%.o)

all:			$(NAME)

$(NAME):		$(SOURCES_O)
	${CC} $(CFLAGS) -o philo -pthread $(SOURCES_O)

objs/%.o: srcs/%.c
	${CC} ${CFLAGS} -c $^ -o $@

clean:
	$(RM) $(SOURCES_O)

fclean:			clean
	$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re