#!/bin/bash

#Linux Installer


install_dir="/bin/" #the installation path
rel_dir="BibCommands/source/" #the relative dir of all files

files=("${rel_dir}Say/main.cpp" "${rel_dir}CreateFile/main.cpp")
names=("crtdoc" "say")


for ((i=0; i<"${#files[@]}"; i++)); do

	file="${files[i]}"
	name="${names[i]}"

	g++ -std=c++11 "$file" -o "$name"

	if [ $? -eq 0 ]; then
		echo "$name compiled successful"
		mv "$name" "$install_dir"
	else
		echo "$name failed to compile"
	fi
done