SRC_DIR := src
NAME := ./a.out

CC := clang++
LANG := c++
STD := c++2b
WARNINGS := -Wall -Wextra -Wpedantic -Weffc++ -Wconversion -Wshadow \
	    -Wnon-virtual-dtor -Wcast-align -Woverloaded-virtual -Wnull-dereference \
	    -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable
CFLAGS := -x $(LANG) -std=$(STD) $(WARNINGS) $(DEBUG) -O0 -fmodules
LIB := -lfmt
SAN := -fsanitize=address,undefined

src := $(shell find $(SRC_DIR) -type f -name "*.cpp")
obj := $(src:.cpp=.o)

all: compile

run: $(NAME)
	@./$(NAME)

debug: CFLAGS += -g -DDEBUG=1

debug: fclean compile

compile: $(NAME)

$(NAME): $(obj)
	$(CC) $(obj) $(LIB) $(SAN) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

leak: $(NAME)
	valgrind --leak-check=full $(NAME)

clean:
	$(RM) $(obj)

fclean: clean
	$(RM) $(NAME)

generate_cc:
	bear -- make
