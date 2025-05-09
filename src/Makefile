.PHONY: all clean clang test s21_graph s21_graph_algorithms gcov_report valgrind install uninstall

FLAGS = g++ -Wall -Wextra -Werror -std=c++20
LIBS = -lgtest -lpthread -lstdc++ -L. -ls21_graph -ls21_graph_algorithms -ls21_stack -ls21_queue

all: clean s21_stack s21_queue s21_graph s21_graph_algorithms test gcov_report

install: clean s21_stack s21_queue s21_graph s21_graph_algorithms
	$(FLAGS) main.cpp $(LIBS) -o app

uninstall: clean
	rm -rf app

s21_stack: containers/s21_stack.cpp
	$(FLAGS) -c containers/s21_stack.cpp -o s21_stack.o
	ar rcs libs21_stack.a s21_stack.o

s21_queue: containers/s21_queue.cpp
	$(FLAGS) -c containers/s21_queue.cpp -o s21_queue.o
	ar rcs libs21_queue.a s21_queue.o

s21_graph: s21_graph.cpp
	$(FLAGS) -c s21_graph.cpp -o s21_graph.o
	ar rcs libs21_graph.a s21_graph.o

s21_graph_algorithms: s21_graph_algorithms.cpp
	$(FLAGS) -c s21_graph_algorithms.cpp -o s21_graph_algorithms.o
	ar rcs libs21_graph_algorithms.a s21_graph_algorithms.o

s21_graph_gcov: s21_graph.cpp
	$(FLAGS) -c --coverage s21_graph.cpp -o s21_graph.o -lstdc++
	ar rcs libs21_graph.a s21_graph.o

s21_graph_algorithms_gcov: s21_graph_algorithms.cpp
	$(FLAGS) -c --coverage s21_graph_algorithms.cpp -o s21_graph_algorithms.o -lstdc++
	ar rcs libs21_graph_algorithms.a s21_graph_algorithms.o

test: clean s21_stack s21_queue s21_graph s21_graph_algorithms
	$(FLAGS) tests/* $(LIBS) -o test.out
	./test.out

gcov_report: clean s21_graph_gcov s21_graph_algorithms_gcov
	$(FLAGS) tests/* --coverage $(LIBS) -o test.out
	./test.out
	lcov -t "./test.out" -exclude="*test*" -exclude="*.h" -exclude="*11*" -o report.info -c -d .
	genhtml -o report/ report.info
	open ./report/index.html

valgrind:
	valgrind ./test.out --leak-check=full -s

clang:
	clang-format-18 -i *cpp *h tests/*cpp containers/*h

clean:
	rm -rf *.o *.a *.gcno *.gcda *.info *.out *.gcov *.gch *.dSYM report test.dot app
	@echo -e "\nAll clean!\n"