#!/bin/bash
#shebang means gotta use bash to run this

# number of tests
NOMBRE_DE_TESTS=18

GREEN='\033[32;1m'
RED='\033[31;1m'
WHITE='\033[0;m'

<< 'This-is-a-comment-thanks-to-here-doc'
This is a containers tester. It will test the containers and see
if they are working properly.

This is a function that will test the containers VECTOR
This-is-a-comment-thanks-to-here-doc


# (()) will change variables see there the rest: https://stackoverflow.com/questions/31255699/double-parenthesis-with-and-without-dollar


# .out are the output files of a program
tests=(constructeurs  operateurs_=  iterators resize capacity assign erase insert
  	push_back pop_back clear rel_operators swap top push pop empty rel_operators constructeurs )

# This the execution of the testers and the diff
i=0
printf "%-23s%s%s\n" "TESTS " "  FT STD DIF (en ms)"
printf "\n %s"" $GREEN VECTOR $WHITE \n"
while [[ $i -le $NOMBRE_DE_TESTS ]]
do
# annonce du container teste
if [[ $i -eq 12 ]]
then
printf "\n %s"" $GREEN STACK $WHITE \n"
fi;

if [[ $i -eq 18 ]]
then
printf "\n %s"" $GREEN MAP $WHITE \n"
fi;

# start="10#$(date +%s%N)"     
./test_results/ft ${i} > ./test_results/ft_test_${i}.out
# runtime_ft=$((($(date +%s%N) - $start)/1000000))                # runtime in milliseconds

# start=$(date +%s%N)
 ./test_results/std  ${i} > ./test_results/std_test_${i}.out
# runtime_std=$((($(date +%s%N) - $start)/1000000))

diff ./test_results/std_test_${i}.out ./test_results/ft_test_${i}.out > test_results/difftest_${i}.out

#time_diff=$((${runtime_ft}/${runtime_std}));

if ! [[ -s test_results/difftest_${i}.out ]];
then
    printf "%-20s%-15s\n" "${i}: ${tests[${i}]}"  " ✅ " #"  ${runtime_ft}   ${runtime_std}   ${time_diff}"
else
    echo -e "\n ${i}: ${tests[${i}]} ❌ "
    diff -y ./test_results/std_test_${i}.out ./test_results/ft_test_${i}.out
fi
    ((i = i + 1))
done

<< testers
https://unix.stackexchange.com/questions/243489/bash-command-script-to-diff-all-mytestn-out-and-testn-out
 diff test${i}.out mytest${i}.out > difftest${i}.txt

  if ! [[ -s difftest${i} ]]; then
      echo "
  else
      echo "❌"
  fi
testers

