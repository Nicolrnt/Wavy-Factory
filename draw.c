/*
** draw.c<game_jam_2017> for wavy_factory in /home/thery/Bureau/game_jam_2017
** 
** Made by Thery
** Login   <thery.fouchter@epitech.eu@epitech.net>
** 
** Started on  Sat Jan 21 14:28:13 2017 Thery
** Last update Sun Jan 22 13:26:02 2017 Thery
*/

#include "game.h"

int	get_rand_box_pos(void)
{
  int	r1;
  int	r2;

  r1 = (rand() % 2);
  r2 = (rand() % 2);
  if (r1 && r2)
    return (0);
  else if (r1 && !r2)
    return (10);
  else if (!r1 && r2)
    return (20);
  return (30);
}

sfColor		sum_color(sfColor c1, sfColor c2, float coef_c2)
{
  if (coef_c2 <= 0)
    coef_c2 = 1;
  c1.r = (c1.r + coef_c2 * c2.r) / (1.0 + coef_c2);
  c1.g = (c1.g + coef_c2 * c2.g) / (1.0 + coef_c2);
  c1.b = (c1.b + coef_c2 * c2.b) / (1.0 + coef_c2);
  c1.a = 255;
  return (c1);
}

void		draw_rect(t_wa *wa, sfVector2i coo,
			  sfVector2i size, sfColor color)
{
  sfColor	c1;
  int		x;
  int		y;
  int		pos_c;

  y = coo.y;
  while (y++ < coo.y + size.y)
    {
      x = coo.x;
      while (x++ < coo.x + size.x)
	{
	  pos_c = ((wa->pxls->width * y) + x) * 4;
	  c1.r = wa->pxls->pixels[pos_c];
	  c1.g = wa->pxls->pixels[pos_c + 1];
	  c1.b = wa->pxls->pixels[pos_c + 2];
	  c1.a = wa->pxls->pixels[pos_c + 3];
	  c1 = sum_color(c1, color, 1.0);
	  put_pixel(wa, x, y, c1);
	}
    }
}

void		draw_events(t_wa *wa)
{
  t_event	*tmp;
  t_event	*last;
  sfVector2i	coo;
  sfVector2i	size;
  sfVector2f    po;
  sfVector2i    si;
  t_event	*t;

  last = wa->events;
  size = (sfVector2i){100, 100};
  tmp = wa->events->next;
  while (tmp)
    {
      if (tmp->magnet)
	{
	  coo = (sfVector2i){tmp->pos.x - 50, tmp->pos.y - 100};
	  if (wa->cur_pp_magnet_red->init || !wa->cur_pp_magnet_red->ppm)
	    wa->cur_pp_magnet_red = wa->cur_pp_magnet_red->next;
	  draw_ppm_resize(wa, wa->cur_pp_magnet_red->ppm, coo, size);
	  wa->cur_pp_magnet_red = wa->cur_pp_magnet_red->next;
	  tmp->pos.x += tmp->speed;
	  if (tmp->pos.x < -500)
	    last->next = tmp->next;
	}
      else if (tmp->box)
	{
	  coo.x = tmp->pos.x - 50;
	  tmp->pos.y = wa->tapis;
	  t = wa->events;
	  while (t)
	    {
	      if (t->magnet)
		{
		  si.x = wa->pxls->width;
		  si.y = wa->pxls->height;
		  po.x = t->pos.x;
		  po.y = t->pos.y;
		  if (tmp->pos.y > wave_calc(tmp->pos.x, po, si, wa))
		    tmp->pos.y = wave_calc(tmp->pos.x, po, si, wa);
		}
	      t = t->next;
	    }
	  //coo.y = tmp->pos.y - 120;
	  coo.y = tmp->pos.y - 100 - tmp->random;
	  if (tmp->destruction == 12)
	    draw_ppm_resize(wa, tmp->ppm, coo, size);
	  else
	    draw_ppm_resize(wa, tmp->destroy, coo, size);
	  tmp->pos.x += tmp->speed;
	  if (tmp->destruction < 12)
	    tmp->destruction = tmp->destruction - 1;
	  if (tmp->destruction < 1)
	    last->next = tmp->next;
	  if (tmp->pos.x < -500)
	    last->next = tmp->next;
	}
      last = tmp;
      tmp = tmp->next;
    }
}

void		draw_player(t_wa *wa)
{
  sfVector2i	coo;
  sfVector2i	size;

  wa->modif_player = 1;
  coo = (sfVector2i){wa->p1->pos.x - 50, wa->p1->pos.y - 50 - 20};
  size = (sfVector2i){100, 100};
  if (wa->p1->stun > 0)
    {
      if (wa->cur_pp_stun->init || !wa->cur_pp_stun->ppm)
	wa->cur_pp_stun = wa->cur_pp_stun->next;
      draw_ppm_resize(wa, wa->cur_pp_stun->ppm, coo, size);
      wa->cur_pp_stun = wa->cur_pp_stun->next;
      wa->p1->stun -= 1;
      if (wa->p1->stun <= 0)
	wa->p1->invincible = 20;
    }
  else if (wa->p1->jump <= wa->pxls->width)
    {
      if (wa->cur_pp_jump->init || !wa->cur_pp_jump->ppm)
	wa->cur_pp_jump = wa->cur_pp_jump->next;
      draw_ppm_resize(wa, wa->cur_pp_jump->ppm, coo, size);
      wa->cur_pp_jump = wa->cur_pp_jump->next;
    }
  else
    {
      if (wa->cur_pp_run->init || !wa->cur_pp_run->ppm)
	wa->cur_pp_run = wa->cur_pp_run->next;
      draw_ppm_resize(wa, wa->cur_pp_run->ppm, coo, size);
      wa->cur_pp_run = wa->cur_pp_run->next;
    }
  if (wa->p1->onde)
    {
      coo = (sfVector2i){wa->p1->pos.x - 300, wa->p1->pos.y - 300 - 20};
      size = (sfVector2i){600, 600};
      if (wa->p1->onde > 20)
	draw_ppm_resize(wa, wa->pp_shock_wave->next->ppm, coo, size);
      else if (wa->p1->onde > 16)
	draw_ppm_resize(wa, wa->pp_shock_wave->next->next->ppm, coo, size);
    }
  if (!wa->p1->stun)
    wa->cur_pp_stun = wa->pp_stun->next;
  if (wa->p1->invincible)
    wa->p1->invincible -= 1;
  if (wa->p1->reload)
    wa->p1->reload -= 1;
  wa->modif_player = 0;
}

void	draw_background(t_wa *wa)
{
  sfVector2i	coo;
  sfVector2i	size;
  int	len_buff;
  int	i;

  if (!wa->pxls_background)
    {
      coo = (sfVector2i){0, 0};
      size = (sfVector2i){wa->pxls->width, wa->pxls->height};
      if (wa->cur_pp_background->init || !wa->cur_pp_background->ppm)
	wa->cur_pp_background = wa->cur_pp_background->next;
      draw_ppm_resize(wa, wa->cur_pp_background->ppm, coo, size);
      wa->cur_pp_background = wa->cur_pp_background->next;
      len_buff = wa->pxls->width * wa->pxls->height * 4;
      wa->pxls_background = malloc(sizeof(*wa->pxls_background) * len_buff);
      i = -1;
      while (++i < len_buff)
	wa->pxls_background[i] = wa->pxls->pixels[i];
    }
  else
    {
      i = -1;
      while (++i < len_buff)
	wa->pxls->pixels[i] = wa->pxls_background[i];
    }
}

void	draw_trap(t_wa *wa)
{
  sfVector2i	coo;
  sfVector2i	size;

  coo = (sfVector2i){0, 0};
  size = (sfVector2i){150, wa->pxls->height};
  draw_ppm_resize(wa, wa->pp_trap->next->next->ppm, coo, size);
  coo = (sfVector2i){wa->pxls->width - 150, 0};
  draw_ppm_resize(wa, wa->pp_trap->next->ppm, coo, size);
}

void	draw_texts(t_wa *wa)
{
  sfRenderWindow_drawText(wa->win, wa->txt_score, NULL);
  if (wa->p1->dead)
    {
      wa->config->difficulty = 5;
      sfRenderWindow_drawText(wa->win, wa->txt_loose, NULL);
    }
}

void		draw_reload(t_wa *wa)
{
  int		perc;
  sfVector2i	coo;
  sfVector2i	size;

  coo = (sfVector2i){wa->pxls->width / 2 - 90, 70};
  size = (sfVector2i){250, 50};
  draw_rect(wa, coo, size, sfBlack);
  size = (sfVector2i){250 - wa->p1->reload, 50};
  draw_rect(wa, coo, size, sfBlue);
}

int	draw_all(t_wa *wa)
{
  clear_pxls(wa->pxls);
  draw_background(wa);
  draw_floor(wa);
  draw_events(wa);
  draw_player(wa);
  draw_reload(wa);
  update_pxls(wa->pxls);
  draw_texts(wa);
  return (0);
}
