/*
** player.c for game_jam_2017 in /home/thery/Bureau/game_jam_2017
** 
** Made by Thery
** Login   <thery.fouchter@epitech.eu@epitech.net>
** 
** Last update Sun Jan 22 13:30:29 2017 nils cambreleng
** Last update Sun Jan 22 03:09:54 2017 nils cambreleng
*/

#include "game.h"

void	reset_player(t_wa *wa, t_player *pl)
{
  pl->pos.x = 200;
  pl->pos.y = wa->tapis - 50;
  pl->speed = 20.0;
  pl->jump = wa->pxls->width;
  pl->onde = 0;
  pl->stun = 0;
  pl->invincible = 0;
  pl->reload = 0;
  pl->dead = 0;
}

t_player	*create_player(t_wa *wa)
{
  t_player	*pl;

  if ((pl = malloc(sizeof(*pl))) == NULL)
    return (NULL);
  reset_player(wa, pl);
  return (pl);
}

int		move_player(t_wa *wa, t_player *pl, int x, int y)
{
  sfVector2f	m;

  if (pl->dead)
    return (0);
  if (pl->stun)
    return (0);
  else
    m = (sfVector2f){pl->speed * x, pl->speed * y};
  if (wa->p1->pos.x + m.x < wa->pxls->width)
    {
      pl->pos.x += m.x;
      pl->pos.y += m.y;
    }
  return (1);
}

int	gravity_pos(t_wa *wa, float *y, int ground)
{
  *y += 8.0;
  if (*y > ground)
    *y = ground;
  else if (*y == ground)
    return (0);
  return (1);
}

int	change_player_pos(t_wa *wa, t_player *pl)
{
  if (pl->pos.x < 0)
    pl->dead = 1;
  if (pl->dead)
    {
      pl->pos.x = -200;
      return (0);
    }
  if (!wa->p1->invincible && wa->p1->stun)
    wa->p1->pos.x -= 20.0;
  wa->p1->pos.y = height_calc(wa);
  return (1);
}
