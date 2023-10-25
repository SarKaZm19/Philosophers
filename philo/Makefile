# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvastena <fvastena@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/20 14:39:47 by fvastena          #+#    #+#              #
#    Updated: 2023/10/25 18:54:37 by fvastena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#          ----------========== {     VARS     } ==========----------

NAME = philo
RMF = rm -f
RMD = rm -rf
CFLAGS = -Wall -Wextra -Werror -pthread -O3 #-fsanitize=thread -g3
HDDIR = -Iincludes

#          ----------========== {     SRCS     } ==========----------

SRCS =	init_datas.c \
		init_utils.c \
		forks.c \
		messages.c \
		monitor.c \
		errors.c \
		free.c \
		ft_atoi.c \
		time.c \
		main.c 

#          ----------========== {     OBJS     } ==========----------

SRCS_DIR = srcs/
OBJS_DIR = objs/

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

VPATH = $(shell find $(SRCS_DIR) -type d)

#           ----------========== {    RULES    } ==========----------

all:
	@$(MAKE) -s $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@printf "\n$(GREEN)$(NAME) created!$(DEFAULT)\n"	

$(OBJS_DIR)%.o:%.c
	@$(CC) $(CFLAGS) $(HDDIR) -c $< -o $@
	@printf "$(GREEN).$(DEFAULT)"
	
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

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