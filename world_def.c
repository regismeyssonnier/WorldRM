static struct SMap{
	int NO;
	int ipmin;
	int ipmax;
	int NX;
	int NY;
	float col;

}SMapW;

typedef struct SMap MapType;
typedef struct SMapW MapTypeW;

struct _Poutre{
	MapType stab[4];
	

};

typedef struct _Poutre Poutre;


struct _House{

	int NO;
	Poutre poutre[4];
	int max_P;
	MapType wall[6];
	int max_W;
	MapType toit[4];
	int ipomin;
	int ipomax;
	
};

typedef struct _House House;


static void Init_House(House *h, int no){

	h->NO = no;
	h->max_P = 0;
	h->max_W = 0;

}


static void Create_Poutre_House(House *h, float tx, float ty, float tz){
	
	int p = h->max_P;
	int no = Iobj;//(p*4)+h->NO;
	
	h->poutre[p].stab[0].NO = no;
	h->poutre[p].stab[0].NX = 1;
	h->poutre[p].stab[0].NY = 1;
	h->poutre[p].stab[0].ipmin = Ipo;
	create_map(h->poutre[p].stab[0].NX, h->poutre[p].stab[0].NY, 1.0f, 5.5f, -10.0f, "bois.jpg", 10.0f, 1.0f);
	h->poutre[p].stab[0].ipmax = Ipo; 

	for(int i = h->poutre[p].stab[0].ipmin;i < h->poutre[p].stab[0].ipmax;i++){
		N[i][0] = -1.0f;
		N[i][1] = 0.0f;
		N[i][2] = 0.1f;
	}

	rotate_mapY(90.0f, h->poutre[p].stab[0].ipmin, h->poutre[p].stab[0].ipmax);
	rotate_mapZ(90.0f, h->poutre[p].stab[0].ipmin, h->poutre[p].stab[0].ipmax);
	
	Scale(1.0f, 3.0f, 0.1f, h->poutre[p].stab[0].ipmin, h->poutre[p].stab[0].ipmax);
	translateO(h->poutre[p].stab[0].ipmin, h->poutre[p].stab[0].ipmax, 5.0f+tx, 10.0f+ty, 2.0f+tz);

	
	h->poutre[p].stab[1].NO = no+1;
	h->poutre[p].stab[1].NX = 1;
	h->poutre[p].stab[1].NY = 1;
	h->poutre[p].stab[1].ipmin = Ipo;
	create_map(h->poutre[p].stab[1].NX, h->poutre[p].stab[1].NY, 1.0f, 5.5f, -10.0f, "bois.jpg", 10.0f, 1.0f);
	h->poutre[p].stab[1].ipmax = Ipo; 

	for(int i = h->poutre[p].stab[1].ipmin;i < h->poutre[p].stab[1].ipmax;i++){
		N[i][0] = 1.0f;
		N[i][1] = 0.0f;
		N[i][2] = 0.1f;
	}

	rotate_mapY(90.0f, h->poutre[p].stab[1].ipmin, h->poutre[p].stab[1].ipmax);
	rotate_mapZ(90.0f, h->poutre[p].stab[1].ipmin, h->poutre[p].stab[1].ipmax);
	
	Scale(1.0f, 3.0f, 0.1f, h->poutre[p].stab[1].ipmin, h->poutre[p].stab[1].ipmax);
	translateO(h->poutre[p].stab[1].ipmin, h->poutre[p].stab[1].ipmax, 6.0f+tx, 10.0f+ty, 2.0f+tz);

	h->poutre[p].stab[2].NO = no+2;
	h->poutre[p].stab[2].NX = 1;
	h->poutre[p].stab[2].NY = 1;
	h->poutre[p].stab[2].ipmin = Ipo;
	create_map(h->poutre[p].stab[2].NX, h->poutre[p].stab[2].NY, 1.0f, 5.5f, -10.0f, "bois.jpg", 10.0f, 1.0f);
	h->poutre[p].stab[2].ipmax = Ipo; 

	for(int i = h->poutre[p].stab[2].ipmin;i < h->poutre[p].stab[2].ipmax;i++){
		N[i][0] = 0.1f;
		N[i][1] = 0.0f;
		N[i][2] = -1.0f;
	}

	rotate_mapX(90.0f, h->poutre[p].stab[2].ipmin, h->poutre[p].stab[2].ipmax);
	
	Scale(0.1f, 3.0f, 1.0f, h->poutre[p].stab[2].ipmin, h->poutre[p].stab[2].ipmax);
	translateO(h->poutre[p].stab[2].ipmin, h->poutre[p].stab[2].ipmax, 10.9f+tx, 10.0f+ty, 6.0f+tz);

	h->poutre[p].stab[3].NO = no+3;
	h->poutre[p].stab[3].NX = 1;
	h->poutre[p].stab[3].NY = 1;
	h->poutre[p].stab[3].ipmin = Ipo;

	for(int i = h->poutre[p].stab[3].ipmin;i < h->poutre[p].stab[3].ipmax;i++){
		N[i][0] = 0.1f;
		N[i][1] = 0.0f;
		N[i][2] = 1.0f;
	}

	create_map(h->poutre[p].stab[3].NX, h->poutre[p].stab[3].NY, 1.0f, 5.5f, -10.0f, "bois.jpg", 10.0f, 1.0f);
	h->poutre[p].stab[3].ipmax = Ipo; 
	rotate_mapX(90.0f, h->poutre[p].stab[3].ipmin, h->poutre[p].stab[3].ipmax);
	
	Scale(0.1f, 3.0f, 1.0f, h->poutre[p].stab[3].ipmin, h->poutre[p].stab[3].ipmax);
	translateO(h->poutre[p].stab[3].ipmin, h->poutre[p].stab[3].ipmax, 10.9f+tx, 10.0f+ty, 7.0f+tz);

	h->max_P = h->max_P + 1;

	
	

}


static void Create_Plaque(House *h, float tx, float ty, float tz){

	int no = h->max_W;
	
	h->wall[no].NO = Iobj;
	h->wall[no].NX = 1;
	h->wall[no].NY = 1;
	h->wall[no].ipmin = Ipo;
	create_map(h->wall[no].NX, h->wall[no].NY, 1.0f, 5.5f, -10.0f, "bois.jpg", 25.0f, 3.0f);
	h->wall[no].ipmax = Ipo; //ipmx2 = Ipo;
	rotate_mapY(90.0f, h->wall[no].ipmin, h->wall[no].ipmax);
	//rotate_mapZ(10.0f, solmap.ipmin, solmap.ipmax);
	//ToSphere(2, 2, ipmi2, ipmx2);
	//Scale(3.0f, 1.0f, 3.0f, h->wall[no].ipmin, h->wall[no].ipmax);
	translateO(h->wall[no].ipmin, h->wall[no].ipmax, 8.0f+tx, 35.0f+ty, 9.0f+tz);

	h->max_W = h->max_W + 1;

}

static void Translate_House(House *h, float tx, float ty, float tz){
	
	for(int i = 0;i < h->max_P;i++){
		for(int ix = 0;ix < 4;ix++){
			translateO(h->poutre[i].stab[ix].ipmin, h->poutre[i].stab[ix].ipmax, tx, ty, tz);
			
		}

	}

	for(int i = 0;i < h->max_W;i++){
		translateO(h->wall[i].ipmin, h->wall[i].ipmax, tx, ty, tz);
	}

}


static void Draw_House(House *h){

	GLint fg = gl_GetUniformLocation(programT2, "fgreen");
	
	for(int i = 0;i < h->max_P;i++){
		for(int ix = 0;ix < 4;ix++){
			if(ix < 2)gl_Uniform3f(fg, 0.0f, 2.0f, 0.0f);
			else gl_Uniform3f(fg, 0.0f, 2.5f, 0.0f);
			Draw_2map(h->poutre[i].stab[ix].NX, h->poutre[i].stab[ix].NO, programT2, 3);
			
		}

	}


	for(int i = 0;i < h->max_W;i++){
		gl_Uniform3f(fg, 0.0f, 0.6f, 0.0f);
		Draw_2map(h->wall[i].NX, h->wall[i].NO, programT2, 3);

	}


}
