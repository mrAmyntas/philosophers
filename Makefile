NAME = philo

CC = gcc

FLAGS = -Wall -Werror -Wextra #-fsanitize=thread

RM = rm -rf

OBJ_DIR = obj/

SRC_DIR = src/

SRC =	src/philosophers.c\
		src/utils.c\
		src/utils2.c\
		src/ft_free.c\
		src/initiateStruct.c\
		src/time_death.c\
		src/philosopherLoop.c\
		src/messages.c

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

HEADER_FILES = inc/philosophers.h

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER_FILES)
		$(CC) -c $(FLAGS) -o $@ $<

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -f obj/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re