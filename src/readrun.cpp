#include "animat.h"



#define TIMEEVAL 10000
#define PRELIMTIME 1000

//static double *trunkpos;
double XRef;
void initScene2();
Animat Ani1;
int i;
double *Apos, *Bpos, dist1, dist2, bestdist1, bestdist2, result;
dReal oldPos[3];
dReal newPos[3];

void simLoop2 (int pause)
{
    simLoop(pause);

    const dReal *pos = dBodyGetPosition(Ani1.limbs[0].id);
    newPos[0] = pos[0];
    newPos[1] = pos[1];
    newPos[2] = pos[2];
    dsDrawLine(oldPos, newPos);

    if (tot_time == TIMEEVAL) {
            tot_time = 0;

            dReal result = 0.0f;
            for (int i = 0; i < 3; i++) {
                result += (oldPos[i] - newPos[i]) * (oldPos[i] - newPos[i]);
            }
            myprintf("\nResult: %f\n", result);

            Ani1.remove();
            resetScene();
            Ani1.generate(0, 0, 0);
            //Ani1.setImmunityTimer(PRELIMTIME);
            Ani1.pushBehindXVert(0);
    }
}

void initScene2()
{
    initWorld();
    fn.step = &simLoop2;
}

int main (int argc, char **argv)
{

    if (argc != 2) {
        fprintf(stderr, "usage: readrun <file.dat>\n");
        return 2;
    }
    tot_time = 0;
    
    //CORRIDOR = 1;
    OUTPUTREDIRECT = TOSTDOUT;
    WORLDTYPE = FLATWORLD;
    BALL = 0;
    initScene2();
    Ani1.read(argv[1]);
 
    VISUAL = 1;
    
    
    /*for (int i=0; i < MAXGENES; i++)
      for (int j=0; j < MAXNEUR; j++)
      for (int k=0; k < MAXCONFROM; k++)
      Ani1.genome[i].neurons[j].confrom[k].reftype = REFBOTH;*/

    resetScene();

    Ani1.generate(0, 0, 0);
    Ani1.setImmunityTimer(PRELIMTIME);
    Ani1.displayRepres();
	Ani1.pushBehindXVert(0);

    const dReal *pos = dBodyGetPosition(Ani1.limbs[0].id);
    oldPos[0] = pos[0];
    oldPos[1] = pos[1];
    oldPos[2] = pos[2];

    
    printf("OK\n");
    dsSimulationLoop (argc,argv,352,288,&fn);
    destroyWorld();
    return 0;
}
