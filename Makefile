NAME = codexion
CC = cc
INC_DIR = includes
CFLAGS = -Wall -Wextra -Werror -I $(INC_DIR)
LD = ld
RM = rm -f
SRCS = src/main.c src/parser.c src/simulation.c src/worker.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

run: re
	./$(NAME) 10 3000 200 100 200 10 400 fifo

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