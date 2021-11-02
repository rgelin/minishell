# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvander- <jvander-@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/02 10:07:20 by jvander-          #+#    #+#              #
#    Updated: 2021/11/02 09:01:08 by jvander-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
LIBFT	=	./libft/
SOURCES =	srcs/
CC		=	gcc
INCLUDES = -I./includes/
FLAGS	=	-Wall -Werror -Wextra $(INCLUDES)

SRCS	=	$(SOURCES)minishell.c \

%.o: %.c
		$(CC) $(FLAGS) -c $< -o $@

OBJS		=	$(SRCS:.c=.o)

$(NAME):	$(OBJS)
			$(MAKE) -C $(LIBFT)
			$(CC) $(FLAGS) $(OBJS) $(LIBFT)libft.a -o  $(NAME)

all:	$(NAME)

bonus:	$(NAME)

clean:
		$(MAKE) clean -C $(LIBFT)
		rm -f $(OBJS)

fclean:	clean
		$(MAKE) fclean -C $(LIBFT)
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean bonus re
