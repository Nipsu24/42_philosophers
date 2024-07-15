# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmeier <mmeier@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 11:47:56 by mmeier            #+#    #+#              #
#    Updated: 2024/06/27 11:33:36 by mmeier           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror
LDFLAGS = -pthread

SRC_DIR = ./
OBJ_DIR = obj

FILES = main.c utils.c error_check.c init.c threads.c control_routine.c free_and_destroy.c

OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ_FILES) $(LDFLAGS)
	@echo "\033[32m philo has been built successfully!\033[0m"

fsanitize: 
	$(CC) -o $(NAME) $(FILES) $(LDFLAGS) -g -fsanitize=address -static-libsan 

fthread: 
	$(CC) -o $(NAME) $(FILES) $(LDFLAGS) -g -fsanitize=thread -static-libsan 
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)philo.h | $(OBJ_DIR) 
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
