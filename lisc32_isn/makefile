TARGET_LIB := liblisc32_isn.so  # Name of the dynamic library (change as needed)
BUILD_DIR := ./../build/isn/
SRC_DIRS := ./

# Find all source files
SRCS := $(shell find $(SRC_DIRS) -name '*.c')

# Create object files from source files
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# Dependency files for each object file
DEPS := $(OBJS:.o=.d)

# Find include directories
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Preprocessor flags (to generate dependencies)
CPPFLAGS := $(INC_FLAGS) -MMD -MP

# Compiler and linker flags
CFLAGS := -Wall -fPIC  # -fPIC ensures position-independent code for shared libraries
LDFLAGS := -shared      # Linker flag for creating shared library

# Rule to build the dynamic library
$(BUILD_DIR)/$(TARGET_LIB): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

# Rule to compile .c files into .o object files
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Clean rule to remove build directory
.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

# Include dependency files to track header changes
-include $(DEPS)
