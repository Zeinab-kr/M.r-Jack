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
#include "instructions.h"
#include "shuffle.h"
#include "action.h"
#include "inquiry.h"

// pointer to functions that do the actions
void (*do_action[8])() = {holmes, suspects, watson, toby, rotate_tile, swap_tiles, rotate_tile, joker};

int main()
{
    int choice;

    intro();

    while (choice != 3) {
        game_menu();
        scanf("%d", &choice);
        puts("");

        if (choice == 1) {
            int char_choice;

            // define game
            define_cards(); // define characters and their hourglass(es)
            define_detectives();
            define_action_tokens();
            shuffle_cards(card_numbers);
            shuffle_cards(tile_numbers); // shuffle tiles
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
            while ((hourglass < 6) || (game_round < 8)) {
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

                int is_seen = ask();
                Sleep(3000);
                system("cls");
                print_map();

                // if m.r Jack hasn't been seen in this round...
                if (!is_seen) {
                    ++hourglass; // ... add an hourglass
                }
            }
        }
        // save hourglasses, map, card numbers, tile numbers, action sides
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
