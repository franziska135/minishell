NAME = minishell
CC = cc
CFLAGS = -g -I include/
RM = rm -rf
# ***************************************************************************

SRCS = 	src/builtin_builtins.c src/expand.c src/parser_split.c\
		src/builtin_cd.c src/ft_here_doc.c src/parser_split_utils.c\
		src/builtin_cd_utils.c src/lexis.c src/parser_struct_cpy.c\
		src/builtin_cleanup.c src/lexis_utils.c src/parser_utils.c\
		src/builtin_echo.c src/main_env_ll.c src/path_finder.c\
		src/builtin_env.c src/main_node_arithmetic.c src/pipin_root.c\
		src/builtin_exit.c src/main_transfer_ll_to_ptr.c src/run_minishell.c\
		src/builtin_export.c src/minishell.c src/signals.c\
		src/builtin_export_utils2.c src/parser.c src/signals_utils.c\
		src/builtin_export_utils3.c src/parser_malloc_struct.c src/syntax.c\
		src/builtin_export_utils.c src/parser_open_redir.c src/utils1.c\
		src/builtin_main.c src/parser_redir.c src/utils.c src/builtin_unset.c\
		src/parser_remove_qoutes.c src/write_expansion.c src/close_fds.c\
		src/parser_scmds_expand.c

OBJDIR = ./obj
OBJS = $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRCS))

.PHONY: all clean fclean re $(OBJDIR)

all: $(OBJDIR) $(NAME)

$(NAME): $(OBJS)
	@make --no-print-directory -C ./libft > /dev/null
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) ./libft/libft.a -lreadline
	echo "\033[1;32m\n\n\t\tMINISHELL IS READY TO USE.\n\033[0m"

clean:
	@make --no-print-directory -C ./libft fclean > /dev/null
	@$(RM) $(OBJDIR) $(OBJS)
	echo "\033[0;91mCleaning was successful.\033[0m"

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

fclean: clean
	@$(RM) $(NAME)

re: fclean all

test : all
	clear; valgrind --leak-check=full --track-origins=yes --track-fds=yes --show-reachable=yes --show-leak-kinds=all --error-limit=no --suppressions=./mini.supp ./$(NAME)

