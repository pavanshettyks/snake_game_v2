#!/usr/bin/env bash
BuildTaskName="$1"

clear
echo -e "$BuildTaskName\n"  # Build Title

# Find and display all the c++ source files to be compiled ...
# temporarily ignore spaces when globing words into file names
temp=$IFS
  IFS=$'\n'  
  sourceFiles=( $(find ./ -name "*.cpp") )
IFS=$temp

echo "compiling ..."
for fileName in "${sourceFiles[@]}"; do
  echo "  $fileName"
done
echo ""


# Set some options and perform the compolations ...
options="-pthread -ansi -std=c++17 -pedantic -Wall -Wold-style-cast -Woverloaded-virtual -Wextra -I./ -DUSING_TOMS_SUGGESTIONS"
$Compiler --version
$Compiler $Options $options -o "$Executable" "${sourceFiles[@]}" && echo -e "\nSuccessfully created  \"$Executable\""
