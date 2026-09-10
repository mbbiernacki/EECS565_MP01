// EECS 565: Mini Project 01
// Marie Biernacki
// TASK 3: Implement brute-force password cracker (MODIFIED FOR OPTIMIZATION)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#define MAX_WORDS 200000 // number of words in dictionary
#define MAX_WORD_LEN 256

char dictionary[MAX_WORDS][MAX_WORD_LEN];
int dict_size = 0;

// comparison function for bsearch
int compareWords(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

// function to load the dictionary into memory before testing keys
void loadDictionary() {
    FILE *file = fopen("MP1_dict.txt", "r");
    if (!file) {
        printf("Error opening MP1_dict.txt\n");
        exit(1);
    }
    
    while (fscanf(file, "%s", dictionary[dict_size]) != EOF) {
        dict_size++;

        // safety bound to prevent buffer overflows
        if (dict_size >= MAX_WORDS) {
            break; 
        }

    }
    fclose(file);
    
    qsort(dictionary, dict_size, MAX_WORD_LEN, compareWords);
    
}

// function to check if a word exists using binary search
bool isWordInDict(char *word) {
    void *result = bsearch(word, dictionary, dict_size, MAX_WORD_LEN, compareWords);
    return result != NULL;
}

// function to conduct the brute force search, using recursion
void bruteForce(char *ciphertext, int *mappedCipher, int kLen, int fwLen, char *currentKey, int keyIndex) {
    // Base Case: The key is fully generated
    if (keyIndex == kLen) {
        currentKey[kLen] = '\0'; // Null-terminate the candidate key
        
        char firstWord[256];
        
       // OPTIMIZATION
        for (int i = 0; i < fwLen; i++) {
            int kIndex = i % kLen;
            int m = mappedCipher[i]; // Use the pre-calculated array!
            int K = currentKey[kIndex] - 'A';

            // NO MORE MODULO: Subtraction is significantly faster for the CPU
            int decrypted = m - K;
            if (decrypted < 0) {
                decrypted += 26; 
            }

            firstWord[i] = decrypted + 'A';
        }
        
        // add the null terminator to the end of the firstWord
        firstWord[fwLen] = '\0';
        
        // check if the decrypted first word is in dictionary
        if (isWordInDict(firstWord)) {
            // if yes, decrypt full ciphertext using the key
            int fullLen = strlen(ciphertext);
            char fullPlaintext[4096];

            for (int i = 0; i < fullLen; i++) {
                int kIndex = i % kLen;
                int m = ciphertext[i] - 'A';
                int K = currentKey[kIndex] - 'A';
                
                int decrypted = (m - K + 26) % 26;
                fullPlaintext[i] = decrypted + 'A';
            }
            // add null terminator to end of plaintext
            fullPlaintext[fullLen] = '\0';

            // print the resulting full plaintext and the currentKey
            printf("\nKey: %s | Plaintext: %s\n", currentKey, fullPlaintext);
            
        }
        return;
    }

    // Recursive Step: Loop through A-Z for the current key position
    for (char c = 'A'; c <= 'Z'; c++) {
        currentKey[keyIndex] = c;
        bruteForce(ciphertext, mappedCipher, kLen, fwLen, currentKey, keyIndex + 1);
    }
}

int main(int argc, char *argv[]) {
    // check for correct number of arguments
    if (argc != 4){
        printf("ERROR: ./task2 <ciphertext> <keylength> <firstWordLength>\n");
        return 1;
    }
    
    // load arguments into respective variables, converting string to integers
    char *ciphertext = argv[1];
    int kLen = atoi(argv[2]);
    int fwLen = atoi(argv[3]);

    // load dictionary first for efficiency
    loadDictionary();

    // set up key buffer
    char currentKey[256];


    // OPTIMIZATION: Pre-calculate the integer values of the ciphertext
    int mappedCipher[256];
    int cipherLen = strlen(ciphertext);
    for(int i = 0; i < cipherLen; i++){
        mappedCipher[i] = ciphertext[i] - 'A';
    }


    // start the clock (for task 3 time reporting)
    clock_t start = clock();

    // call brute force function with arguments
    bruteForce(ciphertext, mappedCipher, kLen, fwLen, currentKey, 0);

    // stop the clock
    clock_t end = clock();

    // calculate and print the time
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nExecution time: %f seconds\n", time_spent);
 
    return 0;
}