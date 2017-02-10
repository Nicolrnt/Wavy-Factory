/*
** events.c<game_jam_2017> for wavy_factory in /home/thery/Bureau/game_jam_2017
** 
** Made by Thery
** Login   <thery.fouchter@epitech.eu@epitech.net>
** 
** Started on  Sat Jan 21 14:28:43 2017 Thery
** Last update Sun Jan 22 13:29:53 2017 Thery
*/

#include "game.h"

t_event		*create_event(void)
{
  t_event	*event;

  if ((event = malloc(sizeof(t_event))) == NULL)
    return (NULL);
  event->next = NULL;
  event->last = NULL;
  event->magnet = 0;
  event->box = 0;
  event->pos = (sfVector2f){0.0, 0.0};
  event->speed = 0.0;
  event->ppm = NULL;
  event->random = 0;
  return (event);
}

void		add_event(t_event *src, t_event *new)
{
  t_event	*tmp;

  tmp = src;
  while (tmp->next)
    tmp = tmp->next;
  tmp->next = new;
  src->last = new;
}

t_event		*get_next_event(t_event *src)
{
  t_event	*ext;

  if (!src->next)
    return (NULL);
  ext = src->next;
  src->next = ext->next;
  if (!src->next)
    src->last = src;
  return (ext);
}

t_event		*init_events(void)
{
  t_event	*event;

  event = create_event();
  event->last = event;
  return (event);
}

int	main_events(t_wa *wa, sfEvent *event)
{
  int	did_smg;

  did_smg = 0;
  if (event->type == sfEvtClosed
      || (event->type == sfEvtKeyPressed
	  && event->key.code == sfKeyEscape))
    sfRenderWindow_close(wa->win);
  else if (event->type != sfEvtKeyPressed);
  else if (event->key.code == sfKeyR && wa->p1->dead)
    {
      reset_wa(wa);
      did_smg += 1;
    }
  if (did_smg)
    draw_all(wa);
  return (did_smg);
}

void	handle_random_events(t_wa *wa, int difficulty)
{
  change_player_pos(wa, wa->p1);
  wa->delta_time = wa->time - wa->time_zero;
  if (wa->delta_time >= 6)
    {
      add_event(wa->events, event_magnet(wa));
      wa->time_zero = wa->time;
    }
  else if (rand() % (100 / (difficulty * 2)) == 1)
    add_event(wa->events, event_box(wa));
}
