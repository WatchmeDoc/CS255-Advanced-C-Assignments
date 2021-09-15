#include "symtable.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define SIZE_TEST 100000

void print_elem(const char *pcKey, void *pvValue, void *pvExtra);

int main()
{
    int *ptr = malloc(sizeof(int)), i, len = 0, codes[SIZE_TEST];
    char string[SIZE_TEST][7];
    SymTable_T table = SymTable_new();
    char *name = "Makhs";
    *ptr = 5;
    assert(SymTable_put(table, name, ptr) == 1);
    assert(SymTable_put(table, name, "PAOK") == 0);
    assert(SymTable_contains(table, name) == 1);
    assert(SymTable_getLength(table) == 1);
    assert(SymTable_get(table, name) == ptr);

    name = "Tsorts";
    assert(SymTable_put(table, name, "PAOK") == 1);
    assert(SymTable_put(table, name, "AEK") == 0);
    assert(strcmp(SymTable_get(table, name), "PAOK") == 0);
    *ptr = 12;
    assert(SymTable_contains(table, "MAKHS") == 0);
    assert(SymTable_put(table, "MAKHS", ptr) == 1);
    assert(SymTable_get(table, "Makhs") == ptr);
    assert(SymTable_get(table, "MAKHS") == ptr);
    assert(SymTable_getLength(table) == 3);

    assert(SymTable_remove(table, "MAKHS") == 1);
    assert(SymTable_getLength(table) == 2);
    assert(SymTable_remove(table, "MAKHS") == 0);
    assert(SymTable_getLength(table) == 2);

    assert(SymTable_remove(table, "Makhs") == 1);
    assert(SymTable_remove(table, name) == 1);
    assert(SymTable_getLength(table) == 0);

    assert(SymTable_put(table, "", "CSD") == 1);
    assert(SymTable_put(table, "", "AEK") == 0);
    assert(SymTable_put(table, "AEZAKMI", "CSD") == 1);
    assert(SymTable_getLength(table) == 2);
    SymTable_map(table, &print_elem, "Alpha Squad");
    srand(time(NULL));
    for (i = 0; i < SIZE_TEST; i++)
    { /* String and code generation. */
        sprintf(string[i], "%d", i);
        codes[i] = rand();
    }
    len = SymTable_getLength(table);
    for (i = 0; i < SIZE_TEST; i++)
    {
        if (SymTable_put(table, string[i], &(codes[i])) == 1)
            len++;
    }
    assert(SymTable_getLength(table) == len);
    SymTable_map(table, &print_elem, "\n\n\n");

    SymTable_free(table);

    printf("Tests passed!\n");
    free(ptr);
    return 0;
}

void print_elem(const char *pcKey, void *pvValue, void *pvExtra)
{ /* Default pfApply func */
    printf("name: %s\ncode: %d\ncategory: %s\n", pcKey, pvValue, pvExtra);
}