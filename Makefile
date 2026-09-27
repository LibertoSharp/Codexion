NAME = codexion
CC = cc
INC_DIR = includes
CFLAGS = -Wall -Wextra -Werror -pthread -I $(INC_DIR)
LD = ld
RM = rm -f
SRCS = src/main.c src/parser.c src/simulation.c src/worker.c src/utils/timeutils.c src/utils/ft_utils.c src/utils/heap.c src/scheduler_functions.c src/utils/worker_utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

run: re
	./$(NAME) 5 3000 200 200 200 10 800 edf

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