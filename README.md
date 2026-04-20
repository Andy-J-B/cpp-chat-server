# cpp-chat-server

This is just a quick implementation of a multi-threaded chat server in C++

# build

Generate the Compilation Database

cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

Link database to root

ln -s build/compile_commands.json .

now build 

cmake -S . -B build && cmake --build build
