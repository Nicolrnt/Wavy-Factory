/*
** keys.c for game_jam_2017 in /home/thery/Bureau/game_jam_2017
** 
** Made by Thery
** Login   <thery.fouchter@epitech.eu@epitech.net>
** 
** Started on  Sat Jan 21 23:59:26 2017 Thery
** Last update Sun Jan 22 13:49:17 2017 Thery
*/

#include "game.h"

int	inputs_keys(t_wa *wa)
{
  int	did_smg;

  did_smg = 0;
  if (sfKeyboard_isKeyPressed(sfKeyDown) == sfTrue
      || sfKeyboard_isKeyPressed(sfKeyS) == sfTrue)
    did_smg += move_player(wa, wa->p1, 0, 1);
  if (sfKeyboard_isKeyPressed(sfKeyLeft) == sfTrue
      || sfKeyboard_isKeyPressed(sfKeyQ) == sfTrue)
    did_smg += move_player(wa, wa->p1, -1, 0);
  if (sfKeyboard_isKeyPressed(sfKeyRight) == sfTrue
      || sfKeyboard_isKeyPressed(sfKeyD) == sfTrue)
    did_smg += move_player(wa, wa->p1, 1, 0);
  if (sfKeyboard_isKeyPressed(sfKeySpace) == sfTrue
      && wa->p1->jump >= wa->pxls->width)
    wa->p1->jump = 0;
  if (!wa->p1->dead && !wa->p1->reload && !wa->p1->onde &&
      (sfKeyboard_isKeyPressed(sfKeyZ) == sfTrue
       || sfKeyboard_isKeyPressed(sfKeyReturn) == sfTrue))
    {
      sfMusic_play(wa->punch_sound_1);
      wa->p1->reload = 250;
      wa->p1->onde = 24;
      sfMusic_play(wa->punch_sound_2);
    }
  draw_all(wa);
  return (did_smg);
}
