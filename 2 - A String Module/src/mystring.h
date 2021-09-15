#include <stdlib.h>
/* strlen - returns the number of characters up until null byte '\0'. Asserts not null input. */
size_t ms_length(const char *s);

/* strcpy - Copies src string into dest. Asserts not null arguments, careful for buffer overrun! Does not check
if there is enough memory allocated for dest parameter. */
char *ms_copy(char *dest, const char *src);

/* strncpy - Copies the very first n characters of src into dest. Careful, strncpy manual says that dest string might
not be null terminated, and so does ms_ncopy */
char *ms_ncopy(char *dest, const char *src, size_t n);

/* strcat - Appends src string into dest, starting by replacing dest's null byte with 
src's first character. */
char *ms_concat(char *dest, const char *src);

/* strncat - Appends the very first n characters of src into dest, this unlike ms_ncopy does
include the null byte as well! */
char *ms_nconcat(char *dest, const char *src, size_t n);

/* strcmp - Compares the 2 given string and returns -1, 0 and 1 if s1 is found
respectively to be less than, to match or to be greater than s2. */
int ms_compare(const char *s1, const char *s2);

/* strncmp - Just like strcmp but compares only the first n characters of both strings -
or until 1 of them reaches null byte. If s1 is longer than s2 and s2 is a substring
of s1 then s1 > s2 (thus returns -1) */
int ms_ncompare(const char *s1, const char *s2, size_t n);

/* strstr - locate a substring in a given string.*/
const char *ms_search(const char *haystack, const char *needle);