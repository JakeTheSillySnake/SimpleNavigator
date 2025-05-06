.PHONY: all clean clang test s21_graph s21_graph_algorithms gcov_report valgrind

FLAGS = g++ -Wall -Wextra -Werror -std=c++20
LIBS = -lgtest -lpthread -lstdc++ -L. -ls21_graph -ls21_graph_algorithms

all: clean s21_graph s21_graph_algorithms test gcov_report

s21_graph: s21_graph.cpp
	$(FLAGS) -c s21_graph.cpp -o s21_graph.o
	ar rcs libs21_graph.a s21_graph.o

s21_graph_algorithms: s21_graph_algorithms.cpp
	$(FLAGS) -c s21_graph_algorithms.cpp -o s21_graph_algorithms.o
	ar rcs libs21_graph_algorithms.a s21_graph_algorithms.o

test: clean
	$(FLAGS) tests/* main.cpp $(LIBS) -o test.out
	./test.out

gcov_report: clean
	$(FLAGS) tests/* main.cpp --coverage $(LIBS) -o test.out
	./test.out
	lcov -t "./test.out" -exclude="*test*" -exclude="*.h" -exclude="*11*" -o report.info -c -d .
	genhtml -o report/ report.info
	open ./report/index.html

valgrind:
	valgrind ./test.out --leak-check=full -s

clang:
	clang-format-18 -i *cpp *h tests/*cpp containers/*h

clean:
	rm -rf *.o *.a *.gcno *.gcda *.info *.out *.gcov *.gch *.dSYM report *dot
	@echo -e "\nAll clean!\n"