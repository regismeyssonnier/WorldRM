static void rotate_WX(float a, int ipomin, int ipomax){

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

		

	float X1, Y1, Z1, X2, Y2, Z2;
	float NX1, NY1, NZ1, NX2, NY2, NZ2;

	for(int i = ipomin; i < ipomax;i++){
		
		X1 = P[i][0]+X; Y1 = P[i][1]+Y; Z1 = P[i][2]+Z;
		X2 = M[0] * X1;
		Y2 = M[4] * Y1 + M[5] * Z1;
		Z2 = M[7] * Y1 + M[8] * Z1;

		P[i][0] = X2-X;
		P[i][1] = Y2-Y;
		P[i][2] = Z2-Z;
		
		/*NX1 = N[i][0]; NY1 = N[i][1]; NZ1 = N[i][2];
		NX2 = M[0] * NX1;
		NX2 = M[4] * NY1 + M[5] * NZ1;
		NX2 = M[7] * NY1 + M[8] * NZ1;

		N[i][0] = NX2;
		N[i][1] = NY2;
		N[i][2] = NZ2;*/

	}



}



static void rotate_WY(float a, int ipomin, int ipomax){

	a = a * 3.141592654f / 180.0f;
			

	float M[9];
	M[0] = cos(a);
	//M[1] = 0.0f;
	M[2] = sinf(a);
	//M[3] = 0.0f;
	M[4] = 1.0f;
	//M[5] = 0.0f;
	M[6] = -sin(a);
	//M[7] = 0.0f;
	M[8] = cos(a);

		

	float X1, Y1, Z1, X2, Y2, Z2;
	float NX1, NY1, NZ1, NX2, NY2, NZ2;

	for(int i = ipomin; i < ipomax;i++){
		
		X1 = P[i][0]+X; Y1 = P[i][1]+Y; Z1 = P[i][2]+Z;
		X2 = M[0] * X1 + M[2] * Z1;
		Y2 = Y1;
		Z2 = M[6] * X1 + M[8] * Z1;

		P[i][0] = X2-X;
		P[i][1] = Y2-Y;
		P[i][2] = Z2-Z;
		
		/*NX1 = N[i][0]; NY1 = N[i][1]; NZ1 = N[i][2];
		NX2 = M[0] * NX1 + M[2] * NZ1;
		NY2 = M[4] * NY1;
		NZ2 = M[6] * NX1 + M[8] * NZ1;

		float sq = sqrt(NX2*NX2 + NY2*NY2 + NZ2*NZ2 ); 
				

		N[i][0] = NX2/sq;
		N[i][1] = NY2/sq;
		N[i][2] = NZ2/sq;*/

	}



}

static void rotate_WZ(float a, int ipomin, int ipomax){

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

	
	float X1, Y1, Z1, X2, Y2, Z2;
	float NX1, NY1, NZ1, NX2, NY2, NZ2;

	for(int i = ipomin; i < ipomax;i++){
		
		X1 = P[i][0]+X; Y1 = P[i][1]+Y; Z1 = P[i][2]+Z;
		X2 = M[0] * X1 + M[1] * Y1 + M[2] * Z1;
		Y2 = M[3] * X1 + M[4] * Y1 + M[5] * Z1;
		Z2 = M[6] * X1 + M[7] * Y1 + M[8] * Z1;

		P[i][0] = X2-X;
		P[i][1] = Y2-Y;
		P[i][2] = Z2-Z;
		
		/*NX1 = N[i][0]; NY1 = N[i][1]; NZ1 = N[i][2];
		NX2 = M[0] * NX1 + M[1] * NY1 + M[2] * NZ1;
		NY2 = M[3] * NX1 + M[4] * NY1 + M[5] * NZ1;
		NZ2 = M[6] * NX1 + M[7] * NY1 + M[8] * NZ1;

		N[i][0] = NX2;
		N[i][1] = NY2;
		N[i][2] = NZ2;*/

	}



}


static void rotate_A(float ax, float ay, float az, int ipomin, int ipomax){

	
	//rotate_WZ(az, ipomin, ipomax);
	//rotate_WX(ax, ipomin, ipomax);
	rotate_WY(ay, ipomin, ipomax);

}




