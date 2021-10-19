 #define _GNU_SOURCE
#include <GL/freeglut.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <asm/unistd.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/io.h>
#include <sched.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>



#include "SOIL.h"
//#include "glmatrix.h"
#include "coderm.h"
#include "mobj.c"

static void rotate_y(float a, int no);
static void key(unsigned char key, int x, int y);

#ifdef _MSC_VER
/* DUMP MEMORY LEAKS */
#include <crtdbg.h>
#endif

/* report GL errors, if any, to stderr */
void checkError(const char *functionName)
{
    GLenum error;
    while (( error = glGetError() ) != GL_NO_ERROR) {
        fprintf (stderr, "GL error 0x%X detected in %s\n", error, functionName);
    }
}

/*
 * OpenGL 2+ shader mode needs some function and macro definitions, 
 * avoiding a dependency on additional libraries like GLEW or the
 * GL/glext.h header
 */
#ifndef GL_FRAGMENT_SHADER
#define GL_FRAGMENT_SHADER 0x8B30
#endif

#ifndef GL_VERTEX_SHADER
#define GL_VERTEX_SHADER 0x8B31
#endif

#ifndef GL_COMPILE_STATUS
#define GL_COMPILE_STATUS 0x8B81
#endif

#ifndef GL_LINK_STATUS
#define GL_LINK_STATUS 0x8B82
#endif

#ifndef GL_INFO_LOG_LENGTH
#define GL_INFO_LOG_LENGTH 0x8B84
#endif

typedef ptrdiff_t ourGLsizeiptr;
typedef char ourGLchar;

#ifndef APIENTRY
#define APIENTRY
#endif

#ifndef GL_VERSION_2_0
typedef GLuint (APIENTRY *PFNGLCREATESHADERPROC) (GLenum type);
typedef void (APIENTRY *PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const ourGLchar **string, const GLint *length);
typedef void (APIENTRY *PFNGLCOMPILESHADERPROC) (GLuint shader);
typedef GLuint (APIENTRY *PFNGLCREATEPROGRAMPROC) (void);
typedef void (APIENTRY *PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (APIENTRY *PFNGLLINKPROGRAMPROC) (GLuint program);
typedef void (APIENTRY *PFNGLUSEPROGRAMPROC) (GLuint program);
typedef void (APIENTRY *PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
typedef void (APIENTRY *PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, ourGLchar *infoLog);
typedef void (APIENTRY *PFNGLGETPROGRAMIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRY *PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei *length, ourGLchar *infoLog);
typedef GLint (APIENTRY *PFNGLGETATTRIBLOCATIONPROC) (GLuint program, const ourGLchar *name);
typedef GLint (APIENTRY *PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, const ourGLchar *name);
typedef void (APIENTRY *PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRY *PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRY *PFNGLUNIFORM3FPROC)(GLint location, GLfloat v0,	GLfloat v1, GLfloat v2);
typedef void (APIENTRY *PFNGLUNIFORM1IPROC)(GLint location, GLint v0);
#endif

PFNGLGENVERTEXARRAYSPROC gl_GenVertexArrays;
PFNGLBINDVERTEXARRAYPROC gl_BindVertexArray;
PFNGLGENBUFFERSPROC gl_GenBuffers;
PFNGLBINDBUFFERPROC gl_BindBuffer;
PFNGLBUFFERDATAPROC gl_BufferData;
PFNGLVERTEXATTRIBPOINTERPROC gl_VertexAttribPointer;
PFNGLENABLEVERTEXATTRIBARRAYPROC gl_EnableVertexAttribArray;

PFNGLCREATESHADERPROC gl_CreateShader;
PFNGLSHADERSOURCEPROC gl_ShaderSource;
PFNGLCOMPILESHADERPROC gl_CompileShader;
PFNGLCREATEPROGRAMPROC gl_CreateProgram;
PFNGLATTACHSHADERPROC gl_AttachShader;
PFNGLLINKPROGRAMPROC gl_LinkProgram;
PFNGLUSEPROGRAMPROC gl_UseProgram;
PFNGLGETSHADERIVPROC gl_GetShaderiv;
PFNGLGETSHADERINFOLOGPROC gl_GetShaderInfoLog;
PFNGLGETPROGRAMIVPROC gl_GetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC gl_GetProgramInfoLog;
PFNGLGETATTRIBLOCATIONPROC gl_GetAttribLocation;
PFNGLGETUNIFORMLOCATIONPROC gl_GetUniformLocation;
PFNGLUNIFORMMATRIX4FVPROC gl_UniformMatrix4fv;
PFNGLUNIFORMMATRIX3FVPROC gl_UniformMatrix3fv;
PFNGLUNIFORM3FPROC gl_Uniform3f;
PFNGLUNIFORM1IPROC gl_Uniform1i;

void initExtensionEntries(void)
{
    gl_GenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) glutGetProcAddress ("glGenVertexArrays");
   gl_BindVertexArray = (PFNGLBINDVERTEXARRAYPROC) glutGetProcAddress ("glBindVertexArray");
   if (!gl_GenVertexArrays || !gl_BindVertexArray)
   {
       fprintf (stderr, "glGenVertexArrays or glBindVertexArray not found");
       exit(1);
   }
   gl_GenBuffers = (PFNGLGENBUFFERSPROC) glutGetProcAddress ("glGenBuffers");
   gl_BindBuffer = (PFNGLBINDBUFFERPROC) glutGetProcAddress ("glBindBuffer");
   gl_BufferData = (PFNGLBUFFERDATAPROC) glutGetProcAddress ("glBufferData");
   if (!gl_GenBuffers || !gl_BindBuffer || !gl_BufferData)
   {
       fprintf (stderr, "glGenBuffers, glBindBuffer or glBufferData not found");
       exit(1);
   }
    gl_VertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) glutGetProcAddress ("glVertexAttribPointer");
    gl_EnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) glutGetProcAddress ("glEnableVertexAttribArray");

    gl_CreateShader = (PFNGLCREATESHADERPROC) glutGetProcAddress ("glCreateShader");
    gl_ShaderSource = (PFNGLSHADERSOURCEPROC) glutGetProcAddress ("glShaderSource");
    gl_CompileShader = (PFNGLCOMPILESHADERPROC) glutGetProcAddress ("glCompileShader");
    gl_CreateProgram = (PFNGLCREATEPROGRAMPROC) glutGetProcAddress ("glCreateProgram");
    gl_AttachShader = (PFNGLATTACHSHADERPROC) glutGetProcAddress ("glAttachShader");
    gl_LinkProgram = (PFNGLLINKPROGRAMPROC) glutGetProcAddress ("glLinkProgram");
    gl_UseProgram = (PFNGLUSEPROGRAMPROC) glutGetProcAddress ("glUseProgram");
    gl_GetShaderiv = (PFNGLGETSHADERIVPROC) glutGetProcAddress ("glGetShaderiv");
    gl_GetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) glutGetProcAddress ("glGetShaderInfoLog");
    gl_GetProgramiv = (PFNGLGETPROGRAMIVPROC) glutGetProcAddress ("glGetProgramiv");
    gl_GetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) glutGetProcAddress ("glGetProgramInfoLog");
    gl_GetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC) glutGetProcAddress ("glGetAttribLocation");
    gl_GetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) glutGetProcAddress ("glGetUniformLocation");
    gl_UniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC) glutGetProcAddress ("glUniformMatrix4fv");
    gl_UniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC) glutGetProcAddress ("glUniformMatrix3fv");
    gl_Uniform3f = (PFNGLUNIFORM3FPROC)glutGetProcAddress ("glUniform3f");
    gl_Uniform1i = (PFNGLUNIFORM1IPROC)glutGetProcAddress ("glUniform1i");
	
    if (!gl_CreateShader || !gl_ShaderSource || !gl_CompileShader || !gl_CreateProgram || !gl_AttachShader || !gl_LinkProgram || !gl_UseProgram || !gl_GetShaderiv || !gl_GetShaderInfoLog || !gl_GetProgramiv || !gl_GetProgramInfoLog || !gl_GetAttribLocation || !gl_GetUniformLocation || !gl_UniformMatrix4fv || !gl_UniformMatrix3fv || !gl_Uniform3f || !gl_Uniform1i)
    {
        fprintf (stderr, "glCreateShader, glShaderSource, glCompileShader, glCreateProgram, glAttachShader, glLinkProgram, glUseProgram, glGetShaderiv, glGetShaderInfoLog, glGetProgramiv, glGetProgramInfoLog, glGetAttribLocation, glGetUniformLocation, glUniformMatrix4fv or gl_UniformMatrix3fv glUniform1f not found");
        exit(1);
    }
}

const ourGLchar *vertexShaderSource[] = {
    /*"/**",
    " * From the OpenGL Programming wikibook: http://en.wikibooks.org/wiki/GLSL_Programming/GLUT/Smooth_Specular_Highlights",
    " * This file is in the public domain.",
    " * Contributors: Sylvain Beucler",
    " ",
    "attribute vec3 fg_coord;",
    "attribute vec3 fg_normal;",
    "varying vec4 position;  // position of the vertex (and fragment) in world space ",
    "varying vec3 varyingNormalDirection;  // surface normal vector in world space ",
    "uniform mat4 m, p;      // don't need v, as always identity in our demo ",
    "uniform mat3 m_3x3_inv_transp;",
    " ",
    "void main()",
    "{",
    "  vec4 fg_coord4 = vec4(fg_coord, 1.0);",
    "  position = m * fg_coord4;",
    "  varyingNormalDirection = normalize(m_3x3_inv_transp * fg_normal);",
    " ",
    "  mat4 mvp = p*m;   // normally p*v*m ",
    "  gl_Position = mvp * fg_coord4;",
    "}"*/


"varying vec3 N;",
"varying vec3 v;",
"varying vec4 vTexCoord;",
//"uniform float fgreen;",
//"varying float vfgreen;",
//"varying float vx;",
//"uniform vec3 texb;",
//"uniform float texb2;",
//"varying float texbb;",

"void main(void)",
"{",
//"   texbb = texb.x;",
//"   vfgreen  =fgreen;",
"   gl_TexCoord[0] = gl_MultiTexCoord0;",
//"   vTexCoord = gl_MultiTexCoord0;",
"   v = vec3(gl_ModelViewMatrix * gl_Vertex);",
"   N = normalize(gl_NormalMatrix * gl_Normal);",
"   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;",
//"   vx = gl_Position[1];",

"}"
	//gl_ModelViewProjectionMatrix gl_NormalMatrix
};

const ourGLchar *fragmentShaderSource[] = { 

	"varying vec3 N;",
	"varying vec3 v;",    
	"uniform sampler2D myTexture;",
	"varying vec4 vTexCoord;",
	//"uniform vec4 texb;",
	//"uniform float texb2;",
	//"varying float texbb;",

	"void main (void)",  
	"{",  
	"  vec3 L = normalize(gl_LightSource[0].position.xyz - v);",   
	"  vec3 E = normalize(-v); /* we are in Eye Coordinates, so EyePos is (0,0,0)*/",  
	"   vec3 R = normalize(-reflect(L,N));",  
	"   vec3 Mt = vec3(0.2, 0.8, 0.2);",
	"   R = normalize(R*Mt);",
	"   /*calculate Ambient Term:*/",  
	"   vec4 Iamb = gl_FrontLightProduct[0].ambient;",    

	"   /*calculate Diffuse Term:*/",  
	"   vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(N,L), 0.0);",    
	   
	"   /* calculate Specular Term:*/",
	"   vec4 Ispec = gl_FrontLightProduct[0].specular * pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess);",
	//"   /*vec4 vt = texture2D(myTexture, gl_TexCoord[0].xy);*/",
	//"   if(texb.x == 0.0){",
	// "  /* write Total Color:*/",  
	//"   	gl_FragColor = (gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec) + vt;",
	//"   }else{",
	"	gl_FragColor = gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec;",
   	"}"

};


const ourGLchar *fragmentShaderSourceT[] = { 

	"varying vec3 N;",
	"varying vec3 v;",    
	"uniform sampler2D myTexture;",
	"varying vec4 vTexCoord;",
	"uniform vec3 fgreen;",
	//"varying float vfgreen;",
	//"varying float vx;",
	//"uniform vec4 texb;",
	//"uniform float texb2;",
	//"varying float texbb;",

	"void main (void)",  
	"{",  
	"  vec3 L = normalize(gl_LightSource[0].position.xyz - v);",   
	"  vec3 E = normalize(-v); /* we are in Eye Coordinates, so EyePos is (0,0,0)*/",  
	"   vec3 R = normalize(-reflect(L,N));",  
	//"   vec3 Mt = vec3(0.9, 0.8, 0.2);",
	//"   R = R*Mt;",
	"   vec4 shin;",
	"   shin = vec4(1.0, 0.7, 0.0, 1.0);",
	"   /*calculate Ambient Term:*/",  
	"   vec4 Iamb = (gl_FrontLightProduct[0].ambient + 0.2*shin);",
	//"   if(v.y < 0.1)Iamb = Iamb - (vec4(0.0, 0.6, 0.6, 1.0));",    
	"   /*calculate Diffuse Term:*/",  
	"   vec4 Idiff = /*vec4(1.0, 1.0, 1.0, 1.0)*/gl_FrontLightProduct[0].diffuse * max(dot(N,L), 0.0);",    
	   
	"   /* calculate Specular Term:*/",
	
	"   vec4 Ispec = gl_FrontLightProduct[0].specular * pow(max(dot(R,E),0.0),gl_FrontMaterial.shininess*1.0);",
	//"   if(fgreen.g == 0.0)fgreen.g = 3.0;",
	"   vec4 vt = texture2D(myTexture, gl_TexCoord[0].xy);vt.r = vt.r - vt.b;vt.g = vt.g - vt.b/fgreen.g;vt.b = vt.b - (vt.r-vt.g);",
	//"    vec3  norm = texture2D(myTexture, gl_TexCoord[0].xy).rgb * 2.0 - 1.0; ",
	//"    vec3  halfVector = normalize(L + E); ",
	//"    float  nxHalf = max(0.0,dot(norm, halfVector));   ", 
	//"   Ispec = Ispec * pow(nxHalf, gl_FrontMaterial.shininess);   ",
	//"   if(texb.x == 0.0){",
	// "  /* write Total Color:*/",  
	"   	gl_FragColor = (gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec) + vt*1.1;",
	//"   }else{",
	//"	gl_FragColor = gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec;}",
   	"}"

};


const ourGLchar *fragmentShaderSourceT2[] = { 

	"varying vec3 N;",
	"varying vec3 v;",    
	"uniform sampler2D myTexture;",
	"uniform sampler2D nmap;",
	"varying vec4 vTexCoord;",
	"uniform vec3 iswater;",
	"uniform vec3 fgreen;",
	"uniform vec3 isshin;",
	"uniform vec3 fblue;",
	"uniform vec3 touch;",
	"uniform vec3 u_res;",
	"uniform vec3 ftime;",
	//"uniform vec3 fgreen;",
	//"varying float vfgreen;",
	//"varying float vx;",
	//"uniform vec4 texb;",
	//"uniform float texb2;",
	//"varying float texbb;",


	"float random (in vec2 st) {",
	"	return fract(sin(dot(st.xy, vec2(12.9898,78.233)))*43758.5453123);",
	"}",

	"float noiseb ( vec2 _st) {",
	"	vec2 i = floor(_st);",
	"	vec2 f = fract(_st);",

		// Four corners in 2D of a tile
	"	float a = random(i);",
	"	float b = random(i + vec2(1.0, 0.0));",
	"	float c = random(i + vec2(0.0, 1.0));",
	"	float d = random(i + vec2(1.0, 1.0));",

	"	vec2 u = f * f * (3.0 - 2.0 * f);",

	"	return mix(a, b, u.x) +",
	"	    (c - a)* u.y * (1.0 - u.x) +",
	"	    (d - b) * u.x * u.y;",
	"}",

	//"int NUM_OCTAVES 5;",
	"float fbm ( in vec2 _st) {",
	"	float v = 0.0;",
	"	float a = 0.5;",
	"	vec2 shift = vec2(100.0);",
		// Rotate to reduce axial bias
	"	mat2 rot = mat2(cos(0.5), sin(0.5),-sin(0.5), cos(0.50));",
	"	for (int i = 0; i < 4; ++i) {",
	"		v += a * noiseb(_st);",
	"		_st = rot * _st * 2.0 + shift;",
	"		a *= 0.5;",
	"	}",
	"	return v;",
	"}",

	"float sphere(vec2 v){",
	"	return length(v);",
	"}",

	"void main (void)",  
	"{",  
	"	vec2 uv = gl_FragCoord.xy / vec2(u_res.x, u_res.y);",
	"  vec3 L = normalize(gl_LightSource[0].position.xyz - v);",   
	//"   vec4 vn = normalize(texture2D(nmap, gl_TexCoord[0].xy).rgba*2.0-1.0);",
	//"clamp(vn, 0.5, 1.0);",
	"  vec3 E = normalize(-v); /* -v we are in Eye Coordinates, so EyePos is (0,0,0)*/",  
	"   vec3 R = normalize(-reflect(L,N));",  
	//"   vec3 Mt = vec3(0.9, 0.8, 0.2);",
	//"   R = R*Mt;",
	"   vec4 shin;",
	"   shin = vec4(1.0, 0.7, 0.0, 1.0)*0.33;",
	"   /*calculate Ambient Term:*/",  
	"   vec4 Iamb = gl_FrontLightProduct[0].ambient;",
	"   if(isshin.r == 1.0)Iamb += shin;",
	//"   Iamb = vec4(1.0, 0.7, 0.0, 1.0);",
	"   clamp(Iamb, 0.0, 1.0);",
	//"   if(v.y < 0.1)Iamb = Iamb - (vec4(0.0, 0.6, 0.6, 1.0));",    
	"   /*calculate Diffuse Term:*/",  
	//"   vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(N,L), 0.0);",    
	"   vec4 Idiff = vec4(0.1, 0.1, 0.00, 1.0)* max(dot(N,L), 0.0);",
	"   clamp(Idiff, 0.0, 1.0);",
	"   /* calculate Specular Term:*/",
	
	//"   vec4 Ispec = gl_FrontLightProduct[0].specular * pow(max(dot(R,E),0.0),gl_FrontMaterial.shininess*5.0);",
	"   vec4 Ispec = vec4(1.00, 0.10, 0.05, 1.0)* pow(max(dot(R,E),0.0),gl_FrontMaterial.shininess);",
	"   clamp(Ispec, 0.0, 1.0);",
	//"   if(Ispec
	//"   if(fgreen.g == 0.0)fgreen.g = 3.0;",
	
	//"   vec4 vt = texture2D(myTexture, gl_TexCoord[0].xy + 0.6 * (E.xy* (0.04*( vec2(vn.r-vn.g, vn.r-vn.g) )) ) );",
	"   vec4 vn;",
	
	"   vec4 vt;",

	
	///"   if(iswater.x == 1.0){",
	//"   	vn = normalize(texture2D(nmap, (gl_TexCoord[0].xy+ftime.y * 0.05 / 500000.0)/*+((gl_TexCoord[0].xy+0.01)+ftime.y * 0.03 / 500000.0)*/).rgba*2.0-1.0);",
	//"	vt = vec4(0.0, 0.2, 0.3, 0.0)+vec4((E.xy*(2.02*vec2(vn.r-vn.g, vn.r-vn.g))), vn.b, 0.0);",
	//"   	vt = texture2D(myTexture, gl_TexCoord[0].xy +  (E.xy*(0.08*vec2(vn.r-vn.g, vn.r-vn.g))) );",
	//"	vt += vec4(0.6, 0.2, 0.8, 0.0);",
	//"       vt.r = vt.r - vt.b;vt.g = vt.g - vt.b/fgreen.g;",
	//"	if(fblue.x == 1.0){ vt.b = fblue.b;}else {vt.b = vt.b - (vt.r-vt.g);}",
	//"	gl_FragColor = mix(vt, vec4(0.5, 1.5, 1.0, 0.0), 0.4);",
	//"   }else{",
	"   if(iswater.x == 0.0){",
	"   vn = normalize(texture2D(nmap, gl_TexCoord[0].xy).rgba*2.0-1.0);",
	
	"   vt = texture2D(myTexture, gl_TexCoord[0].xy +  (E.xy*(.02*vn.rg)) );",
	"   if(iswater.y == 1.0){vt.r = vt.r - vt.b;vt.g = vt.g - vt.b/fgreen.g;vt.b = vt.b - (vt.r-vt.g);}",
	"   gl_FragColor = (gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec) + vt;",
	"   }",

	"   vec4 col = vec4(1.0, 1.0, 1.0, 1.0);",
	"   if(touch.x == 1.0){",
	"	vec2 cer = vec2(uv.x - 0.5, uv.y - 0.5);",
	"	col += vt*1.1;",
	"	float ry;",
	"	ry = ftime.y * 0.5 / 500000.0; ",
	"	vec4 s = vec4(atan(cer.x/cer.y)/3.14, 1.0 / length(cer)*ry, 0.0, 0.0);",
	"	float sr = sphere(cer.xy);",
	"	if( sr  < ry){",
	"		col *= smoothstep(col, s*vt, vec4(0.5, 0.5, 1.0, 1.0));",
	//"		col = vec4(1.0, 0.0, 0.0, 0.0);",
	"   		gl_FragColor = (gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec) + col;",
	"	}else if(( sin(sr)  >= ry) && ( sin(sr)  <= ry+0.01 )){",
	"		col *= smoothstep(col, vt, vec4(1.0, 0.7, 0.0, 1.0));",
	//"		col.r *= smoothstep(col.r, sr*vt.r, sin(s.x*2.0*3.1415));",
	//"		col.g *= smoothstep(col.g, sr*vt.g, sin(s.x*2.0*3.1415));",
	"		gl_FragColor = /*(gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec) +*/ col;",
	"	}else{",
	"		gl_FragColor = (gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec) + vt;",
	"	}",
	"   }",
	//"   else{", 
	//"   	gl_FragColor = /*(gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec) +*/ vt;",
	//"  }",
	
   	"}"

};

const ourGLchar *fragment555ShaderSource[] = {
	
	"varying vec4 vColor;",

	"void main (void) ",
	"{",     
	"   gl_FragColor = vColor;  ",
	"} "

};

const ourGLchar *fragmentShaderSourceTfuckT2[] = {
    "/**",
    " * From the OpenGL Programming wikibook: http://en.wikibooks.org/wiki/GLSL_Programming/GLUT/Smooth_Specular_Highlights",
    " * This file is in the public domain.",
    " * Contributors: Martin Kraus, Sylvain Beucler",
    " */",
    "varying vec3 N;",
    "varying vec3 v;",
    " vec4 position = vec4(v.x, v.y, v.z, 1.0);   /*position of the vertex (and fragment) in world space */",
    " vec3 varyingNormalDirection;   /*surface normal vector in world space */",
    "uniform sampler2D myTexture;",
    "varying vec4 vTexCoord;",
    "/* uniform mat4 v_inv;   // in this demo, the view matrix is always an identity matrix */",
    " ",
    "struct lightSource",
    "{",
    "  vec4 position;",
    "  vec4 diffuse;",
    "  vec4 specular;",
    "  float constantAttenuation, linearAttenuation, quadraticAttenuation;",
    "  float spotCutoff, spotExponent;",
    "  vec3 spotDirection;",
    "};",
    "lightSource light0 = lightSource(",
    "  vec4(2.0, 5.0, 5.0, 0.0),",
    "  vec4(1.0, 1.0, 1.0, 1.0),",
    "  vec4(1.0, 1.0, 1.0, 1.0),",
    "    0.0, 1.0, 0.0,",
    "  180.0, 0.0,",
    "  vec3(0.0, 0.0, 0.0)",
    ");",
    "vec4 scene_ambient = vec4(0.2, 0.2, 0.2, 1.0);",
    " ",
    "struct material",
    "{",
    "  vec4 ambient;",
    "  vec4 diffuse;",
    "  vec4 specular;",
    "  float shininess;",
    "};",
    "material frontMaterial = material(",
    "  vec4(1.0, 1.0, 1.0, 1.0),",
    "  vec4(1.0, 1.0, 1.0, 1.0),",
    "  vec4(1.0, 1.0, 1.0, 1.0),",
    "  100.0",
    ");",
    " ",
    "void main()",
    "{",
    //"  position.xyzw = vec4(v.x, v.y, v.z, 1.0);",
    "  varyingNormalDirection.xyz = N.xyz;",
    "  vec3 normalDirection = normalize(varyingNormalDirection);",
    "  /* vec3 viewDirection = normalize(vec3(v_inv * vec4(0.0, 0.0, 0.0, 1.0) - position)); */",
    "  vec3 viewDirection = normalize(vec3(vec4(0.0, 0.0, 0.0, 1.0) - position));    /* in this demo, the view matrix is always an identity matrix */",
    "  vec3 lightDirection;",
    "  float attenuation;",
    " ",
    "  if (0.0 == light0.position.w) /* directional light? */",
    "    {",
    "      attenuation = 1.0; /* no attenuation */",
    "      lightDirection = normalize(vec3(light0.position));",
    "    } ",
    "  else /* point light or spotlight (or other kind of light) */",
    "    {",
    "      vec3 positionToLightSource = vec3(light0.position - position);",
    "      float distance = length(positionToLightSource);",
    "      lightDirection = normalize(positionToLightSource);",
    "      attenuation = 1.0 / (light0.constantAttenuation",
    "                           + light0.linearAttenuation * distance",
    "                           + light0.quadraticAttenuation * distance * distance);",
    " ",
    "      if (light0.spotCutoff <= 90.0) /* spotlight? */",
    "        {",
    "          float clampedCosine = max(0.0, dot(-lightDirection, light0.spotDirection));",
    "          if (clampedCosine < cos(radians(light0.spotCutoff))) /* outside of spotlight cone? */",
    "            {",
    "              attenuation = 0.0;",
    "            }",
    "          else",
    "            {",
    "              attenuation = attenuation * pow(clampedCosine, light0.spotExponent);   ",
    "            }",
    "        }",
    "    }",
    " ",
    "  vec3 ambientLighting = vec3(scene_ambient) * vec3(frontMaterial.ambient);",
    " ",
    "  vec3 diffuseReflection = attenuation ",
    "    * vec3(light0.diffuse) * vec3(frontMaterial.diffuse)",
    "    * max(0.0, dot(normalDirection, lightDirection));",
    " ",
    "  vec3 specularReflection;",
    "  if (dot(normalDirection, lightDirection) < 0.0) /* light source on the wrong side? */",
    "    {",
    "      specularReflection = vec3(0.0, 0.0, 0.0); /* no specular reflection */",
    "    }",
    "  else /* light source on the right side */",
    "    {",
    "      specularReflection = attenuation * vec3(light0.specular) * vec3(frontMaterial.specular) ",
    "        * pow(max(0.0, dot(reflect(-lightDirection, normalDirection), viewDirection)), frontMaterial.shininess);",
    "    }",
    " ",
    "   vec4 vt = texture2D(myTexture, gl_TexCoord[0].xy);",
    "  gl_FragColor = vec4(ambientLighting + diffuseReflection + specularReflection  , 1.0) * vt;",
    "}"
};

GLint getAttribOrUniformLocation(const char* name, GLuint program, GLboolean isAttrib)
{
    if (isAttrib)
    {
        GLint attrib = gl_GetAttribLocation(program, name);
        if (attrib == -1)
        {
            fprintf(stderr, "Warning: Could not bind attrib %s\n", name);  
        }

		checkError ("getAttribOrUniformLocation");
        return attrib;
    }
    else
    {
        GLint uniform = gl_GetUniformLocation(program, name);
        if (uniform == -1)
        {
            fprintf(stderr, "Warning: Could not bind uniform %s\n", name);  
        }

		checkError ("getAttribOrUniformLocation");
        return uniform;
    }
}

static GLuint program, programT, programT2;
GLint attribute_fg_coord = -1, attribute_fg_normal = -1;  
GLint uniform_m = -1, uniform_p = -1, uniform_m_3x3_inv_transp = -1;
GLint shaderReady = 0;  /* Set to 1 when all initialization went well, to -1 when shader somehow unusable. */



void compileAndCheck(GLuint shader)
{
    GLint status;
    gl_CompileShader (shader);
    gl_GetShaderiv (shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        ourGLchar *infoLog;
        gl_GetShaderiv (shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        infoLog = (ourGLchar*) malloc (infoLogLength);
        gl_GetShaderInfoLog (shader, infoLogLength, NULL, infoLog);
        fprintf (stderr, "compile log: %s\n", infoLog);
        free (infoLog);
    }
    checkError ("compileAndCheck");
}

GLuint compileShaderSource(GLenum type, GLsizei count, const ourGLchar **string)
{
    GLuint shader = gl_CreateShader (type);
    gl_ShaderSource (shader, count, string, NULL);

    checkError ("compileShaderSource");

    compileAndCheck (shader);
    return shader;
}

void linkAndCheck(GLuint program)
{
    GLint status;
    gl_LinkProgram (program);
    gl_GetProgramiv (program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        ourGLchar *infoLog;
        gl_GetProgramiv (program, GL_INFO_LOG_LENGTH, &infoLogLength);
        infoLog = (ourGLchar*) malloc (infoLogLength);
        gl_GetProgramInfoLog (program, infoLogLength, NULL, infoLog);
        fprintf (stderr, "link log: %s\n", infoLog);
        free (infoLog);
    }
    checkError ("linkAndCheck");
}

void createProgram(GLuint *prog, GLuint vertexShader, GLuint fragmentShader)
{
    *prog = gl_CreateProgram ();
    if (vertexShader != 0) {
        gl_AttachShader (*prog, vertexShader);
    }
    if (fragmentShader != 0) {
        gl_AttachShader (*prog, fragmentShader);
    }

    checkError ("createProgram");

    linkAndCheck (*prog);
}



void initShader(void)
{
    const GLsizei vertexShaderLines = sizeof(vertexShaderSource) / sizeof(ourGLchar*);
    GLuint vertexShader =
        compileShaderSource (GL_VERTEX_SHADER, vertexShaderLines, vertexShaderSource);

    const GLsizei fragmentShaderLines = sizeof(fragmentShaderSource) / sizeof(ourGLchar*);
    GLuint fragmentShader =
        compileShaderSource (GL_FRAGMENT_SHADER, fragmentShaderLines, fragmentShaderSource);

    checkError ("initShader - 1");

    createProgram (&program, vertexShader, fragmentShader);

    gl_UseProgram (program);

	
    //const GLsizei vertexShaderLines = sizeof(vertexShaderSource) / sizeof(ourGLchar*);
    GLuint vertexShader2 =
        compileShaderSource (GL_VERTEX_SHADER, vertexShaderLines, vertexShaderSource);

    const GLsizei fragmentShaderLines2 = sizeof(fragmentShaderSourceT) / sizeof(ourGLchar*);
    GLuint fragmentShader2 =
        compileShaderSource (GL_FRAGMENT_SHADER, fragmentShaderLines2, fragmentShaderSourceT);

    checkError ("initShader - 1");

    createProgram (&programT, vertexShader2, fragmentShader2);

	//printf("wvsh ;: %d\n", vertexShaderLines);
    //const GLsizei vertexShaderLines = sizeof(vertexShaderSource) / sizeof(ourGLchar*);
    GLuint vertexShaderT2 =
        compileShaderSource (GL_VERTEX_SHADER, vertexShaderLines, vertexShaderSource);

    const GLsizei fragmentShaderLinesT2 = sizeof(fragmentShaderSourceT2) / sizeof(ourGLchar*);
	//printf("wvsh ;: %d - %p\n", fragmentShaderLinesT2, fragmentShaderSourceT2);
    GLuint fragmentShaderT2 =
        compileShaderSource (GL_FRAGMENT_SHADER, fragmentShaderLinesT2, fragmentShaderSourceT2);

    checkError ("initShader - 1");

    createProgram (&programT2, vertexShaderT2, fragmentShaderT2);


    /*texb = gl_GetUniformLocation(program, "texb");
    if (texb == -1)
	{
	    fprintf(stderr, "Warning: Could not bind uniform %s\n", "texb");  
	}else
		printf("texb : %d\n", texb);
    glUniform4f(texb, 1.0f, 0.0f, 0.0f, 0.0f);*/

		checkError ("getAttribOrUniformLocation");

    /*attribute_fg_coord      = getAttribOrUniformLocation("fg_coord"         , program, GL_TRUE);
    attribute_fg_normal     = getAttribOrUniformLocation("fg_normal"        , program, GL_TRUE);
    uniform_m               = getAttribOrUniformLocation("m"                , program, GL_FALSE);
    uniform_p               = getAttribOrUniformLocation("p"                , program, GL_FALSE);
    uniform_m_3x3_inv_transp= getAttribOrUniformLocation("m_3x3_inv_transp" , program, GL_FALSE);

    gl_EnableVertexAttribArray (attribute_fg_coord);
    gl_EnableVertexAttribArray (attribute_fg_normal);*/

    /*gl_UseProgram (0);

    if (attribute_fg_coord==-1 || attribute_fg_normal==-1 ||
        uniform_m==-1 || uniform_p==-1 || uniform_m_3x3_inv_transp==-1)
        shaderReady = -1;
    else
        shaderReady = 1;*/

    checkError ("initShader - 2");
}

/*
 * This macro is only intended to be used on arrays, of course.
 */
#define NUMBEROF(x) ((sizeof(x))/(sizeof(x[0])))

/*
 * These global variables control which object is drawn,
 * and how it is drawn.  No object uses all of these
 * variables.
 */
static int function_index;
static int slices = 16;
static int stacks = 16;
static double irad = .25;
static double orad = 1.0;   /* doubles as size for objects other than Torus */
static int depth = 4;
static double offset[ 3 ] = { 0, 0, 0 };
static GLboolean show_info = GL_TRUE;
static float ar;
static GLboolean persProject = GL_TRUE;
static GLboolean animateXRot = GL_FALSE;
static GLboolean useShader   = GL_TRUE;
static GLboolean visNormals  = GL_FALSE;


/* vertex array data for a colored 2D triangle, consisting of RGB color values
   and XY coordinates */
const GLfloat varray[] = {
   0.0, 0.0, 1.0f, /* red */
   -0.5, 0.5, 0.0,      /* lower left */

   0.0, 0.0, 1.0f, /* green */
   -0.5, -0.5, 0.0,     /* lower right */

   0.0, 0.0, 1.0f, /* blue */
   0.5, 0.5, 0.0      /* upper left */
};

/* ISO C somehow enforces this silly use of 'enum' for compile-time constants */
enum {
  numColorComponents = 3,
  numVertexComponents = 3,
  stride = sizeof(GLfloat) * (numColorComponents + numVertexComponents),
  numElements = sizeof(varray) / stride
};

/* the name of the vertex buffer object */
GLuint vertexBufferName;
GLuint vertexArrayName;

const GLvoid *bufferObjectPtr (GLsizei index)
{
   return (const GLvoid *) (((char *) NULL) + index);
}

static void drawSolidKUS999(void)
{
   //gl_UniformMatrix4fv (fgProjectionMatrixIndex, 1, GL_FALSE, projectionMatrix);
   //glFrontFace(GL_CCW); 
   gl_BindBuffer (GL_ARRAY_BUFFER, vertexBufferName);
   gl_VertexAttribPointer (attribute_fg_normal, numColorComponents, GL_FLOAT, GL_TRUE,
                           stride, bufferObjectPtr (0));
   gl_VertexAttribPointer (attribute_fg_coord, numVertexComponents, GL_FLOAT, GL_FALSE,
                           stride, bufferObjectPtr(sizeof(GLfloat) * numColorComponents) );
   glDrawArrays(GL_TRIANGLES, 0, numElements);
   //printf("nelem = %d %d %d %d\n", numElements, sizeof(varray), sizeof(GLfloat),  bufferObjectPtr(sizeof(GLfloat) * numColorComponents));
   //checkError ("triangle");
	//glFrontFace(GL_CCW); 
}


static GLuint tex_2d;
static float X=0.0f, Y=0.0f, Z=0.0f;
#include "rotate.c"
#include "shader.c"
#include "shaderdef.c"
#include "Box.c"

static Shader shader, shader_def, shader_wat;

#include "map.c"
#include "world_def.c"
#include "plongeon.c"
#include "stripes.c"
#include "direction.c"
#include "couteau.c"
#include "texture.c"
#include "gun.c"
#include "player.c"
#include "sprite.c"
#include "monster.c"
#include "skybox.c"

static void drawSolidKUS(){
	
	
	#include "coderm.c"




}

static void drawWireKUS(){
	float x = 0.5, y = 0.5, z = -1.0;
	//glFrontFace(GL_CW);
	glBegin( GL_LINE_LOOP );
	//gl_Uniform3f(attribute_fg_normal,  x, y, z);
	glColor3f(1.0, 0.0, 0.0);
	glNormal3f( x, y, z );glVertex3d( -0.5, 0.5, 0.0 );
	glNormal3f( x, y, z );glVertex3d( -0.5, -0.5, 0.0 );
	glNormal3f( x, y, z );glVertex3d( 0.5, -0.5, 0.0 );
	glNormal3f( x, y, z );glVertex3d( 0.5, 0.5, 0.0 );
	glEnd();
	//glFrontFace(GL_CCW);
}

#undef RADIUSFAC




void initBuffer(void)
{
   /* Need to setup a vertex array as otherwise invalid operation errors can
    * occur when accessing vertex buffer (OpenGL 3.3 has no default zero named
    * vertex array) 
    */
   gl_GenVertexArrays(1, &vertexArrayName);
   gl_BindVertexArray(vertexArrayName);

   gl_GenBuffers (1, &vertexBufferName);
   gl_BindBuffer (GL_ARRAY_BUFFER, vertexBufferName);
   gl_BufferData (GL_ARRAY_BUFFER, sizeof(varray), varray, GL_STATIC_DRAW);
   checkError ("initBuffer");
}

/*
 * This structure defines an entry in our function-table.
 */
typedef struct
{
    const char * const name;
    void (*solid) (void);
    void (*wire)  (void);
    int drawSizeInfoFlag;
} entry;


/*!
    Does printf()-like work using freeglut
    glutBitmapString().  Uses a fixed font.  Prints
    at the indicated row/column position.

    Limitation: Cannot address pixels.
    Limitation: Renders in screen coords, not model coords.
*/
static void shapesPrintf (int row, int col, const char *fmt, ...)
{
    static char buf[256];
    int viewport[4];
    void *font = GLUT_BITMAP_9_BY_15;
    va_list args;

    va_start(args, fmt);
#if defined(WIN32) && !defined(__CYGWIN__)
    (void) _vsnprintf (buf, sizeof(buf), fmt, args);
#else
    (void) vsnprintf (buf, sizeof(buf), fmt, args);
#endif
    va_end(args);

    glGetIntegerv(GL_VIEWPORT,viewport);

    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

        glOrtho(0,viewport[2],0,viewport[3],-1,1);

        glRasterPos2i
        (
              glutBitmapWidth(font, ' ') * col,
            - glutBitmapHeight(font) * row + viewport[3]
        );
        glutBitmapString (font, (unsigned char*)buf);

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}





static float W, H;
/* GLUT callback Handlers */
static void
resize(int width, int height)
{
    W = width;H = height; 

    ar = (float) width / (float) height;

	

    glViewport(0, 0, width, height);
}

static Skybox skybox;
static Monster monster;
static Box boxw, boxs;
static float fps, ttouch=0.0f, twater=0.0f;
static Sprite sprite;
static Player player;
static Gun gun;
static Texture texture;
static Direction direction;
static Couteau couteau;
static Plongeon plongeon;
static House house, houseu, houset[51];
static GLfloat Wgreen = 3.0f;
static int NX1, NY1;
static MapType solmap;
static int ipminW, ipmaxW, ipmaxWall;
static GLuint tex_cube;
static char full = 0;
static float tvusec, mx_tvusec=0.0f;
static struct timeval tv, tvp, tvd;
static float RX = 0.0f, RY = 0.0f, RZ = 0.0f;
static float CX, CY;
static int rtx = 1;
static int first = 1; 
static void display(void)
{
   

	syscall(__NR_gettimeofday, &tv, NULL);

	tvusec = tv.tv_usec - tvp.tv_usec;
	if(tvusec < 0.0f)
		tvusec = 16666.6f;
	tvp = tv;
	mx_tvusec  = mx_tvusec + tvusec;
	ttouch  = ttouch + tvusec;
	twater = twater + tvusec;
	monster.touch = monster.touch + tvusec;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
       
        glFrustum(-ar, ar, -1.0, 1.0, 2.0, 300.0);

	

	//Hache
	if(player.couteau == 1){
		OnHit(&couteau, tvusec);
		
		Draw_Couteau(&couteau);
	}
	else if(player.gun == 1){
		//Set_Res_Gun(&gun, W, H);
		OnHit_Gun(&gun);
		//Draw_Gun(&gun);
		Draw_Gun_CM(&gun);
			
	}
	

	if(player.move == 1){
		rotate_A(RZ, RX, RY, ipminW, ipmaxW);
		rotate_A(RZ, RX, RY, solmap.ipmin, solmap.ipmax);
		rotate_A(RZ, RX, RY, house.ipomin, house.ipomax);
		rotate_A(RZ, RX, RY, houseu.ipomin, houseu.ipomax);
				
		for(int i = 0;i < 6;i++){
			rotate_A(RZ, RX, RY, houset[i].ipomin, houset[i].ipomax);
			
		}

		rotate_A(RZ, RX, RY, 0, ipmaxWall);

		Reset_Box(&gun);

		Get_Box(&boxs, solmap.ipmin, solmap.ipmax);
		Create_Box(&boxs, -5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f);
		Add_Gun_Box(&gun, &boxs);

		rotate_A(RZ, RX, RY, monster.stripe[0].Ipomin, monster.stripe[0].Ipomax);
		Get_Box(&monster.box, monster.stripe[0].Ipomin, monster.stripe[0].Ipomax);
		Create_Box(&monster.box, -2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
		Add_Gun_Box(&gun, &monster.box);

		Rotate_Skybox_Y(&skybox, RX);
		gun.rx = P[skybox.Ipomin][0]*0.5;
		gun.ry = P[skybox.Ipomin][1]*0.5;
		gun.rz = P[skybox.Ipomin][2]*0.5;
			
		RX=0.0f;
		player.move = 0;
	}

	

	if(gun.max_OF > 0){
		for(int i = 0;i < gun.max_B;i++){
			Get_Box(&gun.box[0], 0, ipmaxWall);
			Create_Box(&gun.box[0], -5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f);
			//Create_Box(&g->ammo[ia].box, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
		}
	}

	glRotatef(RY, 0,0,1);
	glRotatef(RZ, 1,0,0);
	//glRotatef(RX, 0,1,0);

	Draw_Skybox(&skybox);

        //glMatrixMode(GL_MODELVIEW);
        //glLoadIdentity();

	

        glEnable(GL_LIGHTING);

	
        	

			unsigned char io = inb(0x60);
			if(io == 0x11){
				if((RZ < 90.0f) && (RZ > -90.0f))
					key('z', 0, 0);
				else
					key('s', 0, 0);
			}
			else if(io == 0x1f){
				if((RZ < 90.0f) && (RZ > -90.0f))
					key('s', 0, 0);
				else
					key('z', 0, 0);
			}
			else if(io == 0x10){
				key('a', 0, 0);
			}
			else if(io == 0x12){
				key('e', 0, 0);
			}
			else if(io == 0x2c){
				key('w', 0, 0);
			}
			else if(io == 0x2d){
				key('x', 0, 0);
			}
			else if(io == 0x2e){
				key('c', 0, 0);
			}
			else if(io == 0x2f){
				key('v', 0, 0);
			}
			else if(io == 0x99){
				if(plongeon.in_plongeon == 0)
					Start_Plongeon(&plongeon);
			}
			else if(io == 0x1){
				key(27, 0, 0);
			}
			else if(io == 0x4e){
				Wgreen = Wgreen + 0.01f;
			}
			else if(io == 0x4a){
				if(Wgreen > 0.0f)
					Wgreen = Wgreen - 0.01f;
			}
			else if(io == 0x4f){
				Set_Couteau_Player(&player);
			}
			else if(io == 0x50){
				Set_Gun_Player(&player);
			}
			else if(io == 0x1b){
				if(full != 0x1b)
					key(36, 0, 0);
			}

			full = io;

		if(plongeon.in_plongeon == 1)
		{
			Plonger(&plongeon, tvusec);
			gun.ry = gun.ry - 0.01f;
		}
		
		

		Anim(tvusec, ipminW, ipmaxW);
		//Normal();
		
		//glDepthMask(GL_FALSE);
		//glEnable(GL_POLYGON_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE/*_MINUS_SRC_ALPHA*/);

		//water
		gl_UseProgram (shader_wat.program);
		GLint fg = gl_GetUniformLocation(shader_wat.program, "fgreen");
		
		gl_Uniform3f(fg, 0.0f, Wgreen, 0.0f);
		GLint isw = gl_GetUniformLocation(shader_wat.program, "iswater");
		gl_Uniform3f(isw, 1.0f, 0.0f, 0.0f);

		GLint ishin = gl_GetUniformLocation(shader_wat.program, "isshin");
		gl_Uniform3f(ishin, 0.0f, 0.0f, 0.0f);

		GLint fblue = gl_GetUniformLocation(shader_wat.program, "fblue");
		gl_Uniform3f(fblue, 0.0f, 0.0f, 1.0f);
		GLint ftimetw = gl_GetUniformLocation(shader_wat.program, "ftime");
		gl_Uniform3f(ftimetw, 0.0f, twater, 0.0f);
		
		Draw_2mapN(30, 1, shader_wat.program, 2, 16);
		gl_Uniform3f(fblue, 0.0f, 0.0f, 0.0f);

		//glDisable(GL_POLYGON_SMOOTH);
		glDisable(GL_BLEND);
		//glDepthMask(GL_TRUE);
		

		//wall
		gl_UseProgram (programT2);
		
		GLint touch2 = gl_GetUniformLocation(programT2, "touch");

		if((gun.touch_B == 0)&&(ttouch <= 500000.0f)){
			gl_Uniform3f(touch2, 1.0f, 0.0f, 0.0f);
		}
		else
		{
			ttouch = 0.0f;
			gun.touch_B = -1;
			gl_Uniform3f(touch2, 0.0f, 0.0f, 0.0f);
		}
		GLint ftimet2 = gl_GetUniformLocation(programT2, "ftime");
		gl_Uniform3f(ftimet2, 0.0f, ttouch, 0.0f);
		/*if((gun.touch_B == 0)&&(ttouch > 500000.0f)){
			ttouch = 0.0f;
			gl_Uniform3f(touch2, 0.0f, 0.0f, 0.0f);
		}*/
		GLint ures2 = gl_GetUniformLocation(programT2, "u_res");
		gl_Uniform3f(ures2, W, H, 0.0f);
		GLint fgwa = gl_GetUniformLocation(programT2, "fgreen");
		GLint iswa = gl_GetUniformLocation(programT2, "iswater");
		GLint ishina = gl_GetUniformLocation(programT2, "isshin");
		gl_Uniform3f(ishina, 1.0f, 0.0f, 0.0f);
		gl_Uniform3f(iswa, 0.0f, 0.0f, 0.0f);
		gl_Uniform3f(fgwa, 0.0f, 0.2f, 0.0f);
		Draw_2map(NX1, 0, programT2, 1);
		gl_Uniform3f(touch2, 0.0f, 0.0f, 0.0f);
		
		
		//sol
		gl_UseProgram (shader_def.program);
		GLint fgs = gl_GetUniformLocation(shader_def.program, "fgreen");
		gl_Uniform3f(fgs, 0.0f, 3.0f, 0.0f);
		GLint isws = gl_GetUniformLocation(shader_def.program, "iswater");
		gl_Uniform3f(isws, 0.0f, 0.0f, 0.0f);

		GLint ftime = gl_GetUniformLocation(shader_def.program, "ftime");
		gl_Uniform3f(ftime, 1.0f, mx_tvusec, 0.0f);
		if(mx_tvusec > 2000000.0f)mx_tvusec = 0.0f;
		GLint ures = gl_GetUniformLocation(shader_def.program, "u_res");
		gl_Uniform3f(ures, W, H, 0.0f);
		
		GLint pos = gl_GetUniformLocation(shader_def.program, "position");
		Get_Alpha_Vector(&boxs);
		gl_Uniform3f(pos, boxs.xmc, boxs.ymc, boxs.zmc );
		//printf("Z / %f\n", P[O[2][0][0][0]][2]-25.0f+Z);Display_Box(&boxs);
		
		//gl_UseProgram(programT2);
		//GLint fgs = gl_GetUniformLocation(programT2, "fgreen");
		//GLint isws = gl_GetUniformLocation(programT2, "iswater");
		//sol
		//gl_Uniform3f(isws, 1.0f, 0.0f, 0.0f);
		//gl_UseProgram (shader_def.program/*programT2*/);
		//gl_Uniform3f(fgs, 0.0f, 3.0f, 0.0f);
		Draw_2mapN(solmap.NX, 2, shader_def.program, 3, 13);

		gl_UseProgram(programT2);
		GLint iswah = gl_GetUniformLocation(programT2, "iswater");
		gl_Uniform3f(iswah, 0.0f, 1.0f, 0.0f);
		Draw_House(&house);
		Draw_House(&houseu);
		for(int i = 0;i < 6;i++){
			Draw_House(&houset[i]);
		}

		//gl_UseProgram(shader_def.program);
		//sprite.shader = shader_def.program;
		//Move_Sprite(&sprite, gun.xt, gun.yt, gun.zt);
		//Update_Sprite(&sprite, tvusec);
		//Draw_Sprite(&sprite);
				
	
		
		OnFire_Gun(&gun, &direction, RZ, RX, RY, tvusec);
		//if(gun.onfire == 1)
		if(gun.max_OF > 0){
			Draw_Gun_Ammo(&gun);
			
		}

		Is_Touch_Monster(&monster, &gun);
		Draw_Monster(&monster, W, H);
			
		/*fps += tvusec;
		if(fps > 5000000.0f){
			printf("FPS : %f\n", 1000000.0f / tvusec);
			fps = 0.0;
		}*/
	
    glutSwapBuffers();
}



static void
key(unsigned char key, int x, int y)
{
	float inter = 16666.0f;
	//if(tvusec > 30000.0f)
	//	inter = 30000.0f;
	float VX = tvusec * 0.5f / inter;
	float VZ = tvusec * 0.5f / inter;
	float VRX = 2.0f;//tvusec * 5.0f / 16666.0f;
	float VY = tvusec * 0.1f / inter;

	if(VX < 0.0f)
		VX = 0.1f;
	if(VZ < 0.0f)
		VZ = 0.1f;

	if(VRX < 0.0f)
		VRX = 2.0f;

	if(VY < 0.0f)
		VY = 0.1f;

	/*printf("VZ usec : %f %f\n", VZ, tvusec);
	printf("VX usec : %f %f\n", VX, tvusec);
	printf("VRX usec : %f %f\n", VRX, tvusec);*/
		

    switch (key)
    {
    case 27 :glutLeaveMainLoop () ;break;
 /*   case 'Q':
    case 'q': glutLeaveMainLoop () ;      break;
glRotatef((float)1.0,1,0,0);
            glRotatef((float)-1.0,0,1,0);
	    glRotatef((float)1.0,0,0,1);
	/*case 'x':
		//if(RX < 360.0f){
			RX = RX + 10.0f;
			glRotatef(1.0f,1,0,0);
		//}
		break;
	case 'c':
		//if(RX > 0.0f){
			RX = RX - 10.0f;
			glRotatef(-1.0f,1,0,0);
		//}
		break;
	case 'y':
		//if(RY < 360.0f){
			RY = RY + 10.0f;
			glRotatef(1.0f,0,1,0);
		//}
		break;
	case 'u':
		//if(RY > 0.0f){
			RY = RY - 10.0f;
			glRotatef(-1.0f,0,1,0);
		//}
		break;
	/*case 'z':
		//if(RZ < 360.0f){
			RZ = RZ + 10.0f;
			glRotatef(1.0f,0,0,1);
		//}
		break;*/
	/*case 'e':
		//if(RZ > 0.0f){
			RZ = RZ - 10.0f;
			glRotatef(-1.0f,0,0,1);
		///}
		break;*/

	case 'z':
		//printf("time : %f\n", glutGet(GLUT_ELAPSED_TIME));

		Z = Z + VZ;direction.VZ = VZ;
		gun.rx = gun.rx + 0.01f;
		gun.ry = gun.ry + 0.01f;
		gun.rz = gun.rz + 0.01f;
		/*
		//if(rtx == 1){
			if(RX >= 0.0f){
				if(RX < 10.0f){
					//X = X + VX;
					Z = Z + VZ;
					direction.direction = 1;
					direction.VZ = VZ;
				}
				else if((RX >= 10.0f) && (RX < 60.0f)){
					direction.VX = (RX * VX / 59.99f);
					direction.VZ = VZ;
					X = X - direction.VX;
					Z = Z + VZ;
					//printf("10 and 60 \n");
					direction.direction = 2;
					 

				}
				else if((RX >= 60.0f) && (RX < 120.0f)){
					direction.VX = VX;
					X = X - VX;
					direction.direction = 3;
					//printf("60 and 120 \n");

				}
				else if((RX >= 120.0f) && (RX < 180.0f)){
					direction.VX = (RX * VX / 179.99f);
					direction.VZ = VZ;
					X = X - direction.VX;
					Z = Z - VZ;
					//printf("> 120 \n");
					direction.direction = 4;
					

				}
				else if(RX > 200.0f) 
				{
					RX = -160.0f;
					direction.direction = 8;
				}
				else{
					Z = Z - VZ;
					direction.direction = 5;
					//printf("defaut z \n");
					direction.VZ = VZ;
				}
			}
			else
			{
				if(RX > -10.0f){
					//X = X - VX;
					Z = Z + VZ;
					//printf("> -10\n");
					direction.VZ = VZ;
					direction.direction = 1;
				}
				else if((RX <= -10.0f) && (RX > -60.0f)){
					direction.VX = (RX * VX / -59.99f);
					direction.VZ = VZ;
					X = X + direction.VX;
					Z = Z + VZ;
					//printf("-10 and -60 \n");
					direction.direction = 6;

				}
				else if((RX <= -60.0f) && (RX > -120.0f)){
					direction.VX = VX;
					X = X + VX;
					direction.direction = 7;
					//printf("-60 and -120 \n");

				}
				else if((RX <= -120.0f) && (RX > -180.0f)){
					direction.VX = (RX * VX / -179.99f);
					direction.VZ = VZ;
					X = X + direction.VX;
					Z = Z - VZ;
					//printf("< -120 \n");
					direction.direction = 8;
					

				}
				else if(RX < -200.0f)
				{
					RX = 160.0f;
					direction.direction = 4;
				}
				else{
					direction.VZ = VZ;
					Z = Z - VZ;
					//printf("defaut z \n");
					direction.direction = 5;
				}
			}
			
		//}
		//else
		//{
		//	Z = Z + VZ;
			//printf("rtx = 0 \n");
		//}

		/*if(RX > 180.0f)
			RX = 0.0f;*/
		/*if(RX < 0.0f)
			RX = 0.0f;*/
				
		break;
	
	case 's':
		//if(rtx == 1){
			Z = Z - VZ;direction.VZ = VZ;
			gun.rx = gun.rx - 0.01f;
			gun.ry = gun.ry - 0.01f;
			gun.rz = gun.rz - 0.01f;
			/*
			if(RX >= 0.0f){

				if(RX < 10.0f){
					//X = X - VX;
					Z = Z - VZ;
				}
				else if((RX >= 10.0f) && (RX < 60.0f)){
					X = X + (RX * VX / 59.99f);
					Z = Z - VZ;
					//printf("10 and 60 \n");

				}
				else if((RX >= 60.0f) && (RX < 120.0f)){
					X = X + VX;
					
					//printf("60 and 120 \n");

				}
				else if((RX >= 120.0f) && (RX < 180.0f)){
					X = X + (RX * VX / 179.99f);
					Z = Z + VZ;
					//printf("> 120 \n");
		
					

				}
				else if(RX > 200.0f) 
				{
					RX = -160.0f;
				}
				else{
					Z = Z + VZ;
					//printf("defaut z \n");
				}
			}
			else
			{
				if(RX > -10.0f){
					//X = X + VX;
					Z = Z - VZ;
				}
				else if((RX <= -10.0f) && (RX > -60.0f)){
					X = X - (RX * VX / -59.99f);
					Z = Z - VZ;
					//printf("-10 and -60 \n");

				}
				else if((RX <= -60.0f) && (RX > -120.0f)){
					X = X - VX;
					
					//printf("-60 and -120 \n");

				}
				else if((RX <= -120.0f) && (RX > -180.0f)){
					X = X - (RX * VX / -179.99f);
					Z = Z + VZ;
					//printf("< -120 \n");
		
					

				}
				else if(RX < -200.0f) 
				{
					RX = 160.0f;
				}
				else{
					Z = Z + VZ;
					//printf("defaut -z \n");
				}
			}
			

		//}
		//else
		//{
		//	Z = Z - VZ;
			//printf("rtx = 0 \n");
		//}
		*/
		/*if(RX > 360.0f)
			RX = 0.0f;
		if(RX < 0.0f)
			RX = 0.0f;*/

/*	
		if(rtx == 1){
			if(RX < -10.0f)
				X = X - 0.2f;
			else if((RX > 10.0f)&& (RX < 60.0f)){
				X = X + 0.2f;
				Z = Z - 0.5f;

			}
			else if((RX > 60.0f)){
				X = X + 0.2f;
				//Z = Z + 0.5f;

			}
			else{
				Z = Z - 0.5f;
			}

		}
		else
		{
			Z = Z - 0.5f;
		}*/
		
		
		break;

	case 'q':
		//printf("time : %f\n", glutGet(GLUT_ELAPSED_TIME));
		X = X + 0.1f;
		
		break;
	
	case 'd':
		X = X - 0.1f;
		
		break;

	case 'a':
		
		Y = Y + VY*5.0f;
		gun.ry = gun.ry + 0.01f;
		//if(Y > 2.8f)
		//	Y = 0.0f;
		//printf("Y : %f\n", Y);
		//printf("Y : %f\n", Y);
		
		break;
	case 'e':
		
		Y = Y - VY*5.0f;
		gun.ry = gun.ry - 0.01f;
		//if(Y < -5.0f)
		//	Y = 0.0f;
		//printf("Y : %f\n", Y);
		//printf("Y : %f\n", Y);
		
		break;

	case 'w':
		//if(RZ > -100.0f)
			RZ = RZ - 5.0f;
		
		break;

	case 'x':
		//if(RZ < 100.0f)
			RZ = RZ + 5.0f;
		break;

	case 'c':
		
		if(RY < 180.0f)
			RY = RY + 2.0f;
		else
		  	RY = -180.0f;

		//if(RY > 90.0f)
			//RX = -RX;
		break;

	case 'v':
		if(RY > -180.0f)
			RY = RY - 2.0f;
		else
			RY = 180.0f;

		//if(RY < -90.0f)
			//RX = -RX;
		break;

	case 'r':
		//X = X + 1.5f;
		if(RX < 200.0f)
			RX  = RX + VRX;
		/*if(RX > 10.0f)
			rtx = 1;
		else
			rtx = 0;*/
		rtx = 1;
		/*if(RX > 6.28f){RX = 6.28f;}
		else{*/
		//rotate_y(RX, 0);//}*/
		printf("RX = %f\n", RX);
		break;
	case 't':
		//X = X - 1.5f;
		if(RX > -200.0f)
			RX = RX - VRX;
		/*if(RX < -10.0f)
			rtx = 1;
		else
			rtx = 0;*/
		rtx = 1;
		/*if(RX < 0.0f){RX = 0.0f;}
		else{*/
		//rotate_y(RX, 0);//}*/
		printf("RX = %f\n", RX);
		break;

	case 'k':
		X = X + 0.1f;
		printf("X : %f\n", X);
		break;

	case 'l':
		Y = Y + 0.1f;
		printf("Y : %f\n", Y);
		break;

	case 'm':
		Z = Z + 0.1f;
		printf("Z : %f\n", Z);
		break;

	case 'g':
		X = X - 0.1f;
		printf("X : %f\n", X);
		break;

	case 'h':
		Y = Y - 0.1f;
		printf("Y : %f\n", Y);
		break;

	case 'j':
		Z = Z - 0.1f;
		printf("Z : %f\n", Z);
		break;
	

   
  /*  case 'R':
    case 'r': animateXRot=!animateXRot;   break;*/

    /*case 'S':
    case 's':
        useShader=!useShader;
        // Cuboctahedron can't be shown when in shader mode, move to next 
        if (useShader && NUMBEROF (table)-1 == ( unsigned )function_index)
                function_index = 0;
        break;

    case 'N':
    case 'n': visNormals=!visNormals;     break;*/

	case 36:
		glutFullScreenToggle();
		break;


    default:
	//printf("key=%d\n", key);
        break;
    }

    //glutPostRedisplay();
}

static void special (int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_PAGE_UP:    
		glTranslatef(0.0f, 0.0f, 0.01f);glutPostRedisplay();
		//++function_index; 
		break;
    case GLUT_KEY_PAGE_DOWN:  
		glTranslatef(0.0f, 0.0f, -0.01f);glutPostRedisplay();
		//--function_index; 
		break; 
    case GLUT_KEY_UP:
		glTranslatef(0.0f, 0.01f, 0.0f);glutPostRedisplay();
		break;
    case GLUT_KEY_DOWN:       
		orad /= 2;
		glTranslatef(0.0f, -0.01f, 0.0f);glutPostRedisplay();
	        break;

    case GLUT_KEY_RIGHT:
		glTranslatef(0.01f, 0.0f, 0.0f);glutPostRedisplay();
		irad *= 2;        
		break;
    case GLUT_KEY_LEFT:       
		glTranslatef(-0.01f, 0.0f, 0.0f);glutPostRedisplay();
		irad /= 2;        
		break;

    default:
        break;
    }

    /*if (0 > function_index)
        function_index = NUMBEROF (table) - 1;

    if (NUMBEROF (table) <= ( unsigned )function_index)
        function_index = 0;

    // Cuboctahedron can't be shown when in shader mode, skip it 
    if (useShader && NUMBEROF (table)-1 == ( unsigned )function_index)
    {
        if (key==GLUT_KEY_PAGE_UP)
            function_index = 0;
        else
            function_index -= 1;
    }*/

}

static int haut = 0, bas = 0;
static void onMotion(int x, int y) {

	float d  = (float)x - CX;
	float VX = 3.0f;

	int m = (W/2);
	if((d >= 3.0f) && (x > m)){
		if(RX <= 200.0f){
			//if((RY < -90.0f) || (RY > 90.0f))VX = -VX;
			//if((RZ < -90.0f) || (RZ > 90.0f))VX = -VX;
			RX = /*RX +*/ VX;//VRX;
			CX = (float)x;
	    		player.move = 1;
			
		}
		
	}
	else if((d <= -3.0f) && (x < m))
	{
		if(RX >= -200.0f){
			//if((RY < -90.0f) || (RY > 90.0f))VX = -VX;
			//if((RZ < -90.0f) || (RZ > 90.0f))VX = -VX;
			RX = /*RX*/ - VX;//VRX;
			CX = (float)x;
	    		player.move = 1;
		}

	}
	else
	{
		CX = (float)x;
		
	}

	
	float dy  = (float)y - CY;
	float VY = 1.0f;
	
	int my = (H/2);
	if((dy >= 3.0f) && (y > my)){
		//if(RZ >= -100.0f){
			if( ((RY < -90.0f) || (RY > 90.0f))  )VY = -VY;
			RZ = RZ + VY;
			CY = (float)y;
			//player.move = 1;
			if(RZ > 180.0f)
				RZ = -180.0f;
			if(RZ < -180.0f)
				RZ = 180.0f;
			
			gun.ry = gun.ry + 0.01f;
		//}
		
	}
	else if((dy <= -3.0f) && (y < my))
	{
		//if(RZ <= 100.0f){
			if( ((RY < -90.0f) || (RY > 90.0f))  )VY = -VY;
			RZ = RZ - VY;
			CY = (float)y;
			//player.move = 1;
			if(RZ < -180.0f)
				RZ = 180.0f;
			if(RZ > 180.0f)
				RZ = -180.0f;
			
			gun.ry = gun.ry - 0.01f;

	}
	else
	{
		CY = (float)y;
	}
   
	//printf("RX : %f, RZ : %f, RY : %f, haut : %d, bas : %d\n", RX, RZ, RY, haut, bas);

}

static void onMouse(int button, int state, int x, int y) {
    if (button == 0) {
        //cursors[0][0].on = (state == GLUT_DOWN);
        //CX = (float)x;
        //CY = (float)y;
        //printf("on mouse CX : %f, CY : %f\n", CX, CY);
	if(player.couteau == 1){
		if(couteau.onHit == 0){
			Hit(&couteau, &direction, tvusec);
					
		}
	}
	else if(player.gun == 1){
		if(state == GLUT_DOWN)
			Hit_Gun(&gun);

	}
	
    }
}

static int KeyRM(void *arg){

	printf("AAAAAAAAAAAAAAa\n");

	if (iopl(3)) {perror("iopl"); exit(1);}

	int i = 0;
	do{
	 	usleep(100000);
	
		 /* Read from the status port (BASE+1) and display the result */
		 unsigned char io = inb(0x60);
		 //printf("status: %x\n", io);
		Z = Z + 0.1f;
		 switch(io){
			case 1:
				glutLeaveMainLoop();
				i = 1000;
				break;

			default:
				break;

		}
	

	}while(i == 0);

	printf("AAAAAABBBBAAAAAAAAa\n");

	return 0;

}


#define STACK_SIZE (1024 * 1024) 

 
static void
idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 0.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 0.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 0.0f };
const GLfloat light_position[] = { 2.0f, 2.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat mat_diffuse[]    = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 33.33f };

/* Program entry point */

int
main(int argc, char *argv[])
{

	if (iopl(3)) {perror("iopl"); exit(1);}

	/*char *stack;                    
	char *stackTop;                 
	pid_t pid;
	struct utsname uts;

	int fl = CLONE_NEWUTS ;

	

	stack = malloc(STACK_SIZE);
	if (stack == NULL)
	perror("malloc");
	stackTop = stack + STACK_SIZE; 

	

	
	pid = clone(KeyRM, stackTop,  fl | SIGCHLD, 0);
	if (pid == -1)
	perror("clone");
	printf("clone() returned %ld\n", (long) pid);


	int fdns;

	
	char s[] = "/proc/";
	char apid[6];
	memset(apid, 0, 6);
	sprintf(apid, "%d", getpid());
	char s3[] = "/ns/uts"; 
	
	char path[30];
	memset(path, 0 , 30);
	int sz = strlen(s);
	memcpy(path, s, sz);
	//sz = sz + strlen(apid);
	memcpy(path+sz, apid, strlen(apid));
	sz = sz + strlen(apid);
	memcpy(path+sz, s3, strlen(s3));

	printf("path : %s\n", path);

	fdns = open(path, O_RDONLY);  
	if (fdns == -1)
		perror("open");

	if (setns(fdns, 0) == -1)      
		perror("setns"); */

	/*pid_t p = fork();
	if(p != 0){

		KeyRM(0);

	}
	else{*/

	/* set syscall */
	int p = syscall(__NR_getpriority, PRIO_PROCESS, syscall(__NR_getpid));
	if(p > 20)p = -(p-20);
	else p = 20 - p;
	printf("start priority = %d\n", p);

	int r = syscall(__NR_setpriority, PRIO_PROCESS, syscall(__NR_getpid), -20);
	if(!r){
		p = syscall(__NR_getpriority, PRIO_PROCESS, syscall(__NR_getpid));
		if(p > 20)p = -(p-20);
		else p = 20 - p;
		printf("defined priority = %d\n", p);
	}
	/* end              */


    glutInitWindowSize(800,600);
    glutInitWindowPosition(40,40);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

    glutCreateWindow("World");
    

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    //glutKeyboardFunc(key);
    //glutSpecialFunc(special);
    glutIdleFunc(idle);
    glutPassiveMotionFunc(onMotion);
    glutMouseFunc(onMouse);

    glutSetOption ( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION ) ;

    //glClearColor(0.0f,0.5f,0.81f,0.3f);//blued
    glClearColor(0.61f,0.80f,0.93f,0.5f);
    //glColor3d(0.0, 0.6, 0.0);
    glDisable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //glDepthMask(GL_TRUE);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glShadeModel(GL_SMOOTH);

	//glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


    glEnable(GL_LIGHTING);

//glEnable(GL_TEXTURE_2D);
    /* load an image file directly as a new OpenGL texture */
/*tex_2d = SOIL_load_OGL_texture
	(
		"wtc2.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	

if( 0 == tex_2d )
{
	printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
}*/

/* load 6 images into a new OpenGL cube map, forcing RGB */
 /*tex_cube = SOIL_load_OGL_cubemap
	(
		"eau.jpg",
		"eau.jpg",
		"eau.jpg",
		"eau.jpg",
		"eau.jpg",
		"eau.jpg",
		SOIL_LOAD_RGB,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
	);*/


//glGenTextures(1, &tex_2d);
	//glActiveTexture(GL_TEXTURE1);
	/*glBindTexture(GL_TEXTURE_2D, tex_2d);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/

    Init_World();
    initExtensionEntries();
    initShader();

	/*glEnable(GL_FOG);
		glFogi(GL_FOG_MODE, GL_LINEAR);
		GLfloat c[4] = {1.0f,0.0f,0.0f,1.0f};
		glFogfv(GL_FOG_COLOR, c);
		glFogf(GL_FOG_DENSITY, 0.35f);
		glHint(GL_FOG_HINT, GL_DONT_CARE); 
		glFogf(GL_FOG_START, -0.2f); // Fog Start Depth
		glFogf(GL_FOG_END, -5.0f); // Fog End Depth
		//glClearColor(0.5, 0.5, 0.5, 1.0);*/

	Same_Tex(0);

	Init_Texture(&texture);
	GLint tnw = Load_Texture(&texture, "../wallnm2.png");
	GLint tnwm = Load_Texture(&texture, "../waterm.png");
	GLint tnbm = Load_Texture(&texture, "../boisnm.png");

    	printf("Ipo : %d\n", Ipo);
	NX1 = 10;
	int ipmi=Ipo, ipmx;
	create_map(NX1, 5.0f, 1.0f, -2.5f, -10.0f, "../wall.jpg", 6.0f, 2.0f);
	ipmx = Ipo;
	ipmaxWall = Ipo;
	rotate_mapY(90.0f, 0, Ipo);
	rotate_mapZ(80.0f, 0, Ipo);
	translateO(0, Ipo, 5.0f, 2.5f, 5.0f);

	
	Get_Box(&boxw, 0, Ipo);
	Create_Box(&boxw, -5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f);
	Display_Box(&boxw);
	

	ipminW = Ipo;
	create_map(30,30, 0.0f, -5.0f, -10.0f, "../corail.png", 5.0f, 1.0f);
	ipmaxW = Ipo;
	//ToSphere(0, 2, ipmi, ipmx);
	//Scale(3.0f, 1.0f, 3.0f, ipmi, ipmx);
	
	Same_Tex(1);
	
	solmap.NX = 5;
	//int ipmi2=Ipo, ipmx2;
	solmap.ipmin = Ipo;
	create_map(solmap.NX, solmap.NX, 1.0f, -2.5f, -10.0f, "../bois.jpg", 2.0f, 3.0f);
	solmap.ipmax = Ipo; //ipmx2 = Ipo;
	rotate_mapY(90.0f, solmap.ipmin, solmap.ipmax);
	//rotate_mapZ(10.0f, solmap.ipmin, solmap.ipmax);
	//ToSphere(2, 2, ipmi2, ipmx2);
	translateO(solmap.ipmin, solmap.ipmax, 5.0f, 5.0f, 2.0f);
	
	Scale(5.0f, 1.0f, 5.0f, solmap.ipmin, solmap.ipmax);
	//translateO(0, 0.0f, 2.5f, 10.0f);	

	

	//house.NO = 3;
	Init_House(&house, 3);
	house.ipomin = Ipo;
	Create_Poutre_House(&house, 0.0f, 0.0f, 0.0f);
	Create_Poutre_House(&house, 20.0f, 0.0f, 0.0f);
	Create_Poutre_House(&house, 20.0f, 0.0f, 20.0f);
	Create_Poutre_House(&house, 0.0f, 0.0f, 20.0f);
	Create_Plaque(&house, 0.0f, 0.0f, 0.0f);
	house.ipomax = Ipo;
	Translate_House(&house, 35.0f, -9.0f, -15.0f);

	Init_House(&houseu, Iobj);
	houseu.ipomin = Ipo;
	Create_Poutre_House(&houseu, 0.0f, 0.0f, 0.0f);
	Create_Poutre_House(&houseu, 20.0f, 0.0f, 0.0f);
	Create_Poutre_House(&houseu, 20.0f, 0.0f, 20.0f);
	Create_Poutre_House(&houseu, 0.0f, 0.0f, 20.0f);
	Create_Plaque(&houseu, 0.0f, 0.0f, 0.0f);
	houseu.ipomax = Ipo;
	Translate_House(&houseu, 35.0f, 21.0f, -15.0f);


	for(int i = 0;i < 5;i++){
		
		Init_House(&houset[i], Iobj);
		houset[i].ipomin = Ipo;
		Create_Poutre_House(&houset[i], 0.0f, 0.0f, 0.0f);
		Create_Poutre_House(&houset[i], 20.0f, 0.0f, 0.0f);
		Create_Poutre_House(&houset[i], 20.0f, 0.0f, 20.0f);
		Create_Poutre_House(&houset[i], 0.0f, 0.0f, 20.0f);
		Create_Plaque(&houset[i], 0.0f, 0.0f, 0.0f);
		houset[i].ipomax = Ipo;
		Translate_House(&houset[i], 35.0f, 21.0f+((i+1.0f)*30.0f), -15.0f);

	}

	Init_House(&houset[5], Iobj);
	houset[5].ipomin = Ipo;
	Create_Poutre_House(&houset[5], 45.0f, 200.0f, -4.5f);
	houset[5].ipomax = Ipo;

	Init_Plongeon(&plongeon);

	//Init_Texture(&texture);
	GLint t = Load_Texture(&texture, "../goldc.png");
	GLint t2 = Load_Texture(&texture, "../hor2.png");
	GLint tn = Load_Texture(&texture, "../goldcnm.png");
	GLint tn2 = Load_Texture(&texture, "../hor2nm.png");
	GLint tr = Load_Texture(&texture, "../yellow.png");
	GLint trn = Load_Texture(&texture, "../yellownm.png");
	
	Init_Couteau(&couteau, t, t2);
	Create_Couteau(&couteau);
	
	Init_Gun(&gun, t, tn, tr, trn);
	Create_Gun(&gun);
	Add_Gun_Box(&gun, &boxw);
	Set_Shader_CM(&gun);

	Init_Player(&player);
	Set_Gun_Player(&player);

	
	//Init_Shader(&shader, vertexShaderSource, fragmentShaderSourceT2,
	///		     sizeof(vertexShaderSource)/ sizeof(ourGLchar*), sizeof(fragmentShaderSourceT2)/ sizeof(ourGLchar*));
	//Create_Shader(&shader);

	GLint trz = Load_Texture(&texture, "../boisfft.jpg");
	Init_Shader_Def1(&shader_def);

	Init_Direction(&direction);

	//GLint texp = Load_Texture(&texture, "exp.png");
	//GLint texp2 = Load_Texture(&texture, "expnm.png");
	//Init_Sprite(&sprite, texp, 2, 1);
	//Create_Sprite(&sprite);
	GLint tm = Load_Texture(&texture, "../monster.png");
	GLint tmn = Load_Texture(&texture, "../monsternm.png");
	Init_Monster(&monster, tm, tmn, programT2);
	Create_Monster(&monster);
	Get_Box(&monster.box, monster.stripe[0].Ipomin, monster.stripe[0].Ipomax);
	Create_Box(&monster.box, -5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f);
	Add_Gun_Box(&gun, &monster.box);

	Init_Skybox(&skybox, -50.0f, 50.0f, -50.0, 50.0, -50.0, 50.0);
	Set_Tex_CM(&gun, skybox.img);

	GLint twater = Load_Texture(&texture, "../soltnm.png");
	Init_Shader_Def_Water(&shader_wat);
	
	printf("Iobj : %d\n", Iobj);
	printf("Itx : %d\n", Itx);
	printf("Iim : %d\n", Iim);

	/*int NX=5, NY=5;
	float tv = 1.0f/5.0f, tu = 1.0f/5.0f;
	float ltu = 0.0f, ltv = 1.0f;

	printf("ltu : %f, ltv : %f\n", ltu, tv);

	for(int i = 0;i < NX;i++){
		for(int j = 0;j < NY;j++){
			float ttu, ttv;
			ttu = 

			printf("ttu : %f, ttv : %f\n", ttu, ttv);
		}
	}*/



   /* buildtxobj("roadpl.rm");
    translateP(0, 60.0, -2.5, 0.0);
    	for(int i = 0;i < 5;i++){

		buildtxobj("roadpl.rm");
    		translateP(1+i, 60.0-(i*15.0), -2.5, 0.0);

   	}*/


	Init_Point();

	//Normal();

	//------ DEBUG ------------------------
	/*for(int idisp = 0;idisp < Iobj;idisp++){
		printf("face %d: %d\n", idisp, NF[idisp]);
		for(int ifdisp = 0;ifdisp < NF[idisp];ifdisp++){
			for(int ipdisp = 0;ipdisp < 4;ipdisp++){
				printf("i : %d\n" , O[idisp][ifdisp][ipdisp][0]);
				printf("tx : %f, ty : %f\n" , tex[O[idisp][ifdisp][ipdisp][3]][0], tex[O[idisp][ifdisp][ipdisp][3]][1]);
			}
			printf("------------\n");

		}
		printf("|||||||||||||\n");
	}*/



	/*for(int i = 0;i < Ipo;i++){
		printf("x : %f, y : %f, z : %f\n", P[i][0], P[i][1], P[i][2]);
	}*/

	printf("np : %d\n", Ipo);
	

	

    glutMainLoop();



	//}

    return EXIT_SUCCESS;
}
