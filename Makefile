##
## Makefile for wavy_factory in /home/thery/Bureau/game_jam_2017
## 
## Made by Thery
## Login   <thery.fouchter@epitech.eu@epitech.net>
## 
## Started on  Sat Jan 21 13:39:30 2017 Thery
## Last update Sun Jan 22 09:39:53 2017 Thery
##

SRC	=	draw.c			\
		events_patterns.c	\
		wave.c			\
		draw_calc.c		\
		collisions.c		\
		hit.c			\
		game.c			\
		player.c		\
		draw_floor.c		\
		pp.c			\
		window.c		\
		draw_ppm.c		\
		jump.c			\
		ppm.c			\
		draw_pxls.c		\
		keys.c			\
		pxls.c			\
		events.c		\
		main.c			\
		text.c

INC	=	-I include

LIB	=	-l csfml-graphics -l csfml-window -l csfml-audio -lm

VG	=	-g3

FLAGS	=	-W -Wall -Werror -Wextra

NAME	=	wavy_factory

all: $(NAME)

$(NAME):
	gcc -o $(NAME) $(SRC) $(INC) $(LIB)

clean:
	find . -type f -name "*~" -delete -or -name "#*#" -delete

fclean: clean
	rm -f $(NAME)

re: fclean all

ref: fclean cc_flags

cc_valgrind:
	gcc $(VG) -o $(NAME) $(SRC) $(INC) $(LIB)

cc_flags:
	gcc $(FLAGS) -o $(NAME) $(SRC) $(INC) $(LIB)
