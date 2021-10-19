struct _Player{

	int gun;	
	int couteau;
	int move;

}__Player;

typedef struct _Player Player;


static void Init_Player(Player *p){

	p->gun = 0;
	p->couteau = 1;
	p->move = 0;

}

static void Set_Couteau_Player(Player *p){

	p->gun = 0;
	p->couteau = 1;

}

static void Set_Gun_Player(Player *p){

	p->gun = 1;
	p->couteau = 0;

}

/*
static Player player;
Init_Player(&player);
Set_Gun_Player(&player);
*/
