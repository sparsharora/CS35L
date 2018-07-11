#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "randcpuid.h"
#include <dlfcn.h>

/* Main program, which outputs N bytes of random data.  */
int
main (int argc, char **argv)
{
  /* Check arguments.  */
  bool valid = false;
  long long nbytes;
  if (argc == 2)
    {
      char *endptr;
      errno = 0;
      nbytes = strtoll (argv[1], &endptr, 10);
      if (errno)
	perror (argv[1]);
      else
	valid = !*endptr && 0 <= nbytes;
    }
  if (!valid)
    {
      fprintf (stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
      return 1;
    }

  /* If there's no work to do, don't worry about which library to use.  */
  if (nbytes == 0)
    return 0;

  /* Now that we know we have work to do, arrange to use the
     appropriate library.  */
  void *lib;
  char *err;
  unsigned long long (*rand64) (void);
  
  if (rdrand_supported ())
    {
      lib = dlopen("randlibhw.so", RTLD_NOW);
      if (lib == NULL) { 
	printf("failed to open randlibhw.so: %s\n", dlerror()); 
	exit(1); 
      }  

      rand64 = dlsym(lib, "hardware_rand64");
      
      err = dlerror(); /*check for errors and copy error message*/ 
      if (err != NULL) { 
	printf("failed to locate rand64 for hardware: %s\n", err); 
	exit(1); 
      }

      printf("%s\n","HW");

    }
  else
    {
      lib = dlopen("randlibsw.so", RTLD_NOW);
      if (lib == NULL) {
        printf("failed to open randlibsw.so: %s \n", dlerror());
        exit(1);
      }

      rand64 = dlsym(lib, "software_rand64");
      
      err = dlerror(); /*check for errors and copy error message*/
      if (err != NULL) {
        printf("failed to locate rand64 for software: %s \n", err);
        exit(1);
      }

      printf("%s\n","SW");

    }

  
  int wordsize = sizeof rand64 ();
  int output_errno = 0;

  do
    {
      unsigned long long x = rand64 ();
      size_t outbytes = nbytes < wordsize ? nbytes : wordsize;
      //if (fwrite (&x, 1, outbytes, stdout) != outbytes)
      if(!printf("%llu\n",x))
      {
	  output_errno = errno;
	  break;
	}
      nbytes -= outbytes;
    }
  while (0 < nbytes);

  if (fclose (stdout) != 0)
    output_errno = errno;

  if (output_errno)
    {
      errno = output_errno;
      perror ("output");
      return 1;
    }

  dlclose(lib);
  return 0;
}
