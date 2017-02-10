/*
** text.c for game_jam_2017 in /home/thery/Bureau/game_jam_2017
** 
** Made by Thery
** Login   <thery.fouchter@epitech.eu@epitech.net>
** 
** Started on  Sun Jan 22 07:46:48 2017 Thery
** Last update Sun Jan 22 09:38:50 2017 Thery
*/

#include "game.h"

sfText		*create_text(char *str, int x, int y, int size)
{
  sfText	*text;
  sfFont	*font;
  sfVector2f	pos;

  pos.x = x;
  pos.y = y;
  font = sfFont_createFromFile(DEFAULT_FONT);
  text = sfText_create();
  sfText_setString(text, str);
  sfText_setFont(text, font);
  sfText_setCharacterSize(text, size);
  sfText_setPosition(text, pos);
  return (text);
}

char	*nb_to_text(int nb)
{
  char	*str;
  int	length;
  int	nb_cp;

  if (nb <= 0)
    return (strdup("0"));
  nb_cp = nb;
  length = 1;
  while (nb_cp % 10 != nb_cp)
    {
      length += 1;
      nb_cp /= 10;
    }
  if ((str = malloc(sizeof(*str) * (length + 1))) == NULL)
    return (NULL);
  str[length] = 0;
  while (length > 0)
    {
      str[--length] = (nb % 10) + '0';
      nb /= 10;
    }
  return (str);
}

char	*get_score(int sc)
{
  char	*score;
  char	*nb;
  int	i;
  int	pos_score;

  sc = (sc >= 99999 ? 99999 : sc);
  nb = nb_to_text(sc);
  if ((score = malloc(sizeof(char) * 6)) == NULL)
    return (NULL);
  i = -1;
  while (nb[++i]);
  pos_score = 5 - i;
  i = -1;
  while (++i < pos_score)
    score[i] = '0';
  i = -1;
  while (nb[++i])
    score[pos_score++] = nb[i];
  score[5] = 0;
  free(nb);
  return (score);
}

char	*stick_str(char *s1, char *s2, char sep)
{
  int	i;
  int	length;
  char	*str;
  int	pos_str;

  length = (sep ? 2 : 1);
  i = -1;
  while (s1[++i])
    length += 1;
  i = -1;
  while (s2[++i])
    length += 1;
  if ((str = malloc(sizeof(*str) * length)) == NULL)
    return (NULL);
  pos_str = 0;
  i = -1;
  while (s1[++i])
    str[pos_str++] = s1[i];
  sep ? (str[pos_str++] = sep) : 0;
  i = -1;
  while (s2[++i])
    str[pos_str++] = s2[i];
  str[pos_str] = 0;
  return (str);
}

void	update_texts(t_wa *wa)
{
  char	*nb;

  if (wa->str_score)
    free(wa->str_score);
  nb = get_score(wa->score);
  wa->str_score = stick_str(nb, "pts", ' ');
  free(nb);
  sfText_setString(wa->txt_score, wa->str_score);
}
