/*
** collisions.c for  in /home/nils/projet/GLOBAL_GAME_JAM1/clone/game_jam_2017v2
** 
** Made by nils cambreleng
** Login   <nils@epitech.net>
** 
** Started on  Sat Jan 21 22:08:47 2017 nils cambreleng
** Last update Sun Jan 22 11:20:18 2017 Thery
*/

#include "game.h"

int	collision_box(t_wa *wa)
{
  t_event	*tmp;
  sfVector2f	coo;
  float		dist;

  tmp = wa->events->next;
  while (tmp)
    {
      if (tmp->box && tmp->destruction == 12)
	{
	  coo = (sfVector2f){tmp->pos.x, tmp->pos.y - 50};
	  dist = sqrtf(((wa->p1->pos.x - coo.x) * (wa->p1->pos.x - coo.x)) +
		       ((wa->p1->pos.y - coo.y) * (wa->p1->pos.y - coo.y)));
	  if (dist < 100)
	    return (1);
	}
      tmp = tmp->next;
    }
  return (0);
}

int	collision_sol(t_wa *wa)
{
  if (wa->p1->pos.y > wa->wave[(int)wa->p1->pos.x])
    return (1);
  return (0);
}

int	collision_events(t_wa *wa)
{
  if (collision_sol(wa) == 1)
    wa->p1->pos.y = wa->wave[(int)wa->p1->pos.x] - wa->cur_pp_tapis->ppm->size.y;
  if (!wa->p1->invincible && !wa->p1->stun && collision_box(wa) == 1)
    {
      wa->p1->stun = 50;
      sfMusic_play(wa->hit_sound);
    }
}
