#ifndef PREPARE-GAME_H_INCLUDED
#define PREPARE-GAME_H_INCLUDED

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

void create_map(int wall[], int tile_numbers[])
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
        strcpy(center->down->right->suspect, cards[tile_numbers[8]].name);
    } else {center->down->right = NULL;}

    if (wall[7] != LEFT) {
        center->down->left = (struct tiles *)malloc(sizeof(struct tiles));
        strcpy(center->down->left->suspect, cards[tile_numbers[6]].name);
    } else {center->down->left = NULL;}
}

void print_map(int wall[], int tile_numbers[])
{
    // first row
    print_row(wall, tile_numbers, 1);
    // second row
    print_row(wall, tile_numbers, 2);
    // third row
    print_row(wall, tile_numbers, 3);
}

void print_row(int wall[], int tile_numbers[], int row)
{
    for (int k = 0; k < 3; k++) {
        for (int i = (row-1)*3; i < row*3; i++) {
            if (wall[i] == UP) {
                for (int j = 0; j < 21; j++) {
                    printf(" ");
                }
            }
            else {
                for (int j = 0; j < 10; j++) {
                    printf(" ");
                }
                printf("|");
                for (int j = 0; j < 10; j++) {
                    printf(" ");
                }
            }
        }
        puts("");
    }

    for (int i = (row-1)*3; i < row*3; i++) {
        int len = strlen(cards[tile_numbers[i]].name);
        if (wall[i] == RIGHT) {
            for (int l = 0; l < (int)floor((float)(21-len)/2); l++) {
                printf("-");
            }
            printf("%s", cards[tile_numbers[i]].name);
            for (int l = 0; l < (int)ceil((float)(21-len)/2); l++) {
                printf(" ");
            }
        }
        else if (wall[i] == LEFT) {
            for (int l = 0; l < (int)floor((float)(21-len)/2); l++) {
                printf(" ");
            }
            printf("%s", cards[tile_numbers[i]].name);
            for (int l = 0; l < (int)ceil((float)(21-len)/2); l++) {
                printf("-");
            }
        }
        else {
            for (int l = 0; l < (int)floor((float)(21-len)/2); l++) {
                printf("-");
            }
            printf("%s", cards[tile_numbers[i]].name);
            for (int l = 0; l < (int)ceil((float)(21-len)/2); l++) {
                printf("-");
            }
        }
    }
    puts("");

    for (int k = 0; k < 3; k++) {
        for (int i = (row-1)*3; i < row*3; i++) {
            if (wall[i] == DOWN) {
                for (int j = 0; j < 21; j++) {
                    printf(" ");
                }
            }
            else {
                for (int j = 0; j < 10; j++) {
                    printf(" ");
                }
                printf("|");
                for (int j = 0; j < 10; j++) {
                    printf(" ");
                }
            }
        }
        puts("");
    }
}

#endif // PREPARE-GAME_H_INCLUDED
