# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 16:01:17 by bdevessi          #+#    #+#              #
#    Updated: 2020/12/04 11:35:59 by bdevessi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = ft_ssl
CFLAGS = -Wall -Wextra -Werror -Iinclude
CC = gcc
OBJDIR = obj

include src.mk

OBJS = $(patsubst srcs/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(NAME)

$(OBJDIR)/%.o: srcs/%.c Makefile include/ssl.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re proto
