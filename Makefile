CC = gcc
CFLAGS = -std=c11 -O2

TARGET = vuk

BUILD_DIR = build
CRYPR_DIR = src/cryptography

SRCS = $(wildcard $(CRYPR_DIR)/*.c)
OBJS = $(patsubst $(CRYPR_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(BUILD_DIR)/%.o: $(CRYPR_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

re: clean all
