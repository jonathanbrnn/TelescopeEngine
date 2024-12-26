# Compiler and flags
CXX = clang++
CXXFLAGS = -std=c++17 -Wall \
    -I/opt/homebrew/Cellar/sdl2/2.30.10/include/SDL2 \
    -I/opt/homebrew/Cellar/sdl2_image/2.8.2_2/include/SDL2
LDFLAGS = -L/opt/homebrew/Cellar/sdl2/2.30.10/lib \
    -L/opt/homebrew/Cellar/sdl2_image/2.8.2_2/lib -lSDL2 -lSDL2_image

# Target executable
TARGET = sdl

# Source files (relative paths from the Makefile location)
SRCS = playground.cpp \
       entities/GameObject.cpp \
       entities/TextureManager.cpp \
       rendering/Renderer.cpp

OBJS = playground.o \
	   	entities/TextureManager.o \
       	entities/GameObject.o \
       	rendering/Renderer.o

# Default rule to build the target
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets to prevent conflicts with filenames
.PHONY: clean
