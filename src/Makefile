CC = g++
FLAGS = -Wall -g -std=c++11
objects = main.o user.o transactionfile.o accountsfile.o util.o
deps = constants.h util.h util.cpp

all: main 

clean:
	rm main *.o

main: $(objects)
	$(CC) $(FLAGS) $(objects) -o main

user.o: user.cpp user.h $(deps)
	$(CC) -c $(FLAGS) user.cpp

accountsfile.o: accountsfile.cpp accountsfile.h $(deps)
	$(CC) -c $(FLAGS) accountsfile.cpp

transactionfile.o: transactionfile.cpp transactionfile.h $(deps)
	$(CC) -c $(FLAGS) transactionfile.cpp

main.o: main.cpp $(deps)
	$(CC) -c $(FLAGS) main.cpp
