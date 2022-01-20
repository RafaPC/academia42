COMPILE="clang++ --std=c++98 -o3-Wall -Wextra -Werror"
LOG_DIRECTORY="test_logs"

mkdir test_logs 2> /dev/null  
cd test_logs

clang++ --std=c++98 -o3 ../other_main.cpp -DTEST_FT -o test_ft
clang++ --std=c++98 -o3 ../other_main.cpp -o test_std

./test_ft > test_ft.out
# valgrind --log-file=test_ft.leaks ./test_ft > test_ft.out
./test_std > test_std.out
diff test_ft.out test_std.out > test.diff