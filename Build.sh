#!/usr/bin/env bash
#
# Script file to compile all C++ source files in or under the
# current directory.  This has been used in the cygwin and OpenSUSE 
# environment the GCC and Clang compilers and linkers

# Find and display all the c++ source files to be compiled ...
# temporarily ignore spaces when globing words into file names
temp=$IFS
  IFS=$'\n'  
  sourceFiles=( $(find ./ -name "*.cpp") ) # create array of source files
IFS=$temp

#define options
options="-g3 -O0 -pthread -ansi -std=c++17 -pedantic -Wall -Wold-style-cast -Woverloaded-virtual -Wextra -I./ -DUSING_TOMS_SUGGESTIONS"

additional_options=" -L./ui_layer/sdl/lib/linux -lSDL2 -lSDL2_gfx -lSDL2_ttf -lSDL2main -ldl -lfreetype -Wl,-rpath=./ui_layer/sdl/dll/linux"

echo "compiling ..."
for fileName in "${sourceFiles[@]}"; do
  echo "  $fileName"
done


g++         --version
g++         "${sourceFiles[@]}" -o"snake.exe" $options $additional_options  
