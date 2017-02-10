/*
** draw_pxls.c for game_jam_2017 in /home/thery/Bureau/game_jam_2017
** 
** Made by Thery
** Login   <thery.fouchter@epitech.eu@epitech.net>
** 
** Started on  Sun Jan 22 00:03:41 2017 Thery
** Last update Sun Jan 22 00:03:49 2017 Thery
*/

#include "game.h"

void	put_pixel(t_wa *wa, int x, int y, sfColor color)
{
  int	pos;

  if (color.r >= 245 && color.g <= 20 && color.b >= 245);
  else if (x >= 0 && x < wa->pxls->width && y >= 0 && y < wa->pxls->height)
    {
      pos = (((wa->pxls->width * y) + x) * 4);
      wa->pxls->pixels[pos] = color.r;
      wa->pxls->pixels[pos + 1] = color.g;
      wa->pxls->pixels[pos + 2] = color.b;
      wa->pxls->pixels[pos + 3] = color.a;
    }
}

void	draw_square(t_wa *wa, sfVector2i coo,
		    int size, sfColor color)
{
  int	x;
  int	y;

  y = coo.y;
  while (y++ < coo.y + size)
    {
      x = coo.x - size / 2;
      while (x++ < coo.x + size / 2)
	put_pixel(wa, x, y, color);
    }
}
