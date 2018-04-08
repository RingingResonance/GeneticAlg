/* Random Number Get from File */

#include <iostream>
#include <fstream>
#include <string>
#include "../GeneticAlg/gga.h"
#include "GeneticTest.h"
#include "rget.h"

using namespace std;

ifstream randofile;		//global file I/O stuff.
ofstream resultf;

#define infile "randomnums.txt"

char * inputblock;

int imindex;
char imagered[65025];
char imagegreen[65025];
char imageblue[65025];

unsigned char tgaheader[] = {
00,00,0x2,00,00,00,00,00,00,
00,0xFF,00,0xFF,00,0xFF,00,0x18,0x20
};


unsigned char tgatail[] = {
00,00,00,00,00,00,00,00,0x54,0x52,0x55,0x45,0x56,0x49,0x53,0x49,0x4F,0x4E,0x2D,0x58,0x46,0x49,0x4C,0x5,0x2E,00
};

void imagemake(int brdnum, int geno)
{
  int i = 0;
  int x = 0;
  int y = 0;

  imindex = 0;

  while (imindex < 65025)
  {
    imagered[imindex] = 45;
    imagegreen[imindex] = 45;
    imageblue[imindex] = 45;
    imindex++;
  }

  //Pin position
  while (i < 200)
  {
    x = 0;
    y = 255;
    imindex = 0;
    while (imindex < 65025)
    {
      if (x == xpos[brdnum][i])
      {
	if (y == ypos[brdnum][i])
	{
	  imagegreen[imindex] = 255;
	}
      }

      imindex++;
      if (x == 254)
      {
	x = 0;
	y--;
      }
      else
      {
	x++;
      }
    }
    i++;
  }

   i = 0;
  //Ball path.
  while (i < 1000 && xbpos[brdnum][i] != -1)
  {
    x = 0;
    y = 255;
    imindex = 0;
    while (imindex < 65025)
    {
      if (x == xbpos[brdnum][i])
      {
	if (y == ybpos[brdnum][i])
	{
	  imagered[imindex] = 255;
	}
      }

      imindex++;
      if (x == 254)
      {
	x = 0;
	y--;
      }
      else
      {
	x++;
      }
    }
    i++;
  }

  resultf.open (("./output/Generation_" + std::to_string(geno) + "_Board_" + std::to_string(brdnum) + ".tga"), ios::out | ios::binary);


  i = 0;
  while (i < 18)
  {
    resultf << tgaheader[i];
    i++;
  }

  imindex = 0;
  while (imindex < 65025)
  {
    resultf << imageblue[imindex];
    resultf << imagegreen[imindex];
    resultf << imagered[imindex];
    imindex++;
  }

  i = 0;
  while (i < 25)
  {
    resultf << tgatail[i];
    i++;
  }

  resultf.close();
}

void snapshot(int a, int b)
{
      int i = 0;
      int d = 0;
      int q = 0;
      while (i < genecount)
      {
	d = 0;
	q = 0;
	while (d < paramcount)
	{
	  xpos[i][q] = gene[i][d];
	  d++;
	  ypos[i][q] = gene[i][d];
	  d++;
	  q++;
	}
	i++;
      }
      imagemake(a,b);
}

int rfileget(void)
{
    streampos size;
    //Random number get.
    cout << "Attempting to open file '" << infile << "' \n";

    randofile.open (infile, ios::in | ios::ate);			//open file and position the pointer to end of file so we can get the size.
    if (!randofile.is_open())
    {
        cout << "FAILED TO OPEN FILE '" << infile << "' \n \n";
        return 1;
    }
    cout << "Success! File '" << infile << "' opened. \n";

    size = randofile.tellg();			//get the file size
    inputblock = new char [size];
    randofile.seekg (0, ios::beg);		//seek to beginning of file.
    randofile.read (inputblock, size);		//copy to memory.


    int i;
    i = 0;
    unsigned int testvar;
    unsigned int addvar[3];
    int varplace;
    int tmpplace;
    unsigned int outvar;
    unsigned int vardiv;
    unsigned int randoaddr;
    randoaddr = 0;
    vardiv = 1;
    varplace = 0;

while (i < size)
{
    testvar = inputblock[i];
    if (testvar != 13)
    {
        addvar[varplace] = testvar - 48;
        varplace++;
        vardiv = vardiv * 10;
        i++;
    }
    else
    {
        varplace = varplace - 1;
        tmpplace = varplace;
        while (tmpplace >= 0)
        {
            if (tmpplace == 3)
            {
                vardiv = vardiv / 10;
                addvar[3] = addvar[3] * vardiv;
            }
            else if (tmpplace == 2)
            {
                vardiv = vardiv / 10;
                addvar[2] = addvar[2] * vardiv;
            }
            else if (tmpplace == 1)
            {
                vardiv = vardiv / 10;
                addvar[1] = addvar[1] * vardiv;
            }
            else if (tmpplace == 0)
            {
                vardiv = vardiv / 10;
                addvar[0] = addvar[0] * vardiv;
            }
            tmpplace--;
        }
        tmpplace = varplace;
        outvar = 0;
        while (tmpplace >= 0)
        {
            outvar = outvar + addvar[tmpplace];
            tmpplace--;
        }
        //cout << outvar << "\n";
        i++;
        varplace = 0;
        tmpplace = 0;
        vardiv = 1;
        if (randoaddr >= rbox)
        {
            cout << "Error! file has more numbers. \n";
            return 0;
        }
        else
        {
            randombox[randoaddr] = outvar;
            randoaddr++;
        }
    i++;
    }
}
}
//End of random number get.
