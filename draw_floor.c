/*
** draw_floor.c for game_jam_2017 in /home/thery/Bureau/game_jam_2017
** 
** Made by Thery
** Login   <thery.fouchter@epitech.eu@epitech.net>
** 
** Started on  Sun Jan 22 00:05:25 2017 Thery
** Last update Sun Jan 22 12:00:39 2017 Thery
*/

#include "game.h"

t_ppm		*next_ppm_tapis(t_wa *wa, t_ppm **ppm2)
{
  t_ppm		*ppm;

  wa->cur_pp_tapis = wa->cur_pp_tapis->next;
  wa->cur_pp_tapisup = wa->cur_pp_tapisup->next;
  ppm = wa->cur_pp_tapis->ppm;
  *ppm2 = wa->cur_pp_tapisup->ppm;
  if (wa->cur_pp_tapis->init || !ppm)
    {
      wa->cur_pp_tapis = wa->cur_pp_tapis->next;
      ppm = wa->cur_pp_tapis->ppm;
    }
  if (wa->cur_pp_tapisup->init || !ppm)
    {
      wa->cur_pp_tapisup = wa->cur_pp_tapisup->next;
      *ppm2 = wa->cur_pp_tapisup->ppm;
    }
  return (ppm);
}

void		draw_floor(t_wa *wa)
{
  int		x;
  int		y;
  int		y2;
  int		size;
  t_ppm		*ppm;
  t_ppm		*ppm2;
  sfVector2i	p_int;
  int		tex_x;
  int		tex_x2;
  int		tex_y;

  ppm = next_ppm_tapis(wa, &ppm2);
  if (wa->cur_pos_tapis % 2)
    ppm = next_ppm_tapis(wa, &ppm2);
  tex_x = wa->cur_pos_tapis;
  tex_x2 = wa->cur_pos_tapis;
  wa->cur_pos_tapis += 1;
  if (wa->cur_pos_tapis >= ppm->size.x)
    wa->cur_pos_tapis = 0;
  tex_y = 0;
  x = -1;
  while (++x < wa->pxls->width)
    {
      y = wa->wave[x];
      if (++tex_x >= ppm->size.x)
	tex_x = 0;
      if (++tex_x2 >= ppm2->size.x)
	tex_x2 = 0;
      y2 = y;
      tex_y = -1;
      while (++tex_y < ppm->size.y)
	{
	  p_int.x = tex_x;
	  p_int.y = tex_y;
	  secure_coo_ppm(ppm, &p_int.x, &p_int.y);
	  put_pixel(wa, x, y++, ppm->c[p_int.y][p_int.x]);
	}
      tex_y = ppm2->size.y;
      while (tex_y >= 0)
	{
	  p_int.x = tex_x2;
	  p_int.y = tex_y;
	  secure_coo_ppm(ppm2, &p_int.x, &p_int.y);
	  put_pixel(wa, x, y2--, ppm2->c[p_int.y][p_int.x]);
	  tex_y -= 4;
	}
    }
}
