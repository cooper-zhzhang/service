cc = clang++ -std=c++11 -lpthread
main : test_thread.o
	$(cc) -o main test_thread.o
test_thread.o : test_thread.cpp Thread.h
	$(cc) -c test_thread.cpp
Channel.o : Channel.cpp Channel.h
	$(cc) -c Channel.o
clean :
	rm main test_thread.o
