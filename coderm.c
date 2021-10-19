/*for(int idisp = 0;idisp < Iobj;idisp++){
for(int ifdisp = 0;ifdisp < NF[idisp];ifdisp++){

glEnable(GL_TEXTURE_2D);
gl_UseProgram (programT);
glBindTexture(GL_TEXTURE_2D,im[O[idisp][ifdisp][0][4]]);

glBegin( GL_QUADS );

for(int ipdisp = 0;ipdisp < 4;ipdisp++){


glTexCoord2f(tex[O[idisp][ifdisp][ipdisp][3]][0], tex[O[idisp][ifdisp][ipdisp][3]][1]);
glColor3f(C[O[idisp][ifdisp][ipdisp][2]][0],C[O[idisp][ifdisp][ipdisp][2]][1], C[O[idisp][ifdisp][ipdisp][2]][2]);
glNormal3f(N[O[idisp][ifdisp][ipdisp][1]][0], N[O[idisp][ifdisp][ipdisp][1]][1], N[O[idisp][ifdisp][ipdisp][1]][2]);
glVertex3f(P[O[idisp][ifdisp][ipdisp][0]][0] + X, P[O[idisp][ifdisp][ipdisp][0]][1] + Y, P[O[idisp][ifdisp][ipdisp][0]][2] + Z);

}
glEnd();
glFlush();



}}

*/


int NX = 50, nx1 = NX-1, idt, idc, idn, idv;
glEnable(GL_TEXTURE_2D);
	gl_UseProgram (programT);

	//glBegin( GL_QUAD_STRIP );

	/*for(*/int idisp = 0;/*idisp < Iobj;idisp++){*/

		
		for(int ifdisp = 0;ifdisp < NF[idisp];/*ifdisp++*/){
			glBindTexture(GL_TEXTURE_2D,im[O[idisp][ifdisp][0][4]]);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glBegin( GL_QUAD_STRIP );
			
			for(int nx = 0;nx < NX;nx++){
								
				for(int ipdisp = 0;ipdisp < 2;ipdisp++){
					
					idv = O[idisp][ifdisp][ipdisp][0]; idn=O[idisp][ifdisp][ipdisp][1]; idc = O[idisp][ifdisp][ipdisp][2]; idt=O[idisp][ifdisp][ipdisp][3];
					glTexCoord2f(tex[idt][0], tex[idt][1]);
					glColor4f(C[idc][0],C[idc][1], C[idc][2], 1.0f);
					glNormal3f(N[idn][0], N[idn][1], N[idn][2]);
					glVertex3f(P[idv][0] + X, P[idv][1] + Y, P[idv][2] + Z);

				}

				
				if(nx == nx1){

					for(int ipdisp = 3;ipdisp >= 2 ;ipdisp--){

						idv = O[idisp][ifdisp][ipdisp][0]; idn=O[idisp][ifdisp][ipdisp][1]; idc = O[idisp][ifdisp][ipdisp][2]; idt=O[idisp][ifdisp][ipdisp][3];
						glTexCoord2f(tex[idt][0], tex[idt][1]);
						glColor4f(C[idc][0],C[idc][1], C[idc][2], 1.0f);
						glNormal3f(N[idn][0], N[idn][1], N[idn][2]);
						glVertex3f(P[idv][0] + X, P[idv][1] + Y, P[idv][2] + Z);

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

	//}

	

//Draw_map(30, 30, X, Y, Z);

