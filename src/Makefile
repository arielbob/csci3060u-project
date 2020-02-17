CC = g++
FLAGS = -Wall -g -std=c++11
VPATH = out

objects = main.o user.o transactionfile.o accountsfile.o util.o
# $(patsubst pattern, replacement, text)
OBJS = $(patsubst %.o, out/%.o, $(objects))
deps = constants.h util/util.h util/util.cpp

# Makefile variables
# $@: target (ex: main)
# $^: dependencies (ex: for user.o target - user.cpp, user.h)
# $<: first dependency (ex: for user.o target - user.cpp)

all: main 

clean:
	rm main out/*.o

main: $(objects)
	$(CC) $(FLAGS) $(OBJS) -o $@

util.o: util/util.cpp util/util.h $(deps)
	$(CC) -c $(FLAGS) $< -o out/$@

user.o: user/user.cpp user/user.h $(deps)
	$(CC) -c $(FLAGS) $< -o out/$@

accountsfile.o: accountsfile/accountsfile.cpp accountsfile/accountsfile.h $(deps)
	$(CC) -c $(FLAGS) $< -o out/$@

transactionfile.o: transactionfile/transactionfile.cpp transactionfile/transactionfile.h $(deps)
	$(CC) -c $(FLAGS) $< -o out/$@

main.o: main.cpp $(deps)
	$(CC) -c $(FLAGS) $< -o out/$@
