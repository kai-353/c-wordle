#include "string.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define WORDLE_GAME_LENGTH 6
#define WORDLE_WORD_LENGTH 5

static int is_word_in_file(String guess) {
    // open file
    FILE *fp = fopen("words.txt", "r");
    if (!fp) {
        perror("Error opening file");
        return 0;
    }

    // determine number of words
    fseek(fp, 0, SEEK_END);
    const long filesize = ftell(fp);
    rewind(fp);
    const int record_size = 6; // 5 chars + newline
    const long num_words = filesize / record_size;

    // binary search
    char buffer[6];
    long low = 0, high = num_words - 1;
    while (low <= high) {
        const long mid = (low + high) / 2;

        fseek(fp, mid * record_size, SEEK_SET);
        fread(buffer, record_size, 1, fp);
        String buffer_string = create_string(buffer, WORDLE_WORD_LENGTH);

        const int cmp = compare_strings(&guess, &buffer_string);
        if (cmp == 0) {
            fclose(fp);
            return 1;
        }
        if (cmp < 0) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }

    fclose(fp);
    return 0;
}

static int validate_guess(const char *guess) {
    for (int i = 0; i < WORDLE_WORD_LENGTH; i++) {
        // if not between a-z, the input is not a valid guess.
        if (guess[i] < 'a' || guess[i] > 'z') return 0;
    }
    return 1;
}

int main() {
    char buf[128];
    for (int i = 0; i < WORDLE_GAME_LENGTH; i++) {
        printf("[%d/%d] Enter guess: ", i + 1, WORDLE_GAME_LENGTH);
        if (!fgets(buf, sizeof buf, stdin)) return 0;

        if (!validate_guess(buf)) {
            puts("Invalid guess. A word must consist of 5 letters (a-z)");
            i--; // don't count invalid input
            continue;
        }

        String guess = create_string(buf, WORDLE_WORD_LENGTH);

        if (!is_word_in_file(guess)) {
            puts("Word does not exist! Try again.");
            i--; // don't count invalid input
            continue;
        }

        print_string(guess);

        free_string(&guess);
    }
    return 0;
}