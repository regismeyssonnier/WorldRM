static struct _Couteau{

	Stripe stripe[20];
	int max_S;
	int nIobj;
	int onHit;
	float angleHit;
	float angleHitMax;
	int down;
	float posX;
	int img;
	int img2;


}__Couteau;

typedef struct _Couteau Couteau;


void Init_Couteau(Couteau *c, int img, int img2){

	c->nIobj = Iobj;
	c->max_S = 0;
	c->onHit = 0;
	c->angleHit = 0.0f;
	c->angleHitMax = 50.0f;
	c->down = 1;
	c->img = img;
	c->img2 = img2;
}

void Create_Couteau(Couteau *c){

	
	Init_Obj();
	Straw(&c->stripe[0], 10.0f, 1, c->img, 5.0f);
	Straw(&c->stripe[1], 10.0f, 0, c->img, 5.0f);
	Straw(&c->stripe[2], 3.0f, 1, c->img2, 5.0f);
	Straw(&c->stripe[3], 3.0f, 0, c->img2, 5.0f);
	//Init_Stripe(&c->stripe[0]);
	//Create_Face(&l, &c->stripe[0]);
	c->max_S = 4;

	//printf("

	int pmin = c->stripe[0].Ipomin;
	int pmax = c->stripe[1].Ipomax;
	//int pmin2 = O[c->nIobj][c->stripe[1].Istart][0][0];
	//int pmax2 = O[c->nIobj][c->stripe[1].Iend-1][3][0];
	
	Scale(0.2f, 0.5f, 3.0f, pmin, pmax);
	//Scale(0.1f, 0.1f, 0.3f, pmin2, pmax2);
	//Scale(0.1f, 0.1f, 0.3f, pmin2, pmax2);
	//
	//
	translateO(pmin, pmax, 3.0f, -1.0f, 2.0f);
	//rotate_StripeZ(105.0f, pmin, pmax);
	//rotate_StripeX(75.0f, pmin, pmax);

	pmin = c->stripe[2].Ipomin;
	pmax = c->stripe[3].Ipomax;
	translateO(pmin, pmax, -2.0f, -3.5f, 0.0f);
	//Scale(0.3f, 0.2f, 0.2f, pmin, pmax);

	pmin = c->stripe[0].Ipomin;
	pmax = c->stripe[3].Ipomax;
	rotate_StripeZ(105.0f, pmin, pmax);
	rotate_StripeX(-75.0f, pmin, pmax);
	
	translateO(pmin, pmax, -2.0f, 0.0f, 15.0f);
	
	Iobj = Iobj + 1;

}


void Hit(Couteau *c, Direction *d, float t){

	int pmin, pmax;
	//if(d->direction == 1){
		pmin = c->stripe[0].Ipomin;
		pmax = c->stripe[3].Ipomax;
		c->onHit = 1;
		c->angleHit = 0.0f;
		c->down = 1;
		c->posX = 0.0f;
	//	rotate_StripeX(50.0f * t / 16666.66f, pmin, pmax);
	//}


}

void OnHit(Couteau *couteau, float t){
	if(couteau->onHit == 1)
	{
		if(couteau->down == 1){
			if(couteau->posX > -3.0f){
				translateO(couteau->stripe[0].Ipomin, couteau->stripe[3].Ipomax, 0.0f, -0.5f, 0.0f);
				couteau->posX = couteau->posX - 0.5f;
			}
						
			rotate_StripeX(couteau->angleHit /** t / 16666.66f*/, couteau->stripe[0].Ipomin, couteau->stripe[3].Ipomax);
			couteau->angleHit = couteau->angleHit - 5.0f;
			//printf("ca : %f\n", couteau->angleHit);
			if(couteau->angleHit <= -40.0f){
				couteau->down = 0;
				couteau->angleHit = 0.0f;
			}
		}
		else
		{
			if(couteau->posX < 0.0f){
				translateO(couteau->stripe[0].Ipomin, couteau->stripe[3].Ipomax, 0.0f, 0.5f, 0.0f);
				couteau->posX = couteau->posX + 0.5f;
			}

			rotate_StripeX(couteau->angleHit , couteau->stripe[0].Ipomin, couteau->stripe[3].Ipomax);
			couteau->angleHit = couteau->angleHit + 5.0f;
			//printf("uca : %f\n", couteau->angleHit);
			if(couteau->angleHit >= 40.0f){
				couteau->down = 1;
				couteau->onHit = 0;
				
			}
		}

	}

}

void Draw_Couteau(Couteau *c){

	int idt, idc, idn, idv, ifc;
glEnable(GL_TEXTURE_2D);
	

	gl_UseProgram (programT2);
		
	//gl_Uniform3f(fg, 0.0f, 3.0f, 0.0f);
	//glBegin( GL_QUAD_STRIP );

	int idisp = c->nIobj;

		GLint isw = gl_GetUniformLocation(programT2, "iswater");
			gl_Uniform3f(isw, 0.0f, 0.0f, 0.0f);

			GLint fg = gl_GetUniformLocation(programT2, "fgreen");
			gl_Uniform3f(fg, 0.0f, 3.0f, 0.0f);
			
		for(int s = 0;s < c->max_S;s++){
			gl_UseProgram (programT2);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, O[idisp][c->stripe[s].Istart][0][4]);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			

			if(s < 2){

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
				glBindTexture(GL_TEXTURE_2D, 9);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


			}
			else
			{
				/*gl_UseProgram (programT);
				GLint fg = gl_GetUniformLocation(programT, "fgreen");
				if(s == 2){
				gl_Uniform3f(fg, 0.0f, 3.0f, 0.0f);

				}
				else if(s == 3){
					gl_Uniform3f(fg, 0.0f, 3.0f, 0.0f);

				}*/
				
				gl_Uniform3f(isw, 0.0f, 0.0f, 0.0f);
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
				glBindTexture(GL_TEXTURE_2D, 10);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			}

			//gl_Uniform3f(fg, 0.0f, 1.0f, 0.0f);
			/*if(s == 0){
				gl_Uniform3f(fg, 0.0f, 3.0f, 0.0f);
			}
			else if(s == 1){
				gl_Uniform3f(fg, 0.0f, 3.0f, 0.0f);
			}
			else if(s == 2){
				gl_Uniform3f(fg, 0.0f, 3.0f, 0.0f);

			}
			else if(s == 3){
				gl_Uniform3f(fg, 0.0f, 3.0f, 0.0f);

			}*/

			glBegin( GL_QUAD_STRIP );
			
			for(int nx = c->stripe[s].Istart;nx < c->stripe[s].Iend;nx++){

				
								
				for(int ipdisp = 0;ipdisp < 2;ipdisp++){
					
					idv = O[idisp][nx][ipdisp][0]; idn=O[idisp][nx][ipdisp][1];
					idc = O[idisp][nx][ipdisp][2]; idt=O[idisp][nx][ipdisp][3];

					glTexCoord2f(tex[idt][0], tex[idt][1]);
					//glColor4f(C[idc][0],C[idc][1], C[idc][2], 0.5f);
					glNormal3f(N[idn][0], N[idn][1], N[idn][2]);
					glVertex3f(P[idv][0] , P[idv][1], P[idv][2]);
					//printf("x : %f, y : %f, z : %f\n", P[idv][0] +X, P[idv][1]+Y, P[idv][2]+Z);
				}

				
				if(nx == (c->stripe[s].Iend-1)){

					for(int ipdisp = 3;ipdisp >= 2 ;ipdisp--){

						idv = O[idisp][nx][ipdisp][0]; idn=O[idisp][nx][ipdisp][1];
						idc = O[idisp][nx][ipdisp][2]; idt=O[idisp][nx][ipdisp][3];

						glTexCoord2f(tex[idt][0], tex[idt][1]);
						//glColor4f(C[idc][0],C[idc][1], C[idc][2], 0.5f);
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


