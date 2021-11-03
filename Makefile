# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/02 10:07:20 by jvander-          #+#    #+#              #
#    Updated: 2021/11/02 16:33:31 by rgelin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
				$(SOURCES)ft_command_pwd_cd.c

SRCS_UTILS	=	$(UTILS)ft_tabsize.c \

SRCS_ERRORS	=	$(ERRORS)check_builtin.c \

%.o: %.c
		$(CC) $(FLAGS) -c $< -o $@

OBJS		=	$(SRCS:.c=.o)

OBJS_UTILS	=	$(SRCS_UTILS:.c=.o)

OBJS_ERRORS	=	$(SRCS_ERRORS:.c=.o)

$(NAME):	$(OBJS) $(OBJS_UTILS) $(OBJS_ERRORS)
			$(MAKE) -C $(LIBFT)
			$(CC) $(FLAGS) $(OBJS) $(OBJS_UTILS) $(OBJS_ERRORS) -lreadline $(LIBFT)libft.a -o $(NAME)

all:	$(NAME)

bonus:	$(NAME)

clean:
		$(MAKE) clean -C $(LIBFT)
		rm -f $(OBJS) $(OBJS_UTILS) $(OBJS_ERRORS)

fclean:	clean
		$(MAKE) fclean -C $(LIBFT)
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean bonus re
