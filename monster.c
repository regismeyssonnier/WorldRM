struct _Monster{
	Stripe stripe[2];
	int max_S;
	int nIobj;
	int img;
	int img2;
	Box box;
	int shaderi;
	float touch;

}__Monster;

typedef struct _Monster Monster;

static void Init_Monster(Monster *m, int img , int img2, int sh){

	m->nIobj = Iobj;
	m->max_S = 0;
	m->img = img;
	m->img2 = img2;
	m->shaderi = sh;
	m->touch = 0.0f;
}


static void Create_Monster(Monster *m){

	Init_Obj();
	StrawB(&m->stripe[0], 5.0f, m->img, 2.0f);

	int pmin = m->stripe[0].Ipomin;
	int pmax = m->stripe[0].Ipomax;
	Scale(5.0f, 1.0f, 3.0f, pmin, pmax);
	rotate_StripeZ(-90.0f, pmin, pmax);
	rotate_StripeY(90.0f, pmin, pmax);
	translateO(pmin, pmax, 30.0f, 70.0f, 30.0f);

	m->max_S = m->max_S + 1;
	Iobj = Iobj + 1;

}

static void Is_Touch_Monster(Monster *m, Gun *g){

	GLint touch2 = gl_GetUniformLocation(m->shaderi, "touch");

	if((g->touch_B == 1)&&(m->touch <= 500000.0f)){
		gl_Uniform3f(touch2, 1.0f, 0.0f, 0.0f);
	}
	else
	{
		g->touch_B == -1;
		m->touch = 0.0f;
		gl_Uniform3f(touch2, 0.0f, 0.0f, 0.0f);
	}
	GLint ftimet2 = gl_GetUniformLocation(m->shaderi, "ftime");
	gl_Uniform3f(ftimet2, 0.0f, m->touch, 0.0f);
	/*if((g->touch_B == 1)&&(m->touch > 500000.0f)){
		m->touch = 0.0f;
		gl_Uniform3f(touch2, 0.0f, 0.0f, 0.0f);
	}*/

}

void Draw_Monster(Monster *m, float W, float H){

	int idt, idc, idn, idv, ifc;
glEnable(GL_TEXTURE_2D);
	

	gl_UseProgram (m->shaderi);
		
	GLint isw = gl_GetUniformLocation(m->shaderi, "iswater");
	gl_Uniform3f(isw, 0.0f, 0.0f, 0.0f);

	GLint fg = gl_GetUniformLocation(m->shaderi, "fgreen");
	gl_Uniform3f(fg, 0.0f, 3.0f, 0.0f);

	GLint ishg = gl_GetUniformLocation(m->shaderi, "isshin");
	gl_Uniform3f(ishg, 0.0f, 0.0f, 0.0f);

	

	int idisp = m->nIobj;

	
		GLint ures = gl_GetUniformLocation(m->shaderi, "u_res");
		gl_Uniform3f(ures, W, H, 0.0f);
		//GLint pos = gl_GetUniformLocation(programT2, "position");
		//gl_Uniform3f(pos, 5, 5, 0.0f);
			
		for(int s = 0;s < m->max_S;s++){
			//gl_UseProgram (shader_def.program);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m->img);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		
				GLint myt = gl_GetUniformLocation(m->shaderi, "myTexture");
				if(myt != -1){
				gl_Uniform1i(myt, 0);
				}

				glActiveTexture(GL_TEXTURE1);
				GLint nmap = gl_GetUniformLocation(m->shaderi, "nmap");
				if(nmap != -1){
				gl_Uniform1i(nmap, 1);
				}
				glActiveTexture(GL_TEXTURE1);
				
					glBindTexture(GL_TEXTURE_2D, m->img2);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


			

			glBegin( GL_QUAD_STRIP );
			
			for(int nx = m->stripe[s].Istart;nx < m->stripe[s].Iend;nx++){

				
								
				for(int ipdisp = 0;ipdisp < 2;ipdisp++){
					
					idv = O[idisp][nx][ipdisp][0]; idn=O[idisp][nx][ipdisp][1];
					idc = O[idisp][nx][ipdisp][2]; idt=O[idisp][nx][ipdisp][3];

					glTexCoord2f(tex[idt][0], tex[idt][1]);
					glColor4f(C[idc][0],C[idc][1], C[idc][2], 0.5f);
					glNormal3f(N[idn][0], N[idn][1], N[idn][2]);
					glVertex3f(P[idv][0]+X, P[idv][1]+Y, P[idv][2]+Z);
					
					//printf("x : %f, y : %f, z : %f\n", P[idv][0]+g->ammo[i].X , P[idv][1]+g->ammo[i].Y, P[idv][2]+g->ammo[i].Z);
				}

				
				if(nx == (m->stripe[s].Iend-1)){

					for(int ipdisp = 3;ipdisp >= 2 ;ipdisp--){

						idv = O[idisp][nx][ipdisp][0]; idn=O[idisp][nx][ipdisp][1];
						idc = O[idisp][nx][ipdisp][2]; idt=O[idisp][nx][ipdisp][3];

						glTexCoord2f(tex[idt][0], tex[idt][1]);
						glColor4f(C[idc][0],C[idc][1], C[idc][2], 0.5f);
						glNormal3f(N[idn][0], N[idn][1], N[idn][2]);
						glVertex3f(P[idv][0]+X, P[idv][1]+Y, P[idv][2]+Z);
						//printf("x : %f, y : %f, z : %f\n", P[idv][0]+g->ammo.X+X , P[idv][1]+g->ammo.Y+Y, P[idv][2]+g->ammo.Z+Z);
					
					}

				}
				

				
			}

			glEnd();
			glFlush();

		
		


	}


	

}


