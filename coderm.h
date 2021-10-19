#define MAX_OBJ 1000
#define MAX_P 20000
static float P[MAX_P][3];
static int Ipo  = 0;
static float N[MAX_P][3];
#define MAX_C 30
static int Ico  = 0;
static int Ind  = 0;
static int I[MAX_P];
static float C[MAX_C][3];
#define MAX_FACE 20000
static int O[MAX_OBJ][MAX_FACE][4][5];
static int NF[MAX_OBJ];
static int Iobj  = 0;
static int MAX_F = 10;
static float tex[20000][2];
static int Itx = 0;
#define MAX_IM 200
static GLuint im[MAX_IM];
static int Iim = 0;
static GLint texb;
static void L(float r, float g, float b){
C[Ico][0]=r;
C[Ico][1]=g;
C[Ico][2]=b;
Ico=Ico+1;
}
static void B(float x, float y, float z, float nx, float ny, float nz){P[Ipo][0]=x;
P[Ipo][1]=y;
P[Ipo][2]=z;
N[Ipo][0]=nx;
N[Ipo][1]=ny;
N[Ipo][2]=nz;
}
static void A(int ifc, int ip, int ipt, int inx, int ic){
O[Iobj][ifc][ip][0]=ipt;
O[Iobj][ifc][ip][1]=inx;
O[Iobj][ifc][ip][2]=ic;
}
static void Init_World(){
tex[0][0] = 0;
tex[0][1] = 1;
tex[1][0] = 0;
tex[1][1] = 0;
tex[2][0] = 1;
tex[2][1] = 0;
tex[3][0] = 1;
tex[3][1] = 1;
L(1.0,0.0,0.0);
L(0.0,1.0,0.0);
L(0.0,0.0,1.0);
L(1.0,1.0,0.0);
L(0.0,1.0,1.0);
L(1.0,0.0,1.0);
L(1.0,1.0,1.0);
L(0.0,0.0,0.0);
/*I[Ind]=Ipo;
B(-0.25,0.25,0.25,-1.0,1.0,1.0);
Ipo=Ipo+1;
B(-0.25,-0.25,0.25,-1.0,-1.0,1.0);
Ipo=Ipo+1;
B(0.25,-0.25,0.25,1.0,-1.0,1.0);
Ipo=Ipo+1;
B(0.25,0.25,0.25,1.0,1.0,1.0);
Ipo=Ipo+1;
B(0.25,0.25,-0.25,1.0,1.0,-1.0);
Ipo=Ipo+1;
B(0.25,-0.25,-0.25,1.0,-1.0,-1.0);
Ipo=Ipo+1;
B(-0.25,-0.25,-0.25,-1.0,-1.0,-1.0);
Ipo=Ipo+1;
B(-0.25,0.25,-0.25,-1.0,1.0,-1.0);
Ipo=Ipo+1;
//front
A(0,0,I[Ind]+0,I[Ind]+0,0);
A(0,1,I[Ind]+1,I[Ind]+1,0);
A(0,2,I[Ind]+2,I[Ind]+2,0);
A(0,3,I[Ind]+3,I[Ind]+3,0);
//back
A(1,0,I[Ind]+4,I[Ind]+4,1);
A(1,1,I[Ind]+5,I[Ind]+5,1);
A(1,2,I[Ind]+6,I[Ind]+6,1);
A(1,3,I[Ind]+7,I[Ind]+7,1);
//up
A(2,0,I[Ind]+7,I[Ind]+7,2);
A(2,1,I[Ind]+0,I[Ind]+0,2);
A(2,2,I[Ind]+3,I[Ind]+3,2);
A(2,3,I[Ind]+4,I[Ind]+4,2);
//down
A(3,0,I[Ind]+5,I[Ind]+5,3);
A(3,1,I[Ind]+2,I[Ind]+2,3);
A(3,2,I[Ind]+1,I[Ind]+1,3);
A(3,3,I[Ind]+6,I[Ind]+6,3);
//left
A(4,0,I[Ind]+7,I[Ind]+7,4);
A(4,1,I[Ind]+6,I[Ind]+6,4);
A(4,2,I[Ind]+1,I[Ind]+1,4);
A(4,3,I[Ind]+0,I[Ind]+0,4);
//right
A(5,0,I[Ind]+3,I[Ind]+3,5);
A(5,1,I[Ind]+2,I[Ind]+2,5);
A(5,2,I[Ind]+5,I[Ind]+5,5);
A(5,3,I[Ind]+4,I[Ind]+4,5);
Ind=Ind+1;
NF[Iobj] = 6;
Iobj = Iobj + 1;*/
printf("Iobj = %d\n", Iobj);
printf("Iobj = %d\n", Iobj);}
