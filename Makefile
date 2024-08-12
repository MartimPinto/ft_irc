# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/12 14:40:50 by mcarneir          #+#    #+#              #
#    Updated: 2024/08/12 15:32:10 by mcarneir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserver
SRCS_DIR = srcs
OBJ_DIR = bin
SRCS = $(wildcard $(SRCS_DIR)/*.cpp)
OBJ	= $(patsubst $(SRCS_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
RM = rm -rf
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
INC = includes/

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.cpp
	@$(CXX) $(CXXFLAGS) -I $(INC) -c $< -o $@
	
$(NAME): $(OBJ)
		@ $(CXX) $(OBJ) $(CXXFLAGS) -o $(NAME)

clean:
		@$(RM) $(OBJ)
		
fclean: clean
		@$(RM) $(NAME)

re: fclean all
