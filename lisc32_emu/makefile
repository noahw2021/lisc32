# Target executable
TARGET_EXEC := lisc32_emu

# Build directory
BUILD_DIR := ./../build/emu

# Source directories
SRC_DIRS := ./

# Find all source files
SRCS := $(shell find $(SRC_DIRS) -name '*.c')

# Object files generated from the source files
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# Dependency files (to track header changes)
DEPS := $(OBJS:.o=.d)

# Platform-specific settings
UNAME_S := $(shell uname -s)

# Include directories
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Preprocessor flags (to generate dependencies)
CPPFLAGS := $(INC_FLAGS) -MMD -MP

# Compiler and linker flags
LDFLAGS :=

ifeq ($(UNAME_S), Linux)
    # Linux-specific flags
    CPPFLAGS += -lSDL2 -I/usr/include/SDL2/ -lm -ldl
    LNKFLAGS := -lSDL2 -lm -ldl
endif

ifeq ($(UNAME_S), Darwin)
    # macOS-specific flags
    CPPFLAGS += -I"/opt/homebrew/Cellar/sdl2/2.28.5/include/SDL2/"
    LNKFLAGS := -lSDL2 -L"/opt/homebrew/Cellar/sdl2/2.28.5/lib/"
endif

# Rule to build the executable
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LNKFLAGS)

# Rule to compile .c files into .o object files
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Clean rule to remove build directory
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# Include dependency files to track header changes
-include $(DEPS)
