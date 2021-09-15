A symbol table ADT with 2 different implementations as assigned, one with linked lists and another
with a hashtable. Used valgrind to check and patch any memory leaks so the program is memory safe overall
(memcheck included in the makefile as well). For the bonus part I also implemented a way to increase the 
number of buckets on the hashtable implementation everytime the number of total elements inserted reaches
a specific milestone (as assigned). main.c contains leftover testing code.