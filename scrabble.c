#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int scores[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
long word_scoring(string word);

int main(void)
{
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    int score1 = word_scoring(word1);
    int score2 = word_scoring(word2);

    if (score1 > score2)
    {
        printf("Player 1 Wins!\n");
    }

    else if (score2 > score1)
    {
        printf("Player 2 Wins!\n");
    }

    else
    {
        printf("Tie!\n");
    }
}

long word_scoring(string word)
{
    int total_score = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        if (isupper(word[i]))
        {
            total_score += scores[word[i] - 'A'];
        }
        else if (islower(word[i]))
        {
            total_score += scores[word[i] - 'a'];
        }
    }
    return total_score;
}