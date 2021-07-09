SRC_C =	./client.c \

SRC_S =	./server.c \

SRC_U =	./common_utils.c \

NAME_C = client
NAME_S = server

OBJS_C = $(SRC_C:.c=.o)
OBJS_S = $(SRC_S:.c=.o)
OBJS_U = $(SRC_U:.c=.o)

INCS = .
RM = rm -f
CC = gcc
CFLAGS = #-Wall -Wextra -Werror
MEMORY = #-g3 -fsanitize=address

all : $(NAME_C) $(NAME_S)

$(NAME_C) : $(OBJS_C) $(OBJS_U)
		$(CC) $(CFLAGS) -o $(NAME_C) $(OBJS_C) $(OBJS_U) -I $(INCS)

$(NAME_S) : $(OBJS_S) $(OBJS_U)
		$(CC) $(CFLAGS) -o $(NAME_S) $(OBJS_S) $(OBJS_U) -I $(INCS)

clean :
		$(RM) $(OBJS_C) $(OBJS_S) $(OBJS_U)

fclean : clean
		$(RM) $(NAME_C) $(NAME_S)

re : fclean all
