# Compiler and Flags
CC       = gcc
CFLAGS   = -Wextra  -Ilibft
LDFLAGS  = -Llibft -lft

# Project Name
NAME     = server

# Sources and Objects
SRC_DIR  = src
FCGI_DIR = fcgi
SECURE_DIR = security
SRCS     = main.c $(wildcard $(SRC_DIR)/*.c) $(wildcard $(FCGI_DIR)/*.c) $(wildcard $(SECURE_DIR)/*.c) 
OBJS     = $(SRCS:.c=.o)

# Default Target
all: libft $(NAME)

# Link the binary
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

# Build libft
libft:
	$(MAKE) -C libft

# Clean object files
clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS)

# Clean everything
fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

# Rebuild
re: fclean all

.PHONY: all clean fclean re libft
