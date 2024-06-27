# Define colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
DEFAULT = \033[0m

#SOURCES BONUS
SRCS_BONUS_PATH = srcs_bonus
SRCS_BONUS = action_bonus.c init_bonus.c main_bonus.c \
		utils_bonus.c actions_utils_bonus.c cleanup_bonus.c \
		check_dead.c

OBJ_BONUS_DIR = obj_bonus
OBJS_BONUS = $(SRCS_BONUS:%.c=$(OBJ_BONUS_DIR)/%.o)

#COMPILE
#CC = gcc -fsanitize=thread -g
CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME_BONUS = philo_bonus

all: $(OBJ_BONUS_DIR) $(NAME_BONUS)

#BONUS
$(NAME_BONUS): $(OBJS_BONUS) includes/philo_bonus.h
	@$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)
	@echo "$(YELLOW)$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)$(DEFAULT)"
	@echo "$(GREEN)Executable '$(NAME_BONUS)' has been created successfully!$(DEFAULT)"

$(OBJ_BONUS_DIR)/%.o: $(SRCS_BONUS_PATH)/%.c
	@echo "$(YELLOW)$(CC) $(CFLAGS) -c $< -o $@$(DEFAULT)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_BONUS_DIR):
	@echo "$(YELLOW)Create $(OBJ_BONUS_DIR) directory $(DEFAULT)"
	@mkdir -p $(OBJ_BONUS_DIR)

clean:
	@echo "$(YELLOW)rm -rf $(OBJ_BONUS_DIR)$(DEFAULT)"
	@rm -rf $(OBJ_BONUS_DIR)
	@echo "$(GREEN)Cleaned up $(OBJ_BONUS_DIR) !$(DEFAULT)"

fclean: clean
	@echo "$(YELLOW)rm -f $(NAME_BONUS)$(NC)"
	@rm -f $(NAME_BONUS)
	@echo "$(GREEN)Removed executable '$(NAME_BONUS)'!$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re

