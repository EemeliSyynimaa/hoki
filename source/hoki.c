#include "hoki.h"

void game_update(game_state_t* state)
{
    float speed = 0.05f;

    if (state->keyboard_state.w)
    {
        state->player_y += speed;
    }
    if (state->keyboard_state.s)
    {
        state->player_y -= speed;
    }
    if (state->keyboard_state.a)
    {
        state->player_x -= speed;
    }
    if (state->keyboard_state.d)
    {
        state->player_x += speed;
    }
}