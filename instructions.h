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

void load_game_menu()
{

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

void character_menu()
{
    printf("1. M.r Jack\n");
    printf("2. Sherlock Holmes\n");
    printf("Choose your character: ");
}

#endif // INSTRUCTIONS_H_INCLUDED
