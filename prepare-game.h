#ifndef PREPARE-GAME_H_INCLUDED
#define PREPARE-GAME_H_INCLUDED

#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

struct data {
    char name[20];
    int hourglass;
};
struct data cards[9];

struct tiles {
    int number;
    int wall;
    char suspect[20];
    struct tiles *next;
};
struct tiles *head = NULL;
struct tiles *tail = NULL;

struct char_tokens {
    char name[10];
    int side;
    int block;
};
struct char_tokens detective[3];

struct action_tokens {
    char name[2][10];
    int number[2];
};
struct action_tokens action[4];

void define_cards()
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

void define_detectives()
{
    // Holmes
    strcpy(detective[0].name, "Holmes");
    detective[0].side = LEFT;
    detective[0].block = 1;
    // Watson
    strcpy(detective[1].name, "Watson");
    detective[1].side = RIGHT;
    detective[1].block = 1;
    // Toby
    strcpy(detective[2].name, "Toby");
    detective[2].side = DOWN;
    detective[2].block = 2;
}

void define_action_tokens()
{
    strcpy(action[0].name[0], "Holmes");
    strcpy(action[0].name[1], "Suspects");
    action[0].number[0] = 0;
    action[0].number[1] = 1;

    strcpy(action[1].name[0], "Watson");
    strcpy(action[1].name[1], "Toby");
    action[1].number[0] = 2;
    action[1].number[1] = 3;

    strcpy(action[2].name[0], "Rotate");
    strcpy(action[2].name[1], "Switch");
    action[2].number[0] = 4;
    action[2].number[1] = 5;

    strcpy(action[3].name[0], "Rotate");
    strcpy(action[3].name[1], "Joker");
    action[3].number[0] = 6;
    action[3].number[1] = 7;
}

void create_map(int wall[])
{
    struct tiles *new_tile = (struct tiles *)malloc(sizeof(struct tiles));
    strcpy(new_tile->suspect, cards[tile_numbers[0]].name);
    new_tile->wall = wall[0];
    new_tile->number = 0;
    head = new_tile;
    tail = head;
    for (int i = 1; i < 9; tail = tail->next, i++) {
        new_tile = (struct tiles *)malloc(sizeof(struct tiles));
        strcpy(new_tile->suspect, cards[tile_numbers[i]].name);
        new_tile->wall = wall[i];
        new_tile->number = i;
        tail->next = new_tile;
        tail->next->next = NULL;
    }
}

void print_row(struct tiles *first, int row)
{
    int i;
    struct tiles *current;
    for (int k = 0; k < 3; k++) {
        for (i = 0; i < 10; i++) {
            printf(" ");
        }
        for (current = first, i = 0; i < 3; current = current->next, i++) {
            if (current->wall == UP) {
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

    int flag = 0;
    for (i = 0; i < 3; i++) {
        if (detective[i].side == LEFT && detective[i].block == row) {
            printf("%-10s", detective[i].name);
            flag = 1;
        }
    }
    if (flag == 0) {
        for (i = 0; i < 10; i++) {
            printf(" ");
        }
    }
    for (current = first, i = 0; i < 3; current = current->next, i++) {
        int len = strlen(current->suspect);
        if (current->wall == RIGHT) {
            for (int j = 0; j < (int)floor((float)(21-len)/2); j++) {
                printf("-");
            }
            printf("%s", current->suspect);
            for (int j = 0; j < (int)ceil((float)(21-len)/2); j++) {
                printf(" ");
            }
        }
        else if (current->wall == LEFT) {
            for (int j = 0; j < (int)floor((float)(21-len)/2); j++) {
                printf(" ");
            }
            printf("%s", current->suspect);
            for (int j = 0; j < (int)ceil((float)(21-len)/2); j++) {
                printf("-");
            }
        }
        else {
            for (int j = 0; j < (int)floor((float)(21-len)/2); j++) {
                printf("-");
            }
            printf("%s", current->suspect);
            for (int j = 0; j < (int)ceil((float)(21-len)/2); j++) {
                printf("-");
            }
        }
    }
    flag = 0;
    for (i = 0; i < 3; i++) {
        if (detective[i].side == RIGHT && detective[i].block == row) {
            printf("%s", detective[i].name);
            flag = 1;
        }
    }
    if (flag == 0) {
        for (i = 0; i < 10; i++) {
            printf(" ");
        }
    }
    puts("");

    for (int k = 0; k < 3; k++) {
        for (i = 0; i < 10; i++) {
            printf(" ");
        }
        for (current = first, i = 0; i < 3; current = current->next, i++) {
            if (current->wall == DOWN) {
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

void print_map()
{
    for (int i = 0; i < 10; i++) {
        printf(" ");
    }
    for (int i = 0; i < 3; i++) {
        if (detective[i].side == UP) {
            for (int j = 0; j < (int)floor((float)((21-strlen(detective[i].name))/2)) + (detective[i].block-1)*21; j++) {
                printf(" ");
            }
            printf("%s", detective[i].name);
        }
    }
    puts("");


    struct tiles *current = head;
    for (int i = 1; i <=3; i++, current = current->next->next->next) {
        print_row(current, i);
    }

    for (int i = 0; i < 10; i++) {
        printf(" ");
    }
    for (int i = 0; i < 3; i++) {
        if (detective[i].side == DOWN) {
            for (int j = 0; j < (int)floor((float)((21-strlen(detective[i].name))/2)) + (detective[i].block-1)*21; j++) {
                printf(" ");
            }
            printf("%s", detective[i].name);
        }
    }
    puts("");
}

#endif // PREPARE-GAME_H_INCLUDED
