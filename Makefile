CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude -Isrc
SRCS = src/main.c src/fileHandler.c src/linkedListHandler.c
LOGS = logs/transaction_log.txt
REPORT = report/report.pdf
OBJS = $(SRCS:.c=.o)
RELEASE_DIR = release
TARGET = $(RELEASE_DIR)/fintrack
ZIP_DIR = dist
HEADERS = include/fileHandler.h include/linkedListHandler.h
ZIP_NAME = fintrack.zip
ZIP_PATH = $(ZIP_DIR)/$(ZIP_NAME)

all: $(TARGET)
	@echo "Build complete: $(TARGET)"

zip: $(ZIP_PATH)
	@echo "Created archive: $(ZIP_PATH)"

$(ZIP_PATH): $(TARGET) $(SRCS) $(HEADERS) $(LOGS) $(REPORT) Makefile README.md
	mkdir -p $(ZIP_DIR) 
	rm -f $@
	zip -r $@ $(TARGET) $(SRCS) $(HEADERS) $(LOGS) $(REPORT) Makefile README.md

$(TARGET): $(OBJS) $(HEADERS)
	mkdir -p $(RELEASE_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

src/%.o: src/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(ZIP_PATH)

.PHONY: all clean zip
