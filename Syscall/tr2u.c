#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>


int main(int argctr, char* arg[])
{

  char* from = arg[1];
  char* to = arg[2];

  if(argctr!=3)
    {
      fprintf(stderr, "You need to have 2 arguments!");
      exit(1);
    }


  if(strlen(from)!=strlen(to))
    {
      fprintf(stderr,"Both strings are not of the same size!");
      exit(1);
    }


  int i=0;
  int j=0;
  int t=0;


  for(;i<strlen(from);i++)
    {
      for(;j<strlen(to);j++)
        {
          if(i!=j && from[i]==from[j])
            {
              t=1;
              break;
            }
        }
    }


  if(t==1)
    {
      fprintf(stderr, "Your string contains duplicate charecters!");
      exit(1);
    }

 
  char input[1];

  while(read(0,input,1)>0)
    {
      for(i=0; i<strlen(from);i++)
        {
          if(input[0]==from[i])
            {
              input[0]=to[i];
	    }
        }

      write(1,input,1);
      
    }

  return 0;
}
