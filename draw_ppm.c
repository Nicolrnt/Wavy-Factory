/*
** draw_ppm.c<game_jam_2017> for game_jam_2017 in /home/thery/Bureau/game_jam_2017
** 
** Made by Thery
** Login   <thery.fouchter@epitech.eu@epitech.net>
** 
** Started on  Sat Jan 21 20:05:28 2017 Thery
** Last update Sun Jan 22 09:51:54 2017 Thery
*/

#include "game.h"

void	secure_coo_ppm(t_ppm *ppm, int *x, int *y)
{
  if (*x >= ppm->size.x)
    *x = ppm->size.x - 1;
  else if (x < 0)
    *x = 0;
  if (*y >= ppm->size.y)
    *y = ppm->size.y - 1;
  else if (*y < 0)
    *y = 0;
}

int	get_inc_stun_color(int cur)
{
  int	swap;

  swap = 1;
  while (cur > 0)
    {
      cur -= 5;
      swap = -swap;
    }
  if (swap > 0)
    return (50);
  return (-20);
}

void		draw_ppm_resize(t_wa *wa,
				t_ppm *ppm,
				sfVector2i pos,
				sfVector2i size)
{
  sfVector2f	p;
  sfVector2f	inc;
  sfVector2i	p_int;
  int		x;
  int		y;
  int		inc_color;
  sfColor	c;

  inc_color = 0;
  if (wa->modif_player && (wa->p1->stun || wa->p1->invincible))
    {
      inc_color = get_inc_stun_color(wa->cur_animate_stun);
      wa->cur_animate_stun += 1;
    }
  p.y = 0;
  inc.x = (float)ppm->size.x / size.x;
  inc.y = (float)ppm->size.y / size.y;
  y = pos.y - 1;
  while (++y < pos.y + size.y)
    {
      p.x = 0;
      x = pos.x - 1;
      while (++x < pos.x + size.x)
	{
	  p_int.x = (int)p.x;
	  p_int.y = (int)p.y;
	  secure_coo_ppm(ppm, &p_int.x, &p_int.y);
	  c = ppm->c[p_int.y][p_int.x];
	  if (c.r >= 245 && c.g <= 20 && c.b >= 245);
	  else if (inc_color)
	    {
	      c.r += inc_color;
	      c.g += inc_color;
	      c.b += inc_color;
	      c.r = (c.r >= 255 ? 255 : c.r <= 0 ? 0 : c.r);
	      c.g = (c.g >= 255 ? 255 : c.g <= 0 ? 0 : c.g);
	      c.b = (c.b >= 255 ? 255 : c.b <= 0 ? 0 : c.b);
	    }
	  put_pixel(wa, x, y, c);
	  p.x += inc.x;
	}
      p.y += inc.y;
    }
}
