#include "string.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WORDLE_GAME_LENGTH 6
#define WORDLE_WORD_LENGTH 5

static FILE *open_words_file(void) {
    FILE *fp = fopen("words.txt", "r");
    if (!fp) {
        perror("Error opening file");
    }
    return fp;
}

static long get_word_count(FILE *fp) {
    fseek(fp, 0, SEEK_END);
    const long filesize = ftell(fp);
    rewind(fp);
    const int record_size = WORDLE_WORD_LENGTH + 1; // 5 chars + newline
    return filesize / record_size;
}

static void read_word_at_position(FILE *fp, long position, char *buffer) {
    const int record_size = WORDLE_WORD_LENGTH + 1; // 5 chars + newline
    fseek(fp, position * record_size, SEEK_SET);
    fread(buffer, WORDLE_WORD_LENGTH, 1, fp);
    buffer[WORDLE_WORD_LENGTH] = '\0'; // null-terminate the buffer
}

static int binary_search_word(FILE *fp, const char *word, const long num_words) {
    char buffer[WORDLE_WORD_LENGTH + 1];
    long low = 0, high = num_words - 1;
    
    while (low <= high) {
        const long mid = (low + high) / 2;
        
        read_word_at_position(fp, mid, buffer);
        
        const int cmp = strcmp(word, buffer);
        if (cmp == 0) {
            return 1;
        }
        if (cmp < 0) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    
    return 0;
}

static int is_word_in_file(const char *word) {
    FILE *fp = open_words_file();
    if (!fp) {
        return 0;
    }

    const long num_words = get_word_count(fp);
    const int result = binary_search_word(fp, word, num_words);
    
    fclose(fp);
    return result;
}

static int gen_secret(char *secret) {
    FILE *fp = open_words_file();
    if (!fp) {
        return 0;
    }

    const long num_words = get_word_count(fp);
    const int index = rand() % (num_words + 1);

    read_word_at_position(fp, index, secret);

    fclose(fp);
    return 1;
}

static int validate_guess(char *guess) {
    for (int i = 0; i < WORDLE_WORD_LENGTH; i++) {
        // if not between a-z, the input is not a valid guess.
        if (guess[i] < 'a' || guess[i] > 'z') return 0;
    }
    guess[WORDLE_WORD_LENGTH] = '\0'; // null-terminate the buffer

    return 1;
}

int main() {
    srand(time(NULL));
    char secret[WORDLE_WORD_LENGTH + 1];
    gen_secret(secret);

    char buf[128];
    for (int i = 0; i < WORDLE_GAME_LENGTH; i++) {
        printf("[%d/%d] Enter guess: ", i + 1, WORDLE_GAME_LENGTH);
        if (!fgets(buf, sizeof buf, stdin)) return 0;

        if (!validate_guess(buf)) {
            puts("Invalid guess. A word must consist of 5 letters (a-z)");
            i--; // don't count invalid input
            continue;
        }

        if (!is_word_in_file(buf)) {
            puts("Word does not exist! Try again.");
            i--; // don't count invalid input
            continue;
        }
    }
    return 0;
}