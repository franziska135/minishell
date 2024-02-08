
NAME = minishell

SRCS =  $(wildcard *.c)

BONUS = 

OBJS = ${SRCS:.c=.o}
BONUS_OBJS = ${BONUS:.c=.o}


CC = cc
CFLAGS = -g
RM	=	rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	make --no-print-directory -C ./libft
	${CC} ${CFLAGS} -o ${NAME} $^ ./libft/libft.a -lreadline

bonus: ${BONUS_OBJS}
	make --no-print-directory -C ./libft
	${CC} ${CFLAGS} -o ${NAME} $^ ./libft/libft.a

clean: 
	make --no-print-directory -C ./libft fclean
	${RM} ${OBJS} ${BONUS_OBJS}


fclean: clean
	${RM} ${NAME} ${CHECK}

re: fclean all

test	: all
	clear; valgrind --leak-check=full --track-origins=yes --track-fds=yes --show-reachable=yes --show-leak-kinds=all --error-limit=no --suppressions=./mini.supp ./$(NAME)

.PHONY: all bonus clean fclean re
