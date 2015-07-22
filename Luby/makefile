CC = g++
CFLAGS = -Wall -fexceptions -g -std=c++11 -I.
DEPS = RandomGen.h Encoder.h Luby.h Decoder.h
OBJ = main.o RandomGen.o Encoder.o Decoder.o Luby.o

%.o : %.cpp $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

luby.exe: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)
.PHONY: clean all
clean:
		rm -f $(OBJ) *~