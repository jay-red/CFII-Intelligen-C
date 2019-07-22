all: enigma.o cell.o user.o parse.o

enigma.o: enigma.cc enigma.h
	gcc -c enigma.cc

cell.o: cell.cc cell.h
	gcc -c cell.cc

user.o: user.cc user.h
	gcc -c user.cc

parse.o: parse.cc parse.h
	gcc -c parse.cc

clean:
	rm -rf *.o
