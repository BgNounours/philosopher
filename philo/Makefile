NAME = philo

SRC = src/

FILES = main.c error.c utils.c thread.c turn.c write.c

CC = cc

OBJ = $(addprefix $(SRC), $(FILES:.c=.o))

FLAGS = -Wall -Werror -Wextra -pthread -lpthread

all:	${NAME}

${NAME}: ${OBJ}
		${CC} ${FLAGS} ${OBJ} -o ${NAME}

clean:
	rm -f ${OBJ} ${B_OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all
