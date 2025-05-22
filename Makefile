# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lengarci <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/22 17:10:42 by lengarci          #+#    #+#              #
#    Updated: 2025/05/22 18:31:52 by lengarci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

CC    		= cc
CFLAGS		= -Wall -Wextra -Werror -g

RESET 		= \033[0m
GREEN 		= \033[0;32m
BLUE   		= \033[0;34m
YELLOW		= \033[1;33m

SRCS   	 	= srcs/main.c srcs/test_args.c srcs/utils.c
OBJS  		= $(SRCS:.c=.o)
NAME  		= philosophers
INCLUDES	= -Iincludes

all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(GREEN)==> Linking $(NAME)$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "$(GREEN)✔ Build complete!$(RESET)\n"

%.o: %.c
	@printf "$(YELLOW)==> Compiling $<$(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@printf "$(BLUE)==> Cleaning objects$(RESET)\n"
	@rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	@printf "$(BLUE)==> Cleaning all$(RESET)\n"
	@rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re
