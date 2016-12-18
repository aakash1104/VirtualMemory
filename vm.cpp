#include <iostream>
#include <fstream>
using namespace std;

class virtualPage
{
public:
  unsigned int address;
  bool exist;
  int correctRAM;
  virtualPage();
}; // class virtualPage

virtualPage::virtualPage()
{
  exist = 0;
}

class RAMLine
{
public:
  int whereInLine;
  bool used;
  RAMLine();
}; // class RAMLine
RAMLine::RAMLine()
{
 whereInLine = -1; 
 used = 0;
}

int main(int argc, char** argv)
{
  int i, j, STAR = 0, counter = 0;
  unsigned long int address;
  virtualPage virtualTable[32];
  RAMLine RAM[4];
  ifstream inf(argv[1]);
  ofstream outf("vm-out.txt");
  
  while(inf >> hex >> address)
  {

    if(counter < 32)
    {
      virtualTable[counter].address = address;
      counter++;
    }
    else
    {
      for(j = 0; j < 32; j++)
        if(virtualTable[j].address <= address)
          if(virtualTable[j].address + 1024 > address)
            break;
    
      int pageNumber = j;

      if(virtualTable[pageNumber].exist == false)
      {
        virtualTable[pageNumber].exist = true;
        while(RAM[STAR].used)
        {
          RAM[STAR].used = false;
          STAR++;
          if(STAR == 4)
            STAR = 0;

        } 
      
      
        RAM[STAR].used = true;
        virtualTable[RAM[STAR].whereInLine].exist = false;
        RAM[STAR].whereInLine = pageNumber;        
        virtualTable[pageNumber].correctRAM = STAR;       
        STAR++;
        if(STAR == 4)
          STAR = 0;
      }  
      else
       RAM[virtualTable[pageNumber].correctRAM].used = true;
        
      bool notFirst = false;
      for(i = 0; i < 4; i++)
        if(RAM[i].whereInLine >= 0)
        {
          if(notFirst == true)
            outf << ' ';

          notFirst = true;
          int goCorrectly = RAM[i].whereInLine;
          outf << hex << virtualTable[goCorrectly].address;
        } 
      outf << endl;
    }
  } 


  outf.close();
  return 0;
} 
