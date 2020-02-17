CC = g++
FLAGS = -Wall -g -std=c++11
objects = main.o user.o transactionfile.o accountsfile.o

all: main 

clean:
	rm main *.o

main: $(objects)
	$(CC) $(FLAGS) $(objects) -o main

user.o: user.cpp user.h constants.h
	$(CC) -c $(FLAGS) user.cpp

accountsfile.o: accountsfile.cpp accountsfile.h constants.h
	$(CC) -c $(FLAGS) accountsfile.cpp

transactionfile.o: transactionfile.cpp transactionfile.h constants.h
	$(CC) -c $(FLAGS) transactionfile.cpp

main.o: main.cpp constants.h
	$(CC) -c $(FLAGS) main.cpp
