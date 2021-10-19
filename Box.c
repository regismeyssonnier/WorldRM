struct _Box{

	float xmin;
	float ymin;
	float zmin;
	float xmax;
	float ymax;
	float zmax;
	float xmc;
	float ymc;
	float zmc;


}__Box;

typedef struct _Box Box;

static void Init_Box(Box *b){

	b->xmin = 100000.0f;
	b->ymin = 100000.0f;
	b->zmin = 100000.0f;
	b->xmax = -100000.0f;
	b->ymax = -100000.0f;
	b->zmax = -100000.0f;

}

static void Copy_Box(Box *b, Box *b2){

	b->xmin = b2->xmin;
	b->ymin = b2->ymin;
	b->zmin = b2->zmin;
	b->xmax = b2->xmax;
	b->ymax = b2->ymax;
	b->zmax = b2->zmax;

}



static void Calc_Box(Box *b, float x, float y, float z){

	if(x < b->xmin){
		b->xmin = x;
	}

	if(y < b->ymin){
		b->ymin = y;
	}

	if(z < b->zmin){
		b->zmin = z;
	}

	if(x > b->xmax){
		b->xmax = x;
	}

	if(y > b->ymax){
		b->ymax = y;
	}

	if(z > b->zmax){
		b->zmax = z;
	}

} 

static void Get_Box(Box *b, int ipomin, int ipomax){

	Init_Box(b);

	
	for(int i = ipomin; i < ipomax;i++){
		Calc_Box(b, P[i][0], P[i][1], P[i][2]);
	}

	
}


static void Create_Box(Box *b, float xmi, float xma, float ymi, float yma, float zmi, float zma){

	b->xmin = b->xmin + xmi;
	b->ymin = b->ymin + ymi;
	b->zmin = b->zmin + zmi;
	b->xmax = b->xmax + xma;
	b->ymax = b->ymax + yma;
	b->zmax = b->zmax + zma;

}

static void Display_Box(Box *b){

	printf("min : %f, %f, %f\n", b->xmin, b->ymin, b->zmin);
	printf("max : %f, %f, %f\n", b->xmax, b->ymax, b->zmax);

}


static void Get_Alpha_Vector(Box *b){

	float xmin = b->xmin + X, ymin = b->ymin + Y, zmin = b->zmin + Z, xmax = b->xmax + X, ymax = b->ymax + Y, zmax = b->zmax + Z;
	b->xmc = xmin+((xmax-xmin)/2.0f);
	b->ymc = ymin+((ymax-ymin)/2.0f);
	b->zmc = zmin+((zmax-zmin)/2.0f);


}


static void rotate_BY(Box *b, float a){

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

		

	float X1, Y1, Z1, X2, Y2, Z2;
	float NX1, NY1, NZ1, NX2, NY2, NZ2;

	//for(int i = ipomin; i < ipomax;i++){
		
		X1 = b->xmin+X; Y1 = b->ymin+Y; Z1 = b->zmin+Z;
		X2 = M[0] * X1 + M[1] * Y1 + M[2] * Z1;
		Y2 = M[3] * X1 + M[4] * Y1 + M[5] * Z1;
		Z2 = M[6] * X1 + M[7] * Y1 + M[8] * Z1;

		b->xmin = X2-X;
		b->ymin = Y2-Y;
		b->zmin = Z2-Z;

		X1 = b->xmax+X; Y1 = b->ymax+Y; Z1 = b->zmax+Z;
		X2 = M[0] * X1 + M[1] * Y1 + M[2] * Z1;
		Y2 = M[3] * X1 + M[4] * Y1 + M[5] * Z1;
		Z2 = M[6] * X1 + M[7] * Y1 + M[8] * Z1;

		b->xmax = X2-X;
		b->ymax = Y2-Y;
		b->zmax = Z2-Z;
		
		/*NX1 = N[i][0]; NY1 = N[i][1]; NZ1 = N[i][2];
		NX2 = M[0] * NX1 + M[1] * NY1 + M[2] * NZ1;
		NY2 = M[3] * NX1 + M[4] * NY1 + M[5] * NZ1;
		NZ2 = M[6] * NX1 + M[7] * NY1 + M[8] * NZ1;

		N[i][0] = NX2;
		N[i][1] = NY2;
		N[i][2] = NZ2;*/

	//}



}

