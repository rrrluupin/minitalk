SERVER = src/server.c
CLIENT = src/client.c
LIBFT = cd libft && make
LIB = libft/libft.a
HEAD = includes/minitalk.h

SERVER_SRC = $(SERVER)
SERVER_OBJS = $(SERVER_SRC:.c=.o)
CLIENT_SRC = $(CLIENT)
CLIENT_OBJS = $(CLIENT_SRC:.c=.o)
OBJS = $(CLIENT_OBJS) / $(SERVER_OBJS)

GCC = cc
FLAGC = -Wall -Wextra -Werror -g 
INCLUDE = -I include
SERVER_NAME = server
CLIENT_NAME = client
NAME = server

all: $(NAME)

$(NAME): $(SERVER_OBJS) $(CLIENT_OBJS)
		$(LIBFT)
		$(GCC) $(FLAGC) $(SERVER_OBJS) $(LIB) -o $(SERVER_NAME)
		$(GCC) $(FLAGC) $(CLIENT_OBJS) $(LIB) -o $(CLIENT_NAME)


%.o:	%.c $(HEAD)
		${GCC} ${FLAGC} ${INCLUDE} -c $< -o ${<:.c=.o}

clean:
		make clean -C libft
		rm -f $(CLIENT_OBJS) $(SERVER_OBJS)
		

fclean: clean
		make fclean -C libft
		rm -f $(SERVER_NAME) $(CLIENT_NAME)
		
re:		fclean all

.PHONY: all  clean fclean re 
