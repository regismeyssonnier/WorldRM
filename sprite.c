struct _Sprite{

	int nIobj;
	int img;
	Stripe s;
	float time;	
	float tu;
	float tua;
	float tv;
	float tui;
	float tuif;
	float tvi;
	float nb_img;
	int anim;
	GLuint shader;

}__Sprite;


typedef struct _Sprite Sprite;
#include "shader_sprite.c"

static void Init_Sprite(Sprite *s, int im, int nb_im, int anim){

	s->img = im;
	s->nIobj = Iobj;
	s->time = 0;
	s->nb_img = nb_im;
	s->anim = anim;
}

static void Set_CoordTex_Sprite(Sprite *s){

	s->tui = 1.0f / s->nb_img;
	s->tuif = s->tui / ((float)(s->s.Iend - s->s.Istart)) ;
	s->tu = 0.0f;
	s->time = 0.0f;	 
	s->tv = 1.0f;
	s->tua = 0.0f;
	
	//printf("s->tui : %f, s->tuif : %f\n", s->tui, s->tuif);

}

static void Update_Sprite(Sprite *s, float t){

	s->time = s->time + t;
	if(s->time > 1000000.0f){
		s->tua = s->tua + s->tui;
		if(s->tua == 1.0f)
			s->tua = 0.0f;

		s->time = 0.0f;
	}

}

static void Create_Sprite(Sprite *s){

	Init_Obj();
	StrawS(&s->s, 10.0f, 0, s->img, 0.0f, 9.0f, 1.0f, 1.0f);

	int pmin = s->s.Ipomin;
	int pmax = s->s.Ipomax;
	
	Set_CoordTex_Sprite(s);
	Create_Shader_Sprite(s);

	Iobj = Iobj + 1;

}


static void Move_Sprite(Sprite *s, float x, float y, float z){

	int pmin = s->s.Ipomin;
	int pmax = s->s.Ipomax;

	
	float dx, dy, dz;

	dx =  x - P[pmin][0];
	dy =  y - P[pmin][1];
	dz =  z - P[pmin][2];

	for(int i = pmin;i < pmax;i++){
		P[i][0] = dx + P[i][0];
		P[i][1] = dy + P[i][1];
		P[i][2] = dz + P[i][2];
	} 

}


static void Draw_Sprite(Sprite *s){

	int idt, idc, idn, idv, ifc;
	glEnable(GL_TEXTURE_2D);
	
	gl_UseProgram (s->shader);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE/*_MINUS_SRC_ALPHA*/);

	//GLint isw = gl_GetUniformLocation(programT2, "iswater");
	//		gl_Uniform3f(isw, 0.0f, 0.0f, 0.0f);

			//GLint fg = gl_GetUniformLocation(programT, "fgreen");
			//gl_Uniform3f(fg, 0.0f, 1.0f, 0.0f);

	int idisp = s->nIobj;
	
	//for(int s = 0;s < g->max_S;s++){
			//gl_UseProgram (programT2);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, s->img);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			s->tu = s->tua;
			

			glBegin( GL_QUAD_STRIP );
			
			for(int nx = s->s.Istart;nx < s->s.Iend;nx++){

				
				s->tv = 1.0f;		
				for(int ipdisp = 0;ipdisp < 2;ipdisp++){
					
					idv = O[idisp][nx][ipdisp][0]; idn=O[idisp][nx][ipdisp][1];
					idc = O[idisp][nx][ipdisp][2]; idt=O[idisp][nx][ipdisp][3];

					if( s->anim == 1)
						glTexCoord2f(s->tu, s->tv);
					else
						glTexCoord2f(tex[idt][0], tex[idt][1]);

					//glColor4f(C[idc][0],C[idc][1], C[idc][2], 0.5f);
					glNormal3f(N[idn][0], N[idn][1], N[idn][2]);
					glVertex3f(P[idv][0]+X, P[idv][1]+Y, P[idv][2]+Z);
					//printf("x : %f, y : %f, z : %f\n", P[idv][0] +X, P[idv][1]+Y, P[idv][2]+Z);

					//printf("tu : %f, tv : %f\n", s->tu, s->tv);
					if(s->tv == 1.0f)
						s->tv = 0.0f;
					else
						s->tv = 1.0f;
				}

				s->tu = s->tu + s->tuif;
				

				
				if(nx == (s->s.Iend-1)){
					s->tv = 1.0f;
					for(int ipdisp = 3;ipdisp >= 2 ;ipdisp--){

						idv = O[idisp][nx][ipdisp][0]; idn=O[idisp][nx][ipdisp][1];
						idc = O[idisp][nx][ipdisp][2]; idt=O[idisp][nx][ipdisp][3];

						if( s->anim == 1)
							glTexCoord2f(s->tu, s->tv);
						else
							glTexCoord2f(tex[idt][0], tex[idt][1]);
						//glColor4f(C[idc][0],C[idc][1], C[idc][2], 0.5f);
						glNormal3f(N[idn][0], N[idn][1], N[idn][2]);
						glVertex3f(P[idv][0]+X , P[idv][1]+Y, P[idv][2]+Z);
						//printf("x : %f, y : %f, z : %f\n", P[idv][0] +X, P[idv][1]+Y, P[idv][2]+Z);

						//printf("tu : %f, tv : %f\n", s->tu, s->tv);
						if(s->tv == 1.0f)
							s->tv = 0.0f;
						else
							s->tv = 1.0f;
					}
					s->tu = s->tu + s->tuif;
				}
				

				
			}

			glEnd();
			glFlush();

		//glDisable(GL_BLEND);
		
		//}
	

}
