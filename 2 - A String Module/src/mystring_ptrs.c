#include "mystring.h"
#include <assert.h>

/* strlen - returns the number of characters up until null byte '\0'. Asserts not null input. */
size_t ms_length(const char *pcStr)
{
    const char *pcStrEnd = pcStr;

    assert(pcStr);
    /* while pcstrend != '\0' */
    while (*pcStrEnd)
        pcStrEnd++;
    /* sizeof(char) == 1, so their memory difference is the string's length :) */
    return pcStrEnd - pcStr;
}

/* strcpy - Copies src string into dest. Asserts not null arguments, careful for buffer overrun! Does not check
if there is enough memory allocated for dest parameter - asserts not null pointers. */
char *ms_copy(char *dest, const char *src)
{
    const char *src_curr = src;
    char *dest_curr = dest;
    /* Assert that our pointers are not NULL pointers */
    assert(dest);
    assert(src);
    /* Increase each pointer by 1 after assignment */
    while (*src_curr)
        *(dest_curr++) = *(src_curr++);
    /* include \0 at the end of dest string */
    *dest_curr = *src_curr;
    return dest;
}

/* strncpy - Copies the very first n characters of src into dest. Careful, strncpy manual says that dest string might
not be null terminated, and so does ms_ncopy - asserts not null pointers. */
char *ms_ncopy(char *dest, const char *src, size_t n)
{
    size_t i = 0U;
    /* Assert that our pointers are not NULL pointers */
    assert(dest);
    assert(src);
    for (i = 0U; i < n && *src; i++)
        *(dest + i) = *(src + i);

    for (; i < n; i++)
        *(dest + i) = '\0';
    /* Manual says that dest string might not be null terminated */
    return dest;
}

/* strcat - Appends src string into dest, starting by replacing dest's null byte with 
src's first character - asserts not null pointers. */
char *ms_concat(char *dest, const char *src)
{
    const char *src_curr = src;
    char *dest_curr = dest;
    /* Assert that our pointers are not NULL pointers */
    assert(dest);
    assert(src);
    /* Find the null terminating character '\0' on our dest string */
    while (*dest_curr)
        dest_curr++;
    /* Fill dest string with src characters after null byte */
    while (*src_curr)
        *(dest_curr++) = *(src_curr++);
    /* Include null termination character as well! */
    *dest_curr = '\0';
    return dest;
}

/* strncat - Appends the very first n characters of src into dest, this unlike ms_ncopy does
include the null byte as well! 
- asserts not null pointers. */
char *ms_nconcat(char *dest, const char *src, size_t n)
{
    size_t dest_len;
    size_t i;
    char *dest_curr;
    /* Assert not null pointers */
    assert(dest);
    assert(src);
    dest_len = ms_length(dest);
    /* Save the trouble of calculating dest + dest_len at each loop */
    dest_curr = dest + dest_len;
    for (i = 0; i < n && *src; i++)
        *(dest_curr + i) = *(src + i);
    /* ... and of course include null byte! */
    *(dest_curr + i) = '\0';

    return dest;
}

/* strcmp - Compares the 2 given string and returns -1, 0 and 1 if s1 is found
respectively to be less than, to match or to be greater than s2 - asserts not null pointers. */
int ms_compare(const char *s1, const char *s2)
{
    const char *s1_curr = s1, *s2_curr = s2;
    /* Assert not null pointers */
    assert(s1);
    assert(s2);
    /* While none of them reached null byte, we compare their characters */
    while (*s1_curr && *s2_curr)
        if (*(s1_curr) < *(s2_curr))
            return -1;
        else if (*(s1_curr++) > *(s2_curr++))
            return 1;

    /* If s1_curr != '\0' return 1 (len(s1_curr) > len(s2_curr)) */
    if (*s1_curr)
        return 1;
    /* If s2_curr != '\0' return -1 (len(s1_curr) < len(s2_curr)) */
    if (*s2_curr)
        return -1;
    return 0;
}

/* strncmp - Just like strcmp but compares only the first n characters of both strings -
or until 1 of them reaches null byte. If s1 is longer than s2 and s2 is a substring
of s1 then s1 > s2 (thus returns -1) - asserts not null pointers. */
int ms_ncompare(const char *s1, const char *s2, size_t n)
{
    size_t i;
    /* Assert not null pointers */
    assert(s1);
    assert(s2);
    /* Compare the very first bytes thereof */
    for (i = 0; (i < n) && *s1 && *s2; i++)
        if (*(s1 + i) < *(s2 + i))
            return -1;
        else if (*(s1 + i) > *(s2 + i))
            return 1;
    /* If i == n the first n characters of those strings are equivalent */
    if (i == n)
        return 0;
    /* If s1[i] != '\0' then it implies s2[0] == '\0' and s1 > s2 */
    if (*(s1 + i))
        return -1;
    /* If s1[i] == '\0' then it implies s2[0] != '\0' and s1 < s2 */
    if (*(s2 + i))
        return 1;
    /* If both are null at the same time before i == n, they are equal :) */
    return 0;
}

/* strstr - locate a substring in a given string - asserts not null pointers.*/
const char *ms_search(const char *haystack, const char *needle)
{
    const char *haystack_curr = haystack, *needle_curr = needle, *substr = NULL;
    /* Assert not null pointers */
    assert(haystack);
    assert(needle);

    for (; *haystack_curr && *needle_curr; haystack_curr++)
        if (*(haystack_curr) == *(needle_curr))
        { /* If we found common characters, we move onto the next element */
            needle_curr++;
            if (!substr) /* and save pointer to the start of this substring in haystack */
                substr = haystack_curr;
        }
        else
        { /* Otherwise, we go back from where we started  */
            needle_curr = needle;
            substr = NULL;
        }
    /* If needle_curr did not reach null byte, its not in the haystack */
    if (*needle_curr != '\0')
        substr = NULL;
    return substr;
}