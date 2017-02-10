/*
** pxls.c<game_jam_2017> for wavy_factory in /home/thery/Bureau/game_jam_2017
** 
** Made by Thery
** Login   <thery.fouchter@epitech.eu@epitech.net>
** 
** Started on  Sat Jan 21 14:37:49 2017 Thery
** Last update Sat Jan 21 14:49:02 2017 Thery
*/

#include "game.h"

t_pxls		*create_pxls(sfRenderWindow *window, int width, int height)
{
  t_pxls	*pxls;
  int		len_buff;
  int		i;

  if ((pxls = malloc(sizeof(*pxls))) == NULL)
    return (NULL);
  pxls->win = window;
  pxls->sprite = sfSprite_create();
  pxls->texture = sfTexture_create(width, height);
  sfSprite_setTexture(pxls->sprite, pxls->texture, sfTrue);
  pxls->width = width;
  pxls->height = height;
  len_buff = width * height * 4;
  pxls->pixels = malloc(sizeof(*pxls->pixels) * len_buff);
  i = 0;
  while (i < len_buff)
    pxls->pixels[i++] = 255;
  update_pxls(pxls);
  return (pxls);
}

void	update_pxls(t_pxls *pxls)
{
  sfTexture_updateFromPixels(pxls->texture,
			     pxls->pixels,
			     pxls->width,
			     pxls->height,
			     0, 0);
  sfRenderWindow_clear(pxls->win, sfBlack);
  sfRenderWindow_drawSprite(pxls->win, pxls->sprite, NULL);
}

void	clear_pxls(t_pxls *pxls)
{
  int	length;
  int	i;

  length = pxls->width * pxls->height * 4;
  i = 0;
  while (i < length)
    pxls->pixels[i++] = 255;
}

void	free_pxls(t_pxls *pxls)
{
  sfSprite_destroy(pxls->sprite);
  sfTexture_destroy(pxls->texture);
  free(pxls);
}
