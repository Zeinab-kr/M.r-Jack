#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include "prepare-game.h"
#include "instructions.h"
#include "shuffle.h"
#include "action.h"

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

//          define game
            int card_numbers[9];
            int tile_numbers[9];
            define_cards();// define characters and their hourglass(es)
            define_detectives();
            define_action_tokens();
            shuffle_cards(card_numbers);
            shuffle_cards(tile_numbers); // shuffle tiles
//          -----------------------------------------------------------------------------------------------------
//          M.r Jack's character
            int jack_char = card_numbers[0];
            printf("M.r Jack can see his character after 5 seconds\n");
            printf("Holmes must close his eyes\n");
            //Sleep(5000);
            printf("Your character is %s\n", cards[jack_char].name);
            //Sleep(3000);
            system("cls"); // clear console after 3 seconds so Holmes cannot see Jack's character
//          -----------------------------------------------------------------------------------------------------
//          map
            int wall[9];
            rotation(wall); // randomly choose rotation of each tile
            create_map(wall, tile_numbers, cards);
            print_map(detective);
//          -----------------------------------------------------------------------------------------------------
//          actions
            int action_side[4];
            flip_action_tokens(action_side); // randomly choose actions
            int action_choice[4] = {0};

            action_menu(action, action_side, action_choice);
            printf("Holmes pick an action: ");
            scanf("%d", &action_choice[0]);
            //(*do_action[action[action_choice[0]-1].number[action_side[action_choice[0]-1]])();

            puts("");
            action_menu(action, action_side, action_choice);
            printf("M.r Jack pick an action: ");
            scanf("%d", &action_choice[1]);
            //(*do_action[action[action_choice[1]-1].number[action_side[action_choice[1]-1]])();
            puts("");
            action_menu(action, action_side, action_choice);
            printf("Pick another one: ");
            scanf("%d", &action_choice[2]);
            //(*do_action[action[action_choice[2]-1].number[action_side[action_choice[2]-1]])();

            puts("");
            action_menu(action, action_side, action_choice);
            printf("Holmes pick the action: ");
            scanf("%d", &action_choice[3]);
            //(*do_action[action[action_choice[3]-1].number[action_side[action_choice[3]-1]])();
//          -----------------------------------------------------------------------------------------------------
        }
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
