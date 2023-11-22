CC=g++
CFLAGS=-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal\
       -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs \
       -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions\
	   -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security\
	   -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor\
	   -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing\
	   -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla\
	   -D_DEBUG -D_EJUDGE_CLIENT_SIDE -DWITH_CANARY -DWITH_HASH

TREE_OBJ_DIR = ./Tree/object/
TREE_SRC_DIR = ./Tree/source/

TREE_SRC = $(wildcard $(TREE_SRC_DIR)*.cpp)
TREE_OBJ = $(patsubst $(TREE_SRC_DIR)%.cpp, $(TREE_OBJ_DIR)%.o, $(TREE_SRC))

AKTR_OBJ_DIR = ./Akinator/object/
AKTR_SRC_DIR = ./Akinator/source/

AKTR_SRC = $(wildcard $(AKTR_SRC_DIR)*.cpp)
AKTR_OBJ = $(patsubst $(AKTR_SRC_DIR)%.cpp, $(AKTR_OBJ_DIR)%.o, $(AKTR_SRC))

STK_OBJ_DIR = ./Stack/object/
STK_SRC_DIR = ./Stack/source/

STK_SRC = $(wildcard $(STK_SRC_DIR)*.cpp)
STK_OBJ = $(patsubst $(STK_SRC_DIR)%.cpp, $(STK_OBJ_DIR)%.o, $(STK_SRC))

all: compile

compile: $(TREE_OBJ) $(STK_OBJ) $(AKTR_OBJ)
	$(CC) $(TREE_OBJ) $(STK_OBJ) $(AKTR_OBJ) -o akinator

$(TREE_OBJ_DIR)%.o : $(TREE_SRC_DIR)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(STK_OBJ_DIR)%.o : $(STK_SRC_DIR)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(AKTR_OBJ_DIR)%.o : $(AKTR_SRC_DIR)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(TREE_OBJ) $(STK_OBJ) $(AKTR_OBJ)