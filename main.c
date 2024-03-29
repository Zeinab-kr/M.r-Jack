#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>

// global variables
int card_numbers[9];
int tile_numbers[9];
int hourglass = 0;
int seen_cards[9];
int number_of_seen_card = 0;
int game_round = 1;

// these headers needed to be included after defining global variables
#include "prepare-game.h"
#include "shuffle.h"
#include "action.h"
#include "inquiry.h"
#include "data.h"
#include "instructions.h"

// pointer to functions that do the actions
void (*do_action[8])() = {holmes, suspects, watson, toby, rotate_tile, swap_tiles, rotate_tile, joker};

// prototypes
bool save_game();

int main()
{
    int choice;
    bool check_map = false;

    intro();

    while (choice != 3) {
        game_menu();
        scanf("%d", &choice);
        puts("");

        // define game
        define_cards(); // define characters and their hourglass(es)
        define_detectives();
        define_action_tokens();

        if (choice == 1) {
            int char_choice;

            // shuffle cards and tiles
            shuffle_cards(card_numbers);
            shuffle_tiles(tile_numbers);
//          -----------------------------------------------------------------------------------------------------
            // M.r Jack's character
            int jack_char = card_numbers[0];
            seen_cards[0] = jack_char;
            printf("M.r Jack can see his character after 5 seconds\n");
            printf("Holmes must close his eyes\n");
            Sleep(5000);
            printf("Your character is %s\n", cards[jack_char].name);
            Sleep(3000);
            system("cls"); // clear console after 3 seconds so Holmes cannot see Jack's character
//          -----------------------------------------------------------------------------------------------------
            // map
            int wall[9];
            rotation(wall); // randomly choose rotation of each tile
            create_map(wall);
            print_map();
//          -----------------------------------------------------------------------------------------------------
            // start the game
            int action_side[4];
            while ((hourglass < 6) && (game_round < 8) && (check_map == false)) {

                printf("Round %d\n\n", game_round);

                if (game_round % 2 == 1) {
                    // Holmes starts the round
                    int action_choice[4] = {0};
                    // actions
                    flip_action_tokens(action_side); // randomly choose actions

                    for (int i = 0; i < 4; i++) {
                        action_menu(action, action_side, action_choice);
                        if (i == 0) {
                            printf("Holmes pick an action: ");
                        }
                        if (i == 1) {
                            printf("M.r Jack pick an action: ");
                        }
                        if (i == 2) {
                            printf("Pick another one: ");
                        }
                        if (i == 3) {
                            printf("Holmes pick the action: ");
                        }
                        scanf("%d", &action_choice[i]);
                        if (action_choice[i] == 5) {
                            pause_game_menu();
                            int pause_choice;
                            scanf("%d", &pause_choice);
                            if (pause_choice == 1) {
                                --i;
                                continue;
                            }
                            if (pause_choice == 2) {
                                if (save_game()) {
                                    printf("Saved\n");
                                }
                                else {
                                    printf("Could not save\n");
                                }
                                --i;
                                continue;
                            }
                            if (pause_choice == 3) {
                                end_game_menu();
                                int end_choice;
                                scanf("%d", &end_choice);
                                if (end_choice == 1) {
                                    if (save_game()) {
                                        printf("Saved\n");
                                    }
                                    else {
                                        printf("Could not save\n");
                                    }
                                    return 0;
                                }
                                if (end_choice == 2) {
                                    return 0;
                                }
                            }
                        }
                        (*do_action[action[action_choice[i]-1].number[action_side[action_choice[i]-1]]])();
                        system("cls");
                        print_map();
                    }
                    ++game_round;
                }
                else {
                    // M.r Jack starts the round
                    int action_choice[4] = {0};
                    // actions
                    for (int i = 0; i < 4; i++) {
                        action_side[i] = 1 - action_side[i]; // the other side of the tokens
                    }
                    for (int i = 0; i < 4; i++) {
                        action_menu(action, action_side, action_choice);
                        if (i == 0) {
                            printf("M.r Jack pick an action: ");
                        }
                        if (i == 1) {
                            printf("Holmes pick an action: ");
                        }
                        if (i == 2) {
                            printf("Pick another one: ");
                        }
                        if (i == 3) {
                            printf("M.r Jack pick the action: ");
                        }
                        scanf("%d", &action_choice[i]);
                        if (action_choice[i] == 5) {
                            pause_game_menu();
                            int pause_choice;
                            scanf("%d", &pause_choice);
                            if (pause_choice == 1) {
                                --i;
                                continue;
                            }
                            if (pause_choice == 2) {
                                if (save_game()) {
                                    printf("Saved\n");
                                }
                                else {
                                    printf("Could not save\n");
                                }
                                --i;
                                continue;
                            }
                            if (pause_choice == 3) {
                                end_game_menu();
                                int end_choice;
                                scanf("%d", &end_choice);
                                if (end_choice == 1) {
                                    if (save_game()) {
                                        printf("Saved\n");
                                    }
                                    else {
                                        printf("Could not save\n");
                                    }
                                    return 0;
                                }
                                if (end_choice == 2) {
                                    return 0;
                                }
                            }
                        }
                        (*do_action[action[action_choice[i]-1].number[action_side[action_choice[i]-1]]])();
                        system("cls");
                        print_map();
                    }
                    ++game_round;
                }

                bool is_seen = ask();
                Sleep(3000);
                system("cls");
                print_map();

                // if m.r Jack has not been seen in this round...
                if (!is_seen) {
                    ++hourglass; // ... add an hourglass
                }

                // check if Holmes has found m.r Jack
                check_map = check();

            }
            if (game_round == 8 || hourglass >= 6) {
                printf("M.R JACK WON!!!\n");
            }
            if (check_map) {
                printf("HOLMES WON!!!\n");
            }
        }
//      ----------------------------------------------------------------------------------------------------------------------------
        // load game
        else if (choice == 2) {
            FILE *fptr = fopen("data.bin", "rb"); // open file

            int load_choice;
            load_game_menu(fptr);
            scanf("%d", &load_choice);
            fseek(fptr, (load_choice-1) * sizeof(struct game_data), SEEK_SET);

            fscanf(fptr, "%d%d", &game_round, &hourglass); // load number of round and hourglasses
//          -----------------------------------------------------------------------------------------------------
            // load map
            struct tiles *current = head;
            for (int i = 0; i < 9; i++, current = current->next) {
                fscanf(fptr, "%d%d%20s%p", &current->number, &current->wall, current->suspect, current->next);
            }
//          -----------------------------------------------------------------------------------------------------
            // load the order of cards and tiles
            for (int i = 0; i < 9; i++) {
                fscanf(fptr, "%d", &card_numbers[i]);
            }
            fgetchar(); // skip '\n'
            for (int i = 0; i < 9; i++) {
                fscanf(fptr, "%d", &tile_numbers[i]);
            }
//          -----------------------------------------------------------------------------------------------------
            // cards that have been seen
            for (int i = 0; i < 9; i++) {
                fscanf(fptr, "%d", &seen_cards[i]);
            }

            fscanf(fptr, "%d", &number_of_seen_card);
//          -----------------------------------------------------------------------------------------------------
            // load detectives' data
            for (int i = 0; i < 3; i++) {
                fscanf(fptr, "%d%d", &detective[i].side, &detective[i].block);
            }
//          -----------------------------------------------------------------------------------------------------
            // start the game
            int action_side[4];
            while ((hourglass < 6) && (game_round < 8) && (check_map == false)) {

                printf("Round %d\n\n", game_round);

                if (game_round % 2 == 1) {
                    // Holmes starts the round
                    int action_choice[4] = {0};
                    // actions
                    flip_action_tokens(action_side); // randomly choose actions

                    for (int i = 0; i < 4; i++) {
                        action_menu(action, action_side, action_choice);
                        if (i == 0) {
                            printf("Holmes pick an action: ");
                        }
                        if (i == 1) {
                            printf("M.r Jack pick an action: ");
                        }
                        if (i == 2) {
                            printf("Pick another one: ");
                        }
                        if (i == 3) {
                            printf("Holmes pick the action: ");
                        }
                        scanf("%d", &action_choice[i]);
                        if (action_choice[i] == 5) {
                            pause_game_menu();
                            int pause_choice;
                            scanf("%d", &pause_choice);
                            if (pause_choice == 1) {
                                --i;
                                continue;
                            }
                            if (pause_choice == 2) {
                                if (save_game()) {
                                    printf("Saved\n");
                                }
                                else {
                                    printf("Could not save\n");
                                }
                                --i;
                                continue;
                            }
                            if (pause_choice == 3) {
                                end_game_menu();
                                int end_choice;
                                scanf("%d", &end_choice);
                                if (end_choice == 1) {
                                    if (save_game()) {
                                        printf("Saved\n");
                                    }
                                    else {
                                        printf("Could not save\n");
                                    }
                                    return 0;
                                }
                                if (end_choice == 2) {
                                    return 0;
                                }
                            }
                        }
                        (*do_action[action[action_choice[i]-1].number[action_side[action_choice[i]-1]]])();
                        system("cls");
                        print_map();
                    }
                    ++game_round;
                }
                else {
                    // M.r Jack starts the round
                    int action_choice[4] = {0};
                    // actions
                    for (int i = 0; i < 4; i++) {
                        action_side[i] = 1 - action_side[i]; // the other side of the tokens
                    }
                    for (int i = 0; i < 4; i++) {
                        action_menu(action, action_side, action_choice);
                        if (i == 0) {
                            printf("M.r Jack pick an action: ");
                        }
                        if (i == 1) {
                            printf("Holmes pick an action: ");
                        }
                        if (i == 2) {
                            printf("Pick another one: ");
                        }
                        if (i == 3) {
                            printf("M.r Jack pick the action: ");
                        }
                        scanf("%d", &action_choice[i]);
                        (*do_action[action[action_choice[i]-1].number[action_side[action_choice[i]-1]]])();
                        system("cls");
                        print_map();
                    }
                    ++game_round;
                }

                bool is_seen = ask();
                Sleep(3000);
                system("cls");
                print_map();

                // if m.r Jack has not been seen in this round...
                if (!is_seen) {
                    ++hourglass; // ... add an hourglass
                }

                // check if Holmes has found m.r Jack
                check_map = check();

            }
            if (game_round == 8 || hourglass >= 6) {
                printf("M.R JACK WON!!!\n");
            }
            if (check_map) {
                printf("HOLMES WON!!!\n");
            }
        }
//      ----------------------------------------------------------------------------------------------------------------------------
        else if (choice == 3) {
            break;
        }
        else {
            printf("Invalid choice!\n\n");
        }
    }
}

bool save_game()
{
    FILE *fptr = fopen("data.bin", "wb+"); // open file
    if (fptr == NULL) {
        return false;
    }

    fprintf(fptr, "%d%d", game_round, hourglass); // save number of round and hourglasses
//  -----------------------------------------------------------------------------------------------------
    // save map
    struct tiles *current = head;
    for (int i = 0; i < 9; i++, current = current->next) {
        fprintf(fptr, "%d%d%20s%p", current->number, current->wall, current->suspect, current->next);
    }
//  -----------------------------------------------------------------------------------------------------
    // save the order of cards and tiles
    for (int i = 0; i < 9; i++) {
        fprintf(fptr, "%d", card_numbers[i]);
    }
    for (int i = 0; i < 9; i++) {
        fprintf(fptr, "%d", tile_numbers[i]);
    }
//  -----------------------------------------------------------------------------------------------------
    // cards that have been seen
    for (int i = 0; i < 9; i++) {
        fprintf(fptr, "%d ", seen_cards[i]);
    }

    fprintf(fptr, "%d", number_of_seen_card);
//  -----------------------------------------------------------------------------------------------------
    // save detectives' data
    for (int i = 0; i < 3; i++) {
        fprintf(fptr, "%d%d", detective[i].side, detective[i].block);
    }
//  -----------------------------------------------------------------------------------------------------
    return true;
}
