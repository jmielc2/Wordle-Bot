#include "word_bank.h"

int main(void) {
    WB wb;
    if (!InitWordBank("../words/words.txt", &wb)) {
        return 1;
    }
    
    // Test
    Cursor cursor;
    CreateWordBankCursor(&wb, &cursor);
    MoveToIndex(&cursor, wb.total_word_count);
    while (cursor.wb_index >= 0) {
        printf("%s\n", GetWord(&cursor));
        MoveToPrevWord(&cursor);
    }
    MoveToIndex(&cursor, -15);
    printf("Cursor at: %i\n", cursor.wb_index);

    while (cursor.wb_index < wb.total_word_count) {
        printf("%s\n", GetWord(&cursor));
        MoveToNextWord(&cursor);
    }
    MoveToIndex(&cursor, 32);
    printf("Cursor at: %i\n", cursor.wb_index);

    DestroyWordBankCursor(&cursor);
    DestroyWordBank(&wb);
    return 0;
}