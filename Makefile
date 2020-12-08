# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 16:01:17 by bdevessi          #+#    #+#              #
#    Updated: 2020/12/08 03:48:25 by bdevessi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = ft_ssl
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -Iinclude
OBJDIR = obj
TESTS_OBJDIR = test_obj

UNITY_ROOT = ./unity

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



TESTS = $(wildcard test/test_*.cpp)
TESTS_BIN = test_bin
TESTS_OBJS = $(patsubst test/test_%.cpp, $(TESTS_OBJDIR)/test_%.o, $(TESTS))
OBJS_FOR_TESTS = $(patsubst test/test_%.cpp, $(OBJDIR)/%.o, $(TESTS))

$(TESTS_OBJDIR)/test_%.o: test/test_%.cpp srcs/%.c Makefile
	$(CXX) $(CXXFLAGS) -Ivendor/catch -c $< -o $@

$(TESTS_OBJDIR)/main.o: test/main.cpp
	$(CXX) $(CXXFLAGS) -Ivendor/catch -c $< -o $@

test: $(TESTS_OBJS) $(OBJS_FOR_TESTS) $(TESTS_OBJDIR)/main.o
	$(CXX) $(CXXFLAGS) -Ivendor/catch -o $(TESTS_BIN) $^

	./$(TESTS_BIN)

.PHONY: clean fclean re proto test
