NAME = philo_bonus
bonus = main_bonus.c parse_bonus.c init_process_bonus.c \
		init_table_bonus.c

OBJS = $(bonus:.c=.o)
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	@cc $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "\033[92m√\033[0m \033[97m" $(NAME)

%.o: %.c philo_bonus.h
	@cc $(CFLAGS) -c $< -o $@
	@echo "\033[92m√\033[0m \033[97m" $<

clean:
	rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@echo "\033[91m×\033[0m \033[97m" $(NAME)

re: fclean all

.PHONY: clean