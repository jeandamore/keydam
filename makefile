CC = gcc
CFLAGS = -g -O2 -framework ApplicationServices
OBJECTS = utils.o main.o
EXE = main.exe

main.exe : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o main.exe

clean: 
	rm -f $(OBJECTS) $(EXE)

%.o : %.c
	$(CC) $(CFLAGS) -c $<
