# Detect architecture
ARCH := $(shell uname -m)

# Set correct Homebrew prefix based on architecture
ifeq ($(ARCH), arm64)
    BREW_PREFIX = /opt/homebrew
    ARCH_FLAGS = -arch arm64
else
    BREW_PREFIX = /usr/local
    ARCH_FLAGS = -arch x86_64
endif

# Compiler and flags
CXX = clang++
CXXFLAGS = $(ARCH_FLAGS) -std=c++17 -Wall \
    -I$(BREW_PREFIX)/Cellar/sdl2/2.32.2/include/SDL2 \
    -I$(BREW_PREFIX)/Cellar/sdl2_image/2.8.8/include/SDL2
CFLAGS = $(ARCH_FLAGS) -Wall \
	-I$(BREW_PREFIX)/Cellar/sdl2/2.32.2/include/SDL2 \
    -I$(BREW_PREFIX)/Cellar/sdl2_image/2.8.8/include/SDL2
LDFLAGS = $(ARCH_FLAGS) -L$(BREW_PREFIX)/Cellar/sdl2/2.32.2/lib \
    -L$(BREW_PREFIX)/Cellar/sdl2_image/2.8.8/lib -lSDL2 -lSDL2_image

# Target executable
TARGET = sdl

# Source files (relative paths from the Makefile location)
SRCS = main.cpp \
		animation/AnimationState.cpp \
		animation/Animator.cpp \
		demo/Player.cpp \
		demo/Heart.cpp \
		demo/Celestine.cpp \
		demo/Spikes.cpp \
		core/ContextManager.cpp \
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

OBJS = $(SRCS:.cpp=.o)

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
