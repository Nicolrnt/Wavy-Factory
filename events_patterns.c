/*
** events_patterns.c for game_jam_2017 in /home/thery/Bureau/game_jam_2017
** 
** Made by Thery
** Login   <thery.fouchter@epitech.eu@epitech.net>
** 
** Started on  Sun Jan 22 00:00:06 2017 Thery
** Last update Sun Jan 22 12:41:02 2017 Thery
*/

#include "game.h"

t_event		*event_box(t_wa *wa)
{
  t_event	*e;

  e = create_event();
  e->box = 1;
  e->pos.x = wa->pxls->width + 500;
  e->pos.y = wa->tapis;
  e->destruction = 12;
  e->speed = -10.0;
  if (rand() % 2)
    e->ppm = wa->pp_caisse->next->ppm;
  else
    e->ppm = wa->pp_caisse->next->next->ppm;
  e->destroy = wa->pp_caisse->next->next->next->ppm;
  e->random = get_rand_box_pos();
  return (e);
}

t_event		*event_magnet(t_wa *wa)
{
  t_event	*e;

  e = create_event();
  e->magnet = 1;
  e->pos.x = wa->pxls->width + 500;
  e->pos.y = wa->pxls->height / 4 * 3 + 50 + (rand() % 150);
  e->speed = -10.0;
  return (e);
}
