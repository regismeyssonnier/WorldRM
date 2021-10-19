typedef struct _Shader{

	GLuint vsh;
	GLuint fsh;
	const ourGLchar **vsrc;
	const ourGLchar **fsrc;
	int szvsh;
	int szfsh;
	GLuint program;
	

}__Shader;

typedef struct _Shader Shader;


static void Init_Shader(Shader *s, const ourGLchar **vs, const ourGLchar **fs, int szv, int szf){

	s->vsrc = vs;
	s->fsrc = fs;
	s->szvsh = szv;
	s->szfsh = szf;

}


static void Create_Shader(Shader *s){

	
	//const GLsizei vertexShaderLSprite = sizeof(&s->vsrc[0]) / sizeof(ourGLchar*);
	//printf("vsh ;: %d - %p\n", s->szvsh, s->vsrc);
	if(s->szvsh != 0){
		s->vsh = compileShaderSource (GL_VERTEX_SHADER, s->szvsh, s->vsrc);
	}
	//printf("shad : %s\n", s->fsrc[2]);
	//const GLsizei fragShaderLSprite = sizeof(&s->fsrc[0]) / sizeof(ourGLchar*);
	//printf("fsh ;: %d\n", s->szfsh);
	s->fsh = compileShaderSource (GL_FRAGMENT_SHADER, s->szfsh, s->fsrc);

	checkError ("initShader - 1");

	if(s->szvsh != 0)
		createProgram (&s->program, s->vsh, s->fsh);
	else
		createProgram (&s->program, 0, s->fsh);

	//printf("program : %d\n", s->program);  

}
