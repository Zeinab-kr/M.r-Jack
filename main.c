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
    char suspect[20];
    struct tiles *up;
    struct tiles *down;
    struct tiles *right;
    struct tiles *left;
};
struct tiles *center;
struct data cards[9];

// prototypes
void define_cards(struct data cards[]);
void create_map(int wall[], int tile_numbers[], struct data cards[]);
void print_map(int wall[]);

int main()
{
    int choice;
    define_cards(cards);// define characters and their hourglass(es)

    int card_numbers[9];
    int tile_numbers[9];

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
            shuffle_cards(tile_numbers);

            for (int i = 0; i < 9; i++) {
                wall[i] = rotation(); // randomly choose rotation of each card
            }

            create_map(wall, tile_numbers, cards);
            print_map(wall);
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

void create_map(int wall[], int tile_numbers[], struct data cards[])
{
    // centric tile
    center = (struct tiles *)malloc(sizeof(struct tiles));
    strcpy(center->suspect, cards[tile_numbers[4]].name);

    if (wall[4] != UP) {
        center->up = (struct tiles *)malloc(sizeof(struct tiles));
        strcpy(center->up->suspect, cards[tile_numbers[1]].name);
    } else {center->up = NULL;}

    if (wall[4] != DOWN) {
        center->down = (struct tiles *)malloc(sizeof(struct tiles));
        strcpy(center->down->suspect, cards[tile_numbers[7]].name);
    } else {center->down = NULL;}

    if (wall[4] != RIGHT) {
        center->right = (struct tiles *)malloc(sizeof(struct tiles));
        strcpy(center->right->suspect, cards[tile_numbers[5]].name);
    } else {center->right = NULL;}

    if (wall[4] != LEFT) {
        center->left = (struct tiles *)malloc(sizeof(struct tiles));
        strcpy(center->left->suspect, cards[tile_numbers[3]].name);
    } else {center->left = NULL;}

    // upper row
    if (wall[1] != RIGHT) {
        center->up->right = (struct tiles *)malloc(sizeof(struct tiles));
        strcpy(center->up->right->suspect, cards[tile_numbers[2]].name);
    } else {center->up->right = NULL;}

    if (wall[1] != LEFT) {
        center->up->left = (struct tiles *)malloc(sizeof(struct tiles));
        strcpy(center->up->left->suspect, cards[tile_numbers[0]].name);
    } else {center->up->right = NULL;}

    // lower row
    if (wall[7] != RIGHT) {
        center->down->right = (struct tiles *)malloc(sizeof(struct tiles));
        strcpy(center->down->right, cards[tile_numbers[8]].name);
    } else {center->down->right = NULL;}

    if (wall[7] != LEFT) {
        center->down->left = (struct tiles *)malloc(sizeof(struct tiles));
        strcpy(center->down->left, cards[tile_numbers[6]].name);
    } else {center->down->left = NULL;}
}

void print_map(int wall[])
{
    // first row
    print_row(wall, 1);
    // second row
    print_row(wall, 2);
    // third row
    print_row(wall, 3);
}

void print_row(int wall[], int row)
{
    for (int i = (row-1)*3; i < row*3; i++) {
        if (wall[i] == DOWN) {
            printf("    |    ");
        }
        else {
            for (int j = 0; j < 9; j++) {
                printf(" ");
            }
        }
    }
    puts("");

    for (int i = (row-1)*3; i < row*3; i++) {
        if (wall[i] == DOWN) {
            printf("    |    ");
        }
        else {
            for (int j = 0; j < 9; j++) {
                printf(" ");
            }
        }
    }
    puts("");

    for (int i = (row-1)*3; i < row*3; i++) {
        if (wall[i] == RIGHT) {
            printf("----|    ");
        }
        else if (wall[i] == LEFT) {
            printf("    |----");
        }
        else {
            printf("---- ----");
        }
    }
    puts("");

    for (int i = (row-1)*3; i < row*3; i++) {
        if (wall[i] == UP) {
            printf("    |    ");
        }
        else {
            for (int j = 0; j < 9; j++) {
                printf(" ");
            }
        }
    }
    puts("");

    for (int i = (row-1)*3; i < row*3; i++) {
        if (wall[i] == UP) {
            printf("    |    ");
        }
        else {
            for (int j = 0; j < 9; j++) {
                printf(" ");
            }
        }
    }
    puts("");
}
