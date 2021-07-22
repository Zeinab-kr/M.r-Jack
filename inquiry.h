#ifndef INQUIRY_H_INCLUDED
#define INQUIRY_H_INCLUDED

bool ask()
{
    struct tiles *current = NULL;
    char seen_characters[9][20];
    int num = -1;
    for (int i = 0; i < 3; i++) {
        if (detective[i].side == UP) {
            if (detective[i].block == 1) {
                current = head;
            }
            if (detective[i].block == 2) {
                current = head->next;
            }
            if (detective[i].block == 3) {
                current = head->next->next;
            }
            for (int j = 0; j < 3;) {
                if (current->wall != UP) {
                    strcpy(seen_characters[++num], current->suspect);
                } else {break;}
                if (current->wall != DOWN) {
                    current = current->next->next->next;
                    j++;
                } else {break;}
            }
        }
        if (detective[i].side == DOWN) {
            struct tiles *previous = NULL;
            struct tiles *next = NULL;
            if (detective[i].block == 1) {
                current = head;
                previous = head;
            }
            if (detective[i].block == 2) {
                current = head->next;
                previous = head->next;
            }
            if (detective[i].block == 3) {
                current = head->next->next;
                previous = head->next->next;
            }
            for (int k = 0; k < 3; k++) {
                previous = previous->next;
            }
            for (int k = 0; k < 6; k++) {
                current = current->next;
            }
            for (int j = 0; j < 3;) {
                if (current->wall != DOWN) {
                    strcpy(seen_characters[++num], current->suspect);
                } else {break;}
                if (current->wall != UP) {
                    // move backwards
                    next = current->next->next->next;
                    current->next->next->next = previous;
                    previous = current;
                    current = next;
                    j++;
                } else {break;}
            }
        }
        if (detective[i].side == RIGHT) {
            struct tiles *previous = NULL;
            struct tiles *next = NULL;
            if (detective[i].block == 1) {
                current = head->next->next;
                previous = head->next;
            }
            if (detective[i].block == 2) {
                current = head->next->next;
                previous = head->next;
                for (int k = 0; k < 3; k++) {
                    current = current->next;
                    previous = previous->next;
                }
            }
            if (detective[i].block == 3) {
                current = head->next->next;
                previous = head->next;
                for (int k = 0; k < 6; k++) {
                    current = current->next;
                    previous = previous->next;
                }
            }
            for (int j = 0; j < 3;) {
                if (current->wall != RIGHT) {
                    strcpy(seen_characters[++num], current->suspect);
                } else {break;}
                if (current->wall != LEFT) {
                    // move backwards
                    next = current->next;
                    current->next = previous;
                    previous = current;
                    current = next;
                    j++;
                } else {break;}
            }
        }
        if (detective[i].side == LEFT) {
            if (detective[i].block == 1) {
                current = head;
            }
            if (detective[i].block == 2) {
                current = head;
                for (int k = 0; k < 3; k++) {
                    current = current->next;
                }
            }
            if (detective[i].block == 3) {
                current = head;
                for (int k = 0; k < 6; k++) {
                    current = current->next;
                }
            }
            for (int j = 0; j < 3;) {
                if (current->wall != LEFT) {
                    strcpy(seen_characters[++num], current->suspect);
                } else {break;}
                if (current->wall != RIGHT) {
                    current = current->next;
                    j++;
                } else {break;}
            }
        }
    }

    int flag = false;
    for (int i = 0; seen_characters[i] != NULL; i++) {
        if (strcmp(seen_characters[i], cards[seen_cards[0]].name) == 0) {
            flag = true;
        }
    }
    if (!flag) {
        printf("Holmes cannot see m.r Jack\n");
        current = head;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; seen_characters[j] != NULL; j++) {
                if (strcmp(current->suspect, seen_characters[j]) == 0) {
                    strcpy(current->suspect, " ");
                }
            }
            current = current->next;
        }
    }
    else {
        printf("Holmes can see m.r Jack\n");
        current = head;
        int flag_2;
        for (int i = 0; i < 9; i++) {
            flag_2 = 0;
            for (int j = 0; seen_characters[j] != NULL; j++) {
                if (strcmp(current->suspect, seen_characters[j]) == 0) {
                    flag_2 = 1;
                }
            }
            if (flag_2 == 0) {
                strcmp(current->suspect, " ");
            }
            current = current->next;
        }
    }
    return flag;
}

#endif // INQUIRY_H_INCLUDED
