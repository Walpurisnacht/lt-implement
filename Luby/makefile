CC = g++
CFLAGS = -Wall -I.
DEPS = RandomGen.h Encoder.h Luby.h
OBJ = main.o RandomGen.o Encoder.o

%.o : %.cpp $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

luby.exe: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)
.PHONY: clean
clean:
		rm -f $(OBJ) *~