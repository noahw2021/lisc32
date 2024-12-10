# Target executable
TARGET_EXEC := lisc32_asm

# Build directory
BUILD_DIR := ./../build/asm

# Source directories
SRC_DIRS := ./

# Find all source files
SRCS := $(shell find $(SRC_DIRS) -name '*.c')

# Create object files from source files
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# Dependency files for each object file
DEPS := $(OBJS:.o=.d)

# Include directories
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Preprocessor flags (to generate dependencies)
CPPFLAGS := $(INC_FLAGS) -MMD -MP

# Linker flags
LDFLAGS := -L./../build/isn -llisc32_isn   # Assuming the library is in 'path/to/lib'

# Compiler flags
CFLAGS := -Wall

# Rule to create the executable
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LNKFLAGS)

# Rule to compile .c files into .o object files
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Clean rule to remove the build directory
.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

# Include dependency files to track header changes
-include $(DEPS)
