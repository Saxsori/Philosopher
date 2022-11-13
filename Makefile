SRC = main.c mang_arg.c mang_dumb.c mang_forks.c mang_forks_utils.c mang_time.c mang_ate.c mang_mutex.c mang_action.c

OBJ = ${SRC:.c=.o}

NAME = philo

CC = gcc

FLAGS = -Wall -Wextra -Werror -pthread -g3 

RM = rm -rf

all : ${NAME}

${NAME}: ${OBJ}
		${CC} ${FLAGS} -o ${NAME} ${SRC}

clean : 
		${RM} ${OBJ}

fclean : clean
		${RM} ${NAME}

re : fclean all

.PHONY : all clean fclean re