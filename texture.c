struct _Texture{

	GLint tex[100];
	int max_T;

}__Texture;

typedef struct _Texture Texture;

static void Init_Texture(Texture *t){

	t->max_T = 0;
}

static GLint Load_Texture(Texture *t, char *img){

	
	t->tex[t->max_T] = SOIL_load_OGL_texture
		(
			img,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
		
	/* check for an error during the load process */
	if( 0 == t->tex[t->max_T] )
	{
		t->tex[t->max_T] = -1;
		printf( "MAP SOIL loading error: '%s' %s\n", SOIL_last_result(), img );
	
	}
	else
	{
		GLint tx = t->tex[t->max_T];
		t->max_T = t->max_T + 1;
		printf("loading tex : %s - %d\n", img, tx);
		return tx;
	}

	


}
