/*
** main.c for wavy_factory in /home/thery/Bureau/game_jam_2017
** 
** Made by Thery
** Login   <thery.fouchter@epitech.eu@epitech.net>
** 
** Started on  Sat Jan 21 13:35:30 2017 Thery
** Last update Sun Jan 22 13:27:58 2017 Lucas Le Ray
*/

#include "game.h"

int	main(int ac, char **av)
{
  t_settings    config;

  config.fullscreen = 0;
  config.resolution.x = 1024;
  config.resolution.y = 720;
  if (av[1] != NULL && atoi(av[1]) >= 1 && atoi(av[1]) <= 3)
    config.theme = atoi(av[1]);
  else
    config.theme = 1;
  if (av[2] != NULL && atoi(av[2]) >= 1 && atoi(av[2]) <= 10)
    config.difficulty = atoi(av[2]);
  else
    config.difficulty = 3;
  return (wavy_factory(&config));
}
