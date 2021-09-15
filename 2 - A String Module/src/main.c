#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "mystring.h"
#include <string.h>
/* Trash main - nothing interesting! Used just for a few testing purposes. */
int main()
{
    char s1[20];
    char *s2 = "the";
    ms_copy(s1, "hello\0there");
    printf("strfun = %s\n", s1);
    printf("strfun = %s\n", ms_concat(s1, s2));
    printf("custom strfun = %s\n", ms_search(s1, s2));
    return 0;
}