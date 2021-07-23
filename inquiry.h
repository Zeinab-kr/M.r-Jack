#ifndef INQUIRY_H_INCLUDED
#define INQUIRY_H_INCLUDED

bool ask()
{
    struct tiles *current = head;
    struct tiles copy_of_map[9];
    for (int i = 0; i < 9; i++, current = current->next) {
        copy_of_map[i] = *current;
    }
    char *seen_characters[9];
    for (int i = 0; i < 9; i++) {
        seen_characters[i] = (char *)malloc(20 * sizeof(char));
    }
    int num = -1;
    int k;
    for (int i = 0; i < 3; i++) {
        if (detective[i].side == UP) {
            if (detective[i].block == 1) {
                k = 0;
            }
            if (detective[i].block == 2) {
                k = 1;
            }
            if (detective[i].block == 3) {
                k = 2;
            }
            for (int j = 0; j < 3;) {
                if (copy_of_map[k].wall != UP) {
                    strcpy(seen_characters[++num], copy_of_map[k].suspect);
                } else {break;}
                if (copy_of_map[k].wall != DOWN) {
                    k += 3;
                    j++;
                } else {break;}
            }
        }
        if (detective[i].side == DOWN) {
            if (detective[i].block == 1) {
                k = 6;
            }
            if (detective[i].block == 2) {
                k = 7;
            }
            if (detective[i].block == 3) {
                k = 8;
            }
            for (int j = 0; j < 3;) {
                if (copy_of_map[k].wall != DOWN) {
                    strcpy(seen_characters[++num], copy_of_map[k].suspect);
                } else {break;}
                if (copy_of_map[k].wall != UP) {
                    // move backwards
                    k -= 3;
                    j++;
                } else {break;}
            }
        }
        if (detective[i].side == RIGHT) {
            if (detective[i].block == 1) {
                k = 2;
            }
            if (detective[i].block == 2) {
                k = 5;
            }
            if (detective[i].block == 3) {
                k = 7;
            }
            for (int j = 0; j < 3;) {
                if (copy_of_map[k].wall != RIGHT) {
                    strcpy(seen_characters[++num], copy_of_map[k].suspect);
                } else {break;}
                if (copy_of_map[k].wall != LEFT) {
                    // move backwards
                    k--;
                    j++;
                } else {break;}
            }
        }
        if (detective[i].side == LEFT) {
            if (detective[i].block == 1) {
                k = 0;
            }
            if (detective[i].block == 2) {
                k = 3;
            }
            if (detective[i].block == 3) {
                k = 6;
            }
            for (int j = 0; j < 3;) {
                if (copy_of_map[k].wall != LEFT) {
                    strcpy(seen_characters[++num], copy_of_map[k].suspect);
                } else {break;}
                if (copy_of_map[k].wall != RIGHT) {
                    k++;
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
                strcpy(current->suspect, " ");
            }
            current = current->next;
        }
    }
    return flag;
}

bool check()
{
    struct tiles *current = head;
    int num = 0;
    for (int i = 0; i < 9; i++, current = current->next) {
        if (strcmp(current->suspect, " ") != 0) {
            num++;
        }
    }
    if (num == 1) {
        return true;
    }
    return false;
}

#endif // INQUIRY_H_INCLUDED
