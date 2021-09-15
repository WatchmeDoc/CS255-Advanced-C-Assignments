
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

all: data3 data6 data9 data10

CC = gcc
CFLAGS = -Wall -ansi -pedantic -g

data3:
	@$(CC) $(CFLAGS) src/create$@.c -o src/$@.out
	@./src/$@.out
data6:
	@$(CC) $(CFLAGS) src/create$@.c -o src/$@.out
	@./src/$@.out

data9:
	@$(CC) $(CFLAGS) src/create$@.c -o src/$@.out
	@./src/$@.out
data10:
	@$(CC) $(CFLAGS) src/create$@.c -o src/$@.out
	@./src/$@.out

clean:
	@rm -f src/*.out
	@rm -f data*
	@rm -f src/data*


## Do not touch here
turnin: undoTurnin
	-git tag assignment6
	-git push origin --tags

undoTurnin:
	if git tag --list | egrep -q "assignment6"; then \
		git tag -d assignment6 && git push origin :refs/tags/assignment6; \
		fi
