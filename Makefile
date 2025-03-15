# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsiah <rsiah@42singapore.sg>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/13 17:13:06 by rsiah             #+#    #+#              #
#    Updated: 2025/03/06 16:10:26 by rsiah            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = philo.c

OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -MMD
EXTRA_FLAGS = -lpthread

all: $(NAME)

%.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@

${NAME}: ${OBJS}
	@$(CC) $(CFLAGS) -o $@ $^ $(EXTRA_FLAGS)
	@printf "PHILO: \e[38;5;81;1mCompiled %s\n\e[0m" $(NAME)

clean:
	@rm -f $(OBJS) $(DEPS)
	@printf "PHILO: \e[38;5;82;1mclean\n\e[0m"

fclean: clean
	@rm -f $(NAME)
	@printf "PHILO: \e[38;5;81;1mfclean\n\e[0m"

neat: all clean

re: fclean all

debug: CFLAGS += -g
debug: re

-include $(DEPS)

.PHONY: clean fclean re all debug check neat
