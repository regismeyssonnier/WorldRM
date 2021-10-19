const ourGLchar *VSHsrcDEF1[] = {
	"varying vec3 N;",
	"varying vec3 v;",
	//"varying vec3 v2;",
	"uniform vec3 position;",
	"varying vec4 pos;",
	"void main(void)",
	"{",
	"	gl_TexCoord[0] = gl_MultiTexCoord0;",
	"	v = vec3(gl_ModelViewMatrix * gl_Vertex);",
	//"	v = vec3(gl_ModelViewMatrix * gl_Vertex);",
	"	N = normalize(gl_NormalMatrix * gl_Normal);",
	"	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;",
	"	pos = gl_Vertex;",
	"}"




};

const ourGLchar *FSHsrcDEF1[] = {
	"varying vec4 pos;",
	"varying vec3 N;",
	"varying vec3 v;",
	"uniform vec3 u_res;",
	"uniform sampler2D myTexture;",
	"uniform sampler2D nmap;",
	//"uniform sampler2D noise;",
	"uniform vec3 iswater;",
	"uniform vec3 fgreen;",
	"void main(void)",
	"{",
	"	vec2 uv = gl_FragCoord.xy / vec2(u_res.x, u_res.y);",
	"	uv.y -= 0.2;uv.x-=0.5;",
	"	vec4 vn = texture2D(nmap, gl_TexCoord[0].xy );",
	
	"	vec3 L = normalize(gl_LightSource[0].position.xyz - v);",   
	"	vec3 E = normalize(-v); /* -v we are in Eye Coordinates, so EyePos is (0,0,0)*/",  
"		vec3 R = normalize(-reflect(L,N));",  
	"	vec3 red = vec3(1.0, 0.0, 0.0);",
	//"	uv /= vec2((u_res.y / u_res.x)*2.0, (u_res.y / u_res.x)*2.0);",
	//"	vec4 vt = texture2D(myTexture, gl_TexCoord[0].xy);",
	//"	vec4 vno = texture2D(noise, gl_TexCoord[0].xy  );",
	"	vec4 vt = texture2D(myTexture, gl_TexCoord[0].xy + 0.5*(E.xy* (0.04*( vec2(vn.r-vn.g, vn.r-vn.g) )) ) );",
	"	if(iswater.x == 1.0){vt.r = vt.r - vt.b;vt.g = vt.g - vt.b/fgreen.g;vt.b = vt.b - (vt.r-vt.g);}",
	//"	vec3 col = vec3(5.0*cos((uv.x*vt.r)*3.1415/2.0) * sin((uv.x)*3.1415), uv.y*vt.g, 5.0*cos((uv.y*vt.b)*3.1415/2.0) * sin((uv.y*vt.b)*3.1415));",
	"	vec4 col = vt * (2.1*mod(vec4(sin(atan(uv.y/uv.x)), cos(atan(uv.y/uv.x)), atan(uv.y/uv.x), 1.0), R.y));",
	//"	vec4 col;",
	"	col.r += atan(uv.x/uv.y)/3.14;col.r = clamp(mod(smoothstep(col.r, vt.r, 2.0)*3.14, (0.7)), 0.5, 1.0);",
	"	col.g += 1.0 / length(uv) *0.2;col.g = mod(col.g*2.0, (0.5)) + vt.g;",
	"	col.b += mod(col.b*2.01, 0.2) + vt.b*0.01;",
	"	col.a += vt.a;", 
	"	col = mix(col, vec4(1.0, 1.0, 0.0, 0.0), vec4(0.1, 0.1, 0.2, 0.0));", 
	//"       col = smoothstep(col, vec4(0.0, 0.1, 0.0, 0.0), sin(vno));",
	"	clamp(col, 0.0, 1.0);",
	"	vec4 colf = mix(col, gl_FrontLightModelProduct.sceneColor, vec4(1.0, 1.0, 0.0, 1.0));",
	
	//"	if(gl_FragColor.x > 100.0)gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);",
	//"	else gl_FragColor = vec4(1.0, 1.0, 0.0, 0.0);",
	"	gl_FragColor = col;",
	"}"




};


const ourGLchar *FSHsrcDEF2[] = {
	"varying vec4 pos;",
	"varying vec3 N;",
	"varying vec3 v;",
	"uniform vec3 u_res;",
	"uniform sampler2D myTexture;",
	"uniform sampler2D nmap;",
	"uniform sampler2D noise;",
	"uniform vec3 iswater;",
	"uniform vec3 fgreen;",
	"void main(void)",
	"{",
	"	vec2 uv = gl_FragCoord.xy / vec2(u_res.x, u_res.y);",
	"	uv.y -= 0.1;uv.x-=0.5;",
	"	vec4 vn = texture2D(nmap, gl_TexCoord[0].xy );",
	
	"	vec3 L = normalize(gl_LightSource[0].position.xyz - v);",   
	"	vec3 E = normalize(-v); /* -v we are in Eye Coordinates, so EyePos is (0,0,0)*/",  
"		vec3 R = normalize(-reflect(L,N));",  
	"	vec3 red = vec3(1.0, 0.0, 0.0);",
	//"	uv /= vec2((u_res.y / u_res.x)*2.0, (u_res.y / u_res.x)*2.0);",
	//"	vec4 vt = texture2D(myTexture, gl_TexCoord[0].xy);",
	"	vec4 vno = texture2D(noise, gl_TexCoord[0].xy  );",
	"	vec4 vt = texture2D(myTexture, gl_TexCoord[0].xy + 0.5*(E.xy* (0.04*( vec2(vn.r-vn.g, vn.r-vn.g) )) ) );",
	"	if(iswater.x == 1.0){vt.r = vt.r - vt.b;vt.g = vt.g - vt.b/fgreen.g;vt.b = vt.b - (vt.r-vt.g);}",
	//"	vec3 col = vec3(5.0*cos((uv.x*vt.r)*3.1415/2.0) * sin((uv.x)*3.1415), uv.y*vt.g, 5.0*cos((uv.y*vt.b)*3.1415/2.0) * sin((uv.y*vt.b)*3.1415));",
	//"	vec4 col = vt * (2.1*mod(vec4(sin(atan(uv.y/uv.x)), cos(atan(uv.y/uv.x)), atan(uv.y/uv.x), 1.0), R.y));",
	"	vec4 col;",
	"	col.r = atan(uv.x/uv.y)/3.14;col.r +=smoothstep(col.r, vt.r, 0.5);",
	"	col.g = 1.0 / length(uv)*0.2 ;col.g+=smoothstep(col.g, vt.g, 0.1);",
	"	col.b = vt.b;",
	"	col.a = vt.a;", 
	//"	col = mix(col, vec4(1.0, 1.0, 0.0, 0.0), vec4(0.1, 0.1, 0.2, 0.0));", 
	//"       col += mix(col, vec4(0.0, 0.1, 0.0, 0.0), sin(vno));",
	"	clamp(col, 0.0, 1.0);",
	
	//"	if(gl_FragColor.x > 100.0)gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);",
	//"	else gl_FragColor = vec4(1.0, 1.0, 0.0, 0.0);",
	"	gl_FragColor = col;",
	"}"




};


const ourGLchar *FSHsrcDEF3[] = {
	"varying vec4 pos;",
	"varying vec3 N;",
	"varying vec3 v;",
	"uniform vec3 u_res;",
	"uniform sampler2D myTexture;",
	"uniform sampler2D nmap;",
	"uniform sampler2D noise;",
	"uniform vec3 iswater;",
	"uniform vec3 fgreen;",
	"void main(void)",
	"{",
	"	vec2 uv = gl_FragCoord.xy / vec2(u_res.x, u_res.y);",
	"	uv.y -= 0.1;uv.x-=0.5;",
	"	vec4 vn = texture2D(nmap, gl_TexCoord[0].xy );",
	
	"	vec3 L = normalize(gl_LightSource[0].position.xyz - v);",   
	"	vec3 E = normalize(-v); /* -v we are in Eye Coordinates, so EyePos is (0,0,0)*/",  
"		vec3 R = normalize(-reflect(L,N));",  
	"	vec3 red = vec3(1.0, 0.0, 0.0);",
	//"	uv /= vec2((u_res.y / u_res.x)*2.0, (u_res.y / u_res.x)*2.0);",
	//"	vec4 vt = texture2D(myTexture, gl_TexCoord[0].xy);",
	"	vec4 vno = texture2D(noise, gl_TexCoord[0].xy  );",
	"	vec4 vt = texture2D(myTexture, gl_TexCoord[0].xy + 0.5*(E.xy* (0.04*( vec2(vn.r-vn.g, vn.r-vn.g) )) ) );",
	"	if(iswater.x == 1.0){vt.r = vt.r - vt.b;vt.g = vt.g - vt.b/fgreen.g;vt.b = vt.b - (vt.r-vt.g);}",
	//"	vec3 col = vec3(5.0*cos((uv.x*vt.r)*3.1415/2.0) * sin((uv.x)*3.1415), uv.y*vt.g, 5.0*cos((uv.y*vt.b)*3.1415/2.0) * sin((uv.y*vt.b)*3.1415));",
	//"	vec4 col = vt * (2.1*mod(vec4(sin(atan(uv.y/uv.x)), cos(atan(uv.y/uv.x)), atan(uv.y/uv.x), 1.0), R.y));",
	"	vec4 col;",
	//"	col.r = atan(uv.x/uv.y)/3.14;col.r +=smoothstep(col.r, vt.r, 0.5);",
	//"	col.g = 1.0 / length(uv)*0.2 ;col.g+=smoothstep(col.g, vt.g, 0.1);",
	//"	col.b = vt.b;",
	//"	col.a = vt.a;", 
	//"	col = mix(col, vec4(1.0, 1.0, 0.0, 0.0), vec4(0.1, 0.1, 0.2, 0.0));", 
	//"       col += mix(col, vec4(0.0, 0.1, 0.0, 0.0), sin(vno));",
	//"	col = vec4",
	"	vec4 s = vec4(atan(uv.x/uv.y)/3.14, 1.0 / length(uv)*0.5, 0.0, 0.0);",
	"	s *= vec4(E.xyz, 1.0);",
	//"	s *= mix(s, vec4(1.0, 1.0, 0.0, 0.0), vec4(1.0, 0.0, 0.0, 0.0));",
	//"	s += vec4(5.0, 0.0, 0.0, 0.0);normalize(s);",
	//"	clamp(s, 0.0, 1.0);",
	"	vec2 p = vec2( 5.0*sin(atan(uv.x/uv.y))*cos(atan(uv.x/uv.y)), 5.0*cos(atan(uv.x/uv.y))*cos(atan(uv.x/uv.y)) );",
	"	p *= 1.0 / length(uv)*0.2;",
	"	col = texture2D(myTexture, p.xy+ 0.5*(E.xy* (0.04*( vec2(vn.r-vn.g, vn.r-vn.g) )) ) );",
	"	col *= mix(col, vec4(1.0, 0.0, 0.0, 0.0), vec4(0.2, 0.2, 1.0, 0.0));",
	"	col = col +vt  ;",
	"	col *= mix(col, vt, exp(pow(s*vno, vec4(5.0,5.0,5.0,5.0))));",
	//"	clamp(col, 0.0, 1.0);",
	
	//"	if(gl_FragColor.x > 100.0)gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);",
	//"	else gl_FragColor = vec4(1.0, 1.0, 0.0, 0.0);",
	"	gl_FragColor = col;",
	"}"




};


const ourGLchar *FSHsrcDEF4[] = {
	"uniform vec3 position;",
	"varying vec3 N;",
	"varying vec3 v;",
	"uniform vec3 u_res;",
	"uniform sampler2D myTexture;",
	"uniform sampler2D nmap;",
	"uniform sampler2D noise;",
	"uniform vec3 iswater;",
	"uniform vec3 fgreen;",
	"uniform vec3 ftime;",

	"float sphere(vec2 v){",
	"	return length(v);",
	"}",

	"float sphere3(vec3 v){",
	"	return length(v) -1.0;",
	"}",

	"float lineV(vec2 v, float va, float w){",
	"	if((v.x >= va)&&(v.x <= (va+w)))return 1.0;",
	"	return 0.0;",
	"}",

	"float lineH(vec2 v, float va, float h){",
	"	if((v.y >= va)&&(v.y <= (va+h)))return 1.0;",
	"	return 0.0;",
	"}",

	"float quads(vec2 v, vec2 va, vec2 hw){",
	"	if( (v.x >= va.x)&&(v.x <= (va.x+hw.x)) && (v.y >= va.y) && (v.y <= (va.y+hw.y)) )return 1.0;",
	"	return 0.0;",
	"}",

	"vec4 circle(vec2 uv, float w){",
	//"	if((uv.x == cc.x) && (uv.y == cc.y)){",
	"	return vec4(atan(uv.x/uv.y)/3.14, 1.0 / length(uv)*w, 0.0, 0.0);",
	//"	else {return vec4(1.0, 1.0, 1.0, 1.0);}",
	"}",

	

	"float smooth_edge(float c, float t, float pct){",
	"	return smoothstep(c, t, pct);",
	"}",

	// Plot a line on Y using a value between 0.0-1.0
	"float plot(vec2 st, float pct){",
	"  return  smoothstep( pct-0.02, pct, st.y) -",
	"	  smoothstep( pct, pct+0.02, st.y);",
	"}",

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


	"void main(void)",
	"{",
	"	vec2 uv = gl_FragCoord.xy / vec2(u_res.x, u_res.y);",
	"	vec2 uv2 = vec2(uv.xy);",
	"	uv.y -= 0.1;uv.x-=0.5;",
	"	vec4 vn = texture2D(nmap, gl_TexCoord[0].xy );",
	
	"	vec3 L = normalize(gl_LightSource[0].position.xyz - v);",   
	"	vec3 E = normalize(-v); /* -v we are in Eye Coordinates, so EyePos is (0,0,0)*/",  
"		vec3 R = normalize(-reflect(L,N));",  
	"	vec3 red = vec3(1.0, 0.0, 0.0);",
	"	vec4 vno = texture2D(noise, gl_TexCoord[0].xy  );",
	"	vec4 vt = texture2D(myTexture, gl_TexCoord[0].xy + 0.5*(E.xy* (0.04*( vec2(vn.r-vn.g, vn.r-vn.g) )) ) );",
	"	if(iswater.x == 1.0){vt.r = vt.r - vt.b;vt.g = vt.g - vt.b/fgreen.g;vt.b = vt.b - (vt.r-vt.g);}",
	"	vec4 col=vec4(1.0,1.0,1.0,1.0);",

	

	
	"		col *= mix(col, vec4(1.0, 0.0, 0.0, 0.0), vec4(0.2, 0.2, 1.0, 0.0));",

	"	float dst = length(position);",
	"	if(dst < 50.0){",


	"	col += vt;",
	"	float p = 0.22;",
	"	for(int i = 0;i < 10;i++){",
	"		vec2 lc = vec2(uv2.x - p, uv2.y - 0.0);",
	"		vec4 clc = circle(lc, 0.8);",	
	//"		if((uv2.x >=0.1) && (uv2.x <= 0.6)  &&  (uv2.y >=0.6) && (uv2.y <= 0.7)){",	
	"			col += clc*vno;",
	//"		}",
	"		p += 0.05;",
	"	}",
	

	/*
	"	if(sphere(uv) < 0.2){",
	"		col = vec4(1.0, 0.0, 0.0, 0.0);",
	
	"	}",
	"	else{",
	"		if(sphere(uv) < 0.3){",
	"			col.r *= smooth_edge(col.r, vt.r, 0.5);",
	"			col.g *= smooth_edge(col.g, vt.g, 0.1);",
	"			col.b = vt.b;",
	"		}else",
	"		col *= mix(col, vec4(1.0, 0.0, 0.0, 0.0), vec4(0.2, 0.2, 1.0, 0.0));",
	//"		col = vec4(1.0, 1.0, 0.0, 0.0);",
	"	}",
	"	if(lineV(uv, 0.1, 0.05) == 1.0){",
	"		col = vec4(0.0, 1.0, 0.0, 0.0);",
	"	}",
	"	if(lineH(uv, 0.2, 0.01) == 1.0){",
	"		col = vec4(0.0, 1.0, 1.0, 0.0);",
	"	}",
	"	vec2 vaq = vec2(0.1, 0.3);vec2 hwq = vec2(0.06, 0.06);",
	"	if(quads(uv2, vaq, hwq) == 1.0){",
	"		col = vec4(0.0, 0.0, 1.0, 0.0);",
	"	}",
	
	*/

	"	vec2 cer = vec2(uv2.x - 0.1, uv2.y - 0.6);",
	"	vec2 cer2 = vec2(uv2.x - 0.2, uv2.y - 0.6);",
		

	"	col += vt*1.1;",
	"	float ry;",
	"	if(ftime.x == 1.0){  ry = ftime.y * 0.5 / 2000000.0; } else { ry = 0.2; }",
	"	vec4 s = vec4(atan(cer.x/cer.y)/3.14, 1.0 / length(cer)*ry, 0.0, 0.0);",
	"	col *= mix(col, vt, exp(pow(s*vno, vec4(5.0,5.0,5.0,5.0))));",
	
	//"	col += smoothstep(col, vec4(1.0, 0.0, 1.0, 0.0), ce *  vec4(1.0,0.0,0.0,0.0));",
	
	"	if( sphere(cer2.xy*R.xy)  < 0.3){col *= smoothstep(col, vt/*vec4(1.0, 1.0, 1.0, 0.0)*/, vec4(0.5, 0.5, 1.0, 1.0));}",
	

	//"	col *= smoothstep(col, vt+vec4(fbm(uv2*3.0)), vec4(0.5, 0.5, 1.0, 1.0));",
	//"	float y = sin(uv.x);",
	//"	vec4 color = vec4(0.0,y,0.0,0.0);",
		// Plot a line
	//"	float pct = plot(uv2,y);",
	//"	col *= (1.0-pct)*color+pct*vec4(0.0,1.0,0.0,0.0);",
	
	//"	col *= smoothstep(col, vt*vec4(1.0, 1.0, 0.0, 0.0), vec4(0.5, 0.5, 1.0, 0.0));",

	"	}",
	"	gl_FragColor = col;",
	"}"




};


const ourGLchar *FSHsrcDEFSky[] = {

	"uniform samplerCube skybox;",

	"void main(void)",
	"{",
	"	gl_FragColor = textureCube(skybox, gl_TexCoord[0].xyz);",	
	"}"

};


const ourGLchar *FSHsrcDEFGun[] = {

	"varying vec3 N;",
	"varying vec3 v;",
	"uniform vec3 position;",
	"varying vec4 pos;",
	"uniform samplerCube skybox;",
	"uniform sampler2D myTexture;",
	"uniform sampler2D nmap;",

	"void main(void)",
	"{",
	"	vec3 L = normalize(gl_LightSource[0].position.xyz - v);",   
	"	vec3 E = normalize(position-pos.xyz); /* -v we are in Eye Coordinates, so EyePos is (0,0,0)*/", 
	"   	vec4 vn = normalize(texture2D(nmap, gl_TexCoord[0].xy).rgba*2.0-1.0);", 
	"	vec3 R = normalize(-reflect(E,N));", 
	"	vec3 F = normalize(refract(E,vn.rgb, 0.5));", 
	//"	vec4 vn = texture2D(nmap, gl_TexCoord[0].xy );",
	//"   	vec4 vn = normalize(texture2D(nmap, gl_TexCoord[0].xy).rgba*2.0-1.0);",
	//"	vec4 vno = normalize(vec4(vn.r*2.0-1.0, vn.b, vn.g * 2.0 - 1.0, 0.0));",
	//"	clamp(vn, 0.5, 1.0);",
	//"	vec4 vt = texture2D(myTexture, gl_TexCoord[0].xy + 0.5*(E.xy* (0.04*( vec2(vn.r-vn.g, vn.r-vn.g) )) ) );",
	"	vec2 tx = normalize(F.xy + R.xy + (E.xy*0.02* vec2(vn.r-vn.g, vn.r-vn.g)));",
	"   	vec4 vt = texture2D(myTexture, tx  );",
	"	vec4 TR = textureCube(skybox, R.xyz);",
	//"	vec4 TF = textureCube(skybox, F.xyz);",
	//"	vt *= mix(TR, TF, 0.5);",
	"	gl_FragColor = mix(vt, TR, 0.5);",
	//"	gl_FragColor = mix(vt, mix(TR, TF, 0.5), 0.5);",	
	"}"

};

const ourGLchar *FSHsrcDEFWater[] = {

	"varying vec3 N;",
	"varying vec3 v;",
	"uniform vec3 position;",
	"varying vec4 pos;",
	"uniform samplerCube skybox;",
	"uniform sampler2D myTexture;",
	"uniform sampler2D nmap;",
	"uniform sampler2D noise;",
	"uniform vec3 iswater;",
	"uniform vec3 fgreen;",
	"uniform vec3 isshin;",
	"uniform vec3 fblue;",
	"uniform vec3 touch;",
	"uniform vec3 u_res;",
	"uniform vec3 ftime;",

	"void main(void)",
	"{",
	"  	vec3 L = normalize(/*gl_LightSource[0].position.xyz*/vec3(0.0, 10.0, 10.0) );", 
	" 	vec3 E = normalize(-v); /* -v we are in Eye Coordinates, so EyePos is (0,0,0)*/",  
	"	vec3 No = N * 0.5;",
	"   	vec3 R = normalize(-reflect(L,No));",  
	//"   	vec3 R = normalize(refract(L,N, 0.75));", 
	"   	vec4 vn = normalize(texture2D(nmap, (gl_TexCoord[0].xy+ftime.y * 0.03 / 500000.0)).rgba*2.0-1.0);",
	"   	vec4 vn2 = normalize(texture2D(noise, (gl_TexCoord[0].xy+ftime.y * 0.03 / 500000.0)).rgba*2.0-1.0);",
	//"	vt = vec4(0.0, 0.2, 0.3, 0.0)+vec4((E.xy*(2.02*vec2(vn.r-vn.g, vn.r-vn.g))), vn.b, 0.0);",
	"   	vec4 vt = texture2D(myTexture, gl_TexCoord[0].xy +  (E.xy*(0.18*vec2(vn.r-vn.g, vn.r-vn.g))) );",
	"   	vec4 vt2 = texture2D(myTexture, gl_TexCoord[0].xy +  (E.xy*(0.18*vec2(vn2.r-vn2.g, vn2.r-vn2.g))) );",
	//"   	vec3 R1 = normalize(-reflect(L,vn.rgb));",
	//"   	vec3 R2 = normalize(-reflect(L,vn2.rgb));",
	//"   	R = mix(R1, R2, 0.5);",
	"	vt = mix(vt, vt2, vec4(0.5));",
	//" 	vt += pow(dot(R1,E), 200.0);",//max(dot(R,E),0.0)
	//"	vec3 normal = normalize(vec3( vn2.rgb-vn.rgb));",
	//" 	vt += pow(dot(R,E), 50.0);"
	"	vt += max(dot(No,L), 0.0);",
	"       vt.r = vt.r - vt.b;vt.g = vt.g - vt.b/fgreen.g;",
	"	if(fblue.x == 1.0){ vt.b = fblue.b;}else {vt.b = vt.b - (vt.r-vt.g);}",
	"	gl_FragColor = vt;",//mix(vt, vec4(0.5, 1.5, 1.0, 0.0), 0.2);",

	"}"

};


static void Init_Shader_Def1(Shader *s){

	Init_Shader(s, VSHsrcDEF1, FSHsrcDEF4, sizeof(VSHsrcDEF1)/ sizeof(ourGLchar*), sizeof(FSHsrcDEF4)/ sizeof(ourGLchar*));
	Create_Shader(s);

}

static void Init_Shader_Def_Skybox(Shader *s){

	Init_Shader(s, VSHsrcDEF1, FSHsrcDEFSky, sizeof(VSHsrcDEF1)/ sizeof(ourGLchar*), sizeof(FSHsrcDEFSky)/ sizeof(ourGLchar*));
	Create_Shader(s);

}

static void Init_Shader_Def_Gun(Shader *s){

	Init_Shader(s, VSHsrcDEF1, FSHsrcDEFGun, sizeof(VSHsrcDEF1)/ sizeof(ourGLchar*), sizeof(FSHsrcDEFGun)/ sizeof(ourGLchar*));
	Create_Shader(s);

}

static void Init_Shader_Def_Water(Shader *s){

	Init_Shader(s, VSHsrcDEF1, FSHsrcDEFWater, sizeof(VSHsrcDEF1)/ sizeof(ourGLchar*), sizeof(FSHsrcDEFWater)/ sizeof(ourGLchar*));
	Create_Shader(s);

}
