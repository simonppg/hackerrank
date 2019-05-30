g++ -g Node.cpp Queue.cpp main.cpp
cat data | valgrind --leak-check=full --show-leak-kinds=all ./a.out
