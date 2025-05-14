.PHONY: all clean clang test s21_graph s21_graph_algorithms s21_stack s21_queue gcov_report valgrind app

CFLAGS = g++ -Wall -Wextra -Werror -std=c++20
LFLAGS = -lgtest -lpthread -lstdc++
LIBS = -L. -ls21_graph -ls21_graph_algorithms -ls21_stack -ls21_queue

all: clean test gcov_report

app: s21_stack s21_queue s21_graph s21_graph_algorithms
	$(CFLAGS) --coverage main.cpp $(LIBS) $(LFLAGS) -o app
	rm -rf *dummy* *.o *gcno

s21_stack: libs21_stack.a

s21_queue: libs21_queue.a

s21_graph: libs21_graph.a

s21_graph_algorithms: libs21_graph_algorithms.a

libs21_stack.a:
	echo '#include "containers/s21_stack.h"' >> stack_dummy.cpp
	$(CFLAGS) --coverage -c stack_dummy.cpp -o s21_stack.o $(LFLAGS)
	ar rcs -o libs21_stack.a s21_stack.o

libs21_queue.a:
	echo '#include "containers/s21_queue.h"' >> queue_dummy.cpp
	$(CFLAGS) --coverage -c queue_dummy.cpp -o s21_queue.o $(LFLAGS)
	ar rcs -o libs21_queue.a s21_queue.o

libs21_graph.a:
	$(CFLAGS) --coverage -c graph/s21_graph.cpp -o s21_graph.o $(LFLAGS)
	ar rcs -o libs21_graph.a s21_graph.o

libs21_graph_algorithms.a:
	$(CFLAGS) --coverage -c graph/s21_graph_algorithms.cpp -o s21_graph_algorithms.o $(LFLAGS)
	ar rcs -o libs21_graph_algorithms.a s21_graph_algorithms.o

test: clean s21_stack s21_queue s21_graph s21_graph_algorithms
	$(CFLAGS) --coverage tests/* $(LIBS) $(LFLAGS) -o test.out
	./test.out
	rm -rf *dummy* *.o test.dot 

gcov_report:
	lcov -t "./test.out" -exclude="*test*" -exclude="*11*" -o report.info -c -d .
	genhtml -o report/ report.info
	open ./report/index.html

valgrind:
	valgrind ./test.out --leak-check=full -s

clang:
	clang-format -i *.cpp tests/* containers/* graph/*

clean:
	rm -rf *.o *.a *.gcno *.gcda *.info *.out *.gcov *.gch *.dSYM report test.dot *dummy*
	@echo -e "\nAll clean!\n"