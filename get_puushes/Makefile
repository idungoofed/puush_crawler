bruteForce_v2: bruteForce_v2.c Makefile
	gcc -Wall -std=c99 bruteForce_v2.c -o bruteForce_v2 -pthread
bruteForce: bruteForce.c Makefile
	gcc -Wall -std=c99 bruteForce.c -o bruteForce -pthread
clean:
	rm ./bruteForce_results/* -rf;
	rm *~;
	rm bruteForce; rm bruteForce_v2
