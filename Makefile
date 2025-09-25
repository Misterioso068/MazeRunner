CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -O2

INCLUDES = -Iinclude

# Library directories and libs
LIBDIRS = -Llib/SDL3 -Llib/GL
LIBS = -lSDL3 -lopengl32 -lglew32

TARGET = mazerunner
SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp,build/debug/obj/%.o,$(SRCS))

DLLS = $(wildcard dll/*.dll)
BUILD_DIR = build/debug
OBJ_DIR = $(BUILD_DIR)/obj

.PHONY: all clean

all: $(BUILD_DIR)/$(TARGET)

# Link the target
$(BUILD_DIR)/$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LIBDIRS) $(LIBS)
	$(MAKE) copy-dlls

# Compile source files
build/debug/obj/%.o: src/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Ensure build/debug and obj directories exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Copy DLLs if missing
copy-dlls:
	@for f in $(DLLS); do \
		if [ ! -f $(BUILD_DIR)/$$(basename $$f) ]; then \
			cp $$f $(BUILD_DIR)/; \
			echo "Copied $$f to $(BUILD_DIR)/"; \
		fi \
	done

clean:
	rm -rf $(OBJ_DIR)/*.o $(BUILD_DIR)/$(TARGET)