@echo off
set file1=src/main.c
set file2=src/library.c

gcc -o test_Library %file1% %file2% -Wall