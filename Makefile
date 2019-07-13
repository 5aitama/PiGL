# Compiler that we use to compile src
CC=g++
# The name of the program
EXEC=PiGL
# Where is the main.cpp file
ROOT=PiGL/Sources
# Folder where the build are
BUILD_PATH=PiGL/Build

# Files to compile
OBJECTS=
OBJECTS+= $(ROOT)/WInfos/WInfos.o
OBJECTS+= $(ROOT)/ShaderCompiler/ShaderCompiler.o
OBJECTS+= $(ROOT)/main.o

# Libraries
LIBS=

# Init libraries...
# For Mac OS
ifeq ($(PLATFORM),MACOS)
	LIBS= -framework OpenGL
	LIBS+= -framework Cocoa
	LIBS+= -framework IOKit
	LIBS+= -framework CoreFoundation
	LIBS+= -framework CoreVideo
	LIBS+= -lglfw3
	LIBS+= -lGLEW
endif

# For Raspberry Pi
ifeq ($(PLATFORM),RASPI)
	LIBS= -L/usr/lib/arm-linuxgnueabihf
	LIBS+= -lGL
	LIBS+= -lX11
	LIBS+= -lpthread
	LIBS+= -ldl
	LIBS+= -lglfw3
	LIBS+= -lGLEW
endif

# Compile and run
all: $(EXEC)

# Compile and run
$(EXEC): $(OBJECTS)
	$(CC) -o $(BUILD_PATH)/$@ $^ $(LIBS)

# Create .o with .cpp
%.o: %.cpp
	$(CC) -o $@ -c $<

# Clean all .o and the program, compile and run
run: mrproper $(EXEC)
	$(BUILD_PATH)/$(EXEC)

# Clean all .o
clean:
	rm -f $(OBJECTS)

# Clean all .o and the program
mrproper: clean
	rm -f $(BUILD_PATH)/$(EXEC)