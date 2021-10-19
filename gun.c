static struct _Ammo{
	Stripe stripe[50];
	int max_S;
	int nIobj;
	int img;
	int img2;
	float X;
	float Y;
	float Z;
	int dir;
	int onfire;
	int run;
	Box box;

}__Ammo;

typedef struct _Ammo Ammo;

static void Init_Ammo(Ammo *a, int iobj, int im, int im2){

	a->max_S = 0;
	a->nIobj = iobj;
	a->img = im;
	a->img2 = im2;
	a->X = 0.0f;
	a->Y = 0.0f;
	a->Z = -20.0f;
	a->dir = -1;
	a->onfire = 0;
	a->run = 0;
}



static struct _Gun{

	Stripe stripe[50];
	int max_S;
	int nIobj;
	int img;
	int img2;
	int imgr;
	int imgr2;
	float angle_Z;
	float cx;
	float cy;
	float cz;
	int start;
	int onhit;
	float W;
	float H;
	Ammo ammo[30];
	int max_A;
	int onfire;
	int onfire2;
	float inter;
	int next;
	int max_OF;
	Box box[50];
	int max_B;
	int touch_B;
	float xt;	
	float yt;
	float zt;
	Shader shader;
	int cube_map;
	float rx;
	float ry;
	float rz;

}__Gun;


typedef struct _Gun Gun;


static void Init_Gun(Gun *g, int im, int im2, int imr, int imr2){

	g->max_S = 0;
	g->nIobj = Iobj;
	g->img = im;
	g->img2 = im2;
	g->imgr = imr;
	g->imgr2 = imr2;
	g->angle_Z = 0.0f;
	g->cx = g->cy = g->cz = 0.0f;
	g->start = 0;
	g->onhit = 0;
	g->onfire = 0;
	g->onfire2 = 0;
	g->max_A = 0;
	g->next = -1;
	g->max_OF = 0;
	g->max_B = 0;
	g->touch_B = -1;
	g->xt = -1;
	g->yt = -1;
	g->zt = -1;
	
}

static void Set_Res_Gun(Gun *g, float W, float H){
	
	g->W = W;
	g->H = H;

}

static void Set_Shader_CM(Gun *g){

	Init_Shader_Def_Gun(&g->shader);
	

}

static void Set_Tex_CM(Gun *g, int txcbm){

	g->cube_map = txcbm;
	

}

static void Get_Center_Gun(Gun *g){

	float px =0.0f, py=0.0f, pz=0.0f;
	float pmin = g->stripe[0].Ipomin;
	float pmax = g->stripe[25].Ipomax;

	for(int i = pmin; i < pmax;i++){
		px = px + P[i][0];
		py = py + P[i][1];
		pz = pz + P[i][2];
	}

	
	float n = pmax-pmin;
	g->cx = px / n;
	g->cy = py / n;
	g->cz = pz / n;

}

void Init_Point_Ammo(Gun *g, int ia){

	int pmin = g->ammo[ia].stripe[0].Ipomin;
	int pmax = g->ammo[ia].stripe[5].Ipomax;

	float px=0.0f, py=0.0f, pz=0.0f, ppx, ppy, ppz;
	for(int i = pmin; i < pmax;i++){
		px = px + P[i][0];
		py = py + P[i][1];
		pz = pz + P[i][2];
	}

	
	float n = pmax-pmin;
	ppx = px / n;
	ppy = py / n;
	ppz = pz / n;
	
	for(int i = pmin; i < pmax;i++){
		
		P[i][0] = P[i][0]-ppx;
		P[i][1] = P[i][1]-ppy;
		P[i][2] = P[i][2]-ppz;

	}

}

static void Reset_Box(Gun *g){

	g->max_B = 0;

}


static void Add_Gun_Box(Gun *g, Box *b){

	Copy_Box(&g->box[g->max_B], b);
	g->max_B = g->max_B + 1;
	

}

static void Create_Ammo(Gun *g, int ia){

	Init_Obj();
	int pmin = g->ammo[ia].stripe[0].Ipomin;
	int pmax = g->ammo[ia].stripe[5].Ipomax;

	Init_Ammo(&g->ammo[ia], Iobj, g->img, g->img2);
	StrawC(&g->ammo[ia].stripe[0], 10.0f, 1, g->img, 5.0f);
	StrawC(&g->ammo[ia].stripe[1], 10.0f, 0, g->img, 5.0f);
	StrawS(&g->ammo[ia].stripe[2], 10.0f, 0, g->imgr, 0.0f, 10.0f, 1.0f, 5.0f);
	StrawS(&g->ammo[ia].stripe[3], 10.0f, 1, g->imgr, 0.0f, 10.0f, 1.0f, 5.0f);
	StrawS(&g->ammo[ia].stripe[4], 10.0f, 0, g->imgr, 0.0f, 10.0f, 1.0f, 5.0f);
	StrawS(&g->ammo[ia].stripe[5], 10.0f, 1, g->imgr, 0.0f, 10.0f, 1.0f, 5.0f);

	pmin = g->ammo[ia].stripe[0].Ipomin;
	pmax = g->ammo[ia].stripe[3].Ipomax;
	
	translateO(pmin, pmax, 0.0f, 0.0f, 10.0f);

	pmin = g->ammo[ia].stripe[2].Ipomin;
	pmax = g->ammo[ia].stripe[3].Ipomax;
	rotate_StripeX(90.0f, pmin, pmax);
	translateO(pmin, pmax, 0.0f, 3.45f, -3.5f);
	
	pmin = g->ammo[ia].stripe[4].Ipomin;
	pmax = g->ammo[ia].stripe[5].Ipomax;
	rotate_StripeX(90.0f, pmin, pmax);
	rotate_StripeY(180.0f, pmin, pmax);
	translateO(pmin, pmax, 0.0f, 3.45f, -6.53f);

	pmin = g->ammo[ia].stripe[0].Ipomin;
	pmax = g->ammo[ia].stripe[5].Ipomax;
	Scale(0.02f, 0.02f, 0.05f, pmin, pmax);

	Init_Point_Ammo(g, ia);

	Get_Box(&g->ammo[ia].box, g->ammo[ia].stripe[0].Ipomin, g->ammo[ia].stripe[5].Ipomax);
	Create_Box(&g->ammo[ia].box, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	Display_Box(&g->ammo[ia].box);

	g->ammo[ia].max_S = 6;
	g->max_A = g->max_A + 1; 

	Iobj = Iobj + 1;

}

static void Init_Ammo_Fire(Gun *g){

	for(int i = 0;i < g->max_A;i++){
		g->ammo[i].onfire = 0;
		g->ammo[i].dir = -1;

	}

}


static void Create_Gun(Gun *g){

	Init_Obj();
	StrawC(&g->stripe[0], 10.0f, 1, g->img, 5.0f);
	StrawC(&g->stripe[1], 10.0f, 0, g->img, 5.0f);
	StrawC(&g->stripe[2], 10.0f, 1, g->img, 5.0f);
	StrawC(&g->stripe[3], 10.0f, 0, g->img, 5.0f);
	StrawS(&g->stripe[4], 0.5f, 0, g->img, 0.0f, 9.0f, 1.0f, 5.0f);
	StrawS(&g->stripe[5], 0.5f, 0, g->img, 0.0f, 9.0f, 1.0f, 5.0f);
	StrawS(&g->stripe[6], 0.5f, 0, g->img, 0.0f, 9.0f, 1.0f, 5.0f);
	StrawS(&g->stripe[7], 0.5f, 0, g->img, 0.0f, 9.0f, 1.0f, 5.0f);
	StrawC(&g->stripe[8], 10.0f, 1, g->img, 5.0f);
	StrawC(&g->stripe[9], 10.0f, 0, g->img, 5.0f);
	StrawC(&g->stripe[10], 10.0f, 1, g->img, 5.0f);
	StrawC(&g->stripe[11], 10.0f, 0, g->img, 5.0f);
	StrawS(&g->stripe[12], 0.5f, 0, g->img, 0.0f, 9.0f, 1.0f, 5.0f);
	StrawS(&g->stripe[13], 0.5f, 0, g->img, 0.0f, 9.0f, 1.0f, 5.0f);
	StrawS(&g->stripe[14], 0.5f, 0, g->img, 0.0f, 9.0f, 1.0f, 5.0f);
	StrawS(&g->stripe[15], 0.5f, 0, g->img, 0.0f, 9.0f, 1.0f, 5.0f);
	StrawC(&g->stripe[16], 10.0f, 1, g->img, 5.0f);
	StrawC(&g->stripe[17], 10.0f, 0, g->img, 5.0f);
	StrawS(&g->stripe[18], 0.5f, 0, g->img, 0.0f, 9.0f, 1.0f, 5.0f);
	StrawS(&g->stripe[19], 0.5f, 0, g->img, 0.0f, 9.0f, 1.0f, 5.0f);
	StrawS(&g->stripe[20], 10.0f, 0, g->imgr, 0.0f, 5.0f, 0.0f, 5.0f);
	StrawS(&g->stripe[21], 10.0f, 0, g->imgr, 0.0f, 5.0f, 0.0f, 5.0f);
	StrawC(&g->stripe[22], 10.0f, 1, g->img, 5.0f);
	StrawC(&g->stripe[23], 10.0f, 0, g->img, 5.0f);
	StrawS(&g->stripe[24], 0.5f, 0, g->img, 0.0f, 9.0f, 1.0f, 5.0f);
	StrawS(&g->stripe[25], 0.5f, 0, g->img, 0.0f, 9.0f, 1.0f, 5.0f);

	g->max_S = 26;

	

	int pmin = g->stripe[2].Ipomin;
	int pmax = g->stripe[3].Ipomax;
	
	translateO(pmin, pmax, 20.0f, 0.0f, 0.0f);
	
	pmin = g->stripe[0].Ipomin;
	pmax = g->stripe[3].Ipomax;
	Scale(0.05f, 0.05f, 1.0f, pmin, pmax);

	pmin = g->stripe[5].Ipomin;
	pmax = g->stripe[5].Ipomax;
	rotate_StripeY(180.0f, pmin, pmax);
	translateO(pmin, pmax, 0.0f, 0.0f, 0.33f);
	pmin = g->stripe[4].Ipomin;
	pmax = g->stripe[5].Ipomax;
	rotate_StripeX(90.0f, pmin, pmax);
	translateO(pmin, pmax, 0.0f, 0.173f, -4.925f);

	pmin = g->stripe[7].Ipomin;
	pmax = g->stripe[7].Ipomax;
	rotate_StripeY(180.0f, pmin, pmax);
	translateO(pmin, pmax, 0.0f, 0.0f, 0.33f);
	pmin = g->stripe[6].Ipomin;
	pmax = g->stripe[7].Ipomax;
	rotate_StripeX(90.0f, pmin, pmax);
	translateO(pmin, pmax, 1.0f, 0.173f, -4.925f);

	//tube
	pmin = g->stripe[8].Ipomin;
	pmax = g->stripe[9].Ipomax;
	
	translateO(pmin, pmax, 50.0f, 0.0f, 0.0f);

	pmin = g->stripe[10].Ipomin;
	pmax = g->stripe[11].Ipomax;
	
	translateO(pmin, pmax, 70.0f, 0.0f, 0.0f);
	
	pmin = g->stripe[8].Ipomin;
	pmax = g->stripe[11].Ipomax;
	Scale(0.05f, 0.05f, 1.0f, pmin, pmax);

	//cache
	pmin = g->stripe[13].Ipomin;
	pmax = g->stripe[13].Ipomax;
	rotate_StripeY(180.0f, pmin, pmax);
	translateO(pmin, pmax, 0.0f, 0.0f, 0.33f);
	pmin = g->stripe[12].Ipomin;
	pmax = g->stripe[13].Ipomax;
	rotate_StripeX(90.0f, pmin, pmax);
	translateO(pmin, pmax, 2.5f, 0.173f, -4.925f);

	pmin = g->stripe[15].Ipomin;
	pmax = g->stripe[15].Ipomax;
	rotate_StripeY(180.0f, pmin, pmax);
	translateO(pmin, pmax, 0.0f, 0.0f, 0.33f);
	pmin = g->stripe[14].Ipomin;
	pmax = g->stripe[15].Ipomax;
	rotate_StripeX(90.0f, pmin, pmax);
	translateO(pmin, pmax, 3.5f, 0.173f, -4.925f);

	//tube
	pmin = g->stripe[16].Ipomin;
	pmax = g->stripe[17].Ipomax;
	
	translateO(pmin, pmax, 100.0f, 0.0f, 0.0f);
	
	pmin = g->stripe[16].Ipomin;
	pmax = g->stripe[17].Ipomax;
	Scale(0.05f, 0.05f, 1.0f, pmin, pmax);

	//cache
	pmin = g->stripe[19].Ipomin;
	pmax = g->stripe[19].Ipomax;
	rotate_StripeY(180.0f, pmin, pmax);
	translateO(pmin, pmax, 0.0f, 0.0f, 0.33f);
	pmin = g->stripe[18].Ipomin;
	pmax = g->stripe[19].Ipomax;
	rotate_StripeX(90.0f, pmin, pmax);
	translateO(pmin, pmax, 5.0f, 0.173f, -4.925f);
	
	//ring
	pmin = g->stripe[21].Ipomin;
	pmax = g->stripe[21].Ipomax;
	rotate_StripeY(180.0f, pmin, pmax);
	translateO(pmin, pmax, 0.0f, 0.0f, 9.8f);
	pmin = g->stripe[20].Ipomin;
	pmax = g->stripe[21].Ipomax;
	rotate_StripeX(90.0f, pmin, pmax);
	Scale(0.25f, 0.25f, 1.0f, pmin, pmax);

	//tube 6
	pmin = g->stripe[22].Ipomin;
	pmax = g->stripe[23].Ipomax;
	
	translateO(pmin, pmax, 100.0f, 0.0f, 0.0f);
	
	pmin = g->stripe[22].Ipomin;
	pmax = g->stripe[23].Ipomax;
	Scale(0.05f, 0.05f, 1.0f, pmin, pmax);

	//cache 6
	pmin = g->stripe[25].Ipomin;
	pmax = g->stripe[25].Ipomax;
	rotate_StripeY(180.0f, pmin, pmax);
	translateO(pmin, pmax, 0.0f, 0.0f, 0.33f);
	pmin = g->stripe[24].Ipomin;
	pmax = g->stripe[25].Ipomax;
	rotate_StripeX(90.0f, pmin, pmax);
	translateO(pmin, pmax, 5.0f, 0.173f, -4.925f);
	
	
	//pos tube 1
	pmin = g->stripe[0].Ipomin;
	pmax = g->stripe[1].Ipomax;
	translateO(pmin, pmax, 0.0f, 2.1f, 10.0f);
	pmin = g->stripe[4].Ipomin;
	pmax = g->stripe[5].Ipomax;
	translateO(pmin, pmax, 0.0f, 2.1f, 10.0f);

	//pos tube 2
	pmin = g->stripe[2].Ipomin;
	pmax = g->stripe[3].Ipomax;
	translateO(pmin, pmax, -3.0f, 1.0f, 10.0f);
	pmin = g->stripe[6].Ipomin;
	pmax = g->stripe[7].Ipomax;
	translateO(pmin, pmax, -3.0f, 1.0f, 10.0f);


	//pos tube 3
	pmin = g->stripe[8].Ipomin;
	pmax = g->stripe[9].Ipomax;
	translateO(pmin, pmax, -0.5f, 1.0f, 10.0f);
	pmin = g->stripe[12].Ipomin;
	pmax = g->stripe[13].Ipomax;
	translateO(pmin, pmax, -0.5f, 1.0f, 10.0f);

	//pos tube 4
	pmin = g->stripe[10].Ipomin;
	pmax = g->stripe[11].Ipomax;
	translateO(pmin, pmax, -5.5f, -1.5f, 10.0f);
	pmin = g->stripe[14].Ipomin;
	pmax = g->stripe[15].Ipomax;
	translateO(pmin, pmax, -5.5f, -1.5f, 10.0f);


	//pos tube 5
	pmin = g->stripe[16].Ipomin;
	pmax = g->stripe[17].Ipomax;
	translateO(pmin, pmax, -3.0f, -1.5f, 10.0f);
	pmin = g->stripe[18].Ipomin;
	pmax = g->stripe[19].Ipomax;
	translateO(pmin, pmax, -3.0f, -1.5f, 10.0f);

	//pos tube 5
	pmin = g->stripe[22].Ipomin;
	pmax = g->stripe[23].Ipomax;
	translateO(pmin, pmax, -5.0f, -2.6f, 10.0f);
	pmin = g->stripe[24].Ipomin;
	pmax = g->stripe[25].Ipomax;
	translateO(pmin, pmax, -5.0f, -2.6f, 10.0f);

	pmin = g->stripe[0].Ipomin;
	pmax = g->stripe[25].Ipomax;
	rotate_StripeY(180.0f, pmin, pmax);
	translateO(pmin, pmax, 0.0f, -4.0f, -13.0f);
	rotate_StripeX(10.0f, pmin, pmax);
	//Scale(0.1f, 0.1f, 0.2f, pmin, pmax);

	Get_Center_Gun(g);
	
	Iobj = Iobj + 1;

	Create_Ammo(g, 0);
	Create_Ammo(g, 1);
	Create_Ammo(g, 2);
	Create_Ammo(g, 3);
	Create_Ammo(g, 4);
	Create_Ammo(g, 5);
	Create_Ammo(g, 6);
	Create_Ammo(g, 6);
	Create_Ammo(g, 7);
	Create_Ammo(g, 8);
	Create_Ammo(g, 9);
	//Init_Obj();
	//Create_Ammo(g, 6, 11);
	/*Init_Ammo(&g->ammo, Iobj, g->img, g->img2);
	StrawC(&g->ammo.stripe[0], 10.0f, 1, g->img, 5.0f);
	StrawC(&g->ammo.stripe[1], 10.0f, 0, g->img, 5.0f);
	StrawS(&g->ammo.stripe[2], 10.0f, 0, g->imgr, 0.0f, 10.0f, 1.0f, 5.0f);
	StrawS(&g->ammo.stripe[3], 10.0f, 1, g->imgr, 0.0f, 10.0f, 1.0f, 5.0f);
	StrawS(&g->ammo.stripe[4], 10.0f, 0, g->imgr, 0.0f, 10.0f, 1.0f, 5.0f);
	StrawS(&g->ammo.stripe[5], 10.0f, 1, g->imgr, 0.0f, 10.0f, 1.0f, 5.0f);

	pmin = g->ammo.stripe[0].Ipomin;
	pmax = g->ammo.stripe[3].Ipomax;
	
	translateO(pmin, pmax, 0.0f, 0.0f, 10.0f);

	pmin = g->ammo.stripe[2].Ipomin;
	pmax = g->ammo.stripe[3].Ipomax;
	rotate_StripeX(90.0f, pmin, pmax);
	translateO(pmin, pmax, 0.0f, 3.45f, -3.5f);
	
	pmin = g->ammo.stripe[4].Ipomin;
	pmax = g->ammo.stripe[5].Ipomax;
	rotate_StripeX(90.0f, pmin, pmax);
	rotate_StripeY(180.0f, pmin, pmax);
	translateO(pmin, pmax, 0.0f, 3.45f, -6.53f);

	pmin = g->ammo.stripe[0].Ipomin;
	pmax = g->ammo.stripe[5].Ipomax;
	Scale(0.02f, 0.02f, 0.05f, pmin, pmax);

	Init_Point_Ammo(g, 0, 5);

	g->ammo.max_S = 6;

	Iobj = Iobj + 1;*/


}



static int Gun_Touch_Box(Gun *g, int am){

	float xbi, ybi, zbi, xbx, ybx, zbx, xbwi, ybwi, zbwi, xbwx, ybwx, zbwx, amx, amy, amz ;
	for(int i = 0;i < g->max_B;i++){
		xbi = g->ammo[am].X + g->ammo[am].box.xmin;
		ybi = g->ammo[am].Y + g->ammo[am].box.ymin;
		zbi = g->ammo[am].Z + g->ammo[am].box.zmin;
		xbx = g->ammo[am].X + g->ammo[am].box.xmax;
		ybx = g->ammo[am].Y + g->ammo[am].box.ymax;
		zbx = g->ammo[am].Z + g->ammo[am].box.zmax;
		xbwi = g->box[i].xmin + X;
		ybwi = g->box[i].ymin + Y;
		zbwi = g->box[i].zmin + Z;
		xbwx = g->box[i].xmax + X;
		ybwx = g->box[i].ymax + Y;
		zbwx = g->box[i].zmax + Z;
		amx = xbi + ((xbx - xbi) / 2.0f);
		amy = ybi + ((ybx - ybi) / 2.0f);
		amz = zbi + ((zbx - zbi) / 2.0f);
	
		//printf("box ammo %f %f %f, %f %f %f\n", xbi, ybi, zbi, xbx, ybx, zbx);
		//printf("box worl %f %f %f, %f %f %f\n", xbwi, ybwi, zbwi, xbwx, ybwx, zbwx);
		

		if(  (amx >= xbwi) && (amx <= xbwx) &&
		     (amy >= ybwi) && (amy <= ybwx) &&
		     (amz >= zbwi) && (amz <= zbwx)
		  ){
			g->touch_B = i;
			/*g->xt = xbi;
			g->yt = ybi;
			g->zt = zbi;*/
			//printf("touched %d by %d\n", i, am);
			return 1;
		}
	}

	return 0;

}

static void rotate_GunZ(Gun *g, float a){

	a = a * 3.141592654f / 180.0f;
			

	float M[9];
	M[0] = cos(a);
	M[1] = -sin(a);
	//M[2] = 0.0f;
	M[3] = sin(a);
	M[4] = cos(a);
	//M[5] = 0.0f;
	//M[6] = 0.0;
	//M[7] = 0.0f;
	M[8] = 1.0f;

	float px =0.0f, py=0.0f, pz=0.0f;

	px = g->cx;
	py = g->cy;
	pz = g->cz;
	
	/*X = M[0] * X;
	Y = M[4] * Y + M[5] * Z;
	Z = M[7] * Y + M[8] * Z;*/
	float X1, Y1, Z1, X2, Y2, Z2;
	float NX1, NY1, NZ1, NX2, NY2, NZ2;

	float pmin = g->stripe[0].Ipomin;
	float pmax = g->stripe[25].Ipomax;

	for(int i = pmin; i < pmax;i++){
		
		X1 = P[i][0]-px; Y1 = P[i][1]-py; Z1 = P[i][2]-pz;
		X2 = M[0] * X1 + M[1] * Y1;
		Y2 = M[3] * X1 + M[4] * Y1;
		Z2 = Z1;

		P[i][0] = X2+px;
		P[i][1] = Y2+py;
		P[i][2] = Z2+pz;

		/*NX1 = N[i][0]; NY1 = N[i][1]; NZ1 = N[i][2];
		NX2 = M[0] * NX1 + M[1] * NY1;
		NY2 = M[3] * NX1 + M[4] * NY1;
		NZ2 = NZ1;

		N[i][0] = NX2;
		N[i][1] = NY2;
		N[i][2] = NZ2;*/

	}



}



static void Hit_Gun(Gun *g){
	//g->angle_Z = 0.0f;
	g->angle_Z = 4.0f;
	g->onhit = !g->onhit;
	//g->start = 1;
	g->onfire = !g->onfire;
	//if( (g->onfire == 1) && (g->ammo[g->next].onfire == 0) )g->ammo[g->next].onfire = 1;
	g->onfire2 = 1;
	//g->next = g->next + 1;
	//printf("fire :%d\n", g->ammo.onfire );
}

static void OnHit_Gun(Gun *g){

	if(g->onhit == 1){
		float pmin = g->stripe[0].Ipomin;
		float pmax = g->stripe[25].Ipomax;

		
		rotate_StripeX(-10.0f, pmin, pmax);
		rotate_GunZ(g, g->angle_Z);
		rotate_StripeX(10.0f, pmin, pmax);
		
		
	}

}


static void OnFire_Gun(Gun *g, Direction *d, float rx, float ry, float rz, float ti){

	//for(int s = 0;s < g->ammo.max_S;s++){
	//	for(int nx = g->ammo.stripe[s].Istart;nx < g->ammo.stripe[s].Iend;nx++){
			
	//	}
	//}
//glRotatef(RY, 0,0,1);
//	glRotatef(RZ, 1,0,0);
//	glRotatef(RX, 0,1,0);
	//printf("fire :%d\n", g->ammo.onfire );

	if(g->onfire == 1)
	{
		if(g->max_OF == 0)
		{
			g->ammo[0].onfire = 1; 
			g->next = 1;
			g->max_OF = 1;
		} 
		
		g->inter = g->inter + ti;
		if( (g->inter > 100000.0f) ){
			g->ammo[g->next].onfire = 1;
			g->next = g->next + 1;
			g->max_OF = g->max_OF + 1;
			g->inter = 0;

		}

		

		if(g->next >= g->max_A){
			for(int i = 0;i < g->max_A;i++){
				if(g->ammo[i].onfire == 0)
				{
					g->next = i;
					break;
				}
					
			}
			
		}

		//printf("maxA : %d, next : %d, maxOF : %d, g->inter : %f\n", g->max_A, g->next, g->max_OF, g->inter);

	}

	//printf("rx : %f\n", rx);

	for(int i = 0;i < g->max_A;i++){

		if(g->ammo[i].onfire == 1){
		

			if(g->ammo[i].dir == -1){
				
			
				int pmin = g->ammo[i].stripe[0].Ipomin;
				int pmax = g->ammo[i].stripe[5].Ipomax;

				//Init_Point_Ammo(g, 0, 5);

				g->ammo[i].dir = 1;//d->direction;
				g->ammo[i].X = 0.0f;
				g->ammo[i].Y = 0.0f;
				g->ammo[i].Z = 0.0f;


				//rotate_StripeZ(-rz, pmin, pmax);
				//rotate_StripeX(-rx, pmin, pmax);
				//rotate_StripeY(-ry, pmin, pmax);
				
				
				//translateO(pmin, pmax, 0.0f, 3.45f, -6.53f);

				//printf("dir : %d\n", g->ammo.dir);
				//printf("--x : %f, y : %f, z : %f\n", X, Y, Z);
				//printf("x : %f, y : %f, z : %f\n", P[(int)pmin][0]+g->ammo.X , P[(int)pmin][1]+g->ammo.Y, P[(int)pmin][2]+g->ammo.Z);

			}
			else
			{

				float VX, VY, VZ;
				VX = 0.01f;//d->VX*2.0f;
				VZ = d->VZ*2.0f;
				VY = rx/-45.0f;

				/*switch (g->ammo[i].dir){

					case 1:
						g->ammo[i].Z -= VZ;
						break;

					case 2:
						g->ammo[i].X += VX;
						g->ammo[i].Z -= VZ;
						break;

					case 3:
						g->ammo[i].X += VX;
						
						break;

					case 4:
						g->ammo[i].X += VX;
						g->ammo[i].Z += VZ;
						break;

					case 5:
						g->ammo[i].Z += VZ;
						break;

					case 6:
						g->ammo[i].X -= VX;
						g->ammo[i].Z -= VZ;
						break;

					case 7:
						g->ammo[i].X -= VX;
						break;

					case 8:
						g->ammo[i].X -= VX;
						g->ammo[i].Z += VZ;
						break;

					default:
						break;
				}*/

					

				g->ammo[i].Z -= VZ;
				//if(ry < -45.0f)
					g->ammo[i].Y += VY;
				//else
				//	g->ammo[i].Y -= VY;

				if(Gun_Touch_Box(g, i) == 1){
					g->ammo[i].onfire = 0;
					g->ammo[i].dir = -1;
					g->max_OF = g->max_OF - 1;

				}

				//printf("gammoX  : %f, gammoY : %f, gammoZ : %f\n", g->ammo[i].X, g->ammo[i].Y, g->ammo[i].Z);
				if( (g->ammo[i].X > 50.0f)||(g->ammo[i].X < -50.0f) ||
				    (g->ammo[i].Y > 50.0f)||(g->ammo[i].Y < -50.0f) ||
				    (g->ammo[i].Z > 50.0f)||(g->ammo[i].Z < -50.0f) 
				){
					g->ammo[i].onfire = 0;
					g->ammo[i].dir = -1;
					g->max_OF = g->max_OF - 1;
					//Init_Point_Ammo2(g, 0, 5);
					//printf("end\n");
				}

			}


		}

	}


}


static void Draw_Gun(Gun *g){

	int idt, idc, idn, idv, ifc;
glEnable(GL_TEXTURE_2D);
	

	gl_UseProgram (programT2);
		
	//gl_Uniform3f(fg, 0.0f, 3.0f, 0.0f);
	//glBegin( GL_QUAD_STRIP );

	int idisp = g->nIobj;

		GLint isw = gl_GetUniformLocation(programT2, "iswater");
			gl_Uniform3f(isw, 0.0f, 0.0f, 0.0f);

			GLint fg = gl_GetUniformLocation(programT2, "fgreen");
			gl_Uniform3f(fg, 0.0f, 3.0f, 0.0f);

			GLint ishg = gl_GetUniformLocation(programT2, "isshin");
			gl_Uniform3f(ishg, 0.0f, 0.0f, 0.0f);

		/*GLint ures = gl_GetUniformLocation(shader_def.program, "u_res");
		gl_Uniform3f(ures, g->W, g->H, 0.0f);
		GLint pos = gl_GetUniformLocation(shader_def.program, "position");
		gl_Uniform3f(pos, 5, 5, 0.0f);*/
			
		for(int s = 0;s < g->max_S;s++){
			//gl_UseProgram (shader_def.program);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, O[idisp][g->stripe[s].Istart][0][4]);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			/*if((s == 20) || (s == 21)){
				gl_Uniform3f(isw, 0.0f, 0.0f, 0.0f);
				gl_Uniform3f(fg, 0.0f, 0.5f, 0.0f);

			}
			else*/
				//gl_Uniform3f(isw, 0.0f, 0.0f, 0.0f);

			//if(s < 2){

				GLint myt = gl_GetUniformLocation(programT2, "myTexture");
				if(myt != -1){
				gl_Uniform1i(myt, 0);
				}

				glActiveTexture(GL_TEXTURE1);
				GLint nmap = gl_GetUniformLocation(programT2, "nmap");
				if(nmap != -1){
				gl_Uniform1i(nmap, 1);
				}
				glActiveTexture(GL_TEXTURE1);
				if((s == 20) || (s == 21)){
					glBindTexture(GL_TEXTURE_2D, g->imgr2);
				}
				else
					glBindTexture(GL_TEXTURE_2D, g->img2);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


			

			glBegin( GL_QUAD_STRIP );
			
			for(int nx = g->stripe[s].Istart;nx < g->stripe[s].Iend;nx++){

				
								
				for(int ipdisp = 0;ipdisp < 2;ipdisp++){
					
					idv = O[idisp][nx][ipdisp][0]; idn=O[idisp][nx][ipdisp][1];
					idc = O[idisp][nx][ipdisp][2]; idt=O[idisp][nx][ipdisp][3];

					glTexCoord2f(tex[idt][0], tex[idt][1]);
					glColor4f(C[idc][0],C[idc][1], C[idc][2], 0.5f);
					glNormal3f(N[idn][0], N[idn][1], N[idn][2]);
					glVertex3f(P[idv][0], P[idv][1], P[idv][2]);
					//printf("x : %f, y : %f, z : %f\n", P[idv][0] +X, P[idv][1]+Y, P[idv][2]+Z);
				}

				
				if(nx == (g->stripe[s].Iend-1)){

					for(int ipdisp = 3;ipdisp >= 2 ;ipdisp--){

						idv = O[idisp][nx][ipdisp][0]; idn=O[idisp][nx][ipdisp][1];
						idc = O[idisp][nx][ipdisp][2]; idt=O[idisp][nx][ipdisp][3];

						glTexCoord2f(tex[idt][0], tex[idt][1]);
						glColor4f(C[idc][0],C[idc][1], C[idc][2], 0.5f);
						glNormal3f(N[idn][0], N[idn][1], N[idn][2]);
						glVertex3f(P[idv][0] , P[idv][1], P[idv][2]);
						//printf("x : %f, y : %f, z : %f\n", P[idv][0] +X, P[idv][1]+Y, P[idv][2]+Z);
					
					}

				}
				

				
			}

			glEnd();
			glFlush();

		
		}

	



}


static void Draw_Gun_CM(Gun *g){

	int idt, idc, idn, idv, ifc;
glEnable(GL_TEXTURE_2D);
	

	gl_UseProgram (g->shader.program);
		
	//gl_Uniform3f(fg, 0.0f, 3.0f, 0.0f);
	//glBegin( GL_QUAD_STRIP );

	int idisp = g->nIobj;

	GLint pos = gl_GetUniformLocation(g->shader.program, "position");
	gl_Uniform3f(pos, g->rx, g->ry, g->rz );

		/*GLint isw = gl_GetUniformLocation(programT2, "iswater");
			gl_Uniform3f(isw, 0.0f, 0.0f, 0.0f);

			GLint fg = gl_GetUniformLocation(programT2, "fgreen");
			gl_Uniform3f(fg, 0.0f, 3.0f, 0.0f);

			GLint ishg = gl_GetUniformLocation(programT2, "isshin");
			gl_Uniform3f(ishg, 0.0f, 0.0f, 0.0f);*/

		/*GLint ures = gl_GetUniformLocation(shader_def.program, "u_res");
		gl_Uniform3f(ures, g->W, g->H, 0.0f);
		GLint pos = gl_GetUniformLocation(shader_def.program, "position");
		gl_Uniform3f(pos, 5, 5, 0.0f);*/

		glEnable(GL_TEXTURE_CUBE_MAP);
			//glDepthMask(GL_FALSE);
			glBindTexture(GL_TEXTURE_CUBE_MAP, g->cube_map);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			
		for(int s = 0;s < g->max_S;s++){
			//gl_UseProgram (shader_def.program);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, O[idisp][g->stripe[s].Istart][0][4]);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			

			/*if((s == 20) || (s == 21)){
				gl_Uniform3f(isw, 0.0f, 0.0f, 0.0f);
				gl_Uniform3f(fg, 0.0f, 0.5f, 0.0f);

			}
			else*/
				//gl_Uniform3f(isw, 0.0f, 0.0f, 0.0f);

			//if(s < 2){

				GLint myt = gl_GetUniformLocation(programT2, "myTexture");
				if(myt != -1){
				gl_Uniform1i(myt, 0);
				}

				glActiveTexture(GL_TEXTURE1);
				GLint nmap = gl_GetUniformLocation(programT2, "nmap");
				if(nmap != -1){
				gl_Uniform1i(nmap, 1);
				}
				glActiveTexture(GL_TEXTURE1);
				if((s == 20) || (s == 21)){
					glBindTexture(GL_TEXTURE_2D, g->imgr2);
				}
				else
					glBindTexture(GL_TEXTURE_2D, g->img2);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				

			

			glBegin( GL_QUAD_STRIP );
			
			for(int nx = g->stripe[s].Istart;nx < g->stripe[s].Iend;nx++){

				
								
				for(int ipdisp = 0;ipdisp < 2;ipdisp++){
					
					idv = O[idisp][nx][ipdisp][0]; idn=O[idisp][nx][ipdisp][1];
					idc = O[idisp][nx][ipdisp][2]; idt=O[idisp][nx][ipdisp][3];

					glTexCoord2f(tex[idt][0], tex[idt][1]);
					glColor4f(C[idc][0],C[idc][1], C[idc][2], 0.5f);
					glNormal3f(N[idn][0], N[idn][1], N[idn][2]);
					glVertex3f(P[idv][0], P[idv][1], P[idv][2]);
					//printf("x : %f, y : %f, z : %f\n", P[idv][0] +X, P[idv][1]+Y, P[idv][2]+Z);
				}

				
				if(nx == (g->stripe[s].Iend-1)){

					for(int ipdisp = 3;ipdisp >= 2 ;ipdisp--){

						idv = O[idisp][nx][ipdisp][0]; idn=O[idisp][nx][ipdisp][1];
						idc = O[idisp][nx][ipdisp][2]; idt=O[idisp][nx][ipdisp][3];

						glTexCoord2f(tex[idt][0], tex[idt][1]);
						glColor4f(C[idc][0],C[idc][1], C[idc][2], 0.5f);
						glNormal3f(N[idn][0], N[idn][1], N[idn][2]);
						glVertex3f(P[idv][0] , P[idv][1], P[idv][2]);
						//printf("x : %f, y : %f, z : %f\n", P[idv][0] +X, P[idv][1]+Y, P[idv][2]+Z);
					
					}

				}
				

				
			}

			glEnd();
			glFlush();



		
		}

		glDisable(GL_TEXTURE_CUBE_MAP);
		//glDepthMask(GL_TRUE);



}



static void Draw_Gun_Ammo(Gun *g){

	int idt, idc, idn, idv, ifc;
glEnable(GL_TEXTURE_2D);
	

	gl_UseProgram (programT2);
		
	GLint isw = gl_GetUniformLocation(programT2, "iswater");
	gl_Uniform3f(isw, 0.0f, 0.0f, 0.0f);

	GLint fg = gl_GetUniformLocation(programT2, "fgreen");
	gl_Uniform3f(fg, 0.0f, 3.0f, 0.0f);

	GLint ishg = gl_GetUniformLocation(programT2, "isshin");
	gl_Uniform3f(ishg, 0.0f, 0.0f, 0.0f);

for(int i = 0;i < g->max_A;i++){

	int idisp = g->ammo[i].nIobj;

	if(g->ammo[i].onfire == 0)
		continue;

		

		/*GLint ures = gl_GetUniformLocation(shader_def.program, "u_res");
		gl_Uniform3f(ures, g->W, g->H, 0.0f);
		GLint pos = gl_GetUniformLocation(shader_def.program, "position");
		gl_Uniform3f(pos, 5, 5, 0.0f);*/
			
		for(int s = 0;s < g->ammo[i].max_S;s++){
			//gl_UseProgram (shader_def.program);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, O[idisp][g->ammo[i].stripe[s].Istart][0][4]);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			/*if((s == 20) || (s == 21)){
				gl_Uniform3f(isw, 0.0f, 0.0f, 0.0f);
				gl_Uniform3f(fg, 0.0f, 0.5f, 0.0f);

			}
			else*/
				//gl_Uniform3f(isw, 0.0f, 0.0f, 0.0f);

			//if(s < 2){

				GLint myt = gl_GetUniformLocation(programT2, "myTexture");
				if(myt != -1){
				gl_Uniform1i(myt, 0);
				}

				glActiveTexture(GL_TEXTURE1);
				GLint nmap = gl_GetUniformLocation(programT2, "nmap");
				if(nmap != -1){
				gl_Uniform1i(nmap, 1);
				}
				glActiveTexture(GL_TEXTURE1);
				/*if((s == 20) || (s == 21)){
					glBindTexture(GL_TEXTURE_2D, g->imgr2);
				}
				else*/
					glBindTexture(GL_TEXTURE_2D, g->ammo[i].img2);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


			

			glBegin( GL_QUAD_STRIP );
			
			for(int nx = g->ammo[i].stripe[s].Istart;nx < g->ammo[i].stripe[s].Iend;nx++){

				
								
				for(int ipdisp = 0;ipdisp < 2;ipdisp++){
					
					idv = O[idisp][nx][ipdisp][0]; idn=O[idisp][nx][ipdisp][1];
					idc = O[idisp][nx][ipdisp][2]; idt=O[idisp][nx][ipdisp][3];

					glTexCoord2f(tex[idt][0], tex[idt][1]);
					glColor4f(C[idc][0],C[idc][1], C[idc][2], 0.5f);
					glNormal3f(N[idn][0], N[idn][1], N[idn][2]);
					glVertex3f(P[idv][0]+g->ammo[i].X, P[idv][1]+g->ammo[i].Y, P[idv][2]+g->ammo[i].Z);
					
					//printf("x : %f, y : %f, z : %f\n", P[idv][0]+g->ammo[i].X , P[idv][1]+g->ammo[i].Y, P[idv][2]+g->ammo[i].Z);
				}

				
				if(nx == (g->ammo[i].stripe[s].Iend-1)){

					for(int ipdisp = 3;ipdisp >= 2 ;ipdisp--){

						idv = O[idisp][nx][ipdisp][0]; idn=O[idisp][nx][ipdisp][1];
						idc = O[idisp][nx][ipdisp][2]; idt=O[idisp][nx][ipdisp][3];

						glTexCoord2f(tex[idt][0], tex[idt][1]);
						glColor4f(C[idc][0],C[idc][1], C[idc][2], 0.5f);
						glNormal3f(N[idn][0], N[idn][1], N[idn][2]);
						glVertex3f(P[idv][0]+g->ammo[i].X, P[idv][1]+g->ammo[i].Y, P[idv][2]+g->ammo[i].Z);
						//printf("x : %f, y : %f, z : %f\n", P[idv][0]+g->ammo.X+X , P[idv][1]+g->ammo.Y+Y, P[idv][2]+g->ammo.Z+Z);
					
					}

				}
				

				
			}

			glEnd();
			glFlush();

		
		}


}



}





