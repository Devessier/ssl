# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 16:01:17 by bdevessi          #+#    #+#              #
#    Updated: 2020/12/10 18:28:52 by bdevessi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = ft_ssl
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ilibft/includes -Iinclude -g -std=c99
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -Ilibft/includes -Iinclude -g
OBJDIR = obj
TESTS_OBJDIR = test_obj

UNITY_ROOT = ./unity

include src.mk

OBJS = $(patsubst srcs/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(NAME)

$(OBJDIR)/%.o: srcs/%.c Makefile include/ssl.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) libft/libft.a

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS)

fclean: clean
	rm -rf libft/libft.a
	rm -rf $(NAME)

re: fclean $(NAME)



TESTS = $(wildcard test/test_*.cpp)
TESTS_BIN = test_bin
TESTS_OBJS = $(patsubst test/test_%.cpp, $(TESTS_OBJDIR)/test_%.o, $(TESTS))
OBJS_FOR_TESTS = $(patsubst test/test_%.cpp, $(OBJDIR)/%.o, $(TESTS))
OBJS_WITHOUT_MAIN = $(filter-out $(OBJDIR)/main.o, $(OBJS))

$(TESTS_OBJDIR)/test_%.o: test/test_%.cpp srcs/%.c Makefile
	$(CXX) $(CXXFLAGS) -Ivendor/catch -c $< -o $@

$(TESTS_OBJDIR)/main.o: test/main.cpp
	$(CXX) $(CXXFLAGS) -Ivendor/catch -c $< -o $@

test: $(TESTS_OBJS) $(OBJS_WITHOUT_MAIN) $(TESTS_OBJDIR)/main.o
	$(CXX) $(CXXFLAGS) -Ivendor/catch -o $(TESTS_BIN) $^ libft/libft.a

.PHONY: clean fclean re proto test
