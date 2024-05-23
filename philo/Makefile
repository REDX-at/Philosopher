NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
OBJS_DIR = objs/

SRCS = dinner.c getters_setters.c init.c main.c parse_args.c print.c thread_mutex.c utils.c synchro_utils.c track_dinner.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $@

%.o: %.c philo.h
	@echo "\033[92m√\033[0m \033[97m" $<
	@$(CC) $(CFLAGS) -c $< -o $@

re : fclean all

clean :
	@$(RM) $(OBJS)

fclean : clean
	@echo "\033[0m \033[97mObject Full Cleaned \033[92m√"
	@$(RM) $(NAME)

BOLD_CYAN=\033[1;36m
RESET_COLOR=\033[0m

.PHONY : clean fclean re all bonus
