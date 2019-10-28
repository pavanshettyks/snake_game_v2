# This make file was adopted to run in a MinGW environment.  Assumes your current working
# directory is the root of your project.

CXX       = g++
CXXFLAGS  = -g3 -O0 -ansi -std=c++17 -pedantic -Wall -Wold-style-cast -Woverloaded-virtual -Wextra -I. -DUSING_TOMS_SUGGESTIONS
SOURCES   = $(wildcard *.cpp) $(wildcard */*/*.cpp)
args      = -I./ -L./ui_layer/sdl/lib/linux -lSDL2 -lSDL2_gfx -lSDL2_ttf -ldl -lpthread -lfreetype -Wl,-rpath=./ui_layer/sdl/dll/linux

.PHONY: project_$(CXX).exe
project_$(CXX).exe: $(SOURCES)
	@echo $(SOURCES)
	@$(CXX) --version
	@$(CXX) $(SOURCES) -o $@ $(CXXFLAGS) $(args) 

# options to consider:
#       -Weffc++
