
    UOS=$(shell uname)
    
    ifeq ($(OS),Windows_NT)
        PLATFORM = windows
    else
		ifeq ($(UOS),Linux)
			PLATFORM = linux
		endif
	endif
  ifeq ($(PLATFORM),windows)
    CC = C:\raylib\mingw\bin\g++.exe
    exename ?= PPGSystem.exe
    CFLAGS  = -static -Wall -Iexternal -DPLATFORM_DESKTOP -lopengl32 -lraylib -lgdi32 -lwinmm 
  endif
  ifeq ($(PLATFORM),linux)
    CC = g++
    exename ?= PPGSystem
    CFLAGS  = -Os -Wall -Wno-missing-braces -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
  endif

  all: $(TARGET)
	  $(CC) Source/Main.cpp -o $(exename) $(CFLAGS)