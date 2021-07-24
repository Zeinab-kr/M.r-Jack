#ifndef SHUFFLE_H_INCLUDED
#define SHUFFLE_H_INCLUDED

void shuffle_cards(int numbers[])
{
    for (int i = 0; i < 9; i++) {
        numbers[i] = i;
    }
    srand(time(NULL));
    for (int i = 0; i < 9; i++) {
        int randomIndex = rand() % 9;
        int temp = numbers[i];
        numbers[i] = numbers[randomIndex];
        numbers[randomIndex] = temp;
    }
}

void shuffle_tiles(int numbers[])
{
    int j = 9;
    for (int i = 0; i < 9; i++) {
        numbers[i] = --j;
    }
    srand(time(NULL));
    for (int i = 0; i < 9; i++) {
        int randomIndex = rand() % 9;
        int temp = numbers[i];
        numbers[i] = numbers[randomIndex];
        numbers[randomIndex] = temp;
    }
}

void rotation(int wall[])
{
    srand(time(NULL));
    for (int i = 0; i < 9; i++) {
        wall[i] = rand() % 4 + 1;
    }
    wall[0] = LEFT;
    wall[2] = RIGHT;
    wall[7] = DOWN;
}

void flip_action_tokens(int action_side[])
{
    srand(time(NULL));
    for (int i = 0; i < 4; i++) {
        action_side[i] = rand() % 2;
    }
}

#endif // SHUFFLE_H_INCLUDED
