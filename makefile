cc = clang++ -std=c++11 -lpthread
main : test_thread.o
	$(cc) -o main test_thread.o
test_thread.o : test_thread.cpp Thread.h
	$(cc) -c test_thread.cpp
clean :
	rm test_thread.o main
