#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include "instructions.h"
#include "shuffle.h"
#include "prepare-game.h"

int main()
{
    int choice;
    define_cards();// define characters and their hourglass(es)

    int card_numbers[9];
    int tile_numbers[9];

    intro();

    while (choice != 3) {
        game_menu();
        scanf("%d", &choice);
        puts("");

        if (choice == 1) {
            int char_choice;

            // M.r Jack's character
            shuffle_cards(card_numbers);
            int jack_char = card_numbers[0];
            printf("M.r Jack can see his character after 5 seconds\n");
            printf("Holmes must close his eyes\n");
            //Sleep(5000);
            printf("Your character is %s\n", cards[jack_char].name);
            //Sleep(3000);
            system("cls"); // clear console after 3 seconds so Holmes cannot see Jack's character

            //tokens
            define_detectives();
            define_action_tokens();

            // map
            int wall[9];
            shuffle_cards(tile_numbers);
            rotation(wall); // randomly choose rotation of each tile
            create_map(wall, tile_numbers, cards);
            print_map(detective);

            int action_side[4];
            flip_action_tokens(action_side);
            for (int i = 0; i < 4; i++) {
                printf("%d. %s\n", i+1, action[i].name[action_side[i]]);
            }
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
