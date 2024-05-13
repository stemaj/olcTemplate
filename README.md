### Compile a lib for Emscripten

find . -name '*.cpp' > file_list.txt
em++ -c -std=c++2a -O2 -I./include/ $(<file_list.txt)
emar rcs libbox2d.a *.o
