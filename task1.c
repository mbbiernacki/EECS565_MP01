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
