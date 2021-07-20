#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED

void (*do_action[8])() = {holmes, suspects, watson, toby, rotate_tile, switch_tiles, rotate_tile, joker};

void holmes()
{

}

void suspects()
{
//  discard the cards that have been seen before
    int flag = 0;
    while (flag != 1) {
        shuffle_cards(card_numbers);
        for (int i = 0; i < 9; i++) {
            flag = 1;
            if (seen_cards[i] == card_numbers[0]) {
                flag = 0;
            }
        }
    }
    if (round % 2 == 1) {
//      Holmes's turn
        printf("%s\n", cards[card_numbers[0]].name);
        seen_cards[++number_of_seen_card] = card_numbers[0];

        struct tiles *current = head;
        for (int i = 0; i < 9; i++, current = current->next) {
            if (strcmp(cards[card_numbers[0]].name, current->suspect) == 0) {
                strcpy(current->suspect, " ");
            }
        }
    }
    else {
//      M.r Jack's turn
        printf("%s\n", cards[card_numbers[0]].name);
        hourglass += cards[card_numbers[0]].hourglass;
        seen_cards[++number_of_seen_card] = card_numbers[0];
    }
}

void watson()
{

}

void toby()
{

}

void rotate_tile()
{
    int choice;
    int degree_choice;
    for (int i = 1; i <= 9; i++) {
        printf("%d ");
        if (i % 3 == 0) {
            puts("");
        }
    }
    printf("Choose a tile to rotate: ");
    scanf("%d", &choice);
    printf("1. 90  2. 180  3. 270\n");
    printf("Choose degree: ");
    scanf("%d", &degree_choice);

    struct tiles *current = head;
    for (int i = 0; i < 9; i++, current = current->next) {
        if (current->number == tile_numbers[choice]) {
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

void switch_tiles()
{

}

void joker()
{

}

#endif // ACTION_H_INCLUDED
