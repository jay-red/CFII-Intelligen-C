all: enigma oxymora

oxymora: oxymora.o
	cd enigma && $(MAKE)
	g++ -o oxymora oxymora.o enigma/network_c.o enigma/network.o -std=c++11 -I/cs/student/jared_flores/lib -L/cs/student/jared_flores/lib/lib -lboost_system -D_WEBSOCKETPP_CPP11_STL_pthread_condattr_setclock -lpthread -lssl -lcrypto -ldl

oxymora.o: oxymora.c oxymora.h
	gcc -c oxymora.c

clean:
	rm -rf *.o oxymora
	cd enigma && $(MAKE) clean
