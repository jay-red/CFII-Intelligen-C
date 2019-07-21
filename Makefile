CONTAINER_OBJ = container/arraylist.o \
		container/heap.o \
		container/jstring.o 

ENIGMA_OBJ = enigma/enigma.o

NET_OBJ = network/network_c.o \
	  network/network.o

all: subreqs oxymora

oxymora: oxymora.o
	g++ -o oxymora oxymora.o $(CONTAINER_OBJ) $(ENIGMA_OBJ) $(NET_OBJ) -std=c++11 -I/cs/student/jared_flores/lib -L/cs/student/jared_flores/lib/lib -lboost_system -D_WEBSOCKETPP_CPP11_STL_pthread_condattr_setclock -lpthread -lssl -lcrypto -ldl

oxymora.o: oxymora.cc oxymora.h
	gcc -c oxymora.cc

subreqs: FORCE
	cd container && $(MAKE)
	cd enigma && $(MAKE)
	cd network && $(MAKE)

FORCE: ;

clean:
	rm -rf *.o oxymora
	cd container && $(MAKE) clean
	cd enigma && $(MAKE) clean
	cd network && $(MAKE) clean
