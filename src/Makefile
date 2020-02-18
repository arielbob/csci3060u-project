CC = g++
FLAGS = -Wall -g -std=c++11
VPATH = out # to have make look for target files in out folder

# objects required for final linking
objects = main.o user.o item.o bid.o transactionfile.o accountsfile.o itemsfile.o util.o
# prepend object filenames with out/ folder
# $(patsubst pattern, replacement, text)
OBJS = $(patsubst %.o, out/%.o, $(objects))

# dependencies required everywhere
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

item.o: item/item.cpp item/item.h $(deps)
	$(CC) -c $(FLAGS) $< -o out/$@

bid.o: bid/bid.cpp bid/bid.h $(deps)
	$(CC) -c $(FLAGS) $< -o out/$@

itemsfile.o: itemsfile/itemsfile.cpp itemsfile/itemsfile.h $(deps)
	$(CC) -c $(FLAGS) $< -o out/$@

accountsfile.o: accountsfile/accountsfile.cpp accountsfile/accountsfile.h $(deps)
	$(CC) -c $(FLAGS) $< -o out/$@

transactionfile.o: transactionfile/transactionfile.cpp transactionfile/transactionfile.h $(deps)
	$(CC) -c $(FLAGS) $< -o out/$@

main.o: main.cpp $(deps)
	$(CC) -c $(FLAGS) $< -o out/$@
