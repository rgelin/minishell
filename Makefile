
NAME	=	minishell
LIBFT	=	./libft/
UTILS	=	./utils/
SOURCES =	./srcs/
ERRORS	=	./errors/
CC		=	gcc
FLAGS	=	-Wall -Werror -Wextra

SRCS		=	$(SOURCES)minishell.c \
				$(SOURCES)ft_execute_command.c \
				$(SOURCES)ft_command.c \
				$(SOURCES)parsing.c \
				$(SOURCES)ft_command_pwd_cd.c

SRCS_UTILS	=	$(UTILS)ft_tabsize.c \

SRCS_ERRORS	=	$(ERRORS)check_builtin.c \

OBJS		=	$(SRCS:.c=.o)

OBJS_UTILS	=	$(SRCS_UTILS:.c=.o)

OBJS_ERRORS	=	$(SRCS_ERRORS:.c=.o)


#-------------------COLORS----------------------

RED			=	\x1b[31m

YELLOW		=	\x1b[33m

GREEN		=	\x1b[32m

NO_COLOR	=	\x1b[0m


#-------------------RULES-----------------------
%.o: %.c
		@printf "$(YELLOW)Generating minishell object... %-30s\r$(NO_COLOR)" $@
		@$(CC) $(FLAGS) -c $< -o $@

$(NAME):	$(OBJS) $(OBJS_UTILS) $(OBJS_ERRORS)
			@echo "\n"
			@$(MAKE) -C $(LIBFT)
			@echo "$(GREEN)\nCompiling minishell...$(NO_COLOR)"
			@$(CC) $(FLAGS) $(OBJS) $(OBJS_UTILS) $(OBJS_ERRORS) -lreadline $(LIBFT)libft.a -o $(NAME)
			@echo "\nMinishell ready to be used!"

all:	$(NAME)

bonus:	$(NAME)

clean:
		@echo "$(RED)Deleting objects...\n$(NO_COLOR)"
		@$(MAKE) clean -C $(LIBFT)
		@rm -f $(OBJS) $(OBJS_UTILS) $(OBJS_ERRORS)

fclean:	clean
		@echo "$(RED)Deleting executables...\n$(NO_COLOR)"
		@$(MAKE) fclean -C $(LIBFT)
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean bonus re
