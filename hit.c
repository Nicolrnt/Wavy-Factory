/*
** hit.c for  in /home/nils/projet/GLOBAL_GAME_JAM1/clone/game_jam_2017v3
** 
** Made by nils cambreleng
** Login   <nils@epitech.net>
** 
** Started on  Sun Jan 22 02:48:25 2017 nils cambreleng
** Last update Sun Jan 22 03:54:51 2017 nils cambreleng
*/

#include "game.h"

void	destruction(t_wa *wa)
{
  t_event	*tmp;
  float		dist;
  sfVector2f	coo;

  if (wa->p1->onde == 24)
    {
      tmp = wa->events->next;
      while (tmp)
	{
	  if (tmp->box)
	    {
	      coo = (sfVector2f){tmp->pos.x, tmp->pos.y - 50};
	      dist = sqrtf(((wa->p1->pos.x - coo.x) * (wa->p1->pos.x - coo.x)) +
			   ((wa->p1->pos.y - coo.y) * (wa->p1->pos.y - coo.y)));
	      if (dist < 400)
		{
		  tmp->destruction = tmp->destruction - 1;
		  wa->score = wa->score + 20;
		}
	    }
	  tmp = tmp->next;
	}
    }
  if (wa->p1->onde > 0)
    wa->p1->onde = wa->p1->onde - 1;
}
