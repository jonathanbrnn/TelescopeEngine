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
    -I$(BREW_PREFIX)/Cellar/sdl2_image/2.8.8/include/SDL2 \
	-I$(BREW_PREFIX)/Cellar/nlohmann-json/3.12.0/include
CFLAGS = $(ARCH_FLAGS) -Wall \
	-I$(BREW_PREFIX)/Cellar/sdl2/2.32.2/include/SDL2 \
    -I$(BREW_PREFIX)/Cellar/sdl2_image/2.8.8/include/SDL2 \
	-I$(BREW_PREFIX)/Cellar/nlohmann-json/3.12.0/include
LDFLAGS = $(ARCH_FLAGS) -L$(BREW_PREFIX)/Cellar/sdl2/2.32.2/lib \
    -L$(BREW_PREFIX)/Cellar/sdl2_image/2.8.8/lib -lSDL2 -lSDL2_image \
	-I$(BREW_PREFIX)/Cellar/nlohmann-json/3.12.0/include

# Target executable
TARGET = sdl

# Source files
SRCS = main.cpp \
		dependencies.cpp \
		animation/AnimationState.cpp \
		animation/Animator.cpp \
		demo/Player.cpp \
		demo/Heart.cpp \
		demo/Celestine.cpp \
		demo/Spikes.cpp \
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
		rendering/Camera.cpp \
       	rendering/Renderer.cpp \
	   	input/InputManager.cpp

# Object files under build/
OBJS = $(SRCS:.cpp=.o)
OBJ_FILES = $(patsubst %.o,build/%.o,$(OBJS))

# Default rule
$(TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) $(LDFLAGS) -o $(TARGET)

# Create build dir if not existing and compile each source to build/*.o
build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf build $(TARGET)

.PHONY: clean
