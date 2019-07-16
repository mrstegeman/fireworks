LDLIBS=-lncurses

main: particle.o main.o

clean:
	$(RM) *.o main

.PHONY: clean
