# Define colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
DEFAULT = \033[0m

#SOURCES

#MANDATORY
SRCS_PATH = srcs
SRCS = action.c init.c main.c utils.c actions_utils.c

OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)


#COMPILE
#CC = gcc -fsanitize=thread -g
CC = cc -g
CFLAGS = -Wall -Wextra -Werror

NAME = philo

all: $(OBJ_DIR) $(NAME)

#MANDATORY
$(NAME): $(OBJS) includes/philo.h
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(YELLOW)$(CC) $(CFLAGS) $(OBJS) -o $(NAME)$(DEFAULT)"
	@echo "$(GREEN)Executable '$(NAME)' has been created successfully!$(DEFAULT)"

$(OBJ_DIR)/%.o: $(SRCS_PATH)/%.c
	@echo "$(YELLOW)$(CC) $(CFLAGS) -c $< -o $@$(DEFAULT)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@echo "$(YELLOW)Create $(OBJ_DIR) directory $(DEFAULT)"
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(YELLOW)rm -rf $(OBJ_DIR)$(DEFAULT)"
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)Cleaned up $(OBJ_DIR) !$(DEFAULT)"

fclean: clean
	@echo "$(YELLOW)rm -f $(NAME)$(NC)"
	@rm -f $(NAME)
	@echo "$(GREEN)Removed executable '$(NAME)'!$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re

