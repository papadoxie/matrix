CC = gcc
CFLAGS = -Wall -Wfatal-errors -Wpedantic -Wextra -Wno-multichar
LDFLAGS = -lncursesw

SOURCE_DIR = source
INCLUDE_DIR = include
BIN_DIR = bin

SRCS = $(wildcard $(SOURCE_DIR)/*.c)
HDRS = $(wildcard $(INCLUDE_DIR)/*.h)
OBJS = $(patsubst $(SOURCE_DIR)/%.c, $(BIN_DIR)/%.o, $(SRCS))

BIN = $(BIN_DIR)/matrix

all: $(BIN)

release: CFLAGS += -O2 -DNDEBUG
release: clean
release: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(BIN_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	$(RM) -r $(BIN_DIR)/*