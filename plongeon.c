static struct _Plongeon{

	float ht_deb;
	float ht_act;
	float speed_y;
	float speed_z;
	float speed_x;
	int in_plongeon;
	float palier[15];
	float longueur;
	float longueur_act;
	int max_P;

}__Plongeon;


typedef struct _Plongeon Plongeon;



void Init_Plongeon(Plongeon *p){

	p->in_plongeon = 0;
	p->speed_y = 1.5f;
	p->speed_z = 0.5f;
	p->speed_x = 0.1f;
	p->ht_deb = -15.0f;
	p->ht_act = -10.0f;
	p->longueur = 20.0f;
	p->longueur_act = 0.0f;

	p->max_P = 10;
	
	for(int i = 0;i < p->max_P;i++){

		p->palier[i] = (i*p->ht_act) + p->ht_deb;
		
	}

}

void Start_Plongeon(Plongeon *p){

	p->in_plongeon = 1;

}

void Plonger(Plongeon *p, float t){

	float VY = t * p->speed_y / 16666.6f;
	float VZ = p->speed_z ;

	if(Y < 15.0f){
		Y = Y + VY;
		if(p->longueur_act < p->longueur){
			Z = Z + VZ;
			p->longueur_act = p->longueur_act + VZ;
		}
	}
	else
	{
		Init_Plongeon(p);
		

	}

}



