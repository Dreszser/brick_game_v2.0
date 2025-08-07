.PHONY: rebuild clean style clean_record

CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wno-unused-parameter -g -O0 -fsanitize=address -I $(LIB_SRC_TET_DIR) -I $(FRONT_CLI_DIR)

CPPC = g++
CPPFLAGS = -Wall -Werror -Wextra -Wno-unused-parameter -std=c++20 -g -O0 -fsanitize=address -I $(LIB_SRC_SNK_DIR) -I $(FRONT_CLI_DIR)

FRONT_CLI_DIR = gui/cli
FRONT_CLI = gui/cli/cli.c
TETRIS_BACK = $(wildcard $(LIB_SRC_TET_DIR)/*.c)
SNAKE_BACK = $(wildcard $(LIB_SRC_SNK_DIR)/*.cc)

LIB_SRC_TET_DIR = brick_game/tetris
LIB_OBJ_TET_FILES = $(patsubst $(LIB_SRC_TET_DIR)/%.c, obj/tetris/%.o, $(TETRIS_BACK))

LIB_SRC_SNK_DIR = brick_game/snake
LIB_OBJ_SNK_FILES = $(patsubst $(LIB_SRC_SNK_DIR)/%.cc, obj/snake/%.o, $(SNAKE_BACK))

TETRIS_OBJ_TEST_FILES = $(patsubst $(LIB_SRC_TET_DIR)/%.c, $(LIB_SRC_TET_DIR)/tests/%.o, $(TETRIS_BACK))
CHECK_FILES = $(wildcard $(LIB_SRC_TET_DIR)/tests/*.check)
SNAKE_OBJ_TEST_FILES = $(patsubst $(LIB_SRC_SNK_DIR)/%.cc, $(LIB_SRC_SNK_DIR)/tests/%.o, $(SNAKE_BACK))

SNAKE_TEST_FILES = $(wildcard brick_game/snake/tests/*.cc)

LDFLAGS = -lcheck -lm -lpthread

LTEST = -lgtest

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
  LDFLAGS += -lrt -lsubunit

	LTEST += -lsubunit -lrt -pthread
else ifeq ($(UNAME_S), Darwin)
	LTEST += -pthread
endif

INSTALL_DIR = ../Brick_game

all: rebuild

rebuild: clean tetris_cli snake_cli s21_desktop

snake_cli: s21_snake.a frontend_cli_snake
	$(CPPC) $(CPPFLAGS) obj/snake/s21_snake.a obj/snake/front.o obj/snake/cli.o -lncurses -lm -o snake_cli
 
tetris_cli: s21_tetris.a frontend_cli_tetris
	$(CC) $(CFLAGS) obj/tetris/s21_tetris.a obj/tetris/cli.o obj/tetris/front.o -lncurses -lm -o tetris_cli

s21_tetris.a: $(LIB_OBJ_TET_FILES)
	ar rc obj/tetris/s21_tetris.a obj/tetris/*.o
	ranlib obj/tetris/s21_tetris.a

s21_snake.a: $(LIB_OBJ_SNK_FILES)
	ar rc obj/snake/s21_snake.a obj/snake/*.o
	ranlib obj/snake/s21_snake.a

gcov_s21_tetris.a: $(TETRIS_OBJ_TEST_FILES)
	ar rc obj/tetris/gcov_s21_tetris.a $(LIB_SRC_TET_DIR)/tests/*.o
	ranlib obj/tetris/gcov_s21_tetris.a
	rm -rf $(LIB_SRC_TET_DIR)/tests/*.o 

gcov_s21_snake.a: $(SNAKE_OBJ_TEST_FILES)
	ar rc obj/snake/gcov_s21_snake.a $(LIB_SRC_SNK_DIR)/tests/*.o
	ranlib obj/snake/gcov_s21_snake.a
	rm -rf $(LIB_SRC_SNK_DIR)/tests/*.o 

clean:
	rm -rf obj/*/*.* tetris_cli a.out obj/*.a  obj/*.c docs tetris_test report
	rm -rf snake_cli obj/frontend.o obj/*.o obj/*/*.a
	rm -rf $(LIB_SRC_TET_DIR)/tests/*.gcda $(LIB_SRC_TET_DIR)/tests/*.gcno
	rm -rf BrickGame_v2.0.tar.gz snake_desktop tetris_desktop
	rm -rf gui/desktop/build snake_test
	rm -rf $(LIB_SRC_SNK_DIR)/tests/*.gcda $(LIB_SRC_SNK_DIR)/tests/*.gcno

clean_record:
	rm -rf /tmp/.s21 /tmp/s.s21

style:
	cp ../materials/linters/.clang-format .
	clang-format -n */*/*.h */*/*.c */*/*.cc brick_game/snake/tests/*
	clang-format -i */*/*.h */*/*.c */*/*.cc brick_game/snake/tests/*
	rm -rf .clang-format

# CLI frontend object files
# ==========================
frontend_cli_snake:
	$(CC) -c gui/cli/frontend.c -I $(LIB_SRC_SNK_DIR) -o obj/snake/cli.o
	$(CC) -c $(FRONT_CLI) -I $(LIB_SRC_SNK_DIR) -o obj/snake/front.o

frontend_cli_tetris:
	$(CC) -c gui/cli/frontend.c -I $(LIB_SRC_TET_DIR) -o obj/tetris/cli.o
	$(CC) -c $(FRONT_CLI) -I $(LIB_SRC_TET_DIR) -o obj/tetris/front.o
# ==========================

# Qt
# ==========================
s21_desktop: ./obj/snake/s21_snake.a ./obj/tetris/s21_tetris.a
	cmake -S ./gui/desktop -B ./gui/desktop/build
	cmake --build ./gui/desktop/build --clean-first
	cp ./gui/desktop/build/snake_desktop.app/Contents/MacOS/snake_desktop .
	cp ./gui/desktop/build/tetris_desktop.app/Contents/MacOS/tetris_desktop .
# ==========================

obj/snake/%.o: $(LIB_SRC_SNK_DIR)/%.cc
	$(CPPC) $(CPPFLAGS) -g -c $< -o $@

obj/tetris/%.o: $(LIB_SRC_TET_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

brick_game/tetris/tests/%.o: $(LIB_SRC_TET_DIR)/%.c
	$(CC) $(CFLAGS) -g --coverage -c  $< -o $@

brick_game/snake/tests/%.o: $(LIB_SRC_SNK_DIR)/%.cc
	$(CPPC) $(CPPFLAGS) -g --coverage -c $< -o $@

tetris_test: s21_tetris.a tetris_test.o 
	$(CC) $(CFLAGS) obj/tetris/test.o obj/tetris/s21_tetris.a -o tetris_test $(LDFLAGS)

tetris_test.o:
	checkmk clean_mode=1 $(CHECK_FILES) > obj/tetris/test.c
	$(CC) $(CFLAGS) -c obj/tetris/test.c -o obj/tetris/test.o

snake_test: s21_snake.a
	$(CPPC) $(CPPFLAGS) $(SNAKE_TEST_FILES) obj/snake/s21_snake.a -o snake_test $(LTEST)

snake_test.a:
	$(CPPC) $(CPPFLAGS) -c $(LIB_SRC_SNK_DIR)/tests/test_helper.cc -o obj/snake/test_helper.o
	$(CPPC) $(CPPFLAGS) -c $(LIB_SRC_SNK_DIR)/tests/main_tests.cc -o obj/snake/main_tests.o
	ar rc obj/snake/snake_tests.a obj/snake/*.o
	ranlib obj/snake/snake_tests.a
	rm -rf obj/snake/*.o

vg:
	valgrind --leak-check=full --track-origins=yes ./tetris_test

test: tetris_test snake_test

run_tests:
	./tetris_test
	./snake_test

gcov_report: clean clean_record tetris_test.o gcov_s21_tetris.a snake_test.a gcov_s21_snake.a
	$(CC) $(CFLAGS) --coverage obj/tetris/test.o obj/tetris/gcov_s21_tetris.a -o tetris_test $(LDFLAGS)
	$(CPPC) $(CPPFLAGS) --coverage obj/snake/*.a -o snake_test $(LTEST)
	./tetris_test
	./snake_test
	mkdir -p report
	gcovr --exclude 'brick_game/snake/lib_specification.cc' \
	--exclude-unreachable-branches --exclude-throw-branches --html-details report/index.html \
	--html-medium-threshold 80 --html-high-threshold 95 --html-title "s21_brick_game coverage report"

dvi:
	rm -rf docs
	doxygen -q Doxyfile
	open docs/html/index.html

dist: clean
	tar -czvf BrickGame_v2.0.tar.gz brick_game obj documentation Doxyfile Makefile

# Can be used like this: 'make install DESTDIR=xyz', where xyz - path where you want your game installed
install: clean tetris_cli snake_cli s21_desktop
	if [ -z "$(DESTDIR)" ]; then \
		mkdir $(INSTALL_DIR); \
		mv tetris_cli $(INSTALL_DIR)/.; \
		mv tetris_desktop $(INSTALL_DIR)/.; \
		mv snake_cli $(INSTALL_DIR)/.; \
		mv snake_desktop $(INSTALL_DIR)/.; \
		echo "Game installed to $(INSTALL_DIR)"; \
	else \
		mkdir $(DESTDIR); \
		mv tetris_cli $(DESTDIR)/.; \
		mv tetris_desktop $(DESTDIR)/.; \
		mv snake_cli $(DESTDIR)/.; \
		mv snake_desktop $(DESTDIR)/.; \
		echo "Game installed to $(DESTDIR)"; \
	fi
	make clean
	
uninstall: clean_record
	if [ -z "$(DESTDIR)" ]; then \
		rm -rf $(INSTALL_DIR); \
	else \
		rm -rf $(DESTDIR); \
	fi
	