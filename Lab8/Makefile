CC = gcc
CFLAGS = -std=gnu99 -g
SERVER_SOURCES = server.c task14.c timer.c serverFunctions.c logOutput.c input.c securityFunctions.c
CLIENT_SOURCES = client.c task14.c timer.c logOutput.c input.c securityFunctions.c
LIBRARIES = -lm -lpam -lpam_misc

all:
	$(CC) $(CFLAGS) $(SERVER_SOURCES) $(LIBRARIES) -o Lab8_Server.o
	$(CC) $(CFLAGS) $(CLIENT_SOURCES) $(LIBRARIES) -o Lab8_Client.o

