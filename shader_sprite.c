const GLchar *fragShaderSrcSprite[] = { 

	"varying vec3 N;",
	"varying vec3 v;",    
	"uniform sampler2D myTexture;",
	//"uniform sampler2D nmap;",
	"varying vec4 vTexCoord;",
	"uniform vec3 iswater;",
	"uniform vec3 fgreen;",
	//"uniform vec3 fgreen;",
	//"varying float vfgreen;",
	//"varying float vx;",
	//"uniform vec4 texb;",
	//"uniform float texb2;",
	//"varying float texbb;",

	"void main (void)",  
	"{",  
	"  vec3 L = normalize(gl_LightSource[0].position.xyz - v);",   
	//"   vec4 vn = texture2D(nmap, gl_TexCoord[0].xy);",
	"  vec3 E = normalize(-v); /* -v we are in Eye Coordinates, so EyePos is (0,0,0)*/",  
	"   vec3 R = normalize(-reflect(L,N));",  
	//"   vec3 Mt = vec3(0.9, 0.8, 0.2);",
	//"   R = R*Mt;",
	"   vec4 shin;",
	"   shin = vec4(1.0, 0.7, 0.0, 1.0);",
	"   /*calculate Ambient Term:*/",  
	"   vec4 Iamb = (gl_FrontLightProduct[0].ambient /*+ 0.01*shin*/);",
	//"   Iamb = vec4(1.0, 0.7, 0.0, 1.0);",
	"   clamp(Iamb, 0.0, 1.0);",
	//"   if(v.y < 0.1)Iamb = Iamb - (vec4(0.0, 0.6, 0.6, 1.0));",    
	"   /*calculate Diffuse Term:*/",  
	//"   vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(N,L), 0.0);",    
	"   vec4 Idiff = vec4(0.1, 0.1, 0.00, 1.0)* max(dot(N,L), 0.0);",
	"   clamp(Idiff, 0.0, 1.0);",
	"   /* calculate Specular Term:*/",
	
	"   vec4 Ispec = gl_FrontLightProduct[0].specular * pow(max(dot(R,E),0.0),gl_FrontMaterial.shininess);",
	//"   vec4 Ispec = vec4(1.00, 0.10, 0.05, 1.0)* pow(max(dot(R,E),0.0),gl_FrontMaterial.shininess);",
	"   clamp(Ispec, 0.0, 1.0);",
	//"   if(Ispec
	//"   if(fgreen.g == 0.0)fgreen.g = 3.0;",
	"   vec4 vt = texture2D(myTexture, gl_TexCoord[0].xy);vt.r = vt.r - vt.b;vt.g = vt.g - vt.b/fgreen.g;vt.b = vt.b - (vt.r-vt.g);",
	//"vec4 vt = texture2D(myTexture, gl_TexCoord[0].xy);", 
	//"   vec4 vt = texture2D(myTexture, gl_TexCoord[0].xy + (E.xy* (0.04*( vec2(vn.r-vn.g, vn.r-vn.g) )) )  );",
	//"   if(iswater.x == 1.0){vt.r = vt.r - vt.b;vt.g = vt.g - vt.b/fgreen.g;vt.b = vt.b - (vt.r-vt.g);}",
	/*"    vec3  norm = texture2D(myTexture, gl_TexCoord[0].xy).rgb * 2.0 - 1.0; ",
	"    vec3  halfVector = normalize(L + E); ",
	"    float  nxHalf = max(0.0,dot(norm, halfVector));   ", 
	"   Ispec = Ispec * pow(nxHalf, gl_FrontMaterial.shininess);   ",*/
	//"   if(texb.x == 0.0){",
	// "  /* write Total Color:*/",  
	"   	gl_FragColor = (gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec) + vt;",
	//"   }else{",
	//"	gl_FragColor = gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec;}",
   	"}"

};




static void Create_Shader_Sprite(Sprite *s){

	const GLsizei vertexShaderLSprite = sizeof(vertexShaderSource) / sizeof(ourGLchar*);
	GLuint vertexShSprite = compileShaderSource (GL_VERTEX_SHADER, vertexShaderLSprite, vertexShaderSource);

	const GLsizei fragShaderLSprite = sizeof(fragShaderSrcSprite) / sizeof(GLchar*);
	GLuint fragShaderSprite = compileShaderSource (GL_FRAGMENT_SHADER, fragShaderLSprite, fragShaderSrcSprite);

	checkError ("initShader - 1");

	createProgram (&s->shader, vertexShSprite, fragShaderSprite);



}
