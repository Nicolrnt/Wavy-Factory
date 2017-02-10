/*
** pp.c for wavy_factory in /home/thery/Bureau/game_jam_2017
** 
** Made by Thery
** Login   <thery.fouchter@epitech.eu@epitech.net>
** 
** Started on  Sat Jan 21 19:05:05 2017 Thery
** Last update Sat Jan 21 20:35:28 2017 Thery
*/

#include "game.h"

t_pp	*create_pp(t_ppm *ppm)
{
  t_pp	*pp;

  if ((pp = malloc(sizeof(*pp))) == NULL)
    return (NULL);
  pp->next = NULL;
  pp->init = 0;
  pp->ppm = ppm;
  return (pp);
}

t_ppm	*append_ppm(char *path, int pos, int *nb)
{
  if (*nb <= 9)
    {
      path[pos] = '0';
      path[pos + 1] = '0';
      path[pos + 2] = *nb + '0';
    }
  else if (*nb <= 99)
    {
      path[pos] = '0';
      path[pos + 1] = (*nb / 10) + '0';
      path[pos + 2] = (*nb % 10) + '0';
    }
  else
    {
      path[pos] = (*nb / 100) + '0';
      path[pos + 1] = (*nb % 10 / 10) + '0';
      path[pos + 2] = (*nb % 10) + '0';
    }
  *nb += 1;
  return (init_ppm(path));
}

t_pp	*create_animate_pp(char *path, int nb)
{
  t_pp	*pp;
  t_pp	*new;
  int	pos;
  int	cur_nb;

  path = strdup(path);
  pos = -1;
  while (path[++pos]);
  pos -= 7;
  pp = create_pp(NULL);
  pp->init = 1;
  new = pp;
  cur_nb = 0;
  while (cur_nb < nb)
    {
      new->next = create_pp(append_ppm(path, pos, &cur_nb));
      new = new->next;
      new->next = pp;
    }
  return (pp);
}
