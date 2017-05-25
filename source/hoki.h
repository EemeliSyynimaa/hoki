#ifndef __HOKI_H__
#define __HOKI_H__

typedef struct keyboard_state_t_
{
    char w;
    char a;
    char s;
    char d;
} keyboard_state_t;

typedef struct game_state_t_
{
    keyboard_state_t keyboard_state;
    float player_x;
    float player_y;
} game_state_t;

#endif