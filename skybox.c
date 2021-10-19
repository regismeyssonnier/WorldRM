typedef struct _Skybox{

	int img;
	int Ipomin;
	int Ipomax;
	float left;
	float right; 
	float bottom;
	float top;
	float near;
	float far;
	Shader shader;

}__Skybox;


typedef struct _Skybox Skybox;


static void Load_Skybox(Skybox *s){

	s->img = SOIL_load_OGL_cubemap
	(
		"../posx.png",
		"../negx.png",
		"../posy.png",
		"../negy.png",
		"../posz.png",
		"../negz.png",
		SOIL_LOAD_RGB,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
	);


	if( 0 == s->img )
	{
		s->img = -1;
		printf( "MAP SOIL loading error: '%s'\n", SOIL_last_result() );
	
	}
	else
	{
		printf("loading skybox : %d\n", s->img);
		
	}

}

static void Init_Skybox(Skybox *s, float left, float right, float bottom, float top, float near, float far){

	s->img = -1;
	Init_Shader_Def_Skybox(&s->shader);
	Load_Skybox(s);

	s->left = left;
	s->bottom = bottom;
	s->near = near;
	s->right = right;
	s->top = top;
	s->far = far;
	
	s->Ipomin = Ipo;

	//glTexCoord3i(-1, 1, -1);
	P[Ipo][0] = left;
	P[Ipo][1] = top;
	P[Ipo][2] = near;
	Ipo = Ipo + 1;

 	//glTexCoord3i(-1, 1, 1);
	//glVertex3f(left, top, far);
	P[Ipo][0] = left;
	P[Ipo][1] = top;
	P[Ipo][2] = far;
	Ipo = Ipo + 1;

 	//glTexCoord3i(1, 1, 1);
	//glVertex3f(right, top, far);
	P[Ipo][0] = right;
	P[Ipo][1] = top;
	P[Ipo][2] = far;
	Ipo = Ipo + 1;

 	//glTexCoord3i(1, 1, -1);	
	//glVertex3f(right, top, near);
 	P[Ipo][0] = right;
	P[Ipo][1] = top;
	P[Ipo][2] = near;
	Ipo = Ipo + 1;

	//glEnd();
	//glFlush();

	//Y-
	//glBegin(GL_QUADS);
	
	//glTexCoord3i(-1, -1, 1);	
	//glVertex3f(left, bottom, far);
	P[Ipo][0] = left;
	P[Ipo][1] = bottom;
	P[Ipo][2] = far;
	Ipo = Ipo + 1;

 	//glTexCoord3i(-1, -1, -1);	
	//glVertex3f(left, bottom, near);
	P[Ipo][0] = left;
	P[Ipo][1] = bottom;
	P[Ipo][2] = near;
	Ipo = Ipo + 1;

 	//glTexCoord3i(1, -1, -1);	
	//glVertex3f(right, bottom, near);
	P[Ipo][0] = right;
	P[Ipo][1] = bottom;
	P[Ipo][2] = near;
	Ipo = Ipo + 1;

 	//glTexCoord3i(1, -1, 1);
	//glVertex3f(right, bottom, far);
 	P[Ipo][0] = right;
	P[Ipo][1] = bottom;
	P[Ipo][2] = far;
	Ipo = Ipo + 1;

	//glEnd();
	//glFlush();

	//X+
	//glBegin(GL_QUADS);
	
	//glTexCoord3i(1, 1, 1);
	//glVertex3f(right, top, far);
	P[Ipo][0] = right;
	P[Ipo][1] = top;
	P[Ipo][2] = far;
	Ipo = Ipo + 1;

 	//glTexCoord3i(1, -1, 1);	
	//glVertex3f(right, bottom, far);
	P[Ipo][0] = right;
	P[Ipo][1] = bottom;
	P[Ipo][2] = far;
	Ipo = Ipo + 1;

 	//glTexCoord3i(1, -1, -1);
	//glVertex3f(right, bottom, near);
	P[Ipo][0] = right;
	P[Ipo][1] = bottom;
	P[Ipo][2] = near;
	Ipo = Ipo + 1;

 	//glTexCoord3i(1, 1, -1);
	//glVertex3f(right, top, near);
	P[Ipo][0] = right;
	P[Ipo][1] = top;
	P[Ipo][2] = near;
	Ipo = Ipo + 1;
 		

	//glEnd();
	//glFlush();


	//X-
	//glBegin(GL_QUADS);
	
	//glTexCoord3i(-1, 1, -1);
	//glVertex3f(left, top, near);
	P[Ipo][0] = left;
	P[Ipo][1] = top;
	P[Ipo][2] = near;
	Ipo = Ipo + 1;

 	//glTexCoord3i(-1, -1, -1);		
	//glVertex3f(left, bottom, near);
	P[Ipo][0] = left;
	P[Ipo][1] = bottom;
	P[Ipo][2] = near;
	Ipo = Ipo + 1;

 	//glTexCoord3i(-1, -1, 1);
	//glVertex3f(left, bottom, far);
	P[Ipo][0] = left;
	P[Ipo][1] = bottom;
	P[Ipo][2] = far;
	Ipo = Ipo + 1;

 	//glTexCoord3i(-1, 1, 1);
	//glVertex3f(left, top, far);
	P[Ipo][0] = left;
	P[Ipo][1] = top;
	P[Ipo][2] = far;
	Ipo = Ipo + 1;
 		

	//glEnd();
	//glFlush();


	//Z+
	//glBegin(GL_QUADS);
	
	//glTexCoord3i(-1, 1, 1);
	//glVertex3f(left, top, far);
	P[Ipo][0] = left;
	P[Ipo][1] = top;
	P[Ipo][2] = far;
	Ipo = Ipo + 1;

 	//glTexCoord3i(-1, -1, 1);
	//glVertex3f(left, bottom, far);
	P[Ipo][0] = left;
	P[Ipo][1] = bottom;
	P[Ipo][2] = far;
	Ipo = Ipo + 1;

 	//glTexCoord3i(1, -1, 1);
	//glVertex3f(right, bottom, far);
	P[Ipo][0] = right;
	P[Ipo][1] = bottom;
	P[Ipo][2] = far;
	Ipo = Ipo + 1;

 	//glTexCoord3i(1, 1, 1);
	//glVertex3f(right, top, far);
 	P[Ipo][0] = right;
	P[Ipo][1] = top;
	P[Ipo][2] = far;
	Ipo = Ipo + 1;

	//glEnd();
	//glFlush();

	
	//Z-
	//glBegin(GL_QUADS);
	
	///glTexCoord3i(1, 1, -1);
	//glVertex3f(right, top, near);
	P[Ipo][0] = right;
	P[Ipo][1] = top;
	P[Ipo][2] = near;
	Ipo = Ipo + 1;

 	//glTexCoord3i(1, -1, -1);
	//glVertex3f(right, bottom, near);
	P[Ipo][0] = right;
	P[Ipo][1] = bottom;
	P[Ipo][2] = near;
	Ipo = Ipo + 1;

 	//glTexCoord3i(-1, -1, -1);	
	//glVertex3f(left, bottom, near);
	P[Ipo][0] = left;
	P[Ipo][1] = bottom;
	P[Ipo][2] = near;
	Ipo = Ipo + 1;

 	//glTexCoord3i(-1, 1, -1);
	//glVertex3f(left, top, near);
	P[Ipo][0] = left;
	P[Ipo][1] = top;
	P[Ipo][2] = near;
	Ipo = Ipo + 1;

	s->Ipomax = Ipo;
 		

}


static void Rotate_Skybox_Y(Skybox *s, float a){

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

	for(int i = s->Ipomin; i < s->Ipomax;i++){
		
		X1 = P[i][0]; Y1 = P[i][1]; Z1 = P[i][2];
		X2 = M[0] * X1 + M[2] * Z1;
		Y2 = Y1;
		Z2 = M[6] * X1 + M[8] * Z1;

		P[i][0] = X2;
		P[i][1] = Y2;
		P[i][2] = Z2;
		
	}

/*
	float X1, Y1, Z1, X2, Y2, Z2;
	float NX1, NY1, NZ1, NX2, NY2, NZ2;

	//for(int i = ipomin; i < ipomax;i++){
		
		X1 = s->left; Y1 = s->bottom; Z1 = s->near;
		X2 = M[0] * X1 + M[2] * Z1;
		Y2 = Y1;
		Z2 = M[6] * X1 + M[8] * Z1;

		s->left = X2;
		s->bottom = Y2;
		s->near = Z2;

		X1 = s->right; Y1 = s->top; Z1 = s->far;
		X2 = M[0] * X1 + M[2] * Z1;
		Y2 = Y1;
		Z2 = M[6] * X1 + M[8] * Z1;

		s->right = X2;
		s->top = Y2;
		s->far = Z2;
		
		
	//}
*/


}


static void Draw_Skybox(Skybox *s){

	glEnable(GL_TEXTURE_CUBE_MAP);
	glDepthMask(GL_FALSE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, s->img);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	gl_UseProgram(s->shader.program);

	

	int i = s->Ipomin;
	
	//Y+
	glBegin(GL_QUADS);
	
	glTexCoord3i(-1, 1, -1);
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 	glTexCoord3i(-1, 1, 1);
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 	glTexCoord3i(1, 1, 1);
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 	glTexCoord3i(1, 1, -1);	
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 	

	glEnd();
	glFlush();

	

	//Y-
	glBegin(GL_QUADS);
	
	glTexCoord3i(-1, -1, 1);	
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 	glTexCoord3i(-1, -1, -1);	
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 	glTexCoord3i(1, -1, -1);	
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 	glTexCoord3i(1, -1, 1);
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 		

	glEnd();
	glFlush();//*/i=i+4;

	//X+
	glBegin(GL_QUADS);
	
	glTexCoord3i(1, 1, 1);
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 	glTexCoord3i(1, -1, 1);	
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 	glTexCoord3i(1, -1, -1);
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 	glTexCoord3i(1, 1, -1);
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 		

	glEnd();
	glFlush();


	//X-
	glBegin(GL_QUADS);
	
	glTexCoord3i(-1, 1, -1);
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 	glTexCoord3i(-1, -1, -1);		
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 	glTexCoord3i(-1, -1, 1);
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 	glTexCoord3i(-1, 1, 1);
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 		

	glEnd();
	glFlush();


	//Z+
	glBegin(GL_QUADS);
	
	glTexCoord3i(-1, 1, 1);
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 	glTexCoord3i(-1, -1, 1);
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 	glTexCoord3i(1, -1, 1);
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 	glTexCoord3i(1, 1, 1);
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 		

	glEnd();
	glFlush();

	
	//Z-
	glBegin(GL_QUADS);
	
	glTexCoord3i(1, 1, -1);
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 	glTexCoord3i(1, -1, -1);
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 	glTexCoord3i(-1, -1, -1);	
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 	glTexCoord3i(-1, 1, -1);
	glVertex3f(P[i][0], P[i][1], P[i][2]);i=i+1;
 		

	glEnd();
	glFlush();

	glDisable(GL_TEXTURE_CUBE_MAP);
	glDepthMask(GL_TRUE);

}


/*//Y+
	glBegin(GL_QUADS);
	
	glTexCoord3i(-1, 1, -1);
	glVertex3f(left+X, top+Y, near+Z);
 	glTexCoord3i(-1, 1, 1);
	glVertex3f(left+X, top+Y, far+Z);
 	glTexCoord3i(1, 1, 1);
	glVertex3f(right+X, top+Y, far+Z);
 	glTexCoord3i(1, 1, -1);	
	glVertex3f(right+X, top+Y, near+Z);
 	

	glEnd();
	glFlush();

	//Y-
	glBegin(GL_QUADS);
	
	glTexCoord3i(-1, -1, 1);	
	glVertex3f(left+X, bottom+Y, far+Z);
 	glTexCoord3i(-1, -1, -1);	
	glVertex3f(left+X, bottom+Y, near+Z);
 	glTexCoord3i(1, -1, -1);	
	glVertex3f(right+X, bottom+Y, near+Z);
 	glTexCoord3i(1, -1, 1);
	glVertex3f(right+X, bottom+Y, far+Z);
 		

	glEnd();
	glFlush();

	//X+
	glBegin(GL_QUADS);
	
	glTexCoord3i(1, 1, 1);
	glVertex3f(right+X, top+Y, far+Z);
 	glTexCoord3i(1, -1, 1);	
	glVertex3f(right+X, bottom+Y, far+Z);
 	glTexCoord3i(1, -1, -1);
	glVertex3f(right+X, bottom+Y, near+Z);
 	glTexCoord3i(1, 1, -1);
	glVertex3f(right+X, top+Y, near+Z);
 		

	glEnd();
	glFlush();


	//X-
	glBegin(GL_QUADS);
	
	glTexCoord3i(-1, 1, -1);
	glVertex3f(left+X, top+Y, near+Z);
 	glTexCoord3i(-1, -1, -1);		
	glVertex3f(left+X, bottom+Y, near+Z);
 	glTexCoord3i(-1, -1, 1);
	glVertex3f(left+X, bottom+Y, far+Z);
 	glTexCoord3i(-1, 1, 1);
	glVertex3f(left+X, top+Y, far+Z);
 		

	glEnd();
	glFlush();


	//Z+
	glBegin(GL_QUADS);
	
	glTexCoord3i(-1, 1, 1);
	glVertex3f(left+X, top+Y, far+Z);
 	glTexCoord3i(-1, -1, 1);
	glVertex3f(left+X, bottom+Y, far+Z);
 	glTexCoord3i(1, -1, 1);
	glVertex3f(right+X, bottom+Y, far+Z);
 	glTexCoord3i(1, 1, 1);
	glVertex3f(right+X, top+Y, far+Z);
 		

	glEnd();
	glFlush();

	
	//Z-
	glBegin(GL_QUADS);
	
	glTexCoord3i(1, 1, -1);
	glVertex3f(right+X, top+Y, near+Z);
 	glTexCoord3i(1, -1, -1);
	glVertex3f(right+X, bottom+Y, near+Z);
 	glTexCoord3i(-1, -1, -1);	
	glVertex3f(left+X, bottom+Y, near+Z);
 	glTexCoord3i(-1, 1, -1);
	glVertex3f(left+X, top+Y, near+Z);
 		

	glEnd();
	glFlush();


*/


