CC = g++
FLAGS = -Wall -g -std=c++11
VPATH = out # to have make look for target files in out folder

# objects required for final linking
objects = main.o user.o item.o bid.o transactionfile.o accountsfile.o itemsfile.o util.o login_trans.o logout_trans.o create_trans.o delete_trans.o advertise_trans.o bid_trans.o
# prepend object filenames with out/ folder
# $(patsubst pattern, replacement, text)
OBJS = $(patsubst %.o, out/%.o, $(objects))

# dependencies required everywhere
deps = constants.h util/util.h util/util.cpp
transaction_dep = transaction/transaction.h

# Makefile variables
# $@: target (ex: main)
# $^: dependencies (ex: for user.o target - user.cpp, user.h)
# $<: first dependency (ex: for user.o target - user.cpp)

# make out file
$(shell mkdir out)

all: main 

clean:
	rm main -r out

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

login_trans.o: transaction/login_trans.cpp $(transaction_dep) $(deps)
	$(CC) -c $(FLAGS) $< -o out/$@

logout_trans.o: transaction/logout_trans.cpp $(transaction_dep) $(deps)
	$(CC) -c $(FLAGS) $< -o out/$@

create_trans.o: transaction/create_trans.cpp $(transaction_dep) $(deps)
	$(CC) -c $(FLAGS) $< -o out/$@

delete_trans.o: transaction/delete_trans.cpp $(transaction_dep) $(deps)
	$(CC) -c $(FLAGS) $< -o out/$@

advertise_trans.o: transaction/advertise_trans.cpp $(transaction_dep) $(deps)
	$(CC) -c $(FLAGS) $< -o out/$@

bid_trans.o: transaction/bid_trans.cpp $(transaction_dep) $(deps)
	$(CC) -c $(FLAGS) $< -o out/$@

main.o: main.cpp $(deps)
	$(CC) -c $(FLAGS) $< -o out/$@
