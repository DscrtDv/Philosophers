NAME		=	philo

SRCS		=	./src/main.c \
				./src/utils.c \

OBJS		= 	$(SRCS:.c=.o)
				
	# Compiling Variables #
CC			=	gcc
CFLAG		=	-Wall -Wextra -Werror
RM			=	rm -f

	# Colors #
GREEN		=	\e[38;5;118m
YELLOW		=	\e[38;5;226m
RESET		=	\e[0m
_SUCCESS	=	[$(GREEN)SUCCESS$(RESET)]
_INFO		=	[$(YELLOW)INFO$(RESET)]

	# Debugger #
ifeq ($(DEBUG), 1)
	D_FLAG	=	-g
endif

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(D_FLAG) $(CFLAG) $(OBJS) -o $(NAME)
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