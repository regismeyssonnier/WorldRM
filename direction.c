static struct _Direction{

	int direction;
	float VX;
	float VY;
	float VZ;


}__Direction;


typedef struct _Direction Direction;



static void Init_Direction(Direction *d){


	d->direction = -1;
	d->VX = 0.1f;
	d->VY = 0.1f;
	d->VZ = 0.1f;

}
