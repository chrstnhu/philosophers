SRCS_PATH = srcs

SRCS = $(addprefix $(SRCS_PATH)/, action.c init.c philo.c utils.c actions_utils.c)

OBJS = $(SRCS:.c=.o)

CC = cc -g
CFLAGS = -Wall -Wextra -Werror

NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
