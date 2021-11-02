# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvander- <jvander-@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/02 10:07:20 by jvander-          #+#    #+#              #
#    Updated: 2021/11/02 11:03:44 by jvander-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
LIBFT	=	./libft/
UTILS	=	./utils/
SOURCES =	srcs/
ERRORS	=	./errors/
CC		=	gcc
FLAGS	=	-Wall -Werror -Wextra

SRCS		=	$(SOURCES)minishell.c \

SRCS_UTILS	=	$(UTILS)ft_tabcharsize.c \

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
