# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kemmeric <kemmeric@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 12:48:23 by gmelisan          #+#    #+#              #
#    Updated: 2021/09/13 15:50:56 by gmelisan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CC = clang++
CFLAGS = -g -std=c++98 -Wall -Wextra

SRCDIR = src
SRC = $(addprefix $(SRCDIR)/, \
main.cpp init.cpp Logger.cpp \
utils.cpp Server.cpp Client.cpp \
MessageHandler.cpp Message.cpp)

HEADER = $(addprefix $(SRCDIR)/, \
ft_irc.h init.h Logger.h \
utils.h Server.h Client.h \
MessageHandler.h Message.h)

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $^

$(OBJ): $(HEADER)

%.o : %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
