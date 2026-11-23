# Simple TCP Echo Server

A modular IPv4 TCP echo server written in C using POSIX socket system calls (socket, setsockopt, bind, listen, accept, read, write, close) on Linux.

## Build & Run

Compile from the project root:
  gcc -Wall -Wextra src/main.c src/server.c -Iinclude -o server_app
  ./server_app

Connect from another terminal with nc:
  nc 127.0.0.1 8080
