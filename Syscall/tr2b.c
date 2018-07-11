#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int main (int argc, char* argv[])
{

  char* from = argv[1];
  char* to = argv[2];

  if(argc!=3)
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
      for(;j<strlen(from);j++)
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

  char input=getchar();
  int check=0;  

  while(input!=EOF)
    {
      check=0;
      for(i=0; i<strlen(from);i++)
	{
	  if(input==from[i])
	    {
	      putchar(to[i]);
	      check=1;
	    }
	}

      if(check==0)
	putchar(input);
      
      input=getchar();
    }

  return 0;
}


	  
