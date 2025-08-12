GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

NAME = BitcoinExchange

CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98

SRC =	main.cpp \
		BitcoinExchange.cpp 

OBJ = $(SRC:.cpp=.o)

all: $(NAME)
	@echo "$(GREEN)Sucessfully compiled $(NAME) $(RESET)"

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	
%.o: %.cpp
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@echo "$(RED)Cleaned Objects$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)Cleaned $(NAME)$(RESET)"

re: fclean all

.PHONY: all clean fclean re