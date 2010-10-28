LDLIBS=-lncurses

main: particle.o main.o

clean: $(RM) *.o

.PHONY: clean
