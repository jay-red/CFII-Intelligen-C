all: jstring.o heap.o arraylist.o

jstring.o: jstring.cc jstring.h
	gcc -c jstring.cc

heap.o: heap.cc heap.h
	gcc -c heap.cc

arraylist.o: arraylist.cc arraylist.h
	gcc -c arraylist.cc

clean:
	rm -rf *.o
