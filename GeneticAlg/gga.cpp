
/* Generic Genetic Algorithm Library
 Copyright 2017, Jarrett Cigainero. */

#include "gga.h"
#include <iostream>
#include <thread>

using namespace std;
// User variables
unsigned int paramcount; //number of parameters per gene
unsigned int genecount; //number of genes to be tested
unsigned int parents; //total number of parents to keep after a die off
unsigned int lparents; //total number of randomly selected low score parents to keep after die off
unsigned int muteper; //total mutation percentage per generation, NOT YET IMPLIMINTED
unsigned int children; //total number of children per parent group
unsigned int paramgroup;
unsigned int maxrnum;
//unsigned int paramount;  //number of parents to mix per generation, NOT YET IMPLIMINTED
unsigned int rbox;
unsigned int rboxpoint; //pointer to start random numbers
unsigned int highscore; //the highest score, do not right to!
unsigned int highscoretmp;
unsigned int highparent; //parent with the current high score.

int** gene; //genes to be tested
int* score; //scores pertaining to the genes to be tested
unsigned int* randombox; //box of random numbers to use for mixing.

// Non-user variables.
unsigned int parpoint1;
unsigned int parpoint2;

int** parent;

void mutate(void);
int randpars(int);
void parmove(void);

void childmake(void);
void randomfind(int);
void parentcopy(int, int);

//Main routine
int combine::gcombine(void)
{
    int i;
    int d;
    int test;
    int hp;

    //cout << "G 1 \n";

    /* Find the highest scoring gene. */
    i = 0;
    test = 0;
    highscore = 0;
    //cout << "First score is " << highscore << "\n";
    hp = 0;
    while (i < genecount) {
        if (score[i] > highscore) {
            highscore = score[i];
            hp = i;
        }
        i++;
    }
    highparent = hp;
    highscoretmp = highscore;
    //cout << "High score is " << highscore << " From parent " << hp << "\n";
    //cout << "G 2 \n";
    /* Find the next highest or equal scores and place
    those parents into the parents array along with the random lows. */
    d = 0;
    int p;
    int stop;
    stop = 0;
    p = parents - lparents;
    while (d < p) {
        i = 0;
        while (i < genecount && d < p) {
            if (highscore == score[i]) {
                parentcopy(i, d);
                d++;
            }
            i++;
        }

        highscore--;
    }

    //cout << "G 3 \n";
    /* Find random low score genes. */

    if (lparents != 0) {
        highscore = highscoretmp;
        randomfind(d);
    }

    highscore = highscoretmp;
    //cout << "G 4 \n";
    /* Combine the parents and make children. */
    childmake();

    //cout << "G 5 \n";

    if (muteper != 0) {
        mutate();
    }
    //cout << "G 6 \n";
}

/*****************************/

void mutate(void)
{
    int i = 0;
    int rando;
    int h;
    int n;
    int l;
    while (i < muteper) {

        h = randpars(genecount);
        h = randombox[rboxpoint] & h;

        if (rboxpoint > rbox) {
            rboxpoint = 0;
        }
        rboxpoint++;

        n = randpars(paramcount);
        n = randombox[rboxpoint] & n;

        if (rboxpoint > rbox) {
            rboxpoint = 0;
        }
        rboxpoint++;

        l = randombox[rboxpoint] & maxrnum;

        if (rboxpoint > rbox) {
            rboxpoint = 0;
        }
        rboxpoint++;

        rando = randombox[rboxpoint] & 3;

        if (rando == 0) {
            gene[h][n] = gene[h][n] ^ l;
        }
        else if (rando == 1) {
            gene[h][n] = gene[h][n] & l;
        }
        else if (rando == 2) {
            gene[h][n] = gene[h][n] | l;
        }
        else {
            gene[h][n] = l;
        }

        i++;
    }
}

/* Make children from parents and put them into the gene array. */
void childmake()
{
    int l;
    int n;
    int oldpick = 0;
    int chcount;
    int pdiv;
    int pdiv2;
    int randonum;
    int pg = 0;
    int totchild = 0;
    chcount = children * parents;

    parpoint1 = 0;
    parpoint2 = 1;
    l = 0;
    while (l < genecount) {

        /* The highest scores are kept in case no others can be made for a given generation. */
        if (oldpick == 0) {
            n = 0;
            while (n < paramcount) {
                gene[l][n] = parent[0][n];
                n++;
            }
            oldpick = 1;
        }
        else if (oldpick == 1 && parents > 2) {
            n = 0;
            while (n < paramcount) {
                gene[l][n] = parent[1][n];
                n++;
            }
            oldpick = 2;
        }
        else if (oldpick == 2 && parents > 3) {
            n = 0;
            while (n < paramcount) {
                gene[l][n] = parent[2][n];
                n++;
            }
            oldpick = 3;
        }
        /****************************************************************************************/
	
        else {
	  /* Now we mix up some genes from a parent pair. */
            pdiv = randoget();
            pdiv = pdiv & 1;
            if (pdiv == 0) {
                n = 0;
                while (n < paramcount) {
                    pg = 0;
                    while (pg < paramgroup) {
                        gene[l][n] = parent[parpoint2][n];
                        n++;
                        pg++;
                    }
                    pg = 0;
                    while (pg < paramgroup) {
                        gene[l][n] = parent[parpoint1][n];
                        n++;
                        pg++;
                    }
                }
            }

            else {
                n = 0;
                while (n < paramcount) {
                    pdiv = randoget();
                    pdiv = pdiv & 1;
                    pg = 0;
                    while (pg < paramgroup) {
                        if (pdiv == 0) {
                            gene[l][n] = parent[parpoint2][n];
                        }
                        else {
                            gene[l][n] = parent[parpoint1][n];
                        }
                        n++;
                        pg++;
                    }
                }
            }
        }
        /*****************************************************************************************/
        l++;
        if (totchild == children) {
            parmove();
            totchild = 0;
        }
        else {
            totchild++;
        }
    }
}

void parmove(void)
{
    if (parpoint2 == parents - 1) {
        if (parpoint1 < parents - 2) {
            parpoint1++;
            parpoint2 = parpoint1 + 1;
        }
        else {
            parpoint1 = 0;
            parpoint2 = 1;
        }
    }
    else {
        parpoint2++;
    }
}

/* random get for child making */
int randoget(void)
{
    int rander;
    if (rboxpoint > rbox) {
        rboxpoint = 0;
    }
    rander = randombox[rboxpoint];
    rboxpoint++;
    rander = rander & 15;
    return rander;
}

void randomfind(int d)
{
    int rando;
    int l;
    int h;
    l = 0;
    h = randpars(genecount);
    while (l < lparents && d < parents) {
        if (rboxpoint > rbox) {
            rboxpoint = 0;
        }
        rando = randombox[rboxpoint];
        rando = rando & h;

        if (score[rando] <= highscore) {
            parentcopy(rando, d);
            d++;
            l++;
        }
        rboxpoint++;
    }
}

int randpars(int b)
{
    if (b <= 3) {
        return 1;
    }
    else if (b <= 7) {
        return 3;
    }
    else if (b <= 15) {
        return 7;
    }
    else if (b <= 31) {
        return 15;
    }
    else if (b <= 63) {
        return 31;
    }
    else if (b <= 127) {
        return 63;
    }
    else if (b <= 255) {
        return 127;
    }
    else if (b <= 511) {
        return 255;
    }
    else if (b <= 1023) {
        return 511;
    }
    else if (b <= 2047) {
        return 1023;
    }
    else if (b <= 4095) {
        return 2047;
    }
    else {
        return 4095;
    }
}

//Copys individual parents.
void parentcopy(int from, int to)
{
    int l;
    l = 0;
    while (l < paramcount) {
        parent[to][l] = gene[from][l];
        l++;
    }
}
//class constructor, initialize memory.
combine::combine(void)
{
    long int a;
    gene = new int*[genecount];

    for (int i = 0; i <= genecount; ++i) {
        gene[i] = new int[paramcount];
    }

    parent = new int*[parents];

    for (int i = 0; i <= parents; ++i) {
        parent[i] = new int[paramcount];
    }

    score = new int[genecount];
    randombox = new unsigned int[rbox];
}
