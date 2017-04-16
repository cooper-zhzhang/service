cc = clang++ -std=c++11 -lpthread
main : test_thread.o Channel.o
	$(cc) -o main test_thread.o Channel.o
test_thread.o : test_thread.cpp Thread.h
	$(cc) -c test_thread.cpp
Channel.o : Channel.cpp Channel.h
	$(cc) -c Channel.cpp
Acceptor.o : Acceptor.cpp Acceptor.h
	$(cc) -c Acceptor.cpp
clean :
	rm main test_thread.o
