# CPPRay default Makefile for building CPPRay on GNU GCC or Mingw32
# Original creator: EliteTK
# Edits by: Harha

# Binary name
BINARY = CPPRay

# Use mingw32 by default on windows
ifeq ($(OS), Windows_NT)
	LDLIBS = -lmingw32 -lSDL2main
endif

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra

# Linker flags
LDFLAGS = -Wl,--as-needed

# Linker libraries
LDLIBS += -lSDL2

# Object files to be created
OBJECTS = main.o display.o engine.o mesh.o scene.o

# Disable optimizations if DEBUG is true
DEBUG ?= 0
ifeq ($(DEBUG), 1)
	CXXFLAGS += -Og -g
else
	CXXFLAGS += -Ofast
	LDFLAGS += -Ofast
endif

all: $(BINARY)

CPPRay: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

main.o: main.cpp config.h display.h engine.h input.h
display.o: display.cpp display.h
engine.o: engine.cpp engine.h pathtrace.h
mesh.o: mesh.cpp mesh.h
scene.o: scene.cpp scene.h

tags:
	ctags -R .

TAGS:
	etags *.cpp *.h

clean:
	$(RM) $(OBJECTS) $(BINARY) tags TAGS

.PHONY: all clean
