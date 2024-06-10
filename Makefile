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

#BONUS
SRCS_BONUS_PATH = srcs_bonus
SRCS_BONUS = action_bonus.c init_bonus.c main_bonus.c \
		utils_bonus.c actions_utils_bonus.c

OBJ_BONUS_DIR = obj_bonus
OBJS_BONUS = $(SRCS_BONUS:%.c=$(OBJ_BONUS_DIR)/%.o)

#COMPILE
CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = philo
NAME_BONUS = philo_bonus

all: $(OBJ_DIR) $(NAME)

bonus: $(OBJ_BONUS_DIR) $(NAME_BONUS)

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
	@echo "$(YELLOW)rm -rf $(OBJ_DIR)$(DEFAULT)"
	@echo "$(YELLOW)rm -rf $(OBJ_BONUS_DIR)$(DEFAULT)"
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_BONUS_DIR)
	@echo "$(GREEN)Cleaned up $(OBJ_DIR) !$(DEFAULT)"
	@echo "$(GREEN)Cleaned up $(OBJ_BONUS_DIR) !$(DEFAULT)"

fclean: clean
	@echo "$(YELLOW)rm -f $(NAME)$(NC)"
	@echo "$(YELLOW)rm -f $(NAME_BONUS)$(NC)"
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@echo "$(GREEN)Removed executable '$(NAME)'!$(DEFAULT)"
	@echo "$(GREEN)Removed executable '$(NAME_BONUS)'!$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re

