all: network_c.o network.o

network_c.o: network_c.cpp network_c.h
	g++ -c network_c.cpp -std=c++11 -I/cs/student/jared_flores/lib -L/cs/student/jared_flores/lib/lib -lboost_system -D_WEBSOCKETPP_CPP11_STL_pthread_condattr_setclock -lpthread -lssl -lcrypto -ldl

network.o: network.cpp network.h
	g++ -c network.cpp -std=c++11 -I/cs/student/jared_flores/lib -L/cs/student/jared_flores/lib/lib -lboost_system -D_WEBSOCKETPP_CPP11_STL_pthread_condattr_setclock -lpthread -lssl -lcrypto -ldl

clean:
	rm -rf *.o
