CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++20 -O2 -Iinclude

# Detect platform
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    CXXFLAGS += $(shell pkg-config --cflags sdl3)
    LIBS     := $(shell pkg-config --libs sdl3) -lGLEW -lGL
endif

ifeq ($(UNAME_S),Darwin)
    CXXFLAGS += $(shell pkg-config --cflags sdl3)
    LIBS     := $(shell pkg-config --libs sdl3) -lGLEW -framework OpenGL
endif

ifeq ($(OS),Windows_NT)
    LIBS     := -Llib/SDL3 -Llib/GL -lSDL3 -lopengl32 -lglew32
    DLLS      = $(wildcard dll/*.dll)
endif

# Directories and files
BUILD_DIR := build/debug
OBJ_DIR   := $(BUILD_DIR)/obj
TARGET    := mazerunner

SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
OUT  := $(BUILD_DIR)/$(TARGET)

.PHONY: all clean copy-dlls

all: $(OUT)

# Link
$(OUT): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LIBS)
ifeq ($(OS),Windows_NT)
	$(MAKE) copy-dlls
endif

# Compile
$(OBJ_DIR)/%.o: src/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure directories exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Copy DLLs if on Windows
copy-dlls:
	@for f in $(DLLS); do \
		if [ ! -f $(BUILD_DIR)/$$(basename $$f) ]; then \
			cp $$f $(BUILD_DIR)/; \
			echo "Copied $$f to $(BUILD_DIR)/"; \
		fi \
	done

# Clean
clean:
	rm -rf $(OBJ_DIR)/*.o $(OUT)