# Detect architecture
ARCH := $(shell uname -m)

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
    -I. \
    -I$(BREW_PREFIX)/Cellar/sdl2/2.32.2/include/SDL2 \
    -I$(BREW_PREFIX)/Cellar/sdl2_image/2.8.8/include/SDL2 \
    -I$(BREW_PREFIX)/Cellar/nlohmann-json/3.12.0/include

LDFLAGS = $(ARCH_FLAGS) \
    -L$(BREW_PREFIX)/Cellar/sdl2/2.32.2/lib \
    -L$(BREW_PREFIX)/Cellar/sdl2_image/2.8.8/lib \
    -lSDL2 -lSDL2_image

TARGET = game

# List of source files (relative to this Makefile in src/)
SRCS = main.cpp \
        demo/platformer/Heart.cpp \
        src/Telescope.cpp \
        src/dependencies.cpp \
		src/core/ManagerHub.cpp \
		src/core/EntityManager.cpp \
        src/core/Loop.cpp \
        src/core/GameLoop.cpp \
        src/core/EditorLoop.cpp \
        src/core/TimeManager.cpp \
        src/animation/AnimationState.cpp \
        src/animation/Animator.cpp \
        src/entities/Body.cpp \
        src/entities/Collider.cpp \
        src/entities/Force.cpp \
        src/entities/GameObject.cpp \
        src/entities/TextureManager.cpp \
        src/entities/CollisionManager.cpp \
        src/rendering/Camera.cpp \
        src/rendering/Renderer.cpp \
        src/rendering/GameRenderer.cpp \
        src/rendering/EditorRenderer.cpp \
        src/input/InputManager.cpp \
        src/utilities/BaseObject.cpp 

# Convert .cpp to build/*.o
OBJ_FILES = $(SRCS:.cpp=.o)
OBJ_FILES := $(patsubst %.o,build/%.o,$(OBJ_FILES))

# Final executable target
$(TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) $(LDFLAGS) -o $(TARGET)

build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(TARGET)
	rm -rf build

.PHONY: clean

.PHONY: run 

run: 
	./$(TARGET)


# THIS CURRENTLY DOES NOT WORK 
.PHONY: archive

archive:
	@mkdir -p build/archive
	@i=0; \
	while [ -d build/archive/$(TARGET)_$$i ]; do \
		i=$$((i + 1)); \
	done; \
	mkdir -p build/archive/$(TARGET)_$$i; \
	cp -r build/* build/archive/$(TARGET)_$$i/; \
	echo "Archived current build to build/archive/$(TARGET)_$$i"



