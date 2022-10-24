
CC = gcc
EXEC = hello
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
all : $(EXEC)
%.o : %.c include/*.h
	$(CC) -o $@ -c $<
$(EXEC):$(OBJ)
	$(CC) -o $@ $^
cls :
	del *.exe
	del src\*.o
obj :
	del src\*.o