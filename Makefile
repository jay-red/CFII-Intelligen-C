all:
	g++ -std=c++11 eh.cpp -I/cs/student/jared_flores/lib -L/cs/student/jared_flores/lib/lib -lboost_system -D_WEBSOCKETPP_CPP11_STL_pthread_condattr_setclock -lpthread -lssl -lcrypto -ldl
