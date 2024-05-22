NAME = philosophers

SRCS_DIR = srcs/
INCLUDE_DIR = include/

CC = gcc -Wall -Wextra -Werror -g
CFLAGS = -pthread

SRCS = main.c round.c ft_atoi.c utils.c control.c utils2.c

OBJECTS = $(addprefix $(SRCS_DIR), $(SRCS:.c=.o))

define print_color
	@echo "\033[$1m$2\033[0m"
endef

all: $(NAME)

$(NAME): $(OBJECTS)
		@$(CC) $(CFLAGS) $(OBJECTS) -o $@ -I$(INCLUDE_DIR)
		$(call print_color,36,"Executable created: $@")

%.o: %.c
		@$(CC) $(CFLAGS) -c $< -o $@
		@printf "\033[1;34mCompiling:\033[0m %-30s\033[K\r" $<

clean:
		@rm -rf $(OBJECTS)
		$(call print_color,31,"Deleted object files")

fclean: clean
		@rm -rf $(NAME)
		$(call print_color,31,"Deleted executable")

re: fclean all

.PHONY: all clean fclean re
