



int readline(char *b, int off, int end_off, char *sb){

	int vi = 0, i;
	for(i = off;i < end_off;i=i+1){

		if(b[i] == 0x0A){
			break;
		}
		else
		{
			sb[vi] = b[i];
			vi = vi + 1;
			
		}

	}
	//printf("i = %d, off : %d, end_off : %d\n", i, off, end_off);

	if(i == end_off) 
		return -1;
	else
		return vi+1;	


}


void buildobj(char *filename){

	
	int fd = syscall(__NR_open, filename, O_RDONLY);  
	if (fd == -1)
		perror("open");

	off_t sz = syscall(__NR_lseek, fd, 0, 2);
	if (sz == -1)
		perror("lseek");

	off_t rp = syscall(__NR_lseek, fd, 0, 0);
	if (rp == -1)
		perror("lseek 2 ");

	int NIpo = 0;
	char p = 'u';
	int start = 1;
	NF[Iobj] = 0;

	int rpf = 0, off_rpf = 0;
	int ib = 0;
	int rnl = 1;
	int rsb = 0;
	int off = 0;
	char buffer[100], bf[100];
	int bsz = 100;
	if(bsz > sz)
		bsz = sz;

	while(off < sz){

		if(rpf == 1){
			off_t rp = syscall(__NR_lseek, fd, off_rpf, 0);
			if (rpf == -1)
				perror("lseek 3 ");
			rpf = 0;
			
		}
				
		rsb = syscall(__NR_read, fd, buffer, bsz);
		if (rsb == -1)
			perror("read");
		//write(1, buffer, bsz); 
		
		ib = 0;
		while(ib < rsb){

			//printf("readline\n");
			int rl = readline(buffer, ib, rsb, bf);
			//printf("rl = %d\n", rl);
			if(rl == -1){
				rpf = 1;
				off_rpf = off + ib;
				ib = rsb;
				//printf("repos comm\n");
				
			}
			else
			{		
				//write(1, bf, rl-1);printf("\n");


				if((bf[0] == 'v')&&(bf[1] == ' ')){
					float v1, v2, v3;
													
					sscanf(bf,"v %f %f %f", &v1, &v2, &v3);
					//printf("V = x:%f, y:%f, z:%f\n", v1, v2, v3);

					if(start == 1){
						NIpo = Ipo;
						I[Ind]=Ipo;
						//printf("Ipo : %d\n", Ipo);
						start = 0;
					}

					P[Ipo][0] = v1;
					P[Ipo][1] = v2;
					P[Ipo][2] = v3;
					Ipo = Ipo + 1;

					p = 'v';
								

				}
				else if((bf[0] == 'v')&&(bf[1] == 'n')){
					float v1, v2, v3;
													
					sscanf(bf,"vn %f %f %f", &v1, &v2, &v3);
					//printf("V = x:%f, y:%f, z:%f\n", v1, v2, v3);
					
					N[NIpo][0] = v1;
					N[NIpo][1] = v2;
					N[NIpo][2] = v3;
					NIpo = NIpo + 1;

					p = 'v';
								

				}
				else if((bf[0] == 'f')&&(bf[1] == ' ')){
					int f, f1, f2, f3, i1, i2, i3, i4, c1, c2, c3, c4;
								
					//ind face col					
					sscanf(bf,"f %d//%d//%d %d//%d//%d %d//%d//%d %d//%d//%d ", &i1, &f, &c1, &i2, &f1, &c2 , &i3, &f2, &c3, &i4, &f3, &c4);
					//printf("f : %d, i1 : %d, i2 : %d, i3 : %d, i4 : %d, c1 : %d, c2 : %d, c3 : %d, c4 : %d\n", f, i1, i2, i3, i4, c1, c2, c3, c4);

					O[Iobj][f][0][0] = I[Ind]+i1;
					O[Iobj][f][0][1] = I[Ind]+i1;
					O[Iobj][f][0][2] = c1;

					O[Iobj][f][1][0] = I[Ind]+i2;
					O[Iobj][f][1][1] = I[Ind]+i2;
					O[Iobj][f][1][2] = c2;

					O[Iobj][f][2][0] = I[Ind]+i3;
					O[Iobj][f][2][1] = I[Ind]+i3;
					O[Iobj][f][2][2] = c3;

					O[Iobj][f][3][0] = I[Ind]+i4;
					O[Iobj][f][3][1] = I[Ind]+i4;
					O[Iobj][f][3][2] = c4;
					
					NF[Iobj] = NF[Iobj] + 1;

					p = 'f';
								

				}
				else
				{
					if(p == 'f'){
						NIpo = 0;
						Iobj = Iobj + 1;
						NF[Iobj] = 0;
						Ind = Ind + 1;
						start = 1;

					}

				}



				ib = ib + rl;
			}


			


		}
	
		//printf("offset\n");

		if(rpf == 0)
			off = off + rsb;
		else
			off = off_rpf;
		

	}
	


}



void buildtxobj(char *filename){

	
	int fd = syscall(__NR_open, filename, O_RDONLY);  
	if (fd == -1)
		perror("open");

	off_t sz = syscall(__NR_lseek, fd, 0, 2);
	if (sz == -1)
		perror("lseek");

	off_t rp = syscall(__NR_lseek, fd, 0, 0);
	if (rp == -1)
		perror("lseek 2 ");

	int NIpo = 0;
	char p = 'u';
	int PItx = 0, PIm = 0;Itx = 4;
	NF[Iobj] = 0;
	int start = 1;

	int rpf = 0, off_rpf = 0;
	int ib = 0;
	int rnl = 1;
	int rsb = 0;
	int off = 0;
	char buffer[100], bf[100];
	int bsz = 100;
	if(bsz > sz)
		bsz = sz;

	while(off < sz){

		if(rpf == 1){
			off_t rp = syscall(__NR_lseek, fd, off_rpf, 0);
			if (rpf == -1)
				perror("lseek 3 ");
			rpf = 0;
			
		}
				
		rsb = syscall(__NR_read, fd, buffer, bsz);
		if (rsb == -1)
			perror("read");
		//write(1, buffer, bsz); 
		
		ib = 0;
		while(ib < rsb){
			memset(bf, 0, 100);
			//printf("readline\n");
			int rl = readline(buffer, ib, rsb, bf);
			//printf("rl = %d\n", rl);
			if(rl == -1){
				rpf = 1;
				off_rpf = off + ib;
				ib = rsb;
				//printf("repos comm\n");
				
			}
			else
			{		
				//write(1, bf, rl-1);printf("\n");


				if((bf[0] == 'v')&&(bf[1] == ' ')){
					float v1, v2, v3;
													
					sscanf(bf,"v %f %f %f", &v1, &v2, &v3);
					//printf("V = x:%f, y:%f, z:%f\n", v1, v2, v3);

					if(start == 1){
						NIpo = Ipo;
						I[Ind]=Ipo;
						start = 0;
						//printf("Ipo : %d\n", Ipo);
					}

					P[Ipo][0] = v1;
					P[Ipo][1] = v2;
					P[Ipo][2] = v3;
					Ipo = Ipo + 1;

					p = 'v';
								

				}
				else if((bf[0] == 'v')&&(bf[1] == 'n')){
					float v1, v2, v3;
													
					sscanf(bf,"vn %f %f %f", &v1, &v2, &v3);
					//printf("V = x:%f, y:%f, z:%f\n", v1, v2, v3);
					
					N[NIpo][0] = v1;
					N[NIpo][1] = v2;
					N[NIpo][2] = v3;
					NIpo = NIpo + 1;

					p = 'v';
								

				}
				else if((bf[0] == 'v')&&(bf[1] == 't')){
					int v1, v2, v3;
													
					sscanf(bf,"vt %d %d", &v1, &v2);
					//printf("V = x:%f, y:%f, z:%f\n", v1, v2, v3);
					if(PItx == 0){
						PItx = Itx;
					}
					
					tex[Itx][0] = v1;
					tex[Itx][1] = v2;
					Itx = Itx + 1;

					p = 't';
								

				}
				else if((bf[0] == 'i')&&(bf[1] == 'm')){
					char pim[30];
					
					sscanf(bf,"im %s\n", pim);
					//printf("im : %s\n", pim);

					if(PIm == 0){
						PIm = Iim;
					}

					
					GLuint tx = SOIL_load_OGL_texture
						(
							pim,
							SOIL_LOAD_AUTO,
							SOIL_CREATE_NEW_ID,
							SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y /*| SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT*/
						);
						
					/* check for an error during the load process */
					if( 0 == tx )
					{
						printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
					}

					im[Iim] = tx;


					Iim = Iim + 1;

					p = 'i';


				}
				else if((bf[0] == 'f')&&(bf[1] == ' ')){
					int f, f1, f2, f3, i1, i2, i3, i4, c1, c2, c3, c4, t1, t2, t3, t4, i;
								
					//ind face col					
					sscanf(bf,"f %d//%d//%d//%d %d//%d//%d//%d %d//%d//%d//%d %d//%d//%d//%d %d", &i1, &f, &c1, &t1, &i2, &f1, &c2, &t2 , &i3, &f2, &c3, &t3, &i4, &f3, &c4, &t4, &i);
					//printf("f : %d, i1 : %d, i2 : %d, i3 : %d, i4 : %d, c1 : %d, c2 : %d, c3 : %d, c4 : %d\n", f, i1, i2, i3, i4, c1, c2, c3, c4);

					O[Iobj][f][0][0] = I[Ind]+i1;
					O[Iobj][f][0][1] = I[Ind]+i1;
					O[Iobj][f][0][2] = c1;
					O[Iobj][f][0][3] = PItx+t1;
					O[Iobj][f][0][4] = PIm+i;

					O[Iobj][f][1][0] = I[Ind]+i2;
					O[Iobj][f][1][1] = I[Ind]+i2;
					O[Iobj][f][1][2] = c2;
					O[Iobj][f][1][3] = PItx+t2;
					O[Iobj][f][1][4] = PIm+i;

					O[Iobj][f][2][0] = I[Ind]+i3;
					O[Iobj][f][2][1] = I[Ind]+i3;
					O[Iobj][f][2][2] = c3;
					O[Iobj][f][2][3] = PItx+t3;
					O[Iobj][f][2][4] = PIm+i;

					O[Iobj][f][3][0] = I[Ind]+i4;
					O[Iobj][f][3][1] = I[Ind]+i4;
					O[Iobj][f][3][2] = c4;
					O[Iobj][f][3][3] = PItx+t4;
					O[Iobj][f][3][4] = PIm+i;

					NF[Iobj] = NF[Iobj] + 1;

					p = 'f';
								

				}
				else
				{
					if(p == 'f'){
						NIpo = 0;
						//NF[Iobj] = 6;
						Iobj = Iobj + 1;
						NF[Iobj] = 0;		
						Ind = Ind + 1;
						PIm = 0;
						PItx = 0;
						start = 0;

					}

				}



				ib = ib + rl;
			}


			


		}
	
		//printf("offset\n");

		if(rpf == 0)
			off = off + rsb;
		else
			off = off_rpf;
		

	}
	


}
