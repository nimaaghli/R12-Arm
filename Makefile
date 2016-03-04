CFLAGS :=`pkg-config opencv --cflags` `pkg-config opencv --libs`
all:
	g++ main.cpp -o arm -Wall -lcurl $(CFLAGS) -std=c++11
