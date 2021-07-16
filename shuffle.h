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

int rotation()
{
    srand(time(NULL));
    return rand() % 4 + 1;
}

#endif // SHUFFLE_H_INCLUDED
