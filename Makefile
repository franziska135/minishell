
# NAME = minishell
# SRCS = 	$(wildcard *.c)
# OBJS	=	${SRCS:.c=.o}
# OBJDIR	=	objects


# CC = cc
# CFLAGS = -g
# RM	=	rm -rf

# all: ${NAME}

# ${NAME}: ${OBJS}
# 	@make --no-print-directory -C ./libft > /dev/null
# 	@$(CC) $(CFLAGS) -o $(NAME) $^ ./libft/libft.a -lreadline
# 	@echo "\033[1;32m\n\n\t\tMINISHELL IS READY TO USE.\n\033[0m"


# clean: 
# 	@make --no-print-directory -C ./libft fclean > /dev/null
# 	@$(RM) $(OBJS) $(BONUS_OBJS)
# 	@echo "\033[0;91mCleaning was successful.\033[0m"

# %.o: %.c
# 	@printf "🐋 "
# 	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null


# fclean: clean
# 	@${RM} ${NAME} ${CHECK}m

# re: fclean all

# test	: all
# 	clear; valgrind --leak-check=full --track-origins=yes --track-fds=yes --show-reachable=yes --show-leak-kinds=all --error-limit=no --suppressions=./mini.supp ./$(NAME)

# .PHONY: all bonus clean fclean re

NAME = minishell
CC = cc
CFLAGS = -g -I include/
RM = rm -rf

SRCS = $(wildcard src/*.c)
OBJDIR = ./obj
OBJS = $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRCS))

.PHONY: all clean fclean re $(OBJDIR)

all: $(OBJDIR) $(NAME)

$(NAME): $(OBJS)
	@make --no-print-directory -C ./libft > /dev/null
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) ./libft/libft.a -lreadline
	@echo "\033[1;32m\n\n\t\tMINISHELL IS READY TO USE.\n\033[0m"

clean:
	@make --no-print-directory -C ./libft fclean > /dev/null
	@$(RM) $(OBJDIR) $(OBJS)
	@echo "\033[0;91mCleaning was successful.\033[0m"

$(OBJDIR)/%.o: src/%.c
	@printf "🐋 "
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

fclean: clean
	@$(RM) $(NAME)

re: fclean all

test : all
	clear; valgrind --leak-check=full --track-origins=yes --track-fds=yes --show-reachable=yes --show-leak-kinds=all --error-limit=no --suppressions=./mini.supp ./$(NAME)

