# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/12 14:40:50 by mcarneir          #+#    #+#              #
#    Updated: 2024/08/12 14:56:13 by mcarneir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserver
SRCS_DIR = SRCS_DIR
OBJ_DIR = bin
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJ	= $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
RM = rm -rf
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
INC = includes/

all: $(NAME)

$(OBJ_DIR):
			@mkdir bin/
$(NAME): $(OBJ)
		@ $(CXX) -I $(INC) $(OBJ) -o $(NAME)

clean:
		@$(RM) $(OBJ_DIR)
fclean:
		clean
		@$(RM) $(NAME)

re: fclean all
