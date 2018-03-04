set -e

bundle exec ruco s2.ruco
make
bundle exec ruby s2_concatenator.rb test1.s2 > test1.s2ast
bundle exec ruby s2_lower.rb test1.s2ast > test1.yml
bundle exec ruby s2_il_csource.rb test1.yml > test1.c
bundle exec ruby s2_il_cheader.rb test1.yml > test1.h
bundle exec ruby s2_il_ctest.rb test1.yml > test_test1.c
gcc -ansi -pedantic-errors -Wall -g -Werror test1.c test_test1.c -o test_test1
./test_test1