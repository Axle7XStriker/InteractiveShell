OBJ = read_and_parse.o check_background_process.o launcher.o execute.o main.o
BLT = builtins/ls.c builtins/cd.o builtins/pwd.o builtins/echo.o builtins/pinfo.o builtins/nightswatch.c builtins/exit.o
OBJ += ${BLT}
CC = gcc
CFLAGS = -Wall -g


.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

shell: ${OBJ}
	$(CC) $(CFLAGS) -o $@ ${OBJ} 

clean:
	-rm -f *.o builtins/*.o core *.core

