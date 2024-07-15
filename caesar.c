#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if(argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Define key
    string key = argv[1];

    // Make sure every character in argv[1] is a digit
    int length_key = strlen(key);
    for(int i = 0; i < length_key; i++)
    {
        if(!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Convert argv[1] from a `string` to an `int`
    int k = atoi(argv[1]);

    // Prompt user for plaintext
    string plaintext = get_string("Plaintext: ");

    // For each character in the plaintext:
        // Rotate the character if it's a letter
    printf("Ciphertext: ");
    int length_plaintext = strlen(plaintext);
    for(int j = 0; j < length_plaintext; j++)
    {
        if(isupper(plaintext[j]))
        {
            printf("%c", (((plaintext[j] - 65) + k) %26) + 65);
        }

        else if(islower(plaintext[j]))
        {
            printf("%c", (((plaintext[j] - 97) + k) %26) + 97);
        }

        else
        {
            printf("%c", plaintext[j]);
        }
    }
    printf("\n");
}
