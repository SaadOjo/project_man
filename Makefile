CC = gcc
CFLAGS = -Wall -Iinclude -g 
LDLIBS = -lncurses

SRC_DIR := src
OBJ_DIR := obj
TARGET := project

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(info SRCS = $(SRCS))
$(info OBJS = $(SRCS))


$(TARGET): $(OBJS) 
	$(CC) $(OBJS) $(LDLIBS) -o $@ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean: 
	rm -rf $(TARGET) $(OBJ_DIR)

