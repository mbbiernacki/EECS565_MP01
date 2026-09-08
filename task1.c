// TASK 1: Write a program to implement the Vigenere Cipher.
/*
Encryption: EK(m) = m + K mod 26
Decryption: DK(m) = m - K mod 26
m is the input message, K is the encryption/decryption key

Note:

Assume the plaintext message contains letters only. You don’t need to distinguish between
upper- and lower-case letters. That is, both "A" and "a" must be converted to "0" (or "1") in your
program. If the input has both upper- and lower-case letters, treat them the same.

You don’t need to deal with the space in the plaintext. If the input has spaces, remove them.

You don’t need to check the validity of the input. Assume the input is always valid.
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// function prototype
void cleanString(char *str);

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
            // get the key_index, using modulo to ensure starting at the beginning
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
            // get the key_index, using modulo to ensure starting at the beginning
            int kIndex = i % kLen;

            // map the characters to 0-25
            int m = message[i] - 'A';
            int K = key[kIndex] - 'A';

            // cipher math for encryption (given in program instructions)
            int decrypted = (m - K + 26) % 26;

            // map back to an ASCII character and overwrite the original string
            message[i] = decrypted + 'A';

        }

        // output the ciphertext
        printf("%s\n", message);
    }
    // otherwise, mode is not E or D, print appropriate error message
    else{
        printf("ERROR: ./task1 <E/D> <message> <key>\n");
        return 1;
    }

    return 0;
}




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


