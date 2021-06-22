NAME = philo

FLAGS = -Wall -Wextra -Werror

INC	= -I include

SRCS = error.c eat.c error.c main.c print_msg.c thread.c

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