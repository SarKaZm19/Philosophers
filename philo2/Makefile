# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/20 14:39:47 by fvastena          #+#    #+#              #
#    Updated: 2023/10/18 19:39:25 by fvastena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#          ----------========== {     VARS     } ==========----------

NAME = philo
#BONUS_NAME = so_long_bonus
RMF = rm -f
RMD = rm -rf
CFLAGS = -Wall -Wextra -Werror -pthread -O3 -fsanitize=thread -g
HDDIR = -Iincludes

#          ----------========== {     SRCS     } ==========----------

SRCS =	init_datas.c \
		struct_utils.c \
		forks.c \
		messages.c \
		errors.c \
		free.c \
		ft_atoi.c \
		time.c \
		main.c 

#BONUS_SRCS = 		antag_key_handler_bonus.c \
					datas_bonus.c \
					errors_bonus.c \
					exit_handler_bonus.c \
					ft_free_bonus.c \
					get_img_from_file_bonus.c \
					img_to_win_bonus.c \
					main_bonus.c \
					pathfinding_bonus.c \
					players_bonus.c \
					player_key_handler_bonus.c \
					put_players_to_win_bonus.c \
					read_bonus.c \
					so_long_bonus.c \
					utils_bonus.c \
					verify_map_bonus.c	

#          ----------========== {     OBJS     } ==========----------

SRCS_DIR = srcs/
OBJS_DIR = objs/
#SRCS_BONUS_DIR = bonus/
#OBJS_BONUS_DIR = bonus_objs/

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
#OBJS_BONUS = $(addprefix $(OBJS_BONUS_DIR), $(BONUS_SRCS:.c=.o))

VPATH = $(shell find $(SRCS_DIR) -type d)

#           ----------========== {    RULES    } ==========----------

all:
	@$(MAKE) -s $(NAME)

#bonus:
#	@$(MAKE) -s $(BONUS_NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@printf "\n$(GREEN)$(NAME) created!$(DEFAULT)\n"	

#$(BONUS_NAME):  $(OBJS_BONUS_DIR) $(OBJS_BONUS)
#	@$(CC) $(CFLAGS) $(OBJS_BONUS) -o $@
#	@printf "\n$(GREEN)$(BONUS_NAME) created!$(DEFAULT)\n"

$(OBJS_DIR)%.o:%.c
	@$(CC) $(CFLAGS) $(HDDIR) -c $< -o $@
	@printf "$(GREEN).$(DEFAULT)"

#$(OBJS_BONUS_DIR)%.o:%.c
#	@$(CC) $(CFLAGS) $(HDDIR) -c $< -o $@
#	@printf "$(GREEN).$(DEFAULT)"
	
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

#$(OBJS_BONUS_DIR):
#	@mkdir -p $(OBJS_BONUS_DIR)

clean:
	@$(RMF) $(OBJS)
	@$(RMD) $(OBJS_DIR)
	@printf "$(YELLOW)object files for $(NAME) cleaned!$(DEFAULT)\n"

fclean:
	@$(MAKE) clean
	@$(RMF) $(NAME)
	@printf "$(RED)executables for $(NAME) cleaned!$(DEFAULT)\n"

re: 
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re

#           ----------========== {    COLORS    } ==========----------

RED = \033[1;31m
GREEN = \033[1;32m
GREEN_BG = \033[1;42m
YELLOW = \033[1;33m
DEFAULT = \033[0m