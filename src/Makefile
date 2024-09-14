all: clean dvi clang

CC = g++
FLAGS = -std=c++17 -Wall -Wextra -Werror
GTEST_LIBS = -lgtest -lgtest_main -pthread

dvi:
	open README.txt

install:
# QT
	sh install_script.sh

# Ncurses
	mkdir build_ncurses
	cd build_ncurses
	$(CC) $(FLAGS) -o ./build_ncurses/snake_ncurses main_ncurses.cpp view_ncurses.cpp controller.cpp model.cpp -lncurses  

clean:
# QT
	rm -rf build

# Ncurses
	rm -rf build_ncurses

qt:
	./build/view_qt.app/Contents/MacOS/view_qt

ncurses:
	./build_ncurses/snake_ncurses
     
clang:
	clang-format -i --style=google ./*.cpp ./*.h 
	cp ../.clang-format ../src/.clang-format;
	clang-format -style=Google -n ./*.cpp ./*.h 
	rm .clang-format




	
	

