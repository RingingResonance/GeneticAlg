/* Generic Genetic Algorithm Library
 Copyright 2017, Jarrett Cigainero. */

#ifndef ggah
#define ggah

// User variables
extern unsigned int paramcount;   //number of parameters per gene
extern unsigned int genecount;  //number of genes to be tested
extern unsigned int parents;    //total number of parents to keep after a die off
extern unsigned int lparents;   //total number of randomly selected low score parents to keep after die off
extern unsigned int muteper;    //total mutation percentage per generation, NOT YET IMPLIMINTED
extern unsigned int children;   //total number of children per parent group
extern unsigned int paramgroup;
extern unsigned int maxrnum;
//unsigned int paramount;  //number of parents to mix per generation, NOT YET IMPLIMINTED
extern unsigned int rbox;
extern unsigned int rboxpoint; //pointer to start random numbers
extern unsigned int highscore; //the highest score, do not right to!
extern unsigned int highparent;  //parent with the current high score.

extern int ** gene;     //genes to be tested
extern int * score;    //scores pertaining to the genes to be tested
extern unsigned int * randombox; //box of random numbers to use for mix

int randoget(void);
/* READ ME!!!
You must initialize all variables above properly before creating a class object.
Otherwise the constructor may do something stupid.
*/

class combine
{
public:
    static int gcombine(void);
    combine(void);
};


#endif // ggah
