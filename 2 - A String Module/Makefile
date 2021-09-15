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

CC = gcc
CFLAGS = -Wall -ansi -pedantic -g

all: ar.exe ps.exe

ar.exe: src/main.o src/mystring_ars.o
	$(CC) $(CFLAGS) $^ -o $@

ps.exe: src/main.o src/mystring_ptrs.o
	$(CC) $(CFLAGS) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	-rm -f *.exe ./src/*.o

turnin: undoTurnin
	-git tag assignment2
	-git push origin --tags

undoTurnin:
	if git tag --list | egrep -q "assignment2"; then \
		git tag -d assignment2 && git push origin :refs/tags/assignment2; \
		fi


