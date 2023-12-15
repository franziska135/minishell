NAME	=	minishell
#NAME2	=	minishell_bonus
INC		= 	minishell.h
CC		=	cc
CFLAGS	=	-g
# CFLAGS	=	-Wall -Wextra -Werror -g
AR		=	ar rc
RM		=	rm -f

SRC		=	builtins.c envp.c main.c libft.c cleanup.c

# SRC2	=	builtins.c envp.c main.c libft.c cleanup.c

OBJS	=	$(SRC:.c=.o)
# OBJS2	=	$(SRC2:.c=.o)

.PHONY:		all clean fclean re

all:		$(NAME)

all2:		$(NAME2)

$(NAME): 	$(OBJS)
			$(CC) $(OBJS) -o $(NAME)

$(NAME2):	$(OBJS2)
			$(CC) $(OBJS2) -o $(NAME2)

%.o: %.c 	$(INC)
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJS) $(OBJS2)

fclean: 	clean
			$(RM) $(NAME) $(NAME2)

re:			clean all

# bonus:		clean all2
