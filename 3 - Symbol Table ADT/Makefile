###################################################
#
# file: Makefile
#
# @Author:   Iacovos G. Kolokasis
# @Version:  10-02-2021
# @email:    kolokasis@csd.uoc.gr
#
# Makefile
#
####################################################

all: list.exe hash.exe

CC = gcc
CFLAGS = -Wall -ansi -pedantic -g

clean:
	@rm -f *.exe ./src/*.o *.out

list.exe: src/main.o src/symtablelist.o
	$(CC) $(CFLAGS) $^ -o $@

hash.exe: src/main.o src/symtablehash.o
	$(CC) $(CFLAGS) $^ -o $@

## Creates a .out file with memory report. Needs to have valgrind installed in order to run this command (sudo apt-get install valgrind)
memcheck: list.exe hash.exe
	@valgrind --leak-check=full --show-leak-kinds=definite,indirect,possible,reachable --track-origins=yes --verbose --log-file=listmemcheck.out ./list.exe >/dev/null
	@valgrind --leak-check=full --show-leak-kinds=definite,indirect,possible,reachable --track-origins=yes --verbose --log-file=hashmemcheck.out ./hash.exe >/dev/null

%.o:%.c
	@$(CC) $(CFLAGS) -o $@ -c $<



## Do not touch here
turnin: undoTurnin
	-git tag assignment3
	-git push origin --tags

undoTurnin:
	if git tag --list | egrep -q "assignment3"; then \
		git tag -d assignment3 && git push origin :refs/tags/assignment3; \
		fi


