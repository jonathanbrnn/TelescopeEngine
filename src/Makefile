# Compiler and flags
CXX = clang++
CXXFLAGS = -std=c++17 -Wall \
    -I/opt/homebrew/Cellar/sdl2/2.32.2/include/SDL2 \
    -I/opt/homebrew/Cellar/sdl2_image/2.8.8/include/SDL2
CFLAGS = -Wall \
	-I/opt/homebrew/Cellar/sdl2/2.32.2/include/SDL2 \
    -I/opt/homebrew/Cellar/sdl2_image/2.8.8/include/SDL2
LDFLAGS = -L/opt/homebrew/Cellar/sdl2/2.32.2/lib \
    -L/opt/homebrew/Cellar/sdl2_image/2.8.8/lib -lSDL2 -lSDL2_image

# Target executable
TARGET = sdl

# Source files (relative paths from the Makefile location)
SRCS = main.cpp \
		demo/Player.cpp \
		demo/Heart.cpp \
		demo/Celestine.cpp \
		core/EntityManager.cpp \
		core/ManagerHub.cpp \
		core/Runtime.cpp \
		core/TimeManager.cpp \
		entities/Body.cpp \
		entities/Collider.cpp \
		entities/Force.cpp \
       	entities/GameObject.cpp \
       	entities/TextureManager.cpp \
		entities/CollisionManager.cpp \
       	rendering/Renderer.cpp \
	   	input/InputManager.cpp

OBJS = main.o \
		demo/Player.o \
		demo/Heart.o \
		demo/Celestine.o \
		core/EntityManager.o \
		core/ManagerHub.o \
		core/Runtime.o \
		core/TimeManager.o \
		entities/Body.o \
		entities/Collider.o \
		entities/CollisionManager.o \
		entities/Force.o \
	    entities/GameObject.o \
	   	entities/TextureManager.o \
		input/InputManager.o \
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
