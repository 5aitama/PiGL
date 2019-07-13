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

NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32;01m
ERROR_COLOR=\x1b[31;01m
WARN_COLOR=\x1b[33;01m

OK_STRING=$(OK_COLOR)Ok!$(NO_COLOR)
ERROR_STRING=$(ERROR_COLOR)Error!$(NO_COLOR)
WARN_STRING=$(WARN_COLOR)Warning!$(NO_COLOR)

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
	@$(CC) -o $(BUILD_PATH)/$@ $^ $(LIBS)

# Create .o with .cpp
%.o: %.cpp
	@echo "Compile $<...\c"
	@if $(CC) -o $@ -c $< ; then echo "$(OK_STRING)" ; else echo "$(ERROR_STRING)" ; fi

# Clean all .o and the program, compile, run and clean all .o and program when he finnished to execute...
run: mrproper $(EXEC) mrproper
	@./$(BUILD_PATH)/$(EXEC)

# Clean all .o
clean:
	@rm -f $(OBJECTS)

# Clean all .o and the program
mrproper: clean
	@rm -f $(BUILD_PATH)/$(EXEC)