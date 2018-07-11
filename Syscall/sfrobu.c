#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int compnum=0;

char decode(const char x)
{
  return x^42;
}

int frobcmp(char const* a, char const* b)
{
  compnum++;
  for( ;*a!=' '&&  *b!=' '; a++, b++) //check till either encounters a space
    {
      if ( decode(*a) == decode(*b) )    //use decode function to decode
	continue;
      else if (decode(*a) > decode(*b) )
	return 1;
      else if (decode(*a) < decode(*b) )
	return -1;
    }   

  if (*a == *b)    //find which one ran out to find lesser or more
    return 0;
  else if (*a == ' ')
    return -1;
  else
    return 1;
}


int compare(const void* x, const void* y)
{
  return frobcmp(*(const char **)x,*(const char **)y);
}

int main()
{

  struct stat len;

  fstat(0, &len);
  char* f1;
  
  int size=len.st_size;
  int check;

  if(S_ISREG(len.st_mode) && size>0)
    {
      check=1;
      f1 = malloc(size*sizeof(char));
      if(f1==NULL)
	{
	  fprintf(stderr,"Memory couldn't be allocated");
	  exit(1);
	}
    }
  
  else if(!S_ISREG(len.st_mode))
    {
      check=0;
      f1 = malloc(sizeof(char));      //starting with some space in memory 
      if(f1==NULL)
	{
	  fprintf(stderr,"Memory couldn't be allocated");
	  exit(1);
	}
    }

  else
    {
      fprintf(stderr,"Invalid input!");
      exit(1);
    }


  int ctr=0;
  int input[1];
  
  while(read(0,input,1)>0)  
    {
      if(check==0)
	{
	  f1 = realloc(f1, sizeof(char) * (ctr+1) * 8);  
	  if(f1==NULL)
	    {
	      fprintf(stderr,"Memory couldn't be allocated");
	      exit(1);
	    }
	  

     	}

      if(check==1)
	{
	  if(ctr==size)
	    {
	      f1 = realloc(f1, sizeof(char) * (ctr+1) * 8);   
	      if(f1==NULL)
		{
		  fprintf(stderr,"Memory couldn't be allocated");
		  exit(1);
		}
	    }

	}

      f1[ctr]=input[0];
      ctr++;


    }
 
  if ( f1[ctr-1] != ' ')
    {
	  f1 = realloc(f1, sizeof(char) * (ctr + 1)); //allocating just one more bit of memory.
	  if(f1==NULL)
            {
              fprintf(stderr,"Memory couldn't be allocated");
              exit(1);
            }
	

      f1[ctr]= ' ';    //set last charecter to space
      ctr++;
    }

  char** wordarr = (char**)malloc(0);   //set initial memory to nothing since we keep adding as go on
    if(wordarr == NULL)
      {
	fprintf(stderr,"Memory couldn't be allocated");
	exit(1);
      }
    
  
  int ctr2=0;
  char* str = &f1[0];   //keeping track of every word
  int ctr3=0;
  while ( ctr2 < ctr )
    {
      
      wordarr = realloc(wordarr, sizeof(char*) * (ctr2+1)*8);  //add memory as we move on
      
	  if(wordarr == NULL)
	    { 
	      fprintf(stderr,"Memory couldn't be allocated");
	      exit(1);
	    }

	 
  
      if ( f1[ctr2] == ' ')
	{
	  wordarr[ctr3] = str;
	  str = &f1[ctr2+1];
	  ctr3++;
	}

      ctr2++;
    }

    
  qsort(wordarr, ctr3, sizeof(char*), compare);
  
  int i = 0;
  int ctr4=0;
  char sp[1];
  sp[0]=' ';

    for ( i=0 ; i < ctr3 ; i++)
    {
      for( ctr4=0 ; wordarr[i][ctr4]!=' '; ctr4++)
	{
	  write(1,&wordarr[i][ctr4],1);
	}
      write(1,sp,1);
      }
  
  free(f1);
  free(wordarr);


  fprintf(stderr,"Comparisons: %d\n", compnum);
}
