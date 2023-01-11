NAME		=	philo_bonus
SRCS		=	philo_main_bonus.c \
				philo_algo_bonus.c \
				philo_parsing_bonus.c \
			 	philo_init_bonus.c \
			 	philo_utils_bonus.c \
			 	philo_manager_bonus.c 
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
