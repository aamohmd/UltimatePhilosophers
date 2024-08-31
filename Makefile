# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/11 10:37:39 by aamohame          #+#    #+#              #
#    Updated: 2024/08/31 07:38:25 by aamohame         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		 = philo
CC			 = gcc
CFLAGS		 = -Wall -Werror -Wextra -g -fsanitize=thread
RM			 = rm -f

# Colors
DEF_COLOR = \033[0;39m
GREEN = \033[0;92m
YELLOW = \033[0;93m

SRCS		 = philo.c philo_routine.c monitor.c ft_isdigit.c ft_atoi.c
OBJS		 = $(SRCS:.c=.o)
INCS		 = includes/philo.h

all:
	@$(MAKE) $(NAME)

$(NAME): $(OBJS) $(INCS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✨ PHILOSOPHERS compiled!$(DEF_COLOR)"

%.o: %.c
	@echo "🍩 $(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@echo "$(YELLOW) PHILO Objects Deleted!"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(YELLOW) PHILO Name Deleted!"

re:	fclean all

.PHONY:	all clean fclean re