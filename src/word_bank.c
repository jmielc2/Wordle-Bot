#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "word_bank.h"

static void LoadWordBankPageAtIndex(WB* wb, int index) {
    // Clear word bank
    index = (index / BANK_SIZE) * BANK_SIZE;
    wb->_page_start_index = index;
    wb->_num_loaded_words = 0;
    memset(&wb->words, '\0', sizeof(wb->words));

    // Read
    FILE* file = fopen(wb->filename, "r");
    if (file == NULL) {
        printf("ERROR: Word bank file '%s' no longer exists.\n", wb->filename);
        return;
    }
    size_t word_size = WORD_LEN + 1;
    char* buf = malloc(sizeof(char) * word_size);
    int i = 0;
    while (i < index) {
        getline(&buf, &word_size, file);
        i++;
    }
    i = 0;
    while (i < BANK_SIZE && index + i < wb->total_word_count) {
        getline(&buf, &word_size, file);
        memccpy(&wb->words[i * WORD_LEN], buf, '\n', sizeof(buf));
        wb->words[i * WORD_LEN + 5] = '\0';
        wb->_num_loaded_words++;
        i++;
    }
    free(buf);
    fclose(file);
}

static void LoadNextWordBankPage(WB* wb) {
    // Preliminary checks
    int new_start_index = wb->_page_start_index + BANK_SIZE;
    if (new_start_index >= wb->total_word_count) {
        printf("INFO: No next page to load.\n");
        return;
    }

    // Load Words
    LoadWordBankPageAtIndex(wb, new_start_index);
}

static void LoadPrevWordBankPage(WB* wb) {
    // Preliminary checks
    int new_start_index = wb->_page_start_index - BANK_SIZE;
    if (new_start_index < 0) {
        printf("INFO: No prev page to load.\n");
        return;
    }

    // Load Words
    LoadWordBankPageAtIndex(wb, new_start_index);
}

int InitWordBank(const char* filename, WB* wb) {
    wb->filename = filename;
    memset(&wb->words, '\0', sizeof(wb->words));
    wb->_page_start_index = 0;
    wb->_num_cursors = 0;
    wb->_num_loaded_words = 0;
    wb->total_word_count = 0;
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("ERROR: Word bank file '%s' not found.\n", filename);    
        return 0;
    }
    size_t word_size = WORD_LEN + 1;
    char* buf = malloc(sizeof(char) * word_size);
    for (int i = 0; i < BANK_SIZE && !feof(file); i++) {
        getline(&buf, &word_size, file);
        memccpy(&wb->words[i * WORD_LEN], buf, '\n', sizeof(buf));
        wb->words[i * WORD_LEN + 5] = '\0';
        wb->_num_loaded_words++;
        wb->total_word_count++;
    }
    while (!feof(file)) {
        getline(&buf, &word_size, file);
        wb->total_word_count++;
    }
    free(buf);
    fclose(file);
    return 1;
}

int DestroyWordBank(WB* wb) {
    if (wb->_num_cursors > 0) {
        printf("ERROR: Word Bank can't be closed until are associated cursors are closed.\n");
        return 0;
    }
    memset(&wb->words, '\0', sizeof(wb->words));
    wb->_page_start_index = 0;
    wb->_num_loaded_words = 0;
    wb->total_word_count = 0;
    return 1;
}

int CreateWordBankCursor(WB* wb, Cursor* cursor) {
    wb->_num_cursors++;
    cursor->_wb = wb;
    cursor->wb_index = 0;
    return 1;
}

int DestroyWordBankCursor(Cursor* cursor) {
    cursor->_wb->_num_cursors--;
    cursor->wb_index = 0;
    cursor->_wb = NULL;
    return 1;
}

const char* GetWord(const Cursor* cursor) {
    if (cursor->wb_index == cursor->_wb->total_word_count || cursor->wb_index == -1) {
        return "\0";
    }
    return &cursor->_wb->words[(cursor->wb_index - cursor->_wb->_page_start_index) * WORD_LEN];
}

void MoveToNextWord(Cursor* cursor) {
    WB* wb = cursor->_wb;
    if (cursor->wb_index < wb->total_word_count) {
        cursor->wb_index++;
    } else {
        return;
    }

    if (cursor->wb_index == wb->_page_start_index + wb->_num_loaded_words && cursor->wb_index != wb->total_word_count) {
        LoadNextWordBankPage(wb);
    }
}

void MoveToPrevWord(Cursor* cursor) {
    WB* wb = cursor->_wb;
    if (cursor->wb_index >= 0) {
        cursor->wb_index--;
    } else {
        return;
    }

    if (cursor->wb_index == wb->_page_start_index - 1 && cursor->wb_index != -1) {
        LoadPrevWordBankPage(wb);
    }

}

void MoveToIndex(Cursor* cursor, int index) {
    WB* wb = cursor->_wb;
    if (index < wb->_page_start_index) {
        if (index < 0) {
            index = -1;
            LoadWordBankPageAtIndex(wb, index + 1);
        } else {
            LoadWordBankPageAtIndex(wb, index);
        }
    } else if (index > wb->_page_start_index + wb->_num_loaded_words) {
        if (index >= wb->total_word_count) {
            index = wb->total_word_count;
            LoadWordBankPageAtIndex(wb, index - 1);
        } else {
            LoadWordBankPageAtIndex(wb, index);
        }
    }
    cursor->wb_index = index;
}