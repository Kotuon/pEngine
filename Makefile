# Macros ========================================
CC=C:/Program Files/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin/g++.exe
CFLAGS=-m64 -g -O0 $(OBJECTS) -o $(BUILDDIR)$(EXE) $(INCLUDE) $(LIBRARIES) $(LINKED)
OUTDIR=out/
BUILDDIR=build/
SOURCEDIR=src/
EXE=pEngine.exe
OBJECTS=$(SOURCEDIR)/*.cpp
INCLUDE=-I libraries/SDL2/include -I libraries/GLM -I libraries/GLFW/include
LIBRARIES=-L libraries/SDL2/lib -L libraries/GLFW/lib
LINKED=-lmingw32 -lSDL2main -lSDL2 -lopengl32 -lglfw3dll -lglu32
# Targets ========================================

$(OUTDIR)$(EXE) :
	cls
	$(CC) $(CFLAGS)

rebuild :
	-$(MAKE) --no-print-directory clean
	$(MAKE) --no-print-directory

run :
	$(BUILDDIR)$(EXE)