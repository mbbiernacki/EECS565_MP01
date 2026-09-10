// EECS 565: Mini Project 01
// Marie Biernacki
// TASK 2: Implement brute-force password cracker

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

// comparison function for bsearch and qsort
// required by standard library to know how to sort strings alphabetically
int compareWords(const void *a, const void *b) {
    // returns negative, zero, or positive to dictate alphabetical order
    return strcmp((const char *)a, (const char *)b);
}

// function to load the dictionary into memory before testing keys
void loadDictionary() {
    // open dictionary file in read mode
    FILE *file = fopen("MP1_dict.txt", "r");
    if (!file) {
        // print error and exit if file is missing
        printf("Error opening MP1_dict.txt\n");
        exit(1);
    }
    // read words until the end of the file
    while (fscanf(file, "%s", dictionary[dict_size]) != EOF) {
        dict_size++;

        // safety bound to prevent buffer overflows
        if (dict_size >= MAX_WORDS) {
            break; 
        }

    }
    // close file to free system resources
    fclose(file);
    
    // sort array using c standard library quicksort
    // optimizes code, required for binary search to work
    qsort(dictionary, dict_size, MAX_WORD_LEN, compareWords);
    
}

// function to check if a word exists using binary search
bool isWordInDict(char *word) {
    // bsearch cuts search space in half at each step
    // returns a generic void pointer to memory address if found, otherwise it returns a null pointer
    void *result = bsearch(word, dictionary, dict_size, MAX_WORD_LEN, compareWords);
    
    // return true if result is not null, meaning the word was found
    return result != NULL;
}

// function to conduct the brute force search, using recursion
void bruteForce(char *ciphertext, int kLen, int fwLen, char *currentKey, int keyIndex) {
    // base case where the key is fully generated
    if (keyIndex == kLen) {
        currentKey[kLen] = '\0'; // null-terminate the candidate key
        
        // hardcode array size to avoid slow memory allocation during recursion
        char firstWord[256];
        
        // similar for loop logic from task 1
        for (int i = 0; i < fwLen; i++){
            // wrap the key index using modulo to ensure starting at the beginning
            int kIndex = i % kLen;

            // map the characters to 0-25
            int m = ciphertext[i] - 'A';
            int K = currentKey[kIndex] - 'A';

            // cipher math for decryption
            int encrypted = (m - K + 26) % 26;

            // map back to an ASCII character and store in firstWord array
            firstWord[i] = encrypted + 'A';

        }

        // add the null terminator to the end of the firstWord
        firstWord[fwLen] = '\0';
        
        // check if the decrypted firstWord is in dictionary
        if (isWordInDict(firstWord)) {
            // if yes, decrypt full ciphertext using the key
            int fullLen = strlen(ciphertext);
            
            // hardcode large buffer, avoids malloc speed penalty
            char fullPlaintext[4096];

            // loop through enture ciphertext length
            for (int i = 0; i < fullLen; i++) {
                // wrap key index using modulo to ensure starting at beginning
                int kIndex = i % kLen;
                
                // map characters to 0-25
                int m = ciphertext[i] - 'A';
                int K = currentKey[kIndex] - 'A';
                
                // decrypt and prevent negative modulo results
                int decrypted = (m - K + 26) % 26;

                // convert back to ASCII and save to plaintext array
                fullPlaintext[i] = decrypted + 'A';
            }

            // add null terminator to end of plaintext
            fullPlaintext[fullLen] = '\0';

            // print the resulting full plaintext and the currentKey
            printf("\nKey: %s | Plaintext: %s\n", currentKey, fullPlaintext);
            
        }
        return;
    }

    // recursive step to loop through A-Z for the current key position
    for (char c = 'A'; c <= 'Z'; c++) {
        currentKey[keyIndex] = c;
        bruteForce(ciphertext, kLen, fwLen, currentKey, keyIndex + 1);
    }
}

// main function to run the program, accepting arguments in the terminal from the user
int main(int argc, char *argv[]) {
    
    // if statement checks only 4 arguments are passed
    if (argc != 4){
        // error message explaining correct format to user to run the program
        printf("ERROR: ./task2 <ciphertext> <keylength> <firstWordLength>\n");
        return 1;
    }
    
    // otherwise extract arguments from the user, converting string to integers for kLen and fwLen
    char *ciphertext = argv[1];
    int kLen = atoi(argv[2]);
    int fwLen = atoi(argv[3]);

    // load dictionary first
    loadDictionary();

    // set up key buffer
    char currentKey[256];

    // start the clock (for task 3 time reporting)
    clock_t start = clock();

    // call brute force function
    bruteForce(ciphertext, kLen, fwLen, currentKey, 0);

    // stop the clock
    clock_t end = clock();

    // calculate and print the time
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nExecution time: %f seconds\n", time_spent);
 
    return 0;
}