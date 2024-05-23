NAME = philo_bonus
bonus = main_bonus.c parse_bonus.c init_process_bonus.c \
		init_table_bonus.c
CC = cc
RM = rm -f
OBJS = $(bonus:.c=.o)
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c Philo_bonus.h
	@echo "\033[92m√\033[0m \033[97m" $<
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@echo "\033[91m×\033[0m \033[97m" $(NAME)
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean