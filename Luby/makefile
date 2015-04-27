CC = g++
CFLAGS = -Wall -I.
DEPS = RandomGen.h Encoder.h Luby.h
OBJ = main.o RandomGen.o Encoder.o

%.o : %.cpp $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

main.exe: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)
		
clean:
		rm -f *.o