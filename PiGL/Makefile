# The name of the executable
EXEC_NAME=PiGL

# The src file(s) to compile
SRC=./*.cpp

# The header file(s) to compile
HEADER=./*.hpp

# The platform to compile (MACOS or RASPI)
PLATFORM=MACOS

# All libs to link
LIBS=

ifeq ($(PLATFORM),MACOS)
	LIBS=-framework OpenGL -framework Cocoa -framework IOKit -framework CoreFoundation -framework CoreVideo -lglfw3 -lGLEW
else ifeq ($(PLATFORM),RASPI)
	LIBS=-L/usr/lib/arm-linuxgnueabihf -lGL -lX11 -lpthread -ldl -lglfw3 -lGLEW
else
	LIBS=
endif

build:
	g++ $(SRC) $(HEADER) $(LIBS)
run:
	./$(EXEC_NAME)
clear:
	rm $(EXEC_NAME)
