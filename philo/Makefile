NAME		=	philo

SRCS		=	./src/main.c \
				./src/utils.c \
				./src/init.c \
				./src/threads.c \
				./src/monitor.c \
				./src/routines.c \

OBJS		= 	$(SRCS:.c=.o)
				
	# Compiling Variables #
CC			=	cc
CFLAG		=	-Wall -Wextra -Werror
RM			=	rm -f

	# Colors #
GREEN		=	\e[38;5;118m
YELLOW		=	\e[38;5;226m
RESET		=	\e[0m
_SUCCESS	=	[$(GREEN)SUCCESS$(RESET)]
_INFO		=	[$(YELLOW)INFO$(RESET)]

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -fsanitize=thread -g $(CFLAG) $(OBJS) -pthread -o $(NAME)
	@printf "$(_SUCCESS) $(NAME) ready.\n"

%.o: %.c
	$(CC) $(CFLAG) -c -o $@ $^

clean:
	@printf "$(_INFO) Cleaning $(NAME) object files.\n"
	@rm -f $(OBJS)
	@printf "$(_INFO) Object Files deleted.\n"

fclean: clean
	@ $(RM) $(NAME)
	@printf "$(_INFO) $(NAME) removed.\n"

re: fclean all

mandatory:	$(NAME)

m : mandatory

.PHONY: all clean fclean re mandatory m b