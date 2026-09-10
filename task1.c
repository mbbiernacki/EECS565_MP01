// EECS 565: Mini Project 01
// Marie Biernacki
// TASK 1: Implement the Vigenère Cipher

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// function to clean the string input
void cleanString(char *str){
    
    // set the writeIndex to 0
    int writeIndex = 0;

    // loop through string until null terminator
    for (int readIndex = 0; str[readIndex] != '\0'; readIndex++){

        // isalpha checks if character is a letter, automatically ignoring spaces
        if (isalpha(str[readIndex])){
            // convert to uppercase and write to new position
            str[writeIndex] = toupper(str[readIndex]);
            writeIndex++;
        }
    }

    // end the clean string with a null terminator
    str[writeIndex] = '\0';

}


// main function to run the program, accepting arguments in the terminal from the user
int main(int argc, char *argv[]){

    // if statement checks only 4 arguments are passed
    if (argc != 4){
        // error message explaining correct format to user to run the program
        printf("ERROR: ./task1 <E/D> <message> <key>\n");
        return 1;
    }

    // otherwise, extract the arguments from the user
    char *mode = argv[1];
    char *message = argv[2];
    char *key = argv[3];

    // clean the message and the key, calling the cleanString function
    cleanString(message);
    cleanString(key);

    // store message length and key length respectively
    int mLen = strlen(message);
    int kLen = strlen(key);
    

    // if the mode is E, encrypt
    if (toupper(mode[0]) == 'E'){

        for (int i = 0; i < mLen; i++){
            // wrap the key index using modulo to ensure starting at the beginning
            int kIndex = i % kLen;

            // map the characters to 0-25
            int m = message[i] - 'A';
            int K = key[kIndex] - 'A';

            // cipher math for encryption (given in program instructions)
            int encrypted = (m + K) % 26;

            // map back to an ASCII character and overwrite the original string
            message[i] = encrypted + 'A';

        }

        // output the ciphertext
        printf("%s\n", message);

    }

    // else if the mode is D, decrypt
    else if (toupper(mode[0]) == 'D'){
         for (int i = 0; i < mLen; i++){
            // wrap the key index using modulo to ensure starting at the beginning
            int kIndex = i % kLen;

            // map the characters to 0-25
            int m = message[i] - 'A';
            int K = key[kIndex] - 'A';

            // cipher math for decryption (given in program instructions)
            // +26 prevents negative results before modulo
            int decrypted = (m - K + 26) % 26;

            // map back to an ASCII character and overwrite the original string
            message[i] = decrypted + 'A';

        }

        // output the plaintext
        printf("%s\n", message);
    }
    // otherwise, mode is not E or D, print appropriate error message
    else{
        printf("ERROR: ./task1 <E/D> <message> <key>\n");
        return 1;
    }

    return 0;
}

