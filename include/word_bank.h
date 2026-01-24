#ifndef WORD_BANK
#define WORD_BANK

#define WORD_LEN 6
#define BANK_SIZE 2048

#include "util.h"

typedef struct {
    const char* filename;
    long total_word_count;
    long _page_start_index;
    long _num_loaded_words;
    int _num_cursors;
    char words[BANK_SIZE * WORD_LEN];
} WB;

typedef struct {
    WB* _wb;
    int wb_index;
    char _buf[WORD_LEN];
} Cursor;

extern int InitWordBank(const char* filename, WB* wb);

extern int DestroyWordBank(WB* wb);

extern int CreateWordBankCursor(WB* wb, Cursor* cursor);

extern int DestroyWordBankCursor(Cursor* cursor);

extern const char* GetWord(Cursor* cursor);

extern void MoveToNextWord(Cursor* cursor);

extern void MoveToPrevWord(Cursor* cursor);

extern void MoveToIndex(Cursor* cursor, int index);

extern void RefineWordBank(WB* wb, const char* guess, const Result* result, WB* new_wb);

extern void GetResultCounts(WB* wb, const char* guess, int* resultCountBuffer);

#endif