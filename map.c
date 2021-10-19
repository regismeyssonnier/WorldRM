static int color_map = 4;
static GLuint txmap=0, ntxmap=0, inittx=1, numtx=-1;


void Add_face_X(float sz, int ipo, float ht, int ifc, float ltu, float ltv, float ttu, float ttv){

	//Point
	P[Ipo][0] = P[ipo][0]+sz;
	P[Ipo][1] = P[ipo][1]+ht;
	P[Ipo][2] = P[ipo][2]+sz;

	P[Ipo+1][0] = P[ipo][0]+sz;
	P[Ipo+1][1] = P[ipo][1]+ht;
	P[Ipo+1][2] = P[ipo][2];

	//Normal
	N[Ipo][0] = 0;
	N[Ipo][1] = 1;
	N[Ipo][2] = 0;
		
	N[Ipo+1][0] = 0;
	N[Ipo+1][1] = 1;
	N[Ipo+1][2] = 0;

	//texture coord
	tex[Itx][0] = ltu;
	tex[Itx][1] = 1;

	tex[Itx+1][0] = ltu;
	tex[Itx+1][1] = 1.0f-ttv;

	tex[Itx+2][0] = ltu+ttu;
	tex[Itx+2][1] = 1.0f-ttv;

	tex[Itx+3][0] = ltu+ttu;
	tex[Itx+3][1] = 1.0f;

	
	//indice
	O[Iobj][ifc][0][0] = Ipo-1;
	O[Iobj][ifc][0][1] = Ipo-1;
	O[Iobj][ifc][0][2] = color_map;
	O[Iobj][ifc][0][3] = Itx;
	O[Iobj][ifc][0][4] = Iim;

	O[Iobj][ifc][1][0] = Ipo-2;
	O[Iobj][ifc][1][1] = Ipo-2;
	O[Iobj][ifc][1][2] = color_map;
	O[Iobj][ifc][1][3] = Itx+1;
	O[Iobj][ifc][1][4] = Iim;

	O[Iobj][ifc][2][0] = Ipo;
	O[Iobj][ifc][2][1] = Ipo;
	O[Iobj][ifc][2][2] = color_map;
	O[Iobj][ifc][2][3] = Itx+2;
	O[Iobj][ifc][2][4] = Iim;

	O[Iobj][ifc][3][0] = Ipo+1;
	O[Iobj][ifc][3][1] = Ipo+1;
	O[Iobj][ifc][3][2] = color_map;
	O[Iobj][ifc][3][3] = Itx+3;
	O[Iobj][ifc][3][4] = Iim;


	Ipo = Ipo + 2;
	//Iim = Iim + 1;  
	Itx = Itx + 4;
	NF[Iobj] = NF[Iobj] + 1;
	//Iobj = Iobj + 1;

}

void Add_face_Z(float sz, int ipo, float ht, int ifc, float ltu, float ltv, float ttu, float ttv){

	/*P[Ipo+1][0] = px;
	P[Ipo+1][1] = py;
	P[Ipo+1][2] = pz+sz;

	P[Ipo+2][0] = px+sz;
	P[Ipo+2][1] = py+ht;
	P[Ipo+2][2] = pz+sz;*/

	//Point
	P[Ipo][0] = P[ipo][0];
	P[Ipo][1] = P[ipo][1];
	P[Ipo][2] = P[ipo][2]+sz;

	P[Ipo+1][0] = P[ipo][0]+sz;
	P[Ipo+1][1] = P[ipo][1]+ht;
	P[Ipo+1][2] = P[ipo][2]+sz;

	//Normal
	N[Ipo][0] = 0;
	N[Ipo][1] = 1;
	N[Ipo][2] = 0;
		
	N[Ipo+1][0] = 0;
	N[Ipo+1][1] = 1;
	N[Ipo+1][2] = 0;

	//texture coord
	tex[Itx][0] = ltu;
	tex[Itx][1] = ltv+ttv;

	tex[Itx+1][0] = ltu;
	tex[Itx+1][1] = ltv;

	tex[Itx+2][0] = ltu+ttu;
	tex[Itx+2][1] = ltv;

	tex[Itx+3][0] = ltu+ttu;
	tex[Itx+3][1] = ltv+ttv;

	
	//indice
	O[Iobj][ifc][0][0] = ipo;
	O[Iobj][ifc][0][1] = ipo;
	O[Iobj][ifc][0][2] = color_map;
	O[Iobj][ifc][0][3] = Itx;
	O[Iobj][ifc][0][4] = Iim;

	O[Iobj][ifc][1][0] = Ipo;
	O[Iobj][ifc][1][1] = Ipo;
	O[Iobj][ifc][1][2] = color_map;
	O[Iobj][ifc][1][3] = Itx+1;
	O[Iobj][ifc][1][4] = Iim;

	O[Iobj][ifc][2][0] = Ipo+1;
	O[Iobj][ifc][2][1] = Ipo+1;
	O[Iobj][ifc][2][2] = color_map;
	O[Iobj][ifc][2][3] = Itx+2;
	O[Iobj][ifc][2][4] = Iim;

	O[Iobj][ifc][3][0] = ipo+1;
	O[Iobj][ifc][3][1] = ipo+1;
	O[Iobj][ifc][3][2] = color_map;
	O[Iobj][ifc][3][3] = Itx+3;
	O[Iobj][ifc][3][4] = Iim;


	Ipo = Ipo + 2;
	//Iim = Iim + 1;  
	Itx = Itx + 4;
	NF[Iobj] = NF[Iobj] + 1;
	//Iobj = Iobj + 1;

}


void Add_face_ZX(float sz, int ipo, float ht, int ifc, int p1, int p4, float ltu, float ltv, float ttu, float ttv){

	/*P[Ipo+2][0] = px+sz;
	P[Ipo+2][1] = py+ht;
	P[Ipo+2][2] = pz+sz;*/
	
	//Point
	P[Ipo][0] = P[ipo][0]+sz;
	P[Ipo][1] = P[ipo][1]+ht;
	P[Ipo][2] = P[ipo][2];
	
	//Normal
	N[Ipo][0] = 0;
	N[Ipo][1] = 1;
	N[Ipo][2] = 0;
		
	
	//texture coord
	tex[Itx][0] = ltu;
	tex[Itx][1] = ltv+ttv;

	tex[Itx+1][0] = ltu;
	tex[Itx+1][1] = ltv;

	tex[Itx+2][0] = ltu+ttu;
	tex[Itx+2][1] = ltv;

	tex[Itx+3][0] = ltu+ttu;
	tex[Itx+3][1] = ltv+ttv;

	
	//indice
	O[Iobj][ifc][0][0] = p1;
	O[Iobj][ifc][0][1] = p1;
	O[Iobj][ifc][0][2] = color_map;
	O[Iobj][ifc][0][3] = Itx;
	O[Iobj][ifc][0][4] = Iim;

	O[Iobj][ifc][1][0] = ipo;
	O[Iobj][ifc][1][1] = ipo;
	O[Iobj][ifc][1][2] = color_map;
	O[Iobj][ifc][1][3] = Itx+1;
	O[Iobj][ifc][1][4] = Iim;

	O[Iobj][ifc][2][0] = Ipo;
	O[Iobj][ifc][2][1] = Ipo;
	O[Iobj][ifc][2][2] = color_map;
	O[Iobj][ifc][2][3] = Itx+2;
	O[Iobj][ifc][2][4] = Iim;

	O[Iobj][ifc][3][0] = p4;
	O[Iobj][ifc][3][1] = p4;
	O[Iobj][ifc][3][2] = color_map;
	O[Iobj][ifc][3][3] = Itx+3;
	O[Iobj][ifc][3][4] = Iim;


	Ipo = Ipo + 1;
	//Iim = Iim + 1;  
	Itx = Itx + 4;
	NF[Iobj] = NF[Iobj] + 1;
	//Iobj = Iobj + 1;

}

int Same_Tex(int s){
	inittx = 1;
	txmap = s;
	numtx=-1;
}

void create_map(int _NX, int _NY, float px, float py, float pz, char *img, float _sz, float fact){

	if( ((inittx == 1) && (txmap == 1)) || (txmap == 0) ){
		
			if(numtx == -1){
				
				ntxmap = SOIL_load_OGL_texture
					(
						img,
						SOIL_LOAD_AUTO,
						SOIL_CREATE_NEW_ID,
						SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
					);
					
				/* check for an error during the load process */
				if( 0 == ntxmap )
				{
					printf( "MAP SOIL loading error: '%s'\n", SOIL_last_result() );
				}

				printf("tex : %s - %d\n", img, ntxmap);
			}
			else
				ntxmap = numtx;
		
		inittx = 0;

	}

	float sz = _sz;
	float ht = 0.0f;
	int Ifc = 0;
	int NX = _NX, NY = _NY;
	float tu, tv;

	tu = 1.0f / ((float)NX/fact);
	tv = 1.0f / ((float)NY/fact);
	

	//Point
	P[Ipo][0] = px;
	P[Ipo][1] = py;
	P[Ipo][2] = pz;
	
	P[Ipo+1][0] = px;
	P[Ipo+1][1] = py;
	P[Ipo+1][2] = pz+sz;

	P[Ipo+2][0] = px+sz;
	P[Ipo+2][1] = py+ht;
	P[Ipo+2][2] = pz+sz;

	P[Ipo+3][0] = px+sz;
	P[Ipo+3][1] = py+ht;
	P[Ipo+3][2] = pz;

	//Normal
	N[Ipo][0] = 0;
	N[Ipo][1] = 1;
	N[Ipo][2] = 0;
		
	N[Ipo+1][0] = 0;
	N[Ipo+1][1] = 1;
	N[Ipo+1][2] = 0;

	N[Ipo+2][0] = 0;
	N[Ipo+2][1] = 1;
	N[Ipo+2][2] = 0;

	N[Ipo+3][0] = 0;
	N[Ipo+3][1] = 1;
	N[Ipo+3][2] = 0;

	//texture coord
	tex[Itx][0] = 0;
	tex[Itx][1] = 1;

	tex[Itx+1][0] = 0;
	tex[Itx+1][1] = 1.0f-tv;

	tex[Itx+2][0] = tu;
	tex[Itx+2][1] = 1.0f-tv;

	tex[Itx+3][0] = tu;
	tex[Itx+3][1] = 1;

	//texture
	im[Iim] = ntxmap;
	

	//indice
	O[Iobj][Ifc][0][0] = Ipo;
	O[Iobj][Ifc][0][1] = Ipo;
	O[Iobj][Ifc][0][2] = color_map;
	O[Iobj][Ifc][0][3] = Itx;
	O[Iobj][Ifc][0][4] = Iim;

	O[Iobj][Ifc][1][0] = Ipo+1;
	O[Iobj][Ifc][1][1] = Ipo+1;
	O[Iobj][Ifc][1][2] = color_map;
	O[Iobj][Ifc][1][3] = Itx+1;
	O[Iobj][Ifc][1][4] = Iim;

	O[Iobj][Ifc][2][0] = Ipo+2;
	O[Iobj][Ifc][2][1] = Ipo+2;
	O[Iobj][Ifc][2][2] = color_map;
	O[Iobj][Ifc][2][3] = Itx+2;
	O[Iobj][Ifc][2][4] = Iim;

	O[Iobj][Ifc][3][0] = Ipo+3;
	O[Iobj][Ifc][3][1] = Ipo+3;
	O[Iobj][Ifc][3][2] = color_map;
	O[Iobj][Ifc][3][3] = Itx+3;
	O[Iobj][Ifc][3][4] = Iim;

	//Iim = Iim + 1;  
	Ipo = Ipo + 4;
	Itx = Itx + 4;
	NF[Iobj] = 1;
	//Iobj = Iobj + 1;

	int LFX = Ipo-1, LFX2;
	LFX2 = LFX;
	float ht2 = ht;

	//Add a face
	Ifc = Ifc + 1;

	float ltu, ltv;
	ltu = tu;
	ltv = 1.0f-tv;
	if(ltu >= 1.0f)ltu = 0.0f;
	if(ltv <= tv)ltv = 1.0f-tv;
	
	for(int i = 0;i < NX-1;i++){
		//printf("XXXXX ltu : %f, ltv : %f, i : %d\n", ltu, ltv, i+2);
		Add_face_X(sz, LFX2, ht, Ifc, ltu, ltv, tu, tv);
		LFX2 = Ipo - 1;
		Ifc = Ifc + 1;
		ltu = ltu + tu;
		//if(ltu > 1.0f)ltu = 0.0f;
		

	}

	ltv = ltv - tv;
	ltu = 0;

	//if(ltv < 0.0f)ltv = 1.0f-tv;

	//if(NY >= 2){
	int LFX3=LFX-2, LFX4, p1, p4;
	for(int j = 0;j < NY-1;j++){
		//printf("LFX3 : %d\n", LFX3);
						
		Add_face_Z(sz, LFX3, ht, Ifc, ltu, ltv, tu, tv);
		Ifc = Ifc + 1;
		
		LFX4 = Ipo-1;

		if(j == 0){
			p1 = LFX - 1;//2;//LFX4 - ((NX*2)+1);
			p4 = LFX + 1;//4;//p1+2;
			LFX3 = LFX3 + (NX*2)+1;
		}
		else
		{
			p1 = LFX4 - (NX+1);
			p4 = p1+1;
			LFX3 = LFX3 + (NX+1);
		}

		//LFX3 = LFX3 + ;//NX*(j+2)+(j+2);

		ltu = ltu + tu;
		//if(ltu > 1.0f)ltu = 0.0f;
		//printf("Z ltu : %f, ltv : %f\n", ltu, ltv);
				
		for(int i = 0;i < NX-1;i++){
			//printf("p1 : %d, p4 : %d\n", p1, p4);
			Add_face_ZX(sz, LFX4, ht, Ifc, p1, p4, ltu, ltv, tu, tv);
			LFX4 = Ipo-1;
			p1 = p4;
			if(j == 0)
				p4 = p4+2;
			else
				p4 = p4+1;
			Ifc = Ifc + 1;

			ltu = ltu+tu;
			//if(ltu > 1.0f)ltu = 0.0f;
			//printf("ZX ltu : %f, ltv : %f\n", ltu, ltv);
			//ltv = ltv - tv;
		}

		ltu = 0;
		ltv = ltv - tv;
		
		//if(ltv < 0.0f)ltv = 1.0f-tv;
		//printf("end ltu : %f, ltv : %f\n", ltu, ltv);
		//printf("lfx : %d, lfx2 : %d, lfx3 : %d, lfx4 : %d, p1 : %d, p4 : %d\n", LFX, LFX2, LFX3, LFX4, p1, p4);

		//printf("j : %d\n", j);

	}

	
	
	
	//printf("lfx : %d, lfx2 : %d, lfx3 : %d, lfx4 : %d, p1 : %d, p4 : %d\n", LFX, LFX2, LFX3, LFX4, p1, p4);
	//Add an object
	Iim = Iim + 1;
	Iobj = Iobj + 1;

}

float LastP[MAX_P];
float LastPP[MAX_P];
static float AA = 0.1;
static int PPP = 0;
void Anim(float t, int ipomin, int ipomax){
	float ii = 20.0f;
	for(int i = ipomin;i < ipomax;i++){
		AA = (t * ii) * 0.1f / 1000000.0f;
		//printf("AA : %f\n", AA);
		ii = ii + 0.1f;
		if(ii > 50.0f)
			ii = 20.0f;
		//PPP = PPP + t*i;
		//AA = sinf(PPP) / 1000.0f;//-sinf((float)i);
		if(LastP[i] == 1.0f)
			P[i][1] = P[i][1] + AA;
		else
			P[i][1] = P[i][1] - AA;

		//if(PPP > 1000000.0f)PPP = 0.0f;
		if(P[i][1] > (LastPP[i]+1.5f))LastP[i] = 0;
		if(P[i][1] < LastPP[i])LastP[i] = 1.0f;
	
	}


}



void Init_Point(){

	for(int i = 0;i < Ipo;i++){
		LastP[i] = 1.0f;
		LastPP[i] = P[i][1];
	}


	/*int **t = malloc(10*sizeof(int*));
	for(int i = 0;i < 10;i++){
		for(int j = 0;j < 10;j++){
			t[i] = malloc(10*sizeof(int));
		}
	}

	for(int i = 0;i < 10;i++){
		for(int j = 0;j < 10;j++){
			t[i][j] = (i*10)+j;
		}
	}

	for(int i = 0;i < 10;i++){
		for(int j = 0;j < 10;j++){
			printf("t[i][j]: %d\n", t[i][j]);
		}
	}*/


}


void Normal(){

	int id, idp;
	for(int idisp = 0;idisp < Iobj;idisp++){
		for(int ifdisp = 0;ifdisp < NF[idisp];ifdisp++){
	
			for(int ipdisp = 0;ipdisp < 4;ipdisp++){
				id = O[idisp][ifdisp][ipdisp][1]; idp = O[idisp][ifdisp][ipdisp][0];
				N[id][0] = 1.0f / (N[id][0]/2.0f);
				N[id][1] = 1.0f / (N[id][1]/2.0f) ;
				N[id][2] = 1.0f / (N[id][2]/2.0f) ;

				float sq = sqrt(N[id][0]*N[id][0] + 
					N[id][1]*N[id][1] + 
					N[id][2]*N[id][2] ); 
				N[id][0] = N[id][0] / sq;
				N[id][1] = N[id][1] / sq;
				N[id][2] = N[id][2] / sq;

				if(N[id][0] < 0.0f)N[id][0] = 0.0f;
				if(N[id][1] < 0.0f)N[id][1] = 1.0f;
				if(N[id][2] < 0.0f)N[id][2] = 0.0f;

			}

			



		}

	}

}

void ToSphere(int no, int nb, int ipomin, int ipomax){

	float px =0.0f, py=0.0f, pz=0.0f;

	/*for(int i = ipomin; i < ipomax;i++){
		px = px + P[i][0];
		py = py + P[i][1];
		pz = pz + P[i][2];
	}

	

	float n = ipomax - ipomin;//(float)NF[no]*4.0f;
	px = px / n;
	py = py / n;
	pz = pz / n;*/

	for(int xX = 0;xX < nb;xX++){

		int id, idp, idt;
		/*for(*/int idisp = no;//idisp < Iobj;idisp++){
			for(int ifdisp = 0;ifdisp < NF[idisp];ifdisp++){
		
				for(int ipdisp = 0;ipdisp < 4;ipdisp++){
					id = O[idisp][ifdisp][ipdisp][1]; idp = O[idisp][ifdisp][ipdisp][0];
					idt = O[idisp][ifdisp][ipdisp][1];
					/*N[id][0] = -N[id][0];
					N[id][1] = -N[id][1];
					N[id][2] = -N[id][2];*/

					float sq = sqrt((P[idp][0])*(P[idp][0]) + 
						(P[idp][1])*(P[idp][1]) + 
						(P[idp][2])*(P[idp][2]) ); 
					P[idp][0] = ((P[idp][0]) / sq)*100.0f;
					P[idp][1] = ((P[idp][1]) / sq)*100.0f;
					P[idp][2] = ((P[idp][2]) / sq)*100.0f;

					/*P[idp][0] = P[idp][0]+px;
					P[idp][1] = P[idp][1]+py;
					P[idp][2] = P[idp][2]+pz;*/
					//printf("x : %f, y : %f, z : %f\n", P[idp][0], P[idp][1], P[idp][2]);

					/*sq = sqrt(tex[idt][0]*tex[idt][0] + 
						tex[idt][1]*tex[idt][1]  ); 
					tex[idt][0] = (tex[idt][0] / sq)*5.0f;
					tex[idt][1] = (tex[idt][1] / sq)*5.0f;
					tex[idt][2] = (tex[idt][2] / sq)*5.0f;*/

					/*if(N[id][0] < 0.0f)N[id][0] = 0.0f;
					if(N[id][1] < 0.0f)N[id][1] = 1.0f;
					if(N[id][2] < 0.0f)N[id][2] = 0.0f;*/

				}

				



			}

		//}

	}

	/*for(int xX = 0;xX < nb;xX++){

		for(int i = 0;i < Ipo;i++){
			//id = O[idisp][ifdisp][ipdisp][1]; idp = O[idisp][ifdisp][ipdisp][0];
			

			float sq = sqrt(P[i][0]*P[i][0] + 
				P[i][1]*P[i][1] + 
				P[i][2]*P[i][2] ); 
			P[i][0] = -(P[i][0] / sq)*5.0f;
			P[i][1] = -(P[i][1] / sq)*5.0f;
			P[i][2] = -(P[i][2] / sq)*5.0f;


			

			printf("x : %f, y : %f, z : %f\n", P[i][0], P[i][1], P[i][2]);

		}

	}*/

	/*for(int i = 0;i < Ipo;i++){
		N[i][0] = -N[i][0];
		N[i][1] = -N[i][1];
		N[i][2] = -N[i][2];

	}*/

	

}

static void translateO(int ipmin, int ipmax, float x, float y, float z){

		for(int ip = ipmin;ip < ipmax;ip++){
			P[ip][0] = P[ip][0] + x;
			P[ip][1] = P[ip][1] + y;
			P[ip][2] = P[ip][2] + z;
		}

	

}

void Scale(float x, float y, float z, int ipomin, int ipomax){

	for(int i = ipomin; i < ipomax;i++){
		P[i][0] = P[i][0] * x;
		P[i][1] = P[i][1] * y;
		P[i][2] = P[i][2] * z;

		N[i][0] = N[i][0] * x;
		N[i][1] = N[i][1] * y;
		N[i][2] = N[i][2] * z;
	}

}


void rotate_mapX(float a, int ipomin, int ipomax){

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

		NX1 = N[i][0]; NY1 = N[i][1]; NZ1 = N[i][2];
		NX2 = M[0] * NX1;
		NX2 = M[4] * NY1 + M[5] * NZ1;
		NX2 = M[7] * NY1 + M[8] * NZ1;

		N[i][0] = NX2;
		N[i][1] = NY2;
		N[i][2] = NZ2;

	}



}


void rotate_mapY(float a, int ipomin, int ipomax){

	a = a * 3.141592654f / 180.0f;
			

	float M[9];
	M[0] = cos(a);
	M[1] = 0.0f;
	M[2] = sinf(a);
	M[3] = 0.0f;
	M[4] = 1.0f;
	M[5] = 0.0f;
	M[6] = -sinf(a);
	M[7] = 0.0f;
	M[8] = cosf(a);

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

		N[i][0] = NX2;
		N[i][1] = NY2;
		N[i][2] = NZ2;

	}



}

void rotate_mapZ(float a, int ipomin, int ipomax){

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

		N[i][0] = NX2;
		N[i][1] = NY2;
		N[i][2] = NZ2;

	}



}





void Draw_2map(int _NX, int no, int np, int ntx){

	int NX = _NX, nx1 = NX-1, idt, idc, idn, idv;
glEnable(GL_TEXTURE_2D);
	//gl_UseProgram (np);

	//glBegin( GL_QUAD_STRIP );

	int idisp = no;

			
		for(int ifdisp = 0;ifdisp < NF[idisp];/*ifdisp++*/){

			
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D,im[O[idisp][ifdisp][0][4]]);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			
			//glBindSampler(im[O[idisp][ifdisp][0][4]], 1);

			//if(np == programT2){
				GLint myt = gl_GetUniformLocation(np, "myTexture");
				if(myt != -1){
				gl_Uniform1i(myt, 0);
				}

				glActiveTexture(GL_TEXTURE1);
				GLint nmap = gl_GetUniformLocation(np, "nmap");
				if(nmap != -1){
				gl_Uniform1i(nmap, 1);
				}
				//else perror("nmap");
				glBindTexture(GL_TEXTURE_2D, ntx);
				
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


				
			//}

			

			glBegin( GL_QUAD_STRIP );
			
			for(int nx = 0;nx < NX;nx++){
								
				for(int ipdisp = 0;ipdisp < 2;ipdisp++){
					
					idv = O[idisp][ifdisp][ipdisp][0]; idn=O[idisp][ifdisp][ipdisp][1]; idc = O[idisp][ifdisp][ipdisp][2]; idt=O[idisp][ifdisp][ipdisp][3];
					glTexCoord2f(tex[idt][0], tex[idt][1]);
					glColor4f(C[idc][0],C[idc][1], C[idc][2], 0.5f);
					glNormal3f(N[idn][0], N[idn][1], N[idn][2]);
					glVertex3f(P[idv][0] +X, P[idv][1]+Y, P[idv][2]+Z );
					//printf("x : %f, y : %f, z : %f\n", P[idv][0] +X, P[idv][1]+Y, P[idv][2]+Z);
				}

				
				if(nx == nx1){

					for(int ipdisp = 3;ipdisp >= 2 ;ipdisp--){

						idv = O[idisp][ifdisp][ipdisp][0]; idn=O[idisp][ifdisp][ipdisp][1]; idc = O[idisp][ifdisp][ipdisp][2]; idt=O[idisp][ifdisp][ipdisp][3];
						glTexCoord2f(tex[idt][0], tex[idt][1]);
						glColor4f(C[idc][0],C[idc][1], C[idc][2], 0.5f);
						glNormal3f(N[idn][0], N[idn][1], N[idn][2]);
						glVertex3f(P[idv][0]+X , P[idv][1]+Y, P[idv][2]+Z );

						/*glTexCoord2f(tex[O[idisp][ifdisp][ipdisp][3]][0], tex[O[idisp][ifdisp][ipdisp][3]][1]);
						glColor3f(C[O[idisp][ifdisp][ipdisp][2]][0],C[O[idisp][ifdisp][ipdisp][2]][1], C[O[idisp][ifdisp][ipdisp][2]][2]);
						glNormal3f(N[O[idisp][ifdisp][ipdisp][1]][0], N[O[idisp][ifdisp][ipdisp][1]][1], N[O[idisp][ifdisp][ipdisp][1]][2]);
						glVertex3f(P[O[idisp][ifdisp][ipdisp][0]][0] + X, P[O[idisp][ifdisp][ipdisp][0]][1] + Y, P[O[idisp][ifdisp][ipdisp][0]][2] + Z);*/

					}

				}
				

				ifdisp = ifdisp + 1;

			}

			glEnd();
			glFlush();

		
		}

	

	

}


void Draw_2mapN(int _NX, int no, int np, int ntx, int nntx){

	int NX = _NX, nx1 = NX-1, idt, idc, idn, idv;
glEnable(GL_TEXTURE_2D);
	//gl_UseProgram (np);

	//glBegin( GL_QUAD_STRIP );

	int idisp = no;


	

			
		for(int ifdisp = 0;ifdisp < NF[idisp];/*ifdisp++*/){

			
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D,im[O[idisp][ifdisp][0][4]]);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			
			//glBindSampler(im[O[idisp][ifdisp][0][4]], 1);

			//if(np == programT2){
				GLint myt = gl_GetUniformLocation(np, "myTexture");
				if(myt != -1){
				gl_Uniform1i(myt, 0);
				}

				glActiveTexture(GL_TEXTURE1);
				GLint nmap = gl_GetUniformLocation(np, "nmap");
				if(nmap != -1){
				gl_Uniform1i(nmap, 1);
				}
				//else perror("nmap");
				glBindTexture(GL_TEXTURE_2D, ntx);
				
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


				//if(np == shader_def.program){
					glActiveTexture(GL_TEXTURE2);
					GLint noise = gl_GetUniformLocation(np, "noise");
					if(noise != -1){
					gl_Uniform1i(noise, 2);
					}

					glBindTexture(GL_TEXTURE_2D, nntx);
				
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				//}

			//}

			

			glBegin( GL_QUAD_STRIP );
			
			for(int nx = 0;nx < NX;nx++){
								
				for(int ipdisp = 0;ipdisp < 2;ipdisp++){
					
					idv = O[idisp][ifdisp][ipdisp][0]; idn=O[idisp][ifdisp][ipdisp][1]; idc = O[idisp][ifdisp][ipdisp][2]; idt=O[idisp][ifdisp][ipdisp][3];
					glTexCoord2f(tex[idt][0], tex[idt][1]);
					glColor4f(C[idc][0],C[idc][1], C[idc][2], 0.5f);
					glNormal3f(N[idn][0], N[idn][1], N[idn][2]);
					glVertex3f(P[idv][0] +X, P[idv][1]+Y, P[idv][2]+Z );
					//printf("x : %f, y : %f, z : %f\n", P[idv][0] +X, P[idv][1]+Y, P[idv][2]+Z);
				}

				
				if(nx == nx1){

					for(int ipdisp = 3;ipdisp >= 2 ;ipdisp--){

						idv = O[idisp][ifdisp][ipdisp][0]; idn=O[idisp][ifdisp][ipdisp][1]; idc = O[idisp][ifdisp][ipdisp][2]; idt=O[idisp][ifdisp][ipdisp][3];
						glTexCoord2f(tex[idt][0], tex[idt][1]);
						glColor4f(C[idc][0],C[idc][1], C[idc][2], 0.5f);
						glNormal3f(N[idn][0], N[idn][1], N[idn][2]);
						glVertex3f(P[idv][0]+X , P[idv][1]+Y, P[idv][2]+Z );

						/*glTexCoord2f(tex[O[idisp][ifdisp][ipdisp][3]][0], tex[O[idisp][ifdisp][ipdisp][3]][1]);
						glColor3f(C[O[idisp][ifdisp][ipdisp][2]][0],C[O[idisp][ifdisp][ipdisp][2]][1], C[O[idisp][ifdisp][ipdisp][2]][2]);
						glNormal3f(N[O[idisp][ifdisp][ipdisp][1]][0], N[O[idisp][ifdisp][ipdisp][1]][1], N[O[idisp][ifdisp][ipdisp][1]][2]);
						glVertex3f(P[O[idisp][ifdisp][ipdisp][0]][0] + X, P[O[idisp][ifdisp][ipdisp][0]][1] + Y, P[O[idisp][ifdisp][ipdisp][0]][2] + Z);*/

					}

				}
				

				ifdisp = ifdisp + 1;

			}

			glEnd();
			glFlush();

		
		}

	

	

}


