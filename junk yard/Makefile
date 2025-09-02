ARCH := $(shell uname -m)

ifeq ($(ARCH), arm64)
    BREW_PREFIX = /opt/homebrew
    ARCH_FLAGS = -arch arm64
else
    BREW_PREFIX = /usr/local
    ARCH_FLAGS = -arch x86_64
endif

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

TARGET = test

SRCS = test.cpp 

OBJ_FILES = $(SRCS:.cpp=.o)
OBJ_FILES := $(notdir $(OBJ_FILES))

$(TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) $(LDFLAGS) -o $(TARGET)

clean: 
	rm -f $(TARGET)
	rm -f $(OBJ_FILES)

.PHONY: clean 

