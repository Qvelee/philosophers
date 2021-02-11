# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/14 14:18:05 by nelisabe          #+#    #+#              #
#    Updated: 2021/02/11 12:33:21 by nelisabe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	philo_three

COMP =	clang

FLAGS =	-pthread -Wall -Wextra -Werror

HEADER = philo_three.h

SRC =	errors.c \
		parser.c \
		init_philos.c \
		util_functions.c \
		philo_three.c \
		philo_utils.c \
		supervisor.c

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
