#pragma once

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define K_QUIT	'='
#define K_UP	'w'
#define K_DOWN	's'
#define K_LEFT	'a'
#define K_RIGHT	'd'

#define WGAMEH	30
#define WGAMEW	50
#define WGAMEY  (LINES-WGAMEH)/2
#define WGAMEX  (COLS-WGAMEW)/2
//TODO macro POSY(pos.y) and POSX

#define CP_NORMAL  1
#define CP_BASE	   2

#define NB_ACTIONS 3
#define NB_INTER   3

#define DIF_NORMAL	1
#define DIF_INFINITE	2
#define DIF_TROUBLED	3
#define DIF_FALL	4

struct Action;

typedef struct{ int	y,x;	} vect2i;
typedef struct{	float	i,j,k;	} vect3f;

typedef struct{ int	h,w;
		int	**map,**info;	} Asset;

typedef struct{	int	h,w;
		int	**map,**info,**inter;
		struct Action*	action;			} Interactive;

typedef struct Instance{
	int		id;
	int		y,x;
	Interactive*	inter;
	struct Instance	*previous,*next;	} Instance;

typedef struct{
	int		h,w;
	int		**bg,**clsn,**fg,**it;
	char*		name;
	Instance*	inst;			} Map;

typedef struct{
	struct Action**	actions;
	Interactive**	interactives;	} Info;

typedef struct Action{
	int	c;
	char*	label;
	int	labellen;
	void	(*action)(Instance* inst, Map* map, Info* info);	} Action;

typedef struct{	char*	name;
		int	y,x;	} Player;

int** malloc_arrayint2(int h,int w);
int** calloc_arrayint2(int h,int w);
int** duplicate_arrayint2(int** arr,int h,int w);
char* fread_line(FILE* f);
int** fread_map(FILE* f, int h, int w);
void clear_screen(int cp);

Interactive** create_intertable(Action** actionstable);
void free_intertable(Interactive** inters);
Action** create_actionstable(void);
void free_actionstable(Action** actions);
void fall_tree(Instance* inst, Map* map, Info* info);
void pull_stump(Instance* inst, Map* map, Info* info);
void harvest_fruits(Instance* inst, Map* map, Info* info);

Asset* load_asset(char* path);
void free_asset(Asset* ass);
void paste_asset(Map* map, int y, int x, Asset* ass);
Interactive* load_inter(char* path, Action** actionstable);
void free_inter(Interactive* inter);
void add_inst(Map* map, int y, int x, Interactive* inter);
void destroy_inst(Instance* it);
void free_instlist(Instance* it);

void create_map(Map* map, Info* info);
void free_map(Map* map);

Player* create_player(char* name, int y, int x);
void free_player(Player* pl);

int game(vect3f hue, Map* map, Player* pl, Info* info);
void movement(char c, Player* pl, Map* map);
Instance* check_inst(vect2i pos, Map* map);
int check_collision(vect2i pos, Map* map);

void display_map(Map* map, vect2i pos);
void display_pl(Player* pl, Map* map);
void display_notice(vect2i pos, Map* map);
