## 1. Compiler Information
This project is written in standard C and should be compiled using GCC. To ensure optimal execution speed—which is critical for the brute-force cracking in Task 2, compile the files using the `-O2` optimization flag.

## 2. File Directory Requirements
Ensure the following files are located in the same root directory before compiling or executing:
* `task1.c`: encryption and decryption
* `task2.c`: brute-force password cracking
* `MP1_dict.txt`: dictionary file required by `task2` to validate decrypted words

---

## 3. Running the Programs

### Task 1: Encryption & Decryption
Compile the source file from your integrated terminal:
```bash
gcc -O2 task1.c -o task1
```

Execute the program by providing the mode (E for Encrypt, D for Decrypt), the message, and the key.
Always wrap the message in quotation marks to prevent the terminal from misinterpreting spaces or hidden line-break characters.

Encryption Example:
```bash
./task1 E "THEQUICKBROWNFOX" "KEY"
```
Decryption Example:
```bash
./task1 D "XJOUWKODFPYYRRYB" "KEY"
```

### Task 2: Brute Force Password Cracker
Compile the source file from your integrated terminal:
```bash
gcc -O2 task2.c -o task2
```

Execute the program by providing the ciphertext, the known key length, and known length of the first word.
Always wrap the ciphertext in quotation marks to prevent the terminal from misinterpreting spaces or hidden line-break characters.

Execution Example:
```bash
./task2 "MSOKKJCOSXOEEKDTOSLGFWCMCHSUSGX" 2 6
```



