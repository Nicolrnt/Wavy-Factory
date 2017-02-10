/*
** game.c for wavy_factory in /home/thery/Bureau/game_jam_2017
** 
** Made by Thery
** Login   <thery.fouchter@epitech.eu@epitech.net>
** 
** Started on  Sat Jan 21 13:37:54 2017 Thery
** Last update Sun Jan 22 13:58:31 2017 Thery
*/

#include "game.h"

t_wa		*init_wa(t_settings *config)
{
  t_wa		*wa;
  sfVector2i	pos;

  if ((wa = malloc(sizeof(*wa))) == NULL)
    return (NULL);
  if (config->fullscreen == 0)
    wa->screen = (sfVector2i){config->resolution.x, config->resolution.y};
  else
    wa->screen = (sfVector2i){1920, 1080};
  wa->win = init_window(wa->screen.x, wa->screen.y, NULL, config);
  wa->pxls = create_pxls(wa->win, wa->screen.x, wa->screen.y);
  wa->events = init_events();
  wa->p1 = create_player(wa);
  wa->tapis = wa->pxls->height - (wa->pxls->height / 4);
  wa->time_zero = time(NULL);
  wa->time = wa->time_zero;
  wa->delta_time = 0;
  wa->pp_punch = create_animate_pp("Ressources/punch2_000.ppm", 12);
  wa->cur_pp_punch = wa->pp_punch;
  wa->pp_background = create_animate_pp("Ressources/background_000.ppm", 1);
  wa->cur_pp_background = wa->pp_background;
  wa->pxls_background = NULL;
  wa->pp_magnet_blue = create_animate_pp("Ressources/magnet_blue_000.ppm", 1);
  wa->cur_pp_magnet_blue = wa->pp_magnet_blue;
  wa->pp_magnet_red = create_animate_pp("Ressources/magnet_red_000.ppm", 1);
  wa->cur_pp_magnet_red = wa->pp_magnet_red;
  wa->pp_jump = create_animate_pp("Ressources/jump_000.ppm", 1);
  wa->cur_pp_jump = wa->pp_jump;
  wa->pp_run = create_animate_pp("Ressources/tmln_000.ppm", 62);
  wa->cur_pp_run = wa->pp_run;
  wa->pp_tapis = create_animate_pp("Ressources/tapis_000.ppm", 2);
  wa->cur_pp_tapis = wa->pp_tapis;
  wa->cur_pos_tapis = 0;
  wa->pp_caisse = create_animate_pp("Ressources/caisse_000.ppm", 3);
  wa->box = 0;
  wa->score = 0;
  wa->wave = get_wave(wa);
  wa->pp_stun = create_animate_pp("Ressources/degats_000.ppm", 15);
  wa->cur_pp_stun = wa->pp_stun;
  wa->pp_invincible = create_animate_pp("Ressources/punch2_000.ppm", 12);
  wa->pp_shock_wave = create_animate_pp("Ressources/shock_000.ppm", 2);
  wa->cur_pp_invincible = wa->pp_invincible;
  if (config->theme == 1)
    wa->background_music = sfMusic_createFromFile("Ressources/sound/background_music.ogg");
  else if (config->theme == 2)
    wa->background_music = sfMusic_createFromFile("Ressources/sound/rag_time_2.ogg");
  else
    wa->background_music = sfMusic_createFromFile("Ressources/sound/rag_time_3.ogg");
  sfMusic_setLoop(wa->background_music, sfTrue);
  wa->punch_sound_1 = sfMusic_createFromFile("Ressources/sound/electric.ogg");
  wa->punch_sound_2 = sfMusic_createFromFile("Ressources/sound/wobble.ogg");
  wa->hit_sound = sfMusic_createFromFile("Ressources/sound/impact.ogg");
  sfMusic_setVolume(wa->background_music, 20);
  sfMusic_setVolume(wa->punch_sound_1, 100);
  sfMusic_setVolume(wa->punch_sound_2, 100);
  sfMusic_setVolume(wa->hit_sound, 100);
  wa->str_score = get_score(0);
  pos = (sfVector2i){wa->pxls->width / 2 - 100, 15};
  wa->txt_score = create_text(wa->str_score, pos.x, pos.y, 40);
  sfText_setColor(wa->txt_score, sfWhite);
  wa->cur_animate_stun = 0;
  wa->modif_player = 0;
  wa->str_loose = strdup("The End.");
  pos = (sfVector2i){wa->pxls->width / 2 - 80 * 3, wa->pxls->height / 2 - 40};
  wa->txt_loose = create_text(wa->str_loose, pos.x, pos.y, 80);
  sfText_setColor(wa->txt_loose, sfWhite);
  wa->config = config;
  wa->pp_trap = create_animate_pp("Ressources/trap_000.ppm", 2);
  wa->pp_tapisup = create_animate_pp("Ressources/tapisup_000.ppm", 2);
  wa->cur_pp_tapisup = wa->pp_tapisup;
  return (wa);
}

void	free_all(t_wa *wa)
{
  sfRenderWindow_destroy(wa->win);
  free(wa->str_score);
  sfText_destroy(wa->txt_score);
  sfMusic_destroy(wa->background_music);
  sfMusic_destroy(wa->punch_sound_1);
  sfMusic_destroy(wa->punch_sound_2);
  sfMusic_destroy(wa->hit_sound);
  free_pxls(wa->pxls);
  free(wa);
}

void	reset_event(t_event *src)
{
  while (get_next_event(src));
}

void	reset_wa(t_wa *wa)
{
  wa->config->theme += 1;
  if (wa->config->theme > 3)
    wa->config->theme = 1;
  sfMusic_destroy(wa->background_music);
  if (wa->config->theme == 1)
    wa->background_music = sfMusic_createFromFile("Ressources/sound/background_music.ogg");
  else if (wa->config->theme == 2)
    wa->background_music = sfMusic_createFromFile("Ressources/sound/rag_time_2.ogg");
  else
    wa->background_music = sfMusic_createFromFile("Ressources/sound/rag_time_3.ogg");
  sfMusic_setLoop(wa->background_music, sfTrue);
  sfMusic_setVolume(wa->background_music, 20);
  sfMusic_play(wa->background_music);
  clear_pxls(wa->pxls);
  wa->cur_pp_magnet_blue = wa->pp_magnet_blue;
  wa->cur_pp_magnet_red = wa->pp_magnet_red;
  wa->cur_pp_jump = wa->pp_jump;
  wa->cur_pp_run = wa->pp_run;
  wa->cur_pp_tapis = wa->pp_tapis;
  wa->cur_pp_stun = wa->pp_stun;
  wa->cur_pp_invincible = wa->pp_invincible;
  wa->tapis = wa->pxls->height - (wa->pxls->height / 4);
  wa->time_zero = time(NULL);
  wa->time = wa->time_zero;
  wa->delta_time = 0;
  wa->cur_pos_tapis = 0;
  wa->box = 0;
  wa->score = 0;
  wa->wave = get_wave(wa);
  wa->cur_animate_stun = 0;
  wa->modif_player = 0;
  reset_player(wa, wa->p1);
  reset_event(wa->events);
}

int		wavy_factory(t_settings *config)
{
  t_wa		*wa;
  sfEvent	event;

  wa = init_wa(config);
  draw_all(wa);
  sfMusic_play(wa->background_music);
  while (sfRenderWindow_isOpen(wa->win))
    {
      while (sfRenderWindow_pollEvent(wa->win, &event))
	main_events(wa, &event);
      inputs_keys(wa);
      destruction(wa);
      handle_random_events(wa, config->difficulty);
      collision_events(wa);
      usleep(20000);
      wa->time = time(NULL);
      if (gravity_pos(wa, &wa->p1->pos.y, wa->tapis)
	  || wa->events->next)
	draw_all(wa);
      sfRenderWindow_display(wa->win);
      wa->box += 1;
      free(wa->wave);
      wa->wave = get_wave(wa);
      if (!wa->p1->dead)
	wa->score = wa->score + 1;
      update_texts(wa);
    }
  free_all(wa);
  return (0);
}
