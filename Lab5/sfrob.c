#include <stdio.h>
#include <stdlib.h>

char decode(const char x)
{
  return x^42;
}

int frobcmp(char const* a, char const* b)
{
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

  char* f1 = malloc(sizeof(char));      //starting with some space in memory 
  if(f1==NULL)
    {
      fprintf(stderr,"Memory couldn't be allocated");
      exit(1);
    }

  int ctr=0;
 
  int store = getchar();  

  while(store!=EOF)  
    {
      
      f1 = realloc(f1, sizeof(char) * (ctr+1) * 8);   //allocating more memory for a bit as we go on adding chars 
	  
	  if(f1==NULL)
	    {
	      fprintf(stderr,"Memory couldn't be allocated");
	      exit(1);
	    }
	  

      f1[ctr]=store;
      ctr++;
      store=getchar();   //geting next char
    }

  
  if ( f1[ctr-1] != ' ')
    {
      if ( ctr == sizeof(char) * (ctr+1) * 8 )  //incase we run out of places for setting last place to space
	{
	  f1 = realloc(f1, sizeof(char) * 8 * (ctr + 1)); //allocating just one more bit of memory.
	  if(f1==NULL)
            {
              fprintf(stderr,"Memory couldn't be allocated");
              exit(1);
            }
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

  for ( i=0 ; i < ctr3 ; i++)
    {
      for( ctr4=0 ; wordarr[i][ctr4]!=' '; ctr4++)
	{
	  putchar(wordarr[i][ctr4]);
	}
      putchar(' ');
    }

  free(f1);
  free(wordarr);
}
