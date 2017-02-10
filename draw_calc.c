/*
** draw_calc.c for game_jam_2017 in /home/thery/Bureau/game_jam_2017
** 
** Made by Thery
** Login   <thery.fouchter@epitech.eu@epitech.net>
** 
** Started on  Sun Jan 22 00:04:39 2017 Thery
** Last update Sun Jan 22 00:04:46 2017 Thery
*/

#include "game.h"

int	*my_setup_tapis(int *wave, sfVector2i size, sfVector2f pos, t_wa *wa)
{
  int	i;
  int	tmp;

  i = -1;
  while (++i < wa->pxls->width)
    {
      tmp = wave_calc(i, pos, size, wa);
      if (tmp < wave[i])
	wave[i] = tmp;
    }
  return (wave);
}

int		*get_wave(t_wa *wa)
{
  int		*wave;
  int		i;
  t_event	*tmp;
  sfVector2f	pos;
  sfVector2i	size;

  wave = malloc(sizeof(int) * wa->pxls->width);
  i = -1;
  while (++i < wa->pxls->width)
    wave[i] = wa->tapis;
  tmp = wa->events;
  while (tmp)
    {
      if (tmp->magnet)
	{
	  size.x = wa->pxls->width;
	  size.y = wa->pxls->height;
	  pos.x = tmp->pos.x;
	  pos.y = tmp->pos.y;
	  wave = my_setup_tapis(wave, size, pos, wa);
	}
      tmp = tmp->next;
    }
  return (wave);
}
