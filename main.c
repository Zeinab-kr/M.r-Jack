#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <windows.h>
#include "instructions.h"
#include "shuffle.h"

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

struct data {
    char name[20];
    int hourglass;
};
struct tiles {
    struct data suspect;
    struct tiles *up;
    struct tiles *down;
    struct tiles *right;
    struct tiles *left;
};
struct data cards[9];

// prototypes
void define_cards(struct data cards[]);

int main()
{
    int choice;
    define_cards(cards);// define characters and their hourglass(es)

    int card_numbers[9];

    welcome();

    while (choice != 3) {
        game_menu();
        scanf("%d", &choice);
        puts("");

        if (choice == 1) {
            int char_choice;

            // M.r Jack's character
            shuffle_cards(card_numbers);
            int jack_char = card_numbers[0];
            printf("M.r Jack can see his character after 5 seconds\n");
            printf("Holmes must close his eyes\n");
            Sleep(5000);
            printf("Your character is %s\n", cards[jack_char].name);

            // map
            int wall[9];
            shuffle_cards(card_numbers);

            for (int i = 0; i < 9; i++) {
                wall[i] = rotation(); // randomly choose rotation of each card
            }
        }
        else if (choice == 2) {
            ;
        }
        else if (choice == 3) {
            break;
        }
        else {
            printf("Invalid choice!\n\n");
        }
    }
}

void define_cards(struct data cards[])
{
    strcpy(cards[0].name, "John Smith");
    cards[0].hourglass = 1;

    strcpy(cards[1].name, "Insp. Lestrade");
    cards[1].hourglass = 0;

    strcpy(cards[2].name, "Miss Stealthy");
    cards[2].hourglass = 1;

    strcpy(cards[3].name, "Sgt Goodly");
    cards[3].hourglass = 0;

    strcpy(cards[4].name, "William Gull");
    cards[4].hourglass = 1;

    strcpy(cards[5].name, "Jeremy Bert");
    cards[5].hourglass = 1;

    strcpy(cards[6].name, "John Pizer");
    cards[6].hourglass = 1;

    strcpy(cards[7].name, "Joseph Lane");
    cards[7].hourglass = 1;

    strcpy(cards[8].name, "Madame");
    cards[8].hourglass = 2;
}

void create_map()
{

}
