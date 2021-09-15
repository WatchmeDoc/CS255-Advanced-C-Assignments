#include "symtable.h"
#include <stdlib.h>
#include <assert.h>

/* Static functions hidden from other files. */
static int ms_compare(const char *s1, const char *s2);
static char *ms_copy(char *dest, const char *src);
static size_t ms_length(const char *pcStr);

/*
SymTable is a plain list with a "guard node" in the beginning of the list,
which has null elements and points towards the other nodes.
*/
struct SymTable
{
    char *key;
    void *value;
    SymTable_T next;
};

SymTable_T SymTable_new(void)
{
    SymTable_T new = malloc(sizeof(struct SymTable));
    /* Init SymTableList with "guard node" */
    new->key = NULL;
    new->value = NULL;
    new->next = NULL;

    return new;
}

void SymTable_free(SymTable_T oSymTable)
{
    SymTable_T prev = oSymTable;
    if (!oSymTable)
        return;
    oSymTable = oSymTable->next;
    /* Free all nodes and their keys, if their keys are not null. */
    while (oSymTable)
    {
        if (prev->key)
            free(prev->key);
        free(prev);
        prev = oSymTable;
        oSymTable = oSymTable->next;
    }
    free(prev->key);
    free(prev);
}

unsigned int SymTable_getLength(SymTable_T oSymTable)
{
    unsigned int length;
    assert(oSymTable);
    /* Count all nodes aside from the guard node. */
    for (length = 0, oSymTable = oSymTable->next; oSymTable; oSymTable = oSymTable->next)
        length++;
    return length;
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
    SymTable_T curr;
    assert(oSymTable);
    assert(pcKey);
    /* Check every node excluding the last one. */
    for (curr = oSymTable; curr->next; curr = curr->next)
        if (ms_compare(curr->key, pcKey) == 0)
            return 0;

    if (ms_compare(curr->key, pcKey) == 0)
        return 0;
    /* Create a new node after the last one */
    curr->next = SymTable_new();
    curr = curr->next;
    curr->key = malloc((ms_length(pcKey) + 1) * sizeof(char));
    ms_copy(curr->key, pcKey);
    curr->value = pvValue;
    return 1;
}

int SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{
    SymTable_T curr, prev = NULL;
    assert(oSymTable);
    assert(pcKey);
    for (curr = oSymTable; curr; curr = curr->next)
    { /* Lookup and delete in a list, just a simple O(n) algorithm */
        if (ms_compare(curr->key, pcKey) == 0)
        {
            if (prev == NULL)
                oSymTable = oSymTable->next;
            else
                prev->next = curr->next;
            free(curr->key);
            free(curr);
            return 1;
        }
        prev = curr;
    }
    return 0;
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey)
{ /* Lookup in a list, simple O(n) algorithm */
    SymTable_T curr;
    assert(oSymTable);
    assert(pcKey);
    for (curr = oSymTable; curr; curr = curr->next)
        if (ms_compare(curr->key, pcKey) == 0)
            return 1;
    return 0;
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey)
{ /* Lookup in a list, simple O(n) algorithm */
    SymTable_T curr;
    assert(oSymTable);
    assert(pcKey);
    for (curr = oSymTable; curr; curr = curr->next)
        if (ms_compare(curr->key, pcKey) == 0)
            return curr->value;
    return NULL;
}

void SymTable_map(SymTable_T oSymTable,

                  void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),

                  const void *pvExtra)
{ /* Apply pfApply to all nodes, excluding of course guard node. */
    SymTable_T curr;
    assert(oSymTable);
    assert(pfApply);
    for (curr = oSymTable->next; curr; curr = curr->next)
        pfApply(curr->key, curr->value, pvExtra);
}

/* similar to strcmp - Compares the 2 given string and returns -1, 0 and 1 if s1 is found
respectively to be less than, to match or to be greater than s2. */
static int ms_compare(const char *s1, const char *s2)
{
    const char *s1_curr = s1, *s2_curr = s2;
    if (s1 == NULL)
        if (s2 == NULL)
            return 0;
        else
            return -1;
    else if (s2 == NULL)
        return 1;
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

/* strcpy - Copies src string into dest. Asserts not null arguments, careful for buffer overrun! Does not check
if there is enough memory allocated for dest parameter - asserts not null pointers. */
static char *ms_copy(char *dest, const char *src)
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

/* strlen - returns the number of characters up until null byte '\0'. Asserts not null input. */
static size_t ms_length(const char *pcStr)
{
    const char *pcStrEnd = pcStr;

    assert(pcStr != NULL);
    /* while pcstrend != '\0' */
    while (*pcStrEnd)
        pcStrEnd++;
    /* sizeof(char) == 1, so their memory difference is the string's length :) */
    return pcStrEnd - pcStr;
}
