##
## Makefile for Makefile in /home/jsx/Epitech/tek2/PSU/ftp/PSU_2016_myftp/server/
##
## Made by JSX
## Login   <jean-sebastien.herbaux@epitech.eu>
##
## Started on  Sat May 13 17:46:21 2017 JSX
## Last update Sun May 21 16:53:52 2017 JSX
##

CC			=					gcc

NAME		=					server

CFLAGS  =					-Wextra -Wall -W -Werror          \
                  -I./Includes/

SRCS    =					./Srcs/errors.c			\
									./Srcs/init.c				\
									./Srcs/utils.c			\
									./Srcs/main.c				\
									./Srcs/commands.c				\
									./Srcs/Command/cdup.c				\
									./Srcs/Command/cwd.c				\
									./Srcs/Command/dele.c				\
									./Srcs/Command/help.c				\
									./Srcs/Command/list.c				\
									./Srcs/Command/noop.c				\
									./Srcs/Command/pass.c				\
									./Srcs/Command/pasv.c				\
									./Srcs/Command/pwd.c				\
									./Srcs/Command/quit.c				\
									./Srcs/Command/retr.c				\
									./Srcs/Command/stor.c				\
									./Srcs/Command/user.c				\
									./Srcs/Command/type.c				\

OBJS    =					$(SRCS:.c=.o)

RM      =       	rm -f

CP			=					cp

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<
