# Color definitions
RESET      = \033[0m
RED        = \033[31m
GREEN      = \033[32m
YELLOW     = \033[33m
BLUE       = \033[34m
CYAN       = \033[36m
BOLD       = \033[1m
UNDERLINE  = \033[4m

# Makefile for the philosophers project
NAME = philo

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -pthread

#  Remove command
RM = rm -f

# Include directory
INCLUDES = -I./includes/

# Source files
SRCS = main.c init.c utils1.c utils2.c cleanup.c \
		utils_init.c philo_routine.c monitor.c \
		philo_utils.c

#  Object files directory
OBJ_DIR = ./obj

# Object files
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

# Valgrind configuration
VALGRIND_FLAGS = --tool=helgrind --log-file=helgrind.log

# Default test arguments for philosophers (adjust as needed)
TEST_ARGS = 5 800 200 200 3

# Build targets
all: $(NAME)

#  Build the executable
$(NAME): $(OBJ_DIR) $(OBJS)
	@echo "$(CYAN)Building $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)
	@echo "$(CYAN)Build complete!$(RESET)"

#  Create object files directory
$(OBJ_DIR):
	@echo "$(YELLOW)Creating object files directory...$(RESET)"
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Directory created!$(RESET)"

#  Compile source files to object files
$(OBJ_DIR)/%.o: %.c
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(BLUE)Compiled $< to $@$(RESET)"

#  Valgrind target
valgrind: $(NAME)
	@echo "$(MAGENTA)Running Valgrind on $(NAME)...$(RESET)"
	@valgrind $(VALGRIND_FLAGS) ./$(NAME) $(TEST_ARGS)
	@echo "$(MAGENTA)Valgrind run complete! Check helgrind.log for details.$(RESET)"

# Clean up object files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@$(RM) -r $(OBJ_DIR)
	@echo "$(RED)Object files cleaned!$(RESET)"

# Full clean up
fclean: clean
	@echo "$(RED)Cleaning executable...$(RESET)"
	@$(RM) $(NAME)
	@echo "$(RED)Executable cleaned!$(RESET)"

# Rebuild the project
re: fclean all
	@echo "$(GREEN)Rebuild complete!$(RESET)"

# Phony targets
.PHONY: all clean fclean re valgrind