@echo off

set out=test.exe
set file1=src/TestTree.c
set file2=Unity/src/unity.c
set file3=../database.c

gcc -o %out%  %file1%  %file2% %file3% -Wall -g
%out%