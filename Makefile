NAME = philo

FLAGS = -Wall -Wextra -Werror

INC	= -I include

SRCS = check_arg.c command.c quick.c stack.c main.c quick_sub.c

OBJ = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	gcc $(FLAGS) -o $@ $^

%.o : %.c
	gcc $(FLAGS) $(INC) -c -o $@ $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY:	all clean fclean re