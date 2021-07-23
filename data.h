#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

struct detective_data {
    int side;
    int block;
};

struct game_data {
    int g_round;
    int glass;
    struct tiles tile[9];
    int card_num[9];
    int tile_num[9];
    int seen[9];
    int seen_num;
    struct detective_data d_data[3];
};

#endif // DATA_H_INCLUDED
