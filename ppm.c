/*
** ppm.c<game_jam_2017> for wavy_factory in /home/thery/Bureau/game_jam_2017
** 
** Made by Thery
** Login   <thery.fouchter@epitech.eu@epitech.net>
** 
** Started on  Sat Jan 21 19:01:59 2017 Thery
** Last update Sat Jan 21 20:13:38 2017 Thery
*/

#include "game.h"

static char	*go_to_next_nb(char *str)
{
  int		i;

  i = 0;
  while (str[i] && str[i] >= '0' && str[i] <= '9')
    i += 1;
  while (str[i] && (str[i] < '0' || str[i] > '9'))
    i += 1;
  return (&str[i]);
}

static sfVector2i	ppm_get_size(char **data)
{
  char			*str;
  sfVector2i		size;
  int			i;

  str = *data;
  size.x = 0;
  size.y = 0;
  i = -1;
  while (str[++i] && str[i] != '\n');
  i += 1;
  while (str[i] && str[i] == '#')
    {
      while (str[++i] && str[i] != '\n');
      i += 1;
    }
  size.x = get_ppm_nbr(&str[i]);
  str = go_to_next_nb(&str[i]);
  size.y = get_ppm_nbr(str);
  str = go_to_next_nb(str);
  str = go_to_next_nb(str);
  *data = str;
  return (size);
}

int	get_ppm_nbr(char *data)
{
  int	i;
  int	nb;

  nb = 0;
  i = 0;
  while (data[i] && data[i] >= '0' && data[i] <= '9')
    nb = (nb * 10) + (data[i++] - '0');
  return (nb);
}

char	*read_data(char *path)
{
  int	fd;
  int	size_rd;
  int	size;
  char	*data;

  if ((fd = open(path, O_RDONLY)) == -1)
    return (NULL);
  if ((data = malloc(sizeof(char) * 20)) == NULL)
    return (NULL);
  size = 0;
  while ((size_rd = read(fd, data, 20)) > 0)
    size += size_rd;
  close(fd);
  free(data);
  if ((fd = open(path, O_RDONLY)) == -1)
    return (NULL);
  if ((data = malloc(sizeof(char) * (size + 1))) == NULL)
    return (NULL);
  if ((read(fd, data, size)) == -1)
    return (NULL);
  close(fd);
  data[size] = 0;
  return (data);
}

t_ppm		*init_ppm(char *path)
{
  t_ppm		*ppm;
  char		*data;
  char		*ori_data;

  if ((ppm = malloc(sizeof(*ppm))) == NULL)
    return (NULL);
  if ((data = read_data(path)) == NULL)
    return (NULL);
  ori_data = data;
  if (data[0] && data[1] && data[1] != '3')
    return (NULL);
  ppm->size = ppm_get_size(&data);
  if ((ppm->c = init_ppm_c(ppm->size)) == NULL)
    return (NULL);
  if (complete_ppm(ppm, data) == -1)
    return (NULL);
  free(ori_data);
  return (ppm);
}

sfColor		**init_ppm_c(sfVector2i size)
{
  sfColor	**ppm;
  int		x;
  int		y;

  if (size.x <= 0 || size.y <= 0)
    return (NULL);
  if ((ppm = malloc(sizeof(*ppm) * size.y)) == NULL)
    return (NULL);
  y = -1;
  while (++y < size.y)
    {
      if ((ppm[y] = malloc(sizeof(**ppm) * size.x)) == NULL)
	return (NULL);
      x = -1;
      while (++x < size.x)
	{
	  ppm[y][x].r = 255;
	  ppm[y][x].g = 255;
	  ppm[y][x].b = 255;
	  ppm[y][x].a = 255;
	}
    }
  return (ppm);
}

int	complete_ppm(t_ppm *ppm, char *data)
{
  int	x;
  int	y;

  y = -1;
  while (++y < ppm->size.y)
    {
      x = -1;
      while (++x < ppm->size.x)
	{
	  ppm->c[y][x].r = get_ppm_nbr(data);
	  data = go_to_next_nb(data);
	  ppm->c[y][x].g = get_ppm_nbr(data);
	  data = go_to_next_nb(data);
	  ppm->c[y][x].b = get_ppm_nbr(data);
	  data = go_to_next_nb(data);
	}
    }
  return (0);
}
