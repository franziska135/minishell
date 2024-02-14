
NAME = minishell

SRCS =  $(wildcard *.c)

OBJS = ${SRCS:.c=.o}


CC = cc
CFLAGS = -g
RM	=	rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	@make --no-print-directory -C ./libft > /dev/null
	@$(CC) $(CFLAGS) -o $(NAME) $^ ./libft/libft.a -lreadline
	@echo "\033[1;32m\n\n\t\tMINISHELL IS READY TO USE.\n\033[0m"


clean: 
	@make --no-print-directory -C ./libft fclean > /dev/null
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@echo "\033[0;91mCleaning was successful.\033[0m"

%.o: %.c
	@printf "🐋 "
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null


fclean: clean
	@${RM} ${NAME} ${CHECK}

re: fclean all

test	: all
	clear; valgrind --leak-check=full --track-origins=yes --track-fds=yes --show-reachable=yes --show-leak-kinds=all --error-limit=no --suppressions=./mini.supp ./$(NAME)

.PHONY: all bonus clean fclean re
