cd %~dp0
@echo off
if exist cracker.exe del cracker.exe
g++ cracker.cpp -o cracker -std=c++17 -O3 -s -march=native
