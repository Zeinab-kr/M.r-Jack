#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED

void holmes() //***
{
    int choice;
    printf("1 step forward or 2? ");
    scanf("%d", &choice);

    if (detective[0].side == LEFT) {
        detective[0].block -= choice;
        if (detective[0].block < 1) {
            detective[0].block = 1 - detective[0].block;
            detective[0].side = UP;
        }
    }
    if (detective[0].side == DOWN) {
        detective[0].block -= choice;
        if (detective[0].block < 1) {
            detective[0].block = 3 + detective[0].block;
            detective[0].side = LEFT;
        }
    }
    if (detective[0].side == RIGHT) {
        detective[0].block += choice;
        if (detective[0].block > 3) {
            detective[0].block = 7 - detective[0].block;
            detective[0].side = DOWN;
        }
    }
    if (detective[0].side == UP) {
        detective[0].block += choice;
        if (detective[0].block > 3) {
            detective[0].block = detective[0].block - 3;
            detective[0].side = RIGHT;
        }
    }
}

void suspects()
{
//  discard the cards that have been seen before
    int card_number[9];
    int flag = 0;
    while (flag != 1) {
        shuffle_cards(card_number);
        for (int i = 0; i < 9; i++) {
            flag = 1;
            if (seen_cards[i] == card_number[0]) {
                flag = 0;
            }
        }
    }
    if (game_round % 2 == 1) {
//      Holmes's turn
        printf("%s\n", cards[card_number[0]].name);
        Sleep(3000);
        seen_cards[++number_of_seen_card] = card_number[0]; // add this card to seen

//      the suspicion has been removed from this character so delete it from the map
        struct tiles *current = head;
        for (int i = 0; i < 9; i++, current = current->next) {
            if (strcmp(cards[card_number[0]].name, current->suspect) == 0) {
                strcpy(current->suspect, " ");
            }
        }
    }
    else {
//      M.r Jack's turn
        printf("Holmes must close his eyes\n");
        printf("You can see the card after 3 seconds\n");
        Sleep(3000);
        printf("%s\n", cards[card_number[0]].name);
        Sleep(3000);
        hourglass += cards[card_number[0]].hourglass;
        seen_cards[++number_of_seen_card] = card_number[0]; // add this card to seen
    }
}

void watson()
{
    int choice;
    printf("1 step forward or 2? ");
    scanf("%d", &choice);

    if (detective[1].side == LEFT) {
        detective[1].block -= choice;
        if (detective[1].block < 1) {
            detective[1].block = 1 - detective[1].block;
            detective[1].side = UP;
        }
    }
    if (detective[1].side == DOWN) {
        detective[1].block -= choice;
        if (detective[1].block < 1) {
            detective[1].block = 3 + detective[1].block;
            detective[1].side = LEFT;
        }
    }
    if (detective[1].side == RIGHT) {
        detective[1].block += choice;
        if (detective[1].block > 3) {
            detective[1].block = 7 - detective[1].block;
            detective[1].side = DOWN;
        }
    }
    if (detective[1].side == UP) {
        detective[1].block += choice;
        if (detective[1].block > 3) {
            detective[1].block = detective[1].block - 3;
            detective[1].side = RIGHT;
        }
    }
}

void toby()
{
    int choice;
    printf("1 step forward or 2? ");
    scanf("%d", &choice);

    if (detective[2].side == LEFT) {
        detective[2].block -= choice;
        if (detective[2].block < 1) {
            detective[2].block = 1 - detective[2].block;
            detective[2].side = UP;
        }
    }
    if (detective[2].side == DOWN) {
        detective[2].block -= choice;
        if (detective[2].block < 1) {
            detective[2].block = 3 + detective[2].block;
            detective[2].side = LEFT;
        }
    }
    if (detective[2].side == RIGHT) {
        detective[2].block += choice;
        if (detective[2].block > 3) {
            detective[2].block = 7 - detective[2].block;
            detective[2].side = DOWN;
        }
    }
    if (detective[2].side == UP) {
        detective[2].block += choice;
        if (detective[2].block > 3) {
            detective[2].block = detective[2].block - 3;
            detective[2].side = RIGHT;
        }
    }
}

void rotate_tile()
{
    int choice;
    int degree_choice;
    for (int i = 1; i <= 9; i++) {
        printf("%d ", i);
        if (i % 3 == 0) {
            puts("");
        }
    }
    printf("Choose a tile to rotate: ");
    scanf("%d", &choice);
    choice--;
    printf("1. 90  2. 180  3. 270\n");
    printf("Choose degree: ");
    scanf("%d", &degree_choice);

    struct tiles *current = head;
    for (int i = 0; i < 9; i++, current = current->next) {
        if (current->number == choice) {
            if (degree_choice == 1) {
                current->wall += 1;
                if (current->wall > 4) {
                    current->wall -= 4;
                }
            }
            if (degree_choice == 2) {
                current->wall += 2;
                if (current->wall > 4) {
                    current->wall -= 4;
                }
            }
            if (degree_choice == 3) {
                current->wall += 3;
                if (current->wall > 4) {
                    current->wall -= 4;
                }
            }
        }
    }
}

void swap_tiles()//***
{
    int choice_1, choice_2;
    for (int i = 1; i <= 9; i++) {
        printf("%d ", i);
        if (i % 3 == 0) {
            puts("");
        }
    }
    printf("Choose 2 tiles to switch(<first> <second>): ");
    scanf("%d %d", &choice_1, &choice_2);
    choice_1 -= 1;
    choice_2 -= 1;

    struct tiles *current = head;
    struct tiles copy_of_map[9];
    for (int i = 0; i < 9; i++, current = current->next) {
        copy_of_map[i] = *current;
    }

    for (int i = 0; i < 9; i++) {
        if (copy_of_map[i].number == choice_1) {
            for (int j = 0; j < 9; j++) {
                if (copy_of_map[j].number == choice_2) {
                    struct tiles temp = copy_of_map[i];
                    copy_of_map[i] = copy_of_map[j];
                    copy_of_map[j] = temp;

                    copy_of_map[i].number = choice_1;
                    copy_of_map[j].number = choice_2;
                    break;
                }
            }
            break;
        }
    }

    current = head;
    for (int i = 0; i < 9; i++, current = current->next) {
        *current = copy_of_map[i];
        if (i == 8) {
            current->next = NULL;
        }
    }
    /*struct tiles *previous_1 = NULL;
    struct tiles *previous_2 = NULL;
    struct tiles *current_1 = head;
    struct tiles *current_2 = head;
    for (; current_1->number == choice_1; previous_1 = current_1, current_1 = current_1->next);
    for (; current_2->number == choice_2; previous_2 = current_2, current_2 = current_2->next);
    if (current_1 == head) {
        previous_2->next = current_1;
    }
    else if (current_2 == head) {
        previous_1->next = current_2;
    }
    else {
        previous_1->next = current_2;
        previous_2->next = current_1;
    }
    struct tiles *temp = current_1->next;
    current_1->next = current_2->next;
    current_2->next = temp;

    current_1->number = choice_2;
    current_2->number = choice_1;*/
}

void joker()//***
{
    int choice, char_choice;
    for (int i = 0; i < 3; i++) {
        printf("%d. %s\n", i+1, detective[i].name);
    }
    if (game_round % 2 == 0) {
        printf("4. None");
    }
    printf("Which detective do you want to move? ");
    scanf("%d", &char_choice);

//  if it's m.r Jack's turn and he doesn't want to move any character, return
    if (char_choice == 4) {
        return;
    }

    printf("1 step forward or 2? ");
    scanf("%d", &choice);

    if (detective[char_choice-1].side == LEFT) {
        detective[char_choice-1].block -= choice;
        if (detective[char_choice-1].block < 1) {
            detective[char_choice-1].block = 1 - detective[char_choice-1].block;
            detective[char_choice-1].side = UP;
        }
    }
    if (detective[char_choice-1].side == DOWN) {
        detective[char_choice-1].block -= choice;
        if (detective[char_choice-1].block < 1) {
            detective[char_choice-1].block = 3 + detective[char_choice-1].block;
            detective[char_choice-1].side = LEFT;
        }
    }
    if (detective[char_choice-1].side == RIGHT) {
        detective[char_choice-1].block += choice;
        if (detective[char_choice-1].block > 3) {
            detective[char_choice-1].block = 7 - detective[char_choice-1].block;
            detective[char_choice-1].side = DOWN;
        }
    }
    if (detective[char_choice-1].side == UP) {
        detective[char_choice-1].block += choice;
        if (detective[char_choice-1].block > 3) {
            detective[char_choice-1].block = detective[char_choice-1].block - 3;
            detective[char_choice-1].side = RIGHT;
        }
    }
}

#endif // ACTION_H_INCLUDED
