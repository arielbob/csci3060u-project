#!/bin/bash

# GREEN='\033[0;32m'

# Script to loop through directories to merge files
transaction_tests="tests/*"
# tests="/*"
# Create files to contain the diff results and
# The general results of which test passed
# rm diff_log.txt
# touch diff_log.txt
# rm test_results.txt
# touch test_results.txt

for transaction in $transaction_tests
do
    # echo "$transaction"
    if [ -d "$transaction" ]
    then
        for test in $transaction/*
        do
            test_name=${test##*/}

            echo -e "\t$test"
            touch $test/transactions.output     # transactions file output
            touch $test/$test_name.output       # program output

            # generate necessary files if they don't exist
            touch $test/items.txt
            touch $test/userAccounts.txt

            # cat "$test/${test_name}.input"
            src/main $test/userAccounts.txt $test/items.txt $test/transactions.output < $test/$test_name.input > $test/$test_name.output

            if diff $test/$test_name.output $test/$test_name.exoutput > /dev/null;
            then
                echo -e "\e[102m\e[30m PASS \e[39m\e[49m $test_name"
            else
                echo -e "\e[101m\e[30m FAIL \e[39m\e[49m $test_name"
                diff $test/$test_name.output $test/$test_name.exoutput
                echo -e '\n'
            fi

            # TODO: diff the output transactions file with expected transactions file

            rm $test/transactions.output
            rm $test/$test_name.output

            # for test_f in $test/*
            # do
            #     echo -e "\t\t$test_f"
            # done
        done
    fi
    # If its a directory, go inside of it
#     if [ -d "$transaction" ]
#     then
#         # Make sure the test file exists
#         touch $t/trans.out
#         # Run the script and dump the output in the folder to be compared
#         ./ticket-seller tests/users.ua tests/stock.at $t/trans.out < $t/test.inp
#         # Write a file documenting if the file is ok or not
#         if diff $t/trans.out $t/test.out;
#         then
#             echo "TEST $t: GOOD" >> test_results.txt
#         else
#             # If the file is not good document the issue
#             echo "TEST $t: BAD" >> test_results.txt
#             echo "TEST $t:" >> diff_log.txt
#             diff $t/trans.out $t/test.out >> diff_log.txt
#             echo $'\n' >> diff_log.txt
#         fi
#         # Remove the temporary transaction file
#         rm $t/trans.out
#     fi
    # Clear the terminal at the end of the run
    # clear
done
