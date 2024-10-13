NAME = philo

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3

SRCS = algoritm.c\
helpers.c\
init_struct.c\
philo.c\
creat_join.c\
another_helpers.c\
val_init.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS) philo.h Makefile
	cc $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:all clean fclean re
