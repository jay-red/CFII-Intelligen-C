CXX = g++
CXX_FLAGS = -std=c++11 -I/cs/student/jared_flores/lib -L/cs/student/jared_flores/lib/lib -lboost_system -D_WEBSOCKETPP_CPP11_STL_pthread_condattr_setclock -lpthread -lssl -lcrypto -ldl

all: ws-test

ws-test: network_tb.cpp network.o
	${CXX} -o test network_tb.cpp network.o ${CXX_FLAGS}

network.o: network.cpp network.h
	${CXX} -c network.cpp ${CXX_FLAGS}

clean:
	rm -rf *.o test
