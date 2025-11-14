NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -pthread
RM = rm -f
INCLUDES = -I./includes/
SRCS = main.c init.c utils1.c utils2.c cleanup.c utils_init.c philo_routine.c monitor.c

OBJ_DIR = ./obj

OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
.PHONY: all clean fclean re