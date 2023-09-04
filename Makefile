NAME		= philo
CC			= gcc
ifdef DEBUG
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -g
else
CFLAGS		= -Wall -Wextra -Werror -pthread
endif

OBJ_DIR		= obj/
SRC_DIR		= src/

HEADER_DIR	= includes/
HEADER_SRC	= philo.h
HEADERS		= $(addprefix $(HEADER_DIR), $(HEADER_SRC))

SRC_DIR		= src/
SRC_FILE	= main.c error.c ft_atoi.c ft_calloc.c lock.c monitoring.c mutex.c routine.c time.c thread.c

OBJ			=	$(addprefix $(OBJ_DIR), $(SRC_FILE:.c=.o))

OBJF =	.cache_exists

CYAN_B		=	\033[1;96m
CYAN		=	\033[0;96m

all: $(NAME)

$(NAME): $(OBJ) $(OBJF)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(CYAN_B)- Philosopher is compiled -"

$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(HEADERS)| $(OBJF)
			@mkdir -p $(@D)
			@$(CC) $(CFLAGS) -c $< -o $@

$(OBJF):
		@mkdir -p $(OBJ_DIR)
		@touch $(OBJF)

clean:
		@rm -rf $(OBJ_DIR)
		@rm -f $(OBJF)
		@echo "$(CYAN)- Object files are cleaned -"

fclean: clean
		@rm -f $(NAME)
		@echo "$(CYAN)- Executable files are cleaned -"

re:	fclean all

.PHONY: all clean fclean re