#!/bin/bash

# command line argument to run tests for a single transaction
# ex: ./test.sh addcredit
#     will only run the tests for the addcredit transaction
if [ -n "$1" ]
then
    transaction_tests="tests/$1"
else
    transaction_tests="tests/*"
fi

for transaction in $transaction_tests
do
    if [ -d "$transaction" ]
    then
        transaction_name=${transaction##*/}
        echo -e "\e[7m  $transaction_name  \e[0m"

        # command line arg to only run single test in a transaction
        # ex: ./test.sh login login1
        #     will only run login1 test under login transaction
        if [ -n "$2" ]
        then
            test_dir=$transaction/$2
        else
            test_dir=$transaction/*
        fi

        for test in $test_dir
        do
            test_name=${test##*/}

            touch $test/transactions.output     # transactions file output
            touch $test/$test_name.output       # program output

            # generate necessary files if they don't exist
            # actually, we shouldn't since some tests rely on them not existing
            # touch $test/items.txt
            # touch $test/userAccounts.txt

            src/main $test/userAccounts.txt $test/items.txt $test/transactions.output < $test/$test_name.input > $test/$test_name.output

            if diff $test/$test_name.output $test/$test_name.exoutput > /dev/null && diff $test/transactions.output $test/transactions.txt > /dev/null ;
            then
                echo -e "\e[102m\e[30m PASS \e[39m\e[49m $test_name"
            else
                echo -e "\e[101m\e[30m FAIL \e[39m\e[49m $test_name"
                if ! diff $test/$test_name.output $test/$test_name.exoutput > /dev/null ;
                then
                    echo -e "\e[106m\e[30m OUTPUT DIFF \e[39m\e[49m"
                    diff $test/$test_name.output $test/$test_name.exoutput
                fi

                if ! diff $test/transactions.output $test/transactions.txt > /dev/null ;
                then
                    echo -e "\e[106m\e[30m TRANSACTIONS DIFF \e[39m\e[49m"
                    diff $test/transactions.output $test/transactions.txt
                fi
                echo
            fi

            # remove temporary files
            rm $test/transactions.output
            rm $test/$test_name.output
        done

        echo
    fi
done
