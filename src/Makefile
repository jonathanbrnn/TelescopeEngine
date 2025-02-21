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
SRCS = main.cpp \
		core/EntityManager.cpp \
		core/Runtime.cpp \
       	entities/GameObject.cpp \
       	entities/TextureManager.cpp \
		entities/CollisionManager.cpp \
       	rendering/Renderer.cpp \
	   	input/InputManager.cpp

OBJS = main.o \
		core/ManagerHub.o \
		core/TimeManager.o \
		core/EntityManager.o \
		core/Runtime.o \
	    entities/GameObject.o \
	   	entities/TextureManager.o \
		entities/CollisionManager.o \
       	rendering/Renderer.o \
		input/InputManager.o

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
