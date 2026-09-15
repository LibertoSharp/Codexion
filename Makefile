NAME = codexion
CC = cc
INC_DIR = includes
CFLAGS = -Wall -Wextra -Werror -pthread -I $(INC_DIR)
LD = ld
RM = rm -f
SRCS = src/main.c src/parser.c src/simulation.c src/worker.c src/utils/timeutils.c src/utils/ft_utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

run: re
	./$(NAME) 5 5000 100 100 100 3 500 fifo

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: test fclean clean all re bonus