NAME		= philo
SRCS		= philo_main.c philo_algo.c philo_parsing.c \
			  philo_init.c philo_manager.c philo_utils.c
CC			= clang
CFLAGS		= -Wall -Werror -Wextra -pthread
OBJS		= ${SRCS:.c=.o}

all: ${NAME}

$(NAME): ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${SRCS}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
	rm -f ${OBJS}

fclean : clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
