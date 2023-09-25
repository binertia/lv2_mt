CC = gcc
C_FLAGS = -Wall -Wextra -Werror -I.

HEADERS = minitalk.h
UTILS = utils
SERVER = server
CLIENT = client
SERVER_B = server_bonus
CLIENT_B = client_bonus

UTILS_SRC = utils.c
SERVER_SRC = manda/server.c
CLIENT_SRC = manda/client.c
SERVER_B_SRC = bonus/server_bonus.c
CLIENT_B_SRC = bonus/client_bonus.c

UTILS_OBJ = $(UTILS_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_B_OBJ = $(SERVER_B_SRC:.c=.o)
CLIENT_B_OBJ = $(CLIENT_B_SRC:.c=.o)

.PHONY: all bonus clean fclean re

all: $(SERVER) $(CLIENT)

$(UTILS_OBJ): $(UTILS_SRC) $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(SERVER_OBJ): $(SERVER_SRC) $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(CLIENT_OBJ): $(CLIENT_SRC) $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(SERVER): $(UTILS_OBJ) $(SERVER_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(CLIENT): $(UTILS_OBJ) $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

bonus : $(SERVER_B) $(CLIENT_B)

$(SERVER_B_OBJ): $(SERVER_B_SRC) $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(CLIENT_B_OBJ): $(CLIENT_B_SRC) $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(SERVER_B): $(UTILS_OBJ) $(SERVER_B_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(CLIENT_B): $(UTILS_OBJ) $(CLIENT_B_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(UTILS_OBJ) $(SERVER_OBJ) $(CLIENT_OBJ) $(SERVER_B_OBJ) $(CLIENT_B_OBJ)

fclean: clean
	rm -rf $(SERVER) $(CLIENT) $(SERVER_B) $(CLIENT_B)

re: fclean all
