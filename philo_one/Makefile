# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/14 14:18:05 by nelisabe          #+#    #+#              #
#    Updated: 2021/01/14 17:18:58 by nelisabe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	philo_one

COMP =	clang

FLAGS =	#-Wall -Wextra -Werror

HEADER = philo_one.h

SRC =	errors.c \
		ft_itoa.c \
		ft_atoi.c

MAIN =	main.c

OBJ_D =	./temp/

OBJ	=	$(addprefix $(OBJ_D), $(SRC:.c=.o))

all: temp $(NAME)

temp:
	mkdir -p $(OBJ_D)

$(NAME): $(OBJ) $(HEADER)
	$(COMP) $(FLAGS) $(OBJ) $(MAIN) -o $@
	
$(addprefix $(OBJ_D), %.o): %.c $(HEADER)
	$(COMP) $(FLAGS) -c $< -o $@

clean:
	rm -rf ./temp

fclean: clean
	rm -rf $(NAME)

re: fclean all
