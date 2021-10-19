static struct _LineEdge{

	float lineH[200];
	float lineB[200];
	float lineG[200];
	float lineD[200];

}__LineEdge;

static struct _Line{

	float line1[200][3];
	float line2[200][3];
	int max_L;
	int max_L2;
	float N[200][3];
	float N2[200][3];
	float T[200][2];
	float T2[200][2];
	int col;
	int img;

}__Line;


typedef struct _Line Line;
typedef struct _LineEdge LineEdge;


static void Init_Line(Line *l){

	l->max_L = 0;
	l->max_L2 = 0;
	l->col = 6;
}

static void Line2_e_Line1(Line *l){

	for(int i = 0;i < l->max_L;i++){
		l->line2[i][0] = l->line1[i][0];
		l->line2[i][1] = l->line1[i][1];
		l->line2[i][2] = l->line1[i][2];
	}


}


static struct _Stripe{

	int Istart;
	int Iend;
	int Ipomin;
	int Ipomax;
	int Itxmin;
	int Itxmax;
	
}__Stripe;

typedef struct _Stripe Stripe;

static void Init_Stripe(Stripe *s){
	s->Istart = 0;
	s->Iend = 0;

}

static void Init_Obj(){

	NF[Iobj] = 0;

}


static void Add_Line1(Line *l){

	int mx = l->max_L;
	for(int i = 0;i < mx;i++){

		//Point
		P[Ipo][0] = l->line1[i][0];
		P[Ipo][1] = l->line1[i][1];
		P[Ipo][2] = l->line1[i][2];
		
		//Normal
		N[Ipo][0] = l->N[i][0];
		N[Ipo][1] = l->N[i][1];
		N[Ipo][2] = l->N[i][2];
	
		Ipo = Ipo + 1;

		tex[Itx][0] = l->T[i][0];
		tex[Itx][1] = l->T[i][1];

		Itx = Itx + 1;
		
			
	}

}

static void Add_Line2(Line *l){

	int mx = l->max_L2;
	for(int i = 0;i < mx;i++){

		//Point
		P[Ipo][0] = l->line2[i][0];
		P[Ipo][1] = l->line2[i][1];
		P[Ipo][2] = l->line2[i][2];
		
		//Normal
		N[Ipo][0] = l->N2[i][0];
		N[Ipo][1] = l->N2[i][1];
		N[Ipo][2] = l->N2[i][2];
	
		Ipo = Ipo + 1;

		tex[Itx][0] = l->T2[i][0];
		tex[Itx][1] = l->T2[i][1];

		Itx = Itx + 1;
			
	}


}


static void Create_Face(Line *l, Stripe *s){

	int mx = l->max_L;
	int Ifc = NF[Iobj];
	int ipomin = s->Ipomin;
	int ipomax = s->Ipomax;
	int itxmin = s->Itxmin;
	int itxmax = s->Itxmax;
	
	s->Istart = Ifc;

	

	for(int i = 0;i < mx-1;i++){

		//indice
		O[Iobj][Ifc][0][0] = ipomin;
		O[Iobj][Ifc][0][1] = ipomin;
		O[Iobj][Ifc][0][2] = l->col;
		O[Iobj][Ifc][0][3] = itxmin;
		O[Iobj][Ifc][0][4] = l->img;

		O[Iobj][Ifc][1][0] = ipomin+mx;
		O[Iobj][Ifc][1][1] = ipomin+mx;
		O[Iobj][Ifc][1][2] = l->col;
		O[Iobj][Ifc][1][3] = itxmin+mx;
		O[Iobj][Ifc][1][4] = l->img;

		O[Iobj][Ifc][2][0] = ipomin+mx+1;
		O[Iobj][Ifc][2][1] = ipomin+mx+1;
		O[Iobj][Ifc][2][2] = l->col;
		O[Iobj][Ifc][2][3] = itxmin+mx+1;
		O[Iobj][Ifc][2][4] = l->img;

		O[Iobj][Ifc][3][0] = ipomin+1;
		O[Iobj][Ifc][3][1] = ipomin+1;
		O[Iobj][Ifc][3][2] = l->col;
		O[Iobj][Ifc][3][3] = itxmin+1;
		O[Iobj][Ifc][3][4] = l->img;

		ipomin = ipomin + 1;
		itxmin = itxmin + 1;

	
		NF[Iobj] = NF[Iobj] + 1;//Init a 0 avant
		Ifc = Ifc + 1;

	}

	s->Iend = Ifc;

}



static void Straw(Stripe  *s, float longueur, int sens, int img, float tuv){

	Line l;

	Init_Line(&l);
	l.col = 4;

	l.line1[0][0] = 2.0f;
	l.line1[0][1] = 5.0f;
	l.line1[0][2] = -15.0f;
	l.N[0][0] = 0.0f;
	l.N[0][1] = 1.0f;
	l.N[0][2] = 0.1f;
	l.N2[0][0] = 0.0f;
	l.N2[0][1] = 1.0f;
	l.N2[0][2] = 0.1f;
	l.T[0][0] = 0.0f;
	l.T[0][1] = 1.0f;
	l.T2[0][0] = 0.0f;
	l.T2[0][1] = 0.0f;
	

	float tx = 1.0f / tuv;
	float ty = 1.0f / tuv;

	float max_ampl = 4.0f;
	float sta;

	l.img = img;
	l.max_L = 9;
	l.max_L2 = 9;

	
	for(int i = 1;i < l.max_L;i++){
		sta = sin(((float)i/max_ampl)/2.0f*3.1415) ;

		
		l.line1[i][0] = l.line1[i-1][0] + 1.0f;
			
		
		if(sens == 1)
			l.line1[i][1] = l.line1[0][1] + sta;
		else
			l.line1[i][1] = l.line1[0][1] - sta;

		l.line1[i][2] = l.line1[i-1][2];

		l.N[i][0] = l.N[i-1][0];
		l.N[i][1] = l.N[i-1][1];
		l.N[i][2] = l.N[i-1][2];

		l.T[i][0] = l.T[i-1][0] + tx;
		l.T[i][1] = l.T[i-1][1];
		

		
	}


	

	for(int i = 0;i < l.max_L;i++){

		l.line2[i][0] = l.line1[i][0];
		l.line2[i][1] = l.line1[i][1];
		l.line2[i][2] = l.line1[i][2]+longueur;

		l.N2[i][0] = l.N[i][0];
		l.N2[i][1] = l.N[i][1];
		l.N2[i][2] = l.N[i][2];

		l.T2[i][0] = tx * (float)i;
		l.T2[i][1] = 0.0f;

	}

	/*for(int i = 0;i < l.max_L;i++){
		printf("----------i : %d------------\n", i);
		printf("L x : %f, y : %f, z : %f\n", l.line1[i][0], l.line1[i][1], l.line1[i][2]);
		printf("L x : %f, y : %f, z : %f\n", l.N[i][0], l.N[i][1], l.N[i][2]);
		printf("L s : %f, t : %f\n", l.T[i][0], l.T[i][1]);

	}
	for(int i = 0;i < l.max_L2;i++){
		printf("----------i2 : %d------------\n", i);
		printf("L2 x : %f, y : %f, z : %f\n", l.line2[i][0], l.line2[i][1], l.line2[i][2]);
		printf("L x : %f, y : %f, z : %f\n", l.N2[i][0], l.N2[i][1], l.N2[i][2]);
		printf("L s : %f, t : %f\n", l.T2[i][0], l.T2[i][1]);


	}*/
	

	Init_Stripe(s);
	s->Ipomin = Ipo;
	s->Itxmin = Itx;
	Add_Line1(&l);
	Add_Line2(&l);
	s->Ipomax = Ipo;
	s->Itxmax = Itx;

	Create_Face(&l, s);
	
}

static void StrawC(Stripe  *s, float longueur, int sens, int img, float tuv){

	Line l;

	Init_Line(&l);
	l.col = 4;

	l.line1[0][0] = longueur;
	l.line1[0][1] = 5.0f;
	l.line1[0][2] = -15.0f;
	l.N[0][0] = 0.0f;
	l.N[0][1] = 1.0f;
	l.N[0][2] = 0.1f;
	l.N2[0][0] = 0.0f;
	l.N2[0][1] = 1.0f;
	l.N2[0][2] = 0.1f;
	l.T[0][0] = 0.0f;
	l.T[0][1] = 1.0f;
	l.T2[0][0] = 0.0f;
	l.T2[0][1] = 0.0f;
	

	float tx = 1.0f / tuv;
	float ty = 1.0f / tuv;

	float max_ampl = 4.0f;
	float sta;

	l.img = img;
	l.max_L = 11;
	l.max_L2 = 11;
	float max = 10.0f ;
	
	for(int i = 1;i < l.max_L;i++){
		sta = longueur * sin(  ((float)i/(float)max)*3.141592654f) ;

		
		l.line1[i][0] = longueur * cos(  ((float)i/(float)max)*3.141592654f); //l.line1[i-1][0] + 1.0f;
			
		
		if(sens == 1)
			l.line1[i][1] = l.line1[0][1] + sta;
		else
			l.line1[i][1] = l.line1[0][1] - sta;

		l.line1[i][2] = l.line1[i-1][2];

		l.N[i][0] = l.N[i-1][0];
		l.N[i][1] = l.N[i-1][1];
		l.N[i][2] = l.N[i-1][2];

		l.T[i][0] = l.T[i-1][0] + tx;
		l.T[i][1] = l.T[i-1][1];
		

		
	}


	

	for(int i = 0;i < l.max_L;i++){

		l.line2[i][0] = l.line1[i][0];
		l.line2[i][1] = l.line1[i][1];
		l.line2[i][2] = l.line1[i][2]+longueur;

		l.N2[i][0] = l.N[i][0];
		l.N2[i][1] = l.N[i][1];
		l.N2[i][2] = l.N[i][2];

		l.T2[i][0] = tx * (float)i;
		l.T2[i][1] = 0.0f;

	}
	/*for(int i = 0;i < l.max_L;i++){
		printf("----------i : %d------------\n", i);
		printf("L x : %f, y : %f, z : %f\n", l.line1[i][0], l.line1[i][1], l.line1[i][2]);
		printf("L x : %f, y : %f, z : %f\n", l.N[i][0], l.N[i][1], l.N[i][2]);
		printf("L s : %f, t : %f\n", l.T[i][0], l.T[i][1]);

	}
	for(int i = 0;i < l.max_L2;i++){
		printf("----------i2 : %d------------\n", i);
		printf("L2 x : %f, y : %f, z : %f\n", l.line2[i][0], l.line2[i][1], l.line2[i][2]);
		printf("L x : %f, y : %f, z : %f\n", l.N2[i][0], l.N2[i][1], l.N2[i][2]);
		printf("L s : %f, t : %f\n", l.T2[i][0], l.T2[i][1]);


	}*/
	

	Init_Stripe(s);
	s->Ipomin = Ipo;
	s->Itxmin = Itx;
	Add_Line1(&l);
	Add_Line2(&l);
	s->Ipomax = Ipo;
	s->Itxmax = Itx;

	Create_Face(&l, s);
	
}


static void StrawS(Stripe  *s, float longueur, int sens, int img, float nb, float nh, float ny, float tuv){

	Line l;

	Init_Line(&l);
	l.col = 4;

	l.line1[0][0] = 0.0f;
	l.line1[0][1] = 0.0f;
	l.line1[0][2] = 0.0f;
	l.N[0][0] = 0.0f;
	l.N[0][1] = 1.0f;
	l.N[0][2] = 0.1f;
	l.N2[0][0] = 0.0f;
	l.N2[0][1] = 1.0f;
	l.N2[0][2] = 0.1f;
	l.T[0][0] = 0.0f;
	l.T[0][1] = 0.0f;
	l.T2[0][0] = 0.0f;
	l.T2[0][1] = 0.0f;
	

	float tx = 1.0f / tuv;
	float ty = 1.0f / tuv;

	float max_ampl = 4.0f;
	float sta;

	l.img = img;
	l.max_L = 11;
	l.max_L2 = 11;
	float max = 10.0f ;
	
	for(int i = 0;i < l.max_L;i++){
		sta = longueur* cos(  ((float)nb/(float)max)*(3.141592654f/2.0f)) * sin(  ((float)i/(float)max)*3.141592654f) ;

//longueur *sin(  ((float)i/(float)max)*3.141592654f) ;

		
		l.line1[i][0] = longueur * cos(  (nb)*(3.141592654f/2.0f)) * cos(  ((float)i/(float)max)*3.141592654f); 
			
		l.line1[i][1] = l.line1[0][1];
		
		if(sens == 1)
			l.line1[i][2] =  sta;
		else
			l.line1[i][2] =  -sta;

		l.N[i][0] = l.N[0][0];
		l.N[i][1] = l.N[0][1];
		l.N[i][2] = l.N[0][2];

		l.T[i][0] = (float)i * tx;
		l.T[i][1] = 0.0f;
		

		
	}


	float stay = longueur *sin(  ((float)ny/(float)max)*3.141592654f) ;

	for(int i = 0;i < l.max_L;i++){

		sta = longueur* cos(  ((float)nh/(float)max)*(3.141592654f/2.0f)) * sin(  ((float)i/(float)max)*3.141592654f) ;

		
		l.line2[i][0] = longueur * cos(  (nh/(float)max)*(3.141592654f/2.0f)) * cos(  ((float)i/(float)max)*3.141592654f); 
			
		l.line2[i][1] = l.line1[i][1] + stay;
		
		if(sens == 1)
			l.line2[i][2] =  sta;
		else
			l.line2[i][2] = - sta;

		l.N2[i][0] = l.N[i][0];
		l.N2[i][1] = l.N[i][1];
		l.N2[i][2] = l.N[i][2];

		l.T2[i][0] = tx * (float)i;
		l.T2[i][1] = ty;

	}
	/*for(int i = 0;i < l.max_L;i++){
		printf("----------i : %d------------\n", i);
		printf("L x : %f, y : %f, z : %f\n", l.line1[i][0], l.line1[i][1], l.line1[i][2]);
		printf("L x : %f, y : %f, z : %f\n", l.N[i][0], l.N[i][1], l.N[i][2]);
		printf("L s : %f, t : %f\n", l.T[i][0], l.T[i][1]);

	}
	for(int i = 0;i < l.max_L2;i++){
		printf("----------i2 : %d------------\n", i);
		printf("L2 x : %f, y : %f, z : %f\n", l.line2[i][0], l.line2[i][1], l.line2[i][2]);
		printf("L x : %f, y : %f, z : %f\n", l.N2[i][0], l.N2[i][1], l.N2[i][2]);
		printf("L s : %f, t : %f\n", l.T2[i][0], l.T2[i][1]);


	}*/
	

	Init_Stripe(s);
	s->Ipomin = Ipo;
	s->Itxmin = Itx;
	Add_Line1(&l);
	Add_Line2(&l);
	s->Ipomax = Ipo;
	s->Itxmax = Itx;

	Create_Face(&l, s);
	
}


static void StrawB(Stripe  *s, float longueur, int img, float tuv){

	Line l;

	Init_Line(&l);
	l.col = 4;

	l.line1[0][0] = 2.0f;
	l.line1[0][1] = 5.0f;
	l.line1[0][2] = -15.0f;
	l.N[0][0] = 0.0f;
	l.N[0][1] = 1.0f;
	l.N[0][2] = 0.1f;
	l.N2[0][0] = 0.0f;
	l.N2[0][1] = 1.0f;
	l.N2[0][2] = 0.1f;
	l.T[0][0] = 0.0f;
	l.T[0][1] = 1.0f;
	l.T2[0][0] = 0.0f;
	l.T2[0][1] = 0.0f;
	
	l.max_L = 2;
	l.max_L2 = 2;
	float tx = 1.0f / ((float)l.max_L/tuv);
	float ty = 1.0f / ((float)l.max_L/tuv);

	float max_ampl = 4.0f;
	float sta;

	l.img = img;
	

	
	for(int i = 1;i < l.max_L;i++){
				
		l.line1[i][0] = l.line1[0][0];
		l.line1[i][1] = l.line1[0][1];
		l.line1[i][2] = l.line1[i-1][2] + longueur;

		l.N[i][0] = l.N[i-1][0];
		l.N[i][1] = l.N[i-1][1];
		l.N[i][2] = l.N[i-1][2];

		l.T[i][0] = l.T[i-1][0] + tx;
		l.T[i][1] = l.T[i-1][1];
		

		
	}


	

	for(int i = 0;i < l.max_L;i++){

		l.line2[i][0] = l.line1[i][0]+longueur;
		l.line2[i][1] = l.line1[i][1];
		l.line2[i][2] = l.line1[i][2];

		l.N2[i][0] = l.N[i][0];
		l.N2[i][1] = l.N[i][1];
		l.N2[i][2] = l.N[i][2];

		l.T2[i][0] = tx * (float)i;
		l.T2[i][1] = 0.0f;

	}

	/*for(int i = 0;i < l.max_L;i++){
		printf("----------i : %d------------\n", i);
		printf("L x : %f, y : %f, z : %f\n", l.line1[i][0], l.line1[i][1], l.line1[i][2]);
		printf("L x : %f, y : %f, z : %f\n", l.N[i][0], l.N[i][1], l.N[i][2]);
		printf("L s : %f, t : %f\n", l.T[i][0], l.T[i][1]);

	}
	for(int i = 0;i < l.max_L2;i++){
		printf("----------i2 : %d------------\n", i);
		printf("L2 x : %f, y : %f, z : %f\n", l.line2[i][0], l.line2[i][1], l.line2[i][2]);
		printf("L x : %f, y : %f, z : %f\n", l.N2[i][0], l.N2[i][1], l.N2[i][2]);
		printf("L s : %f, t : %f\n", l.T2[i][0], l.T2[i][1]);
	}*/
		

	Init_Stripe(s);
	s->Ipomin = Ipo;
	s->Itxmin = Itx;
	Add_Line1(&l);
	Add_Line2(&l);
	s->Ipomax = Ipo;
	s->Itxmax = Itx;

	Create_Face(&l, s);
	
}

static void rotate_StripeX(float a, int ipomin, int ipomax){

	a = a * 3.141592654f / 180.0f;
	float M[9];
	M[0] = 1.0f;
	M[1] = 0.0f;
	M[2] = 0.0f;
	M[3] = 0.0f;
	M[4] = cos(a);
	M[5] = -sin(a);
	M[6] = 0.0f;
	M[7] = sin(a);
	M[8] = cos(a);

	float px =0.0f, py=0.0f, pz=0.0f;

	for(int i = ipomin; i < ipomax;i++){
		px = px + P[i][0];
		py = py + P[i][1];
		pz = pz + P[i][2];
	}

	

	float n = ipomax - ipomin;//(float)NF[no]*4.0f;
	px = px / n;
	py = py / n;
	pz = pz / n;
	
	/*X = M[0] * X;
	Y = M[4] * Y + M[5] * Z;
	Z = M[7] * Y + M[8] * Z;*/
	float X1, Y1, Z1, X2, Y2, Z2;
	float NX1, NY1, NZ1, NX2, NY2, NZ2;

	for(int i = ipomin; i < ipomax;i++){
		
		X1 = P[i][0]-px; Y1 = P[i][1]-py; Z1 = P[i][2]-pz;
		X2 = M[0] * X1;
		Y2 = M[4] * Y1 + M[5] * Z1;
		Z2 = M[7] * Y1 + M[8] * Z1;

		P[i][0] = X2+px;
		P[i][1] = Y2+py;
		P[i][2] = Z2+pz;

		/*NX1 = N[i][0]; NY1 = N[i][1]; NZ1 = N[i][2];
		NX2 = M[0] * NX1;
		NX2 = M[4] * NY1 + M[5] * NZ1;
		NX2 = M[7] * NY1 + M[8] * NZ1;

		float sq = sqrt(NX2*NX2 + NY2*NY2 + NZ2*NZ2 ); 
				

		N[i][0] = NX2/sq;
		N[i][1] = NY2/sq;
		N[i][2] = NZ2/sq;*/


	}



}


static void rotate_StripeY(float a, int ipomin, int ipomax){

	a = a * 3.141592654f / 180.0f;
			

	float M[9];
	M[0] = cos(a);
	M[1] = 0.0f;
	M[2] = sin(a);
	M[3] = 0.0f;
	M[4] = 1.0f;
	M[5] = 0.0f;
	M[6] = -sin(a);
	M[7] = 0.0f;
	M[8] = cos(a);

	float px =0.0f, py=0.0f, pz=0.0f;

	for(int i = ipomin; i < ipomax;i++){
		px = px + P[i][0];
		py = py + P[i][1];
		pz = pz + P[i][2];
	}

	

	float n = ipomax - ipomin;//(float)NF[no]*4.0f;
	px = px / n;
	py = py / n;
	pz = pz / n;
	
	/*X = M[0] * X;
	Y = M[4] * Y + M[5] * Z;
	Z = M[7] * Y + M[8] * Z;*/
	float X1, Y1, Z1, X2, Y2, Z2;
	float NX1, NY1, NZ1, NX2, NY2, NZ2;

	for(int i = ipomin; i < ipomax;i++){
		
		X1 = P[i][0]-px; Y1 = P[i][1]-py; Z1 = P[i][2]-pz;
		X2 = M[0] * X1 + M[1] * Y1 + M[2] * Z1;
		Y2 = M[3] * X1 + M[4] * Y1 + M[5] * Z1;
		Z2 = M[6] * X1 + M[7] * Y1 + M[8] * Z1;

		P[i][0] = X2+px;
		P[i][1] = Y2+py;
		P[i][2] = Z2+pz;

		NX1 = N[i][0]; NY1 = N[i][1]; NZ1 = N[i][2];
		NX2 = M[0] * NX1 + M[1] * NY1 + M[2] * NZ1;
		NY2 = M[3] * NX1 + M[4] * NY1 + M[5] * NZ1;
		NZ2 = M[6] * NX1 + M[7] * NY1 + M[8] * NZ1;

		float sq = sqrt(NX2*NX2 + NY2*NY2 + NZ2*NZ2 ); 
				

		N[i][0] = NX2/sq;
		N[i][1] = NY2/sq;
		N[i][2] = NZ2/sq;


	}



}

static void rotate_StripeZ(float a, int ipomin, int ipomax){

	a = a * 3.141592654f / 180.0f;
			

	float M[9];
	M[0] = cos(a);
	M[1] = -sin(a);
	M[2] = 0.0f;
	M[3] = sin(a);
	M[4] = cos(a);
	M[5] = 0.0f;
	M[6] = 0.0;
	M[7] = 0.0f;
	M[8] = 1.0f;

	float px =0.0f, py=0.0f, pz=0.0f;

	for(int i = ipomin; i < ipomax;i++){
		px = px + P[i][0];
		py = py + P[i][1];
		pz = pz + P[i][2];
	}

	

	float n = ipomax - ipomin;//(float)NF[no]*4.0f;
	px = px / n;
	py = py / n;
	pz = pz / n;
	
	/*X = M[0] * X;
	Y = M[4] * Y + M[5] * Z;
	Z = M[7] * Y + M[8] * Z;*/
	float X1, Y1, Z1, X2, Y2, Z2;
	float NX1, NY1, NZ1, NX2, NY2, NZ2;

	for(int i = ipomin; i < ipomax;i++){
		
		X1 = P[i][0]-px; Y1 = P[i][1]-py; Z1 = P[i][2]-pz;
		X2 = M[0] * X1 + M[1] * Y1 + M[2] * Z1;
		Y2 = M[3] * X1 + M[4] * Y1 + M[5] * Z1;
		Z2 = M[6] * X1 + M[7] * Y1 + M[8] * Z1;

		P[i][0] = X2+px;
		P[i][1] = Y2+py;
		P[i][2] = Z2+pz;

		NX1 = N[i][0]; NY1 = N[i][1]; NZ1 = N[i][2];
		NX2 = M[0] * NX1 + M[1] * NY1 + M[2] * NZ1;
		NY2 = M[3] * NX1 + M[4] * NY1 + M[5] * NZ1;
		NZ2 = M[6] * NX1 + M[7] * NY1 + M[8] * NZ1;

		float sq = sqrt(NX2*NX2 + NY2*NY2 + NZ2*NZ2 ); 
				

		N[i][0] = NX2/sq;
		N[i][1] = NY2/sq;
		N[i][2] = NZ2/sq;


	}



}


