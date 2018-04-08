/* Genetic algorithm test */

#include <iostream>
#include <thread>
#include "../GeneticAlg/gga.h"
#include "GeneticTest.h"
#include "rget.h"

using namespace std;

/*
extern unsigned int paramcount;   //number of parameters per gene
extern unsigned int genecount;  //number of genes to be tested
extern unsigned int parents;    //total number of parents to keep after a die off
extern unsigned int lparents;   //total number of randomly selected low score parents to keep after die off
extern unsigned int muteper;    //total mutation percentage per generation, NOT YET IMPLIMINTED
extern unsigned int children;   //total number of children per parent group
//unsigned int paramount;  //number of parents to mix per generation, NOT YET IMPLIMINTED
extern unsigned int rbox;
extern unsigned int rboxpoint; //pointer to start random numbers
extern unsigned int highscore; //the highest score, do not right to!

extern int * gene;   [genecount,paramcount]  //genes to be tested
extern int * score;  [genecount]  //scores pertaining to the genes to be tested
extern unsigned int * randombox; //box of random numbers to use for mix
*/

#define width 255
#define height 255
#define ballraid 4

#define boards 30

int xpos[boards][200];
int ypos[boards][200];

int xbpos[boards][1000];
int ybpos[boards][1000];

int printmes = 0;

int ballDifficulty = 250;
int bdiff = 0;


void copyto(void);
void copyfrom(void);
void boardsim(void);

int main()
{
    paramcount = 400; //Number of parameters per Gene.
    genecount = boards; //Number of Genes.
    parents = 10; //Total number of parents to keep.
    lparents = 1; //Number of low scoreing parents to keep.
    children = 2; //Number of children per parent pair.
    rbox = 20000; //Number of random numbers in randombox. Randombox must be filled with random numbers manualy!
    rboxpoint = 2; //Starting point for randombox.
    muteper = 800; //Number of Total parameters to "mutate".
    paramgroup = 2; //Groups of Gene Parameters
    maxrnum = 255; //Max output number of bits. This gets &ed with the final results.

    /* Create Genetic class for test
     This also initalizes the arrays that use the above info. */
    combine gtest1;

    /* Create Simulation Classes */

    rfileget(); //get the random numbers out of file and into randombox.

    int cycles = 0;
    int i = 0;
    int d = 0;

    //Fill the boards with random pins with info from randombox.
    cout << "Making pins \n";
    while (i < genecount) //20 boards
    {
        d = 0;
        while (d < 200) //200 pins per board
        {
            if (rboxpoint > rbox) {
                rboxpoint = 0;
            }
            xpos[i][d] = randombox[rboxpoint] & 255;
            rboxpoint++;
            if (rboxpoint > rbox) {
                rboxpoint = 0;
            }
            ypos[i][d] = randombox[rboxpoint] & 255;
            rboxpoint++;
            //cout << d << "\n";
            d++;
        }
        //cout << i << "\n";
        i++;
    }

    /*int ramp = 0;
    int ramp2 = 200;
    while (ramp < 200)
    {
      xpos[1][ramp] = ramp;
      ypos[1][ramp] = ramp2;
      ramp++;
      ramp2--;
    }*/

    int generation = 0;

    cout << "Entering main loop. \n";
    //Main loop.

    int q;
    while (generation <= 2500) //This is where we stop at.
    {

        if (bdiff == 25000) //Raise the scoreing difficulty every so often.
        {
            if (ballDifficulty > 2) {
                ballDifficulty--;
            }
            bdiff = 0;
        }
        bdiff++;

        cycles++;
        boardsim();

        //cout << "Copy \n";
        copyto();

        //cout << "Comparing scores. \n";

        gtest1.gcombine();

        q = randoget();
        q = q & 255;
        rboxpoint = rboxpoint ^ q;

        cout << "\r";
        cout << "Current high score of " << highscore << " for parent number " << highparent + 1 << " of generation number " << generation << "        ";

        //imagemake(1,generation);
        //cout << "X " << xpos[1][2] << " Y " << ypos[1][2] << "\n";
        if (i > 25) {
            imagemake(highparent, generation);
            i = 0;
        }
        else {
            i++;
        }
        generation++;

        copyfrom();
    }
    cout << "\n";
    return 0;
}

/******************************************************
 ******************************************************/

void copyto(void)
{
    int i = 0;
    int d = 0;
    int q = 0;
    while (i < genecount) {
        d = 0;
        q = 0;
        while (d < paramcount) {
            gene[i][d] = xpos[i][q];
            d++;
            gene[i][d] = ypos[i][q];
            d++;
            q++;
        }
        i++;
    }
}

void copyfrom(void)
{
    int i = 0;
    int d = 0;
    int q = 0;
    while (i < genecount) {
        d = 0;
        q = 0;
        while (d < paramcount) {
            xpos[i][q] = gene[i][d];
            d++;
            ypos[i][q] = gene[i][d];
            d++;
            q++;
        }
        i++;
    }
}

//ball is 2 pixels wide and 1 pixel tall...
void boardsim(void)
{
    int i;
    int q;

    i = 0;
    q = 0;

    thread threads[genecount];
    // spawn n threads:
    for (int i = 0; i < genecount; i++) {
        threads[i] = thread(bsim::ballsimul, i);
    }

    for (auto& th : threads) {
        th.join();
    }
}

void bsim::ballsimul(int i)
{
    unsigned int ballx;
    unsigned int bally;
    int tmpx;
    int movhoriz = 0;
    int movdown = 0;
    int timeout = 0;
    int q = 0;

    ballx = 128;
    bally = 255;

    timeout = 0;

    while (bally >= 2) {
        if (timeout > 1000) {
            break;
        }

        q = 0;

        xbpos[i][timeout] = ballx;
        ybpos[i][timeout] = bally;
        while (q < 200) //200 pins
        {

            if (bally == ypos[i][q]) {
                tmpx = ballx - 1;
                if (ballx == xpos[i][q]) {
                    movhoriz = -1; //move left
                    movdown = 0;
                    //cout << "Left \n";
                    ballx--;
                    break;
                }
                else if (tmpx == xpos[i][q]) {
                    movhoriz = 1; //move right
                    movdown = 0;
                    //cout << "Right \n";
                    ballx++;
                    break;
                }
                else {
                    movhoriz = 0; //move down
                    movdown = 1;
                }
            }
            else {
                movhoriz = 0; //move down
                movdown = 1;
            }
            q++;
        }

        if (movdown == 1) {
            bally--;
            movdown = 0;
        }
        timeout++;
    }

    if (timeout > 1000) {
        score[i] = 1;
        //cout << "\n" << "Ball timeout \n";
    }
    else {
        score[i] = ballx;
        xbpos[i][timeout + 1] = -1;
        //cout << i << " s " << score[i] << "\n";
    }
}
