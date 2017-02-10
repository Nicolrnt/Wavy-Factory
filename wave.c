/*
** wave.c for  in /home/nils/projet/GLOBAL_GAME_JAM1/game_jam_2017
** 
** Made by nils cambreleng
** Login   <nils@epitech.net>
** 
** Started on  Sat Jan 21 14:10:33 2017 nils cambreleng
** Last update Sat Jan 21 19:18:54 2017 nils cambreleng
*/

#include "game.h"

int	wave_calc(int x, sfVector2f pos, sfVector2i size, t_wa *wa)
{
  float	y;
  float	tmp;
  float	height;

  y = (wa->tapis / pos.y) * (wa->tapis / pos.y);//y peut être précalculer
  tmp = (size.x * y) / 3;// on peut changer 3 pour augmenter la longeur des vagues
  if (x + tmp < pos.x || x - tmp > pos.x)
    return (wa->tapis);// on peut définir la constante de retour pour opti les calculs
  height = y * cosf((x - pos.x) * ((M_PI / 2) / tmp)); //on calcul la hauteur théorique
  height = wa->tapis - (height * size.y / 3); // maintenant on calcul la hauteur relative à l'écran (en changeant 3 on change la hauteur des vagues
  return (height);
}
