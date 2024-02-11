GCC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++
SOURCE = $(wildcard back/modeltransform/*.cc)
UNAME_S := $(shell uname -s)
OBJ_TEST = s21_tests/*.cc
APP = build/3DViewer.app

ifeq ($(UNAME_S),Linux)
  	OPEN_CMD = xdg-open
	LEAKS_CMD = valgrind --tool=memcheck --leak-check=yes
	ADD_LIB = -lgtest -lpthread -lm
endif

ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open -a "Google Chrome"
	LEAKS_CMD = leaks -atExit --
	ADD_LIB = -lgtest
endif

all: uninstall install

test: 
	@$(GCC) $(CFLAGS) $(SOURCE) $(OBJ_TEST) -o test $(ADD_LIB)
	./test

test_leaks: 
	@$(GCC) $(CFLAGS) $(SOURCE) $(OBJ_TEST) -o test_leaks $(ADD_LIB)
	$(LEAKS_CMD) ./test_leaks

build:  
	@mkdir build
	@cd build &&  qmake ../ && make

install: build
	@cp -rf $(APP) $(HOME)/Desktop/
	@make clean
	@echo "**********************************************"
	@echo "*    The installation was successful.        *"
	@echo "*     The project is located in the          *"
	@echo "* folder Viewer on the desktop.              *"
	@echo "**********************************************"

uninstall:
	@rm -rf $(HOME)/Desktop/3DViewer.app

dvi:
	@open specification/specification3DViewer.md

dist: all
	@mkdir $(HOME)/Desktop/dist
	@cp -R $(HOME)/Desktop/3DViewer.app $(HOME)/Desktop/dist
	@cp specification/specification3DViewer.md $(HOME)/Desktop/dist 
	@cd $(HOME)/Desktop/dist && tar cvzf Viewer.tgz *
	@cd $(HOME)/Desktop/dist && rm -rf 3DViewer.app specification3DViewer.md
	@rm -rf $(HOME)/Desktop/3DViewer.app
	@echo "******************************************"
	@echo "*     The tar file is located in the     *"
	@echo "*    folder dist and the desktop.        *"
	@echo "******************************************"



clean:
	@-rm -rf build*
	@-rm -rf *.o && rm -rf *.gcno
	@-rm -rf *.a && rm -rf *.gcda
	@-rm -rf *.info && rm -rf *.gcov
	@-rm -rf ./gcov_report
	@-rm -fr report
	@-rm -fr test test_leaks
	@-rm -rf *.txt


	
gcov_report:${SOURCE}
	@$(GCC) $(CFLAGS) --coverage $(OBJ_TEST) $(SOURCE) -o test $(ADD_LIB)
	@./test
	@rm -rf test_main.gcda test_main.gcno
	@lcov -t "s21_viewer_test" -o fizzbuzz.info -c -d .
	@genhtml -o report fizzbuzz.info
	@$(OPEN_CMD) report/index.html

style:
	@find . \( -name "*.cc" -o -name "*.cpp" -o -name "*.h" \) -exec clang-format -style=Google -n {} \;



.PHONY:	all test install uninstall dvi dist clean build test_leaks style
