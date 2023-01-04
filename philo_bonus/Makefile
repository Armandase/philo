NAME		=	philo
SRCS		=	philo_main_bonus.c \
				philo_algo_bonus.c \
				philo_parsing_bonus.c \
			 	philo_init_bonus.c \
			 	philo_utils_bonus.c \
			 	philo_manager_bonus.c 
CC			= clang
CFLAGS		= -Wall -Werror -Wextra -pthread -g
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

norm:
	norminette *.c && norminette *.h

.PHONY: all clean fclean re norm 
