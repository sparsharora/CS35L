randlibhw.so : randlibhw.c
	gcc $(CFLAGS) randlibhw.c -fPIC -shared -o randlibhw.so
randlibsw.so : randlibsw.c
	gcc $(CFLAGS) randlibsw.c -fPIC -shared -o randlibsw.so 
randmain : randcpuid.o randmain.o 
	gcc $(CFLAGS) randmain.o randcpuid.o -ldl -Wl,-rpath=$(PWD) -o randmain
