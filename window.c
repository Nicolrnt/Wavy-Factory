/*
** window.c for game_jam_2017 in /home/thery/Bureau/game_jam_2017
** 
** Made by Thery
** Login   <thery.fouchter@epitech.eu@epitech.net>
** 
** Started on  Sun Jan 22 00:00:55 2017 Thery
** Last update Sun Jan 22 00:01:06 2017 Thery
*/

#include "game.h"

sfRenderWindow		*init_window(int width, int height,
				     int *error, t_settings *config)
{
  sfRenderWindow	*window;
  sfVideoMode		mode;
  sfVector2i		pos;
  sfVideoMode		dsk;

  mode.width = width;
  mode.height = height;
  mode.bitsPerPixel = BITS_PER_PXL;
  if (config->fullscreen == 0)
    window = sfRenderWindow_create(mode, MAIN_TITLE, WIN_STYLE, NULL);
  else
    {
      mode.width = 1920;
      mode.height = 1080;
      window = sfRenderWindow_create(mode, MAIN_TITLE, WIN_STYLE | sfFullscreen, NULL);
    }
  dsk = sfVideoMode_getDesktopMode();
  pos.x = dsk.width / 2 - width / 2;
  pos.y = dsk.height / 2 - height / 2;
  sfRenderWindow_setPosition(window, pos);
  if (!window)
    {
      error ? (*error += 1) : 0;
      return (NULL);
    }
  sfRenderWindow_clear(window, sfBlack);
  sfRenderWindow_setMouseCursorVisible(window, sfFalse);
  return (window);
}
