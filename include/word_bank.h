#ifndef WORD_BANK
#define WORD_BANK

#include "stdio.h"

#define WORD_LEN 6
#define BANK_SIZE 6

typedef struct {
    const char* filename;
    char words[BANK_SIZE * WORD_LEN];
    int total_word_count;
    int _page_start_index;
    int _num_loaded_words;
    int _num_cursors;
} WB;

typedef struct {
    WB* _wb;
    int wb_index;
} Cursor;

extern int InitWordBank(const char* filename, WB* wb);

extern int DestroyWordBank(WB* wb);

extern int CreateWordBankCursor(WB* wb, Cursor* cursor);

extern int DestroyWordBankCursor(Cursor* cursor);

extern const char* GetWord(const Cursor* cursor);

extern void MoveToNextWord(Cursor* cursor);

extern void MoveToPrevWord(Cursor* cursor);

extern void MoveToIndex(Cursor* cursor, int index);

#endif