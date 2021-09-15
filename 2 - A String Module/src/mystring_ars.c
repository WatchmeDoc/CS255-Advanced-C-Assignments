#include "mystring.h"
#include <assert.h>

/* strlen - returns the number of characters up until null byte '\0'. Asserts not null input. */
size_t ms_length(const char pcStr[])
{

    size_t uiLength = 0U;
    /* Assert not null array */
    assert(pcStr);
    /* While pcStr[uiLength] != '\0' */
    while (pcStr[uiLength])
        uiLength++;

    return uiLength;
}

/* strcpy - Copies src string into dest. Asserts not null arguments, careful for buffer overrun! Does not check
if there is enough memory allocated for dest parameter - asserts not null arrays. */
char *ms_copy(char dest[], const char src[])
{
    size_t i;
    /* Assert that our arrays are not NULL pointers */
    assert(dest);
    assert(src);
    /* Copy every src character until null byte */
    for (i = 0U; src[i]; i++)
        dest[i] = src[i];
    /* include \0 at the end of dest string */
    dest[i] = src[i];
    return dest;
}

/* strncpy - Copies the very first n characters of src into dest. Careful, strncpy manual says that dest string might
not be null terminated, and so does ms_ncopy - asserts not null arrays.  */
char *ms_ncopy(char dest[], const char src[], size_t n)
{
    size_t i;
    /* Assert that our arrays are not NULL pointers */
    assert(dest);
    assert(src);
    /* Copy the first n elemens of src, up until the null byte */
    for (i = 0U; i < n && src[i]; i++)
        dest[i] = src[i];
    /* if the length of src is less than n, we fill the rest of dest_arr with null bytes */
    for (; i < n; i++)
        dest[i] = '\0';
    /* Manual says that dest string might not be null terminated */
    return dest;
}

/* strcat - Appends src string into dest, starting by replacing dest's null byte with 
src's first character - asserts not null arrays. */
char *ms_concat(char dest[], const char src[])
{
    size_t i = 0U, j = 0U;
    /* Assert that our pointers are not NULL pointers */
    assert(dest);
    assert(src);
    /* Find the null terminating character '\0' on our dest string */
    while (dest[i])
        i++;
    /* Fill dest string with src characters after null byte */
    for (; src[j]; i++)
        dest[i] = src[j++];
    /* Include null termination character as well! */
    dest[i] = '\0';
    return dest;
}

/* strncat - Appends the very first n characters of src into dest, this unlike ms_ncopy does
include the null byte as well!
- asserts not null arrays.  */
char *ms_nconcat(char *dest, const char *src, size_t n)
{
    size_t i, j;
    /* Assert not null arrays */
    assert(dest);
    assert(src);
    j = ms_length(dest);
    /* start from null byte and concat the rest of the string or its n first characters - asserts not null arrays. */
    for (i = 0; i < n && src[i]; i++)
        dest[j++] = src[i];
    /* ... and of course include null byte! */
    dest[j] = '\0';

    return dest;
}

/* strcmp - Compares the 2 given string and returns -1, 0 and 1 if s1 is found
respectively to be less than, to match or to be greater than s2 - asserts not null arrays.  */
int ms_compare(const char *s1, const char *s2)
{
    size_t i;
    /* Assert not null arrays */
    assert(s1);
    assert(s2);
    /* While none of them reached null byte, we compare their characters - asserts not null arrays. */
    for (i = 0U; s1[i] && s2[i]; i++)
        if (s1[i] < s2[i])
            return -1;
        else if (s1[i] > s2[i])
            return 1;

    /* If s1_curr != '\0' return 1 (len(s1_curr) > len(s2_curr)) */
    if (s1[i])
        return 1;
    /* If s2_curr != '\0' return -1 (len(s1_curr) < len(s2_curr)) */
    if (s2[i])
        return -1;
    return 0;
}

/* strncmp - Just like strcmp but compares only the first n characters of both strings -
or until 1 of them reaches null byte. If s1 is longer than s2 and s2 is a substring
of s1 then s1 > s2 (thus returns -1) - asserts not null arrays. */
int ms_ncompare(const char *s1, const char *s2, size_t n)
{
    size_t i;
    /* Assert not null pointers */
    assert(s1);
    assert(s2);
    /* Compare the very first bytes thereof */
    for (i = 0; (i < n) && *s1 && *s2; i++)
        if (s1[i] < s2[i])
            return -1;
        else if (s1[i] > s2[i])
            return 1;
    /* If i == n the first n characters of those strings are equivalent */
    if (i == n)
        return 0;
    /* If s1[i] != '\0' then it implies s2[0] == '\0' and s1 > s2 */
    if (s1[i])
        return -1;
    /* If s1[i] == '\0' then it implies s2[0] != '\0' and s1 < s2 */
    if (s2[i])
        return 1;
    /* If both are null at the same time before i == n, they are equal :) */
    return 0;
}

/* strstr - locate a substring in a given string - asserts not null arrays.*/
const char *ms_search(const char *haystack, const char *needle)
{
    size_t i, j = 0U, k = 0U;
    assert(haystack);
    assert(needle);

    for (i = 0U; haystack[i] && needle[j]; i++)
        if (haystack[i] == needle[j])
        {               /* If we found common characters, we move onto the next element */
            if (j == 0) /* and save starting index */
                k = i;
            j++;
        }
        else
        { /* Otherwise, we go back from where we started  */
            j = 0;
        }
    /* If needle[j] did not reach null byte, its not in the haystack */
    if (needle[j] != '\0')
        return NULL;
    return &haystack[k];
}