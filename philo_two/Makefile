# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/14 14:18:05 by nelisabe          #+#    #+#              #
#    Updated: 2021/02/06 13:44:09 by nelisabe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	philo_two

COMP =	clang

FLAGS =	-pthread #-Wall -Wextra -Werror

HEADER = philo_two.h

SRC =	errors.c \
		parser.c \
		init_philos.c \
		util_functions.c \
		philo_two.c \
		philo_utils.c

MAIN =	main.c

OBJ_D =	./temp/

OBJ	=	$(addprefix $(OBJ_D), $(SRC:.c=.o))

all: temp $(NAME)

temp:
	mkdir -p $(OBJ_D)

$(NAME): $(OBJ) $(MAIN) $(HEADER)
	$(COMP) $(FLAGS) $(OBJ) $(MAIN) -o $@
	
$(addprefix $(OBJ_D), %.o): %.c $(HEADER)
	$(COMP) $(FLAGS) -c $< -o $@

clean:
	rm -rf ./temp

fclean: clean
	rm -rf $(NAME)

re: fclean all
