#ifndef INSTRUCTIONS_H_INCLUDED
#define INSTRUCTIONS_H_INCLUDED

void intro()
{
    printf("********************************************************\n");
    printf("*                                                      *\n");
    printf("*   ****   ****            ****               **       *\n");
    printf("*   ** ** ** **             **                **       *\n");
    printf("*   **  ***  **   * **      **   ***    ****  ** ***   *\n");
    printf("*   **       **   **     *  **  *  **  **     ***      *\n");
    printf("*   **       ** * **      ***    *** *  ****  ** ***   *\n");
    printf("*                                                      *\n");
    printf("********************************************************\n");
    puts("");
}

void game_menu()
{
    printf("1. New Game\n");
    printf("2. Load Game\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

void load_game_menu(FILE *fptr)
{
    int i = -1;
    int g_round, glasses;
    while(!feof(fptr)) {
        fseek(fptr, (++i) * sizeof(struct game_data), SEEK_SET);
        fscanf("%d%d", &g_round, &glasses);
        printf("%d) round: %d | hourglasses: %d\n", i+1, g_round, glasses);
    }
    printf("Choose the game: ");
    rewind(fptr);
}

void pause_game_menu()
{
    printf("1. Resume\n");
    printf("2. Save Game\n");
    printf("3. End Game\n");
    printf("Enter your choice: ");
}

void end_game_menu()
{
    printf("If you haven't saved the game, all the game data will be lost\n");
    printf("1. Save Game\n");
    printf("2. Exit Without Saving\n");
    printf("Enter your choice: ");
}

void action_menu(struct action_tokens action[], int action_side[], int choice[])
{
    int i ;
    for (i = 1; i <= 4; i++) {
        int flag = 1;
        for (int k = 0; k < 4; k++) {
            if (i == choice[k]) {
                flag = 0;
            }
        }
        if (flag == 1) {
            printf("%d. %s\n", i, action[i-1].name[action_side[i-1]]);
        }
    }
    printf("%d. Pause Game\n\n", i);
}

#endif // INSTRUCTIONS_H_INCLUDED
