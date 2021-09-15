
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

## Do not touch here
turnin: undoTurnin
	-git tag assignment4
	-git push origin --tags

undoTurnin:
	if git tag --list | egrep -q "assignment4"; then \
		git tag -d assignment4 && git push origin :refs/tags/assignment4; \
		fi
