OBJ = read_and_parse.o check_background_process.o launcher.o execute.o main.o redirection.o piping.o
BLT = builtins/ls.o builtins/cd.o builtins/pwd.o builtins/echo.o builtins/pinfo.o builtins/kjob.o
BLT += builtins/nightswatch.o builtins/exit_quit.o builtins/setenv_unsetenv.o builtins/jobs.o builtins/fg_bg.o
BLT += builtins/overkill.o
OBJ += ${BLT}
CC = gcc
CFLAGS = -Wall -g


.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

shell: ${OBJ}
	$(CC) $(CFLAGS) -o $@ ${OBJ} 

clean:
	-rm -f *.o builtins/*.o core *.core

