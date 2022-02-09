FLAGS="--std=c++98 -o3 -Wall -Wextra -Werror"
LOG_DIRECTORY="test_logs"

mkdir $LOG_DIRECTORY 2> /dev/null
cd $LOG_DIRECTORY

clang++ $FLAGS ../main.cpp -DTEST_FT -o test_ft
clang++ $FLAGS ../main.cpp -o test_std

./test_ft > test_ft.out
# valgrind --log-file=test_ft.leaks ./test_ft > /dev/null
./test_std > test_std.out
diff test_ft.out test_std.out > test.diff