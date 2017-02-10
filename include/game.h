/*
** game.h for wavy_factory in /home/thery/Bureau/game_jam_2017
** 
** Made by Thery
** Login   <thery.fouchter@epitech.eu@epitech.net>
**
** Started on  Sat Jan 21 13:37:54 2017 Thery 
** Last update Sun Jan 22 13:31:59 2017 Thery
*/

#ifndef GAME_H_
# define GAME_H_
# define BITS_PER_PXL		32
# define MAIN_TITLE		"wavy_factory"
# define WIN_STYLE		(sfClose)
# define DEFAULT_FONT		"Ressources/Symtext.ttf"

# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <SFML/Graphics.h>
# include <SFML/Audio.h>
# include <math.h>
# include <time.h>
# include <stdio.h>
# include <string.h>

typedef struct		s_pxls
{
  sfRenderWindow	*win;
  sfUint8		*pixels;
  int			width;
  int			height;
  sfSprite		*sprite;
  sfTexture		*texture;
}			t_pxls;

typedef struct	s_ppm
{
  sfColor	**c;
  sfVector2i	size;
}		t_ppm;

typedef struct		s_event
{
  struct s_event	*next;
  struct s_event	*last;
  int			magnet;
  int			box;
  int			destruction;
  sfVector2f		pos;
  float			speed;
  t_ppm			*ppm;
  t_ppm			*destroy;
  int			random;
}			t_event;

typedef struct		s_player
{
  sfVector2f		pos;
  float			speed;
  int			jump;
  int			onde;
  int			stun;
  int			invincible;
  int			reload;
  int			dead;
}			t_player;

typedef struct		s_settings
{
  int			fullscreen;
  sfVector2i		resolution;
  int			theme;
  int			difficulty;
}			t_settings;

typedef struct	s_pp
{
  struct s_pp	*next;
  t_ppm		*ppm;
  int		init;
}		t_pp;

typedef struct		s_wa
{
  sfRenderWindow	*win;
  sfVector2i		screen;
  t_pxls		*pxls;
  t_event		*events;
  t_player		*p1;
  int			*wave;
  int			score;
  int			tapis;
  int			time;
  int			time_zero;
  int			delta_time;
  int			box;
  t_pp			*pp_shock_wave;
  t_pp			*pp_punch;
  t_pp			*cur_pp_punch;
  t_pp			*pp_background;
  t_pp			*cur_pp_background;
  t_pp			*pp_magnet_blue;
  t_pp			*cur_pp_magnet_blue;
  t_pp			*pp_magnet_red;
  t_pp			*cur_pp_magnet_red;
  t_pp			*pp_jump;
  t_pp			*cur_pp_jump;
  t_pp			*pp_run;
  t_pp			*cur_pp_run;
  t_pp			*pp_tapis;
  t_pp			*cur_pp_tapis;
  sfUint8		*pxls_background;
  int			cur_pos_tapis;
  t_pp			*pp_caisse;
  t_pp			*pp_stun;
  t_pp			*cur_pp_stun;
  t_pp			*pp_invincible;
  t_pp			*cur_pp_invincible;
  sfMusic		*background_music;
  sfMusic		*punch_sound_1;
  sfMusic		*punch_sound_2;
  sfMusic		*hit_sound;
  sfText		*txt_score;
  char			*str_score;
  int			cur_animate_stun;
  int			modif_player;
  sfText		*txt_loose;
  char			*str_loose;
  t_settings		*config;
  t_pp			*pp_trap;
  t_pp			*pp_tapisup;
  t_pp			*cur_pp_tapisup;
}			t_wa;

void    set_configs(t_settings *config, char *fullscreen, char *resolution, char *theme, char *difficulty);
int	main(int ac, char **av);
int	draw_all(t_wa *wa);
int	*my_setup_tapis(int *wave, sfVector2i size, sfVector2f pos, t_wa *wa);
int	*get_wave(t_wa *wa);
t_ppm	*next_ppm_tapis(t_wa *wa, t_ppm **ppm2);
void	draw_floor(t_wa *wa);
void	secure_coo_ppm(t_ppm *ppm, int *x, int *y);
void	draw_ppm_resize(t_wa *wa, t_ppm *ppm, sfVector2i pos, sfVector2i size);
void	put_pixel(t_wa *wa, int x, int y, sfColor color);
void	draw_square(t_wa *wa, sfVector2i coo, int size, sfColor color);
t_event	*create_event(void);
void    add_event(t_event *src, t_event *new);
t_event	*get_next_event(t_event *src);
t_event	*init_events(void);
int	main_events(t_wa *wa, sfEvent *event);
void	handle_random_events(t_wa *wa, int difficulty);
t_event	*event_box(t_wa *wa);
t_event	*event_magnet(t_wa *wa);
t_wa	*init_wa(t_settings *config);
int	wavy_factory(t_settings *config);
int	height_calc(t_wa *wa);
int	collision_sol(t_wa *wa);
int	collision_box(t_wa *wa);
int	collision_events(t_wa *wa);
int	inputs_keys(t_wa *wa);
t_player	*create_player(t_wa *wa);
void	reset_player(t_wa *wa, t_player *pl);
int	move_player(t_wa *wa, t_player *pl, int x, int y);
int	gravity_pos(t_wa *wa, float *y, int ground);
int	change_player_pos(t_wa *wa, t_player *pl);
t_pp	*create_pp(t_ppm *ppm);
t_ppm	*append_ppm(char *path, int pos, int *nb);
t_pp	*create_animate_pp(char *path, int nb);
int	get_ppm_nbr(char *data);
char	*read_data(char *path);
t_ppm	*init_ppm(char *path);
sfColor	**init_ppm_c(sfVector2i size);
int	complete_ppm(t_ppm *ppm, char *data);
t_pxls	*create_pxls(sfRenderWindow *window, int width, int height);
void	update_pxls(t_pxls *pxls);
void	clear_pxls(t_pxls *pxls);
void	free_pxls(t_pxls *pxls);
int	wave_calc(int x, sfVector2f pos, sfVector2i size, t_wa *wa);
sfRenderWindow		*init_window(int width, int height, int *error, t_settings *config);
sfText	*create_text(char *str, int x, int y, int size);
char	*nb_to_text(int nb);
char	*get_score(int sc);
char	*stick_str(char *s1, char *s2, char sep);
void	update_texts(t_wa *wa);

void	reset_wa(t_wa *wa);
void	destruction(t_wa *wa);
int	get_rand_box_pos(void);

#endif /* !GAME_H_ */
