# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/20 19:39:21 by nabentay          #+#    #+#              #
#    Updated: 2022/07/30 22:35:07 by nabentay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc
INCLUDE = ./include/
CFLAGS = -Werror -Wextra -Wall
RM = rm -rf

FILES = pipex\
		pipex_utils\
		pipex_utils2\
		error\

FILES_UTILS = get_next_line\

SRCS_DIR = ./mandatory/
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./objs/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

all: $(OBJS_DIR) $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
		$(CC) -o $@ -c $< $(CFLAGS) -I $(INCLUDE)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -o $@ $^

$(OBJS_DIR):
		@mkdir $@

clean:
		$(RM) $(OBJS_DIR) $(OBJS_B_DIR)

fclean: clean
		rm -f $(NAME) $(BONUS_NAME)

re: clean all

.PHONY: bonus all clean fclean re
