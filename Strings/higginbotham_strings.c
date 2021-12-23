//Foster Higginbotham's File.
//This project will demonstrate the ability to write and apply C code that can process and manipulate strings. 

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int menu_choice();
void palindrome_checker();
void leet_speak();
void encrypt();
void decrypt();
char decrypt_alphabet_position(char character);
char encrypt_alphabet_position(char character);

int main(void) {
    /*
     * From here, we can start with our menu. We put the code in an infinite loop by checking if 0 is equal to 0,
     * which it is. The menu choices are based on the assignment.
    */
    do
    {
        int choice = menu_choice();

        if (choice == 1) {
            palindrome_checker();
        }
        else if (choice == 2) {
            leet_speak();
        }
        else if (choice == 3) {
            encrypt();
        }
        else if (choice == 4) {
            decrypt();
        }
        else if (choice == -1) {
            printf("Goodbye for now.\n");
            break;
        }
        else {
            printf("Invalid choice.\n");
        }
    } while (0 == 0);

    return 0;
}

/*
 * This function prompts the user to enter his choice for the menu. This is separately done to make the main more organized.
 * We can return the users choice if they enter a valid choice, if not, we are returned zero. Note this will return 0 if you enter
 * a number not in bounds, or if you enter a string since atoi() will return 0.
 * Atoi() will be used a lot since it fits what we are doing, making strings into integers. It is also good since it will
 * automatically check if a string has been entered and return 0 if so.
*/

int menu_choice() {
    char input[256];
    int choice;

    printf("What function do you want to do?\n1 = Palindrome Checker\n2 = 1337 Sp3ak Converter\n3 = Encrypt Message\n4 = UnEncrypt Message\n-1 = Quit\n\n");

    scanf("%s", input);
    choice = atoi(input);

    if (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == -1) {
        return choice;
    }
    return 0;
}

/*
 * Make our character stream buffers (size 256 just in case) for our temporary, fixed, and incoming input.
 * (Fixed is the input set to only lowercase characters for the sake of comparison, while input is just the incoming
 * input from the user, something we want to keep original. Temporary should be obviously left for our temporary string
 * reversal storage.)
 * Scan in the user's input and get the size of the string, then we can then change all of our original input to lower.
 * After that, begin setting up the temporary array with the reverse characters with a for loop and an extra outside
 * counter. We can do a string comparison after between our reversed and fixed strings and that will give us our answer!
 */

void palindrome_checker() {
    char input[256] , fixed[256], temp[256];
    int j, comparison;

    printf("Checking for Palindrome... please enter a word\n");

    scanf("%s", input);
    int size = strlen(input);

    for (int i = 0; i < size; i++) {
        fixed[i] = tolower(input[i]);
        fixed[i + 1] = '\0';
    }

    j = size - 1;
    for (int i = 0; i < size; i++) {
        temp[i] = fixed[j];
        j--;
        temp[i + 1] = '\0';
    }

    comparison = strcmp(fixed, temp);
    if (comparison == 0) {
        printf("\"%s\" is a Palindrome!!\n\n", input);
    }
    else {
        printf("\"%s\" aint a palindrome!!\n\n", input);
    }
}

/*
 * We need to first setup our input buffer stream as well as a flag to differentiate between leet and normal words.
 * We can scan our input from the user and check if it is leet or not. From there we can create our temp array with
 * size of the input word. Based on if its a leet word or not (checking our flag status, 1 vs 0), run a for loop over
 * the word and convert to the proper format. From there, just print our word!
 */

void leet_speak() {
    char input[256];
    int leet_word_flag = 0;

    printf("Leet Speak Conversion Tool.... please enter a word\n");

    scanf("%s", input);
    int size = strlen(input);

    for (int i = 0; i < size; i++) {
        if (isdigit(input[i])) {
            leet_word_flag = 1;
            break;
        }
    }

    char temp[size];

    if (leet_word_flag) {
        printf("1337 word detected.\n");
        for (int i = 0; i < size; i++) {
            if (input[i] == '4') {
                temp[i] = 'a';
            }
            else if (input[i] == '8') {
                temp[i] = 'b';
            }
            else if (input[i] == '3') {
                temp[i] = 'e';
            }
            else if (input[i] == '6') {
                temp[i] = 'g';
            }
            else if (input[i] == '1') {
                temp[i] = 'l';
            }
            else if (input[i] == '0') {
                temp[i] = 'o';
            }
            else if (input[i] == '5') {
                temp[i] = 's';
            }
            else if (input[i] == '7') {
                temp[i] = 't';
            }
            else {
                temp[i] = input[i];
            }
        }
        temp[size] = '\0';
        printf("New Word: %s\n\n", temp);
    }
    else {
        printf("Normal word detected.\n");
        for (int i = 0; i < size; i++) {
            if (input[i] == 'a' || input[i] == 'A'){
                temp[i] = '4';
            }
            else if (input[i] == 'b' || input[i] == 'B'){
                temp[i] = '8';
            }
            else if (input[i] == 'e' || input[i] == 'E'){
                temp[i] = '3';
            }
            else if (input[i] == 'g' || input[i] == 'G'){
                temp[i] = '6';
            }
            else if (input[i] == 'l' || input[i] == 'L'){
                temp[i] = '1';
            }
            else if (input[i] == 'o' || input[i] == 'O'){
                temp[i] = '0';
            }
            else if (input[i] == 's' || input[i] == 'S'){
                temp[i] = '5';
            }
            else if (input[i] == 't' || input[i] == 'T'){
                temp[i] = '7';
            }
            else {
                temp[i] = input[i];
            }
        }
        temp[size] = '\0';
        printf("1337 Word: %s\n\n", temp);
    }
}

/*
 * [This applies to both encrypt and decrypt!]
 *
 * First we can start by getting how many words we will be encoding/decoding. After we can make out input and result
 * arrays based on this size. After, we can see how many words we are scanning in based on our word size (like before).
 * A 2D array is needed here to hold all the words and their separate chars. Using the 2D array filled with words,
 * we can initiate a nested loop to go through every char in every word in input, then using the
 * encrypt_alphabet_position() we can assign the letter we have to the results array. Dont forget to add a null
 * character and display our encoded message!
 */

void encrypt() {
    char word_size[12];

    printf("How many words is your message?\n");
    scanf("%s", word_size);
    int words = atoi(word_size);

    char input[words][256];
    char result[words][256];

    printf("Type the message now:\n");

    if (words == 1) {
        scanf("%s", input[0]);
    }
    else if (words == 2) {
        scanf("%s %s", input[0], input[1]);
    }
    else if (words == 3) {
        scanf("%s %s %s", input[0], input[1], input[2]);
    }
    else if (words == 4) {
        scanf("%s %s %s %s", input[0], input[1], input[2], input[3]);
    }
    else if (words == 5) {
        scanf("%s %s %s %s %s", input[0], input[1], input[2], input[3], input[4]);
    }
    else if (words == 6) {
        scanf("%s %s %s %s %s %s", input[0], input[1], input[2], input[3], input[4], input[5]);
    }
    else if (words == 7) {
        scanf("%s %s %s %s %s %s %s", input[0], input[1], input[2], input[3], input[4], input[5], input[6]);
    }
    else if (words == 8) {
        scanf("%s %s %s %s %s %s %s %s", input[0], input[1], input[2], input[3], input[4], input[5], input[6], input[7]);
    }
    else if (words == 9) {
        scanf("%s %s %s %s %s %s %s %s %s", input[0], input[1], input[2], input[3], input[4], input[5], input[6], input[7], input[8]);
    }
    else if (words == 10) {
        scanf("%s %s %s %s %s %s %s %s %s %s", input[0], input[1], input[2], input[3], input[4], input[5], input[6], input[7], input[8], input[9]);
    }

    for (int i = 0; i < words; i++) {
        for (int j = 0; j < strlen(input[i]); j++) {
            result[i][j] = encrypt_alphabet_position(input[i][j]);
            result[i][j + 1] = '\0';
        }
    }

    printf("Encoded Message: ");
    for (int i = 0; i < words; i++)
    {
        printf("%s ", result[i]);
    }
    printf("\n\n");
}

void decrypt() {
    char word_size[12];

    printf("How many words is your encrypted message?\n");
    scanf("%s", word_size);
    int words = atoi(word_size);

    char input[words][256];
    char result[words][256];

    printf("Type the message now:\n");

    if (words == 1) {
        scanf("%s", input[0]);
    }
    else if (words == 2) {
        scanf("%s %s", input[0], input[1]);
    }
    else if (words == 3) {
        scanf("%s %s %s", input[0], input[1], input[2]);
    }
    else if (words == 4) {
        scanf("%s %s %s %s", input[0], input[1], input[2], input[3]);
    }
    else if (words == 5) {
        scanf("%s %s %s %s %s", input[0], input[1], input[2], input[3], input[4]);
    }
    else if (words == 6) {
        scanf("%s %s %s %s %s %s", input[0], input[1], input[2], input[3], input[4], input[5]);
    }
    else if (words == 7) {
        scanf("%s %s %s %s %s %s %s", input[0], input[1], input[2], input[3], input[4], input[5], input[6]);
    }
    else if (words == 8) {
        scanf("%s %s %s %s %s %s %s %s", input[0], input[1], input[2], input[3], input[4], input[5], input[6], input[7]);
    }
    else if (words == 9) {
        scanf("%s %s %s %s %s %s %s %s %s", input[0], input[1], input[2], input[3], input[4], input[5], input[6], input[7], input[8]);
    }
    else if (words == 10) {
        scanf("%s %s %s %s %s %s %s %s %s %s", input[0], input[1], input[2], input[3], input[4], input[5], input[6], input[7], input[8], input[9]);
    }

    for (int i = 0; i < words; i++) {
        for (int j = 0; j < strlen(input[i]); j++) {
            result[i][j] = decrypt_alphabet_position(input[i][j]);
            result[i][j + 1] = '\0';
        }
    }

    printf("Encoded Message: ");
    for (int i = 0; i < words; i++)
    {
        printf("%s ", result[i]);
    }
    printf("\n\n");
}

/*
 * Simple functions to get a character, evaluate it with a simple switch statement, and then return the character
 * we need. If encryption, go three letters back. If decryption, go forward 3 letters.
 */

char encrypt_alphabet_position(char character)
{
    switch (character) {
        case 'a':
            return 'x';
        case 'A':
            return 'X';
        case 'b':
            return 'y';
        case 'B':
            return 'Y';
        case 'c':
            return 'z';
        case 'C':
            return 'Z';
        case 'd':
            return 'a';
        case 'D':
            return 'A';
        case 'e':
            return 'b';
        case 'E':
            return 'B';
        case 'f':
            return 'c';
        case 'F':
            return 'C';
        case 'g':
            return 'd';
        case 'G':
            return 'D';
        case 'h':
            return 'e';
        case 'H':
            return 'E';
        case 'i':
            return 'f';
        case 'I':
            return 'F';
        case 'j':
            return 'g';
        case 'J':
            return 'G';
        case 'k':
            return 'h';
        case 'K':
            return 'H';
        case 'l':
            return 'i';
        case 'L':
            return 'I';
        case 'm':
            return 'j';
        case 'M':
            return 'J';
        case 'n':
            return 'k';
        case 'N':
            return 'K';
        case 'o':
            return 'l';
        case 'O':
            return 'L';
        case 'p':
            return 'm';
        case 'P':
            return 'M';
        case 'q':
            return 'n';
        case 'Q':
            return 'N';
        case 'r':
            return 'o';
        case 'R':
            return 'O';
        case 's':
            return 'p';
        case 'S':
            return 'P';
        case 't':
            return 'q';
        case 'T':
            return 'Q';
        case 'u':
            return 'r';
        case 'U':
            return 'R';
        case 'v':
            return 's';
        case 'V':
            return 'S';
        case 'w':
            return 't';
        case 'W':
            return 'T';
        case 'x':
            return 'u';
        case 'X':
            return 'U';
        case 'y':
            return 'v';
        case 'Y':
            return 'V';
        case 'z':
            return 'w';
        case 'Z':
            return 'W';
    }
}

char decrypt_alphabet_position(char character)
{
    switch (character) {
        case 'a':
            return 'd';
        case 'A':
            return 'D';
        case 'b':
            return 'e';
        case 'B':
            return 'E';
        case 'c':
            return 'f';
        case 'C':
            return 'F';
        case 'd':
            return 'g';
        case 'D':
            return 'G';
        case 'e':
            return 'h';
        case 'E':
            return 'H';
        case 'f':
            return 'i';
        case 'F':
            return 'I';
        case 'g':
            return 'j';
        case 'G':
            return 'J';
        case 'h':
            return 'k';
        case 'H':
            return 'K';
        case 'i':
            return 'l';
        case 'I':
            return 'L';
        case 'j':
            return 'm';
        case 'J':
            return 'M';
        case 'k':
            return 'n';
        case 'K':
            return 'N';
        case 'l':
            return 'o';
        case 'L':
            return 'O';
        case 'm':
            return 'p';
        case 'M':
            return 'P';
        case 'n':
            return 'q';
        case 'N':
            return 'Q';
        case 'o':
            return 'r';
        case 'O':
            return 'R';
        case 'p':
            return 's';
        case 'P':
            return 'S';
        case 'q':
            return 't';
        case 'Q':
            return 'T';
        case 'r':
            return 'u';
        case 'R':
            return 'U';
        case 's':
            return 'v';
        case 'S':
            return 'V';
        case 't':
            return 'w';
        case 'T':
            return 'W';
        case 'u':
            return 'x';
        case 'U':
            return 'X';
        case 'v':
            return 'y';
        case 'V':
            return 'Y';
        case 'w':
            return 'z';
        case 'W':
            return 'Z';
        case 'x':
            return 'a';
        case 'X':
            return 'A';
        case 'y':
            return 'b';
        case 'Y':
            return 'B';
        case 'z':
            return 'c';
        case 'Z':
            return 'C';
    }
}
