# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oozdiyar <oozdiyar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/04 18:27:36 by oozdiyar          #+#    #+#              #
#    Updated: 2022/10/04 18:27:36 by oozdiyar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	:= libftprintf.a
CC		:= gcc
CFLAGS  := -Wall -Wextra -Werror -I. -c
FILES   := ft_putchar.c printf.c
OBJ		:= $(FILES:%.c=%.o)

all: $(NAME)
$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re