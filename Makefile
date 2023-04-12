NAME	:=	philo

HEADER 	:= philo.h

SRC	:=	./srcs/main.c \
		./srcs/arguments.c \
		./srcs/arguments_utils.c \
		./srcs/error_free.c \
		./srcs/philo_operations.c \
		./srcs/thread_functions.c \

OBJ := $(SRC:.c=.o)

CC	:=	gcc

CFLAGS	:=	-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME) $(OBJ)

re: fclean all

.PHONY: all clean fclean re