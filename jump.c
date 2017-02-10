/*
** jump.c for  in /home/nils/projet/GLOBAL_GAME_JAM1/clone/game_jam_2017_clone1
** 
** Made by nils cambreleng
** Login   <nils@epitech.net>
** 
** Started on  Sat Jan 21 18:26:37 2017 nils cambreleng
** Last update Sun Jan 22 01:12:33 2017 Lucas Le Ray
** Last update Sat Jan 21 22:30:29 2017 nico_lrnt
** Last update Sun Jan 22 00:37:23 2017 Thery
*/

#include "game.h"

int	height_calc(t_wa *wa)
{
  float	tmp;
  int	height;

  if (wa->p1->jump > wa->pxls->width)
    return (wa->tapis - 52);
  tmp = wa->pxls->width / 2;
  tmp = cosf((wa->p1->jump - (wa->pxls->width / 2)) * ((M_PI / 2) / tmp));
  height = wa->tapis - 52 - (tmp * (float)wa->pxls->height) / 2.0;
  wa->p1->jump = wa->p1->jump + 52;
  //printf("jump = %d\n", wa->p1->jump);
  return (height);
}
