/* SymTable Data Structure */
typedef struct SymTable *SymTable_T;

/* Create and return a new allocated SymTable_T */
SymTable_T SymTable_new(void);

/* Free allocated memory for oSymTable. If oSymTable == NULL do nothing */
void SymTable_free(SymTable_T oSymTable);

/* Count and return the number of saved elements */
unsigned int SymTable_getLength(SymTable_T oSymTable);

/* Insert element to oSymTable. Assert oSymTable and pcKey not NULL and return 1 on success, or 
if element with the same string as pcKey exists return 0. */
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue);

/* Look up and remove element with the same string as pcKey. Return 1 on success, 0 if not found. */
int SymTable_remove(SymTable_T oSymTable, const char *pcKey);

/* Look up and return 1 if element with the same string as pcKey exists, or else 0. */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey);

/* Look up and return pvValue of element with the same string as pcKey from oSymTable if found, or else NULL.
Assert oSymTable and pcKey not being NULL. */
void *SymTable_get(SymTable_T oSymTable, const char *pcKey);

/* Apply to all oSymTable elements the function pfApply. Assert oSymTable and pfApply not being NULL. */
void SymTable_map(SymTable_T oSymTable,

                  void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),

                  const void *pvExtra);