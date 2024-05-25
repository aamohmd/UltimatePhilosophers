# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/11 10:37:39 by aamohame          #+#    #+#              #
#    Updated: 2024/05/23 16:20:05 by aamohame         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		 = philo
BONUS_NAME	 = philo_bonus
CC			 = gcc
CFLAGS		 = -Wall -Werror -Wextra -pthread
RM			 = rm -f

LIB			 = lib/
LIBFT_DIR	 = $(LIB)UltimateLibft/
LIBFT		 = $(LIBFT_DIR)libft.a

# Colors
DEF_COLOR = \033[0;39m
GREEN = \033[0;92m
YELLOW = \033[0;93m

SRCS		 = philo.c philo_routine.c philo_utils.c
BONUS_SRCS	 = 
OBJS		 = $(SRCS:.c=.o)
BONUS_OBJS	 = $(BONUS_SRCS:.c=.o)
INCS		 = includes/philo.h
INCS_BONUS	 = 

all: makelibs
	@$(MAKE) -s $(NAME)

makelibs:
	@$(MAKE) -s -C $(LIBFT_DIR)

bonus: makelibs
	@$(MAKE) -s $(BONUS_NAME)

$(BONUS_NAME) : $(BONUS_OBJS) $(INCS_BONUS)
	@$(CC) $(CFLAGS) -L $(LIBFT_DIR) -lft $(BONUS_OBJS) -o $(BONUS_NAME)
	@echo "$(GREEN)✨ FDF bonus compiled!$(DEF_COLOR)"

$(NAME): $(OBJS) $(INCS)
	@$(CC) $(CFLAGS) -L $(LIBFT_DIR) -lft $(OBJS) -o $(NAME)
	@echo "$(GREEN)✨ FDF compiled!$(DEF_COLOR)"

%.o: %.c
	@echo "🍩 $(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@echo "$(YELLOW) PHILO Objects Deleted!"
	@$(RM) $(BONUS_OBJS)
	@echo "$(YELLOW) PHILO Bonus Objects Deleted!"
	@$(MAKE) clean -s -C $(LIBFT_DIR)
	@echo "$(YELLOW) Libft Objects Deleted!"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(YELLOW) PHILO Name Deleted!"
	@$(RM) $(BONUS_NAME)
	@echo "$(YELLOW) PHILO bonus Name Deleted!"
	@$(MAKE) fclean -s -C $(LIBFT_DIR)
	@echo "$(YELLOW) Libft Name Deleted!"

re:	fclean all

.PHONY:	all clean fclean re