/*TODO
 * Add checking for private addresses.
 * Thread the base address. Ex: thread 1 checks .../a*, thread 2 checks .../b*, etc.
 * Look into using -B option (base url)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

//v2: Adds checking for 5 character addresses (lines 246-252, 268-274)

//NEW_VERSION
//Checks for private file against a string. Not fully tested.
//However, it is much quicker than the old version.
//Might delete files that are not necessarily private.

//OLD_VERSION
//Slower than the new version, but fully tested. Definitely will only delete private files.
#define NEW_VERSION //OLD_VERSION

//VERBOSE
//equivalent to wget -nv ...

//QUITE
//equivalent to wget -q ...
#define QUIET //QUIET //VERBOSE


void *checkFile(void *check) {

#ifdef NEW_VERSION
  FILE *f1, *f2;
  char *nCheck = (char *)malloc(sizeof(char) * 20);
  strncpy(nCheck, "./puu.sh/\0", 10);
  strcat(nCheck, (char *)check);
  f2 = fopen(nCheck, "r");
  if (!f2) {
    //printf("FILE FAILED\n");
    return NULL;
  }
  f1 = fopen("../missingFile.jpg", "r");
  int ch1, ch2, i;
  char privateFile[42] = "You do not have access to view that puush.";
  ch1 = getc(f1);
  ch2 = getc(f2);
  i = 0;
  while ((ch1!=EOF) && (ch2!=EOF) && (privateFile[i]!='.') && ((ch1 == ch2) || (ch2 == privateFile[i]))) {
    ch1 = getc(f1);
    ch2 = getc(f2);
    i++;
  }
  if (ch1 == ch2 || ch2 == '.') {
    char *rmVal = (char *)malloc(23 * sizeof(char));
    strncpy(rmVal, "rm \0", 4);
    strcat(rmVal, (char *)nCheck);
    //printf("Removing %s\n", rmVal);
    system(rmVal);
    free(rmVal);
    fclose(f1);
    fclose(f2);
    free(nCheck);
    return NULL;
  }
  fclose(f1);
  fclose(f2);

  char *rmVal = (char *)malloc(23 * sizeof(char));
  strncpy(rmVal, "rm \0", 4);
  strcat(rmVal, (char *)nCheck);
  //printf("Removing %s\n", rmVal);
  system(rmVal);
  free(rmVal);
  char *tVal = (char *)malloc((6+strlen(nCheck))*sizeof(char));
  strncpy(tVal, "touch \0", 7);
  strcat(tVal, nCheck);
  printf("Creating %s\n", nCheck);
  system(tVal);
  free(tVal);
  free(nCheck);

  //free((char *)check);
  return NULL;
#endif


#ifdef OLD_VERSION
  int cont = 1;
  //remove missingFile
  FILE *f1, *f2;
  f1 = fopen("../missingFile.jpg", "r");
  char *nCheck = (char *)malloc(sizeof(char) * 20);
  strncpy(nCheck, "./puu.sh/\0", 10);
  strcat(nCheck, (char *)check);
  f2 = fopen((char *)nCheck, "r");
  //printf("check = %s\n", (char *)check);
  //printf("nCheck = %s\n", nCheck);
  int ch1, ch2;
  if (!f1 || !f2) {
    if (f1) {
      fclose(f1);
    }
    if (f2) {
      fclose(f2);
    }
    //printf("FILE FAILED\n");
    return NULL;
  }
  ch1 = getc(f1);
  ch2 = getc(f2);
  while ((ch1!=EOF) && (ch2!=EOF) && (ch1 == ch2)) {
    ch1 = getc(f1);
    ch2 = getc(f2);
  }
  if (ch1 == ch2) {
    char *rmVal = (char *)malloc(23 * sizeof(char));
    strncpy(rmVal, "rm \0", 4);
    strcat(rmVal, (char *)nCheck);
    //printf("Removing %s\n", rmVal);
    system(rmVal);
    free(rmVal);
    cont = 0;
    fclose(f1);
    fclose(f2);
    free(nCheck);
    return NULL;
  }
  fclose(f1);
  fclose(f2);
  free(nCheck);
  
  if (cont) {
    //remove privateFile
    FILE *f3, *f4;
    nCheck = (char *)malloc(sizeof(char) * 20);
    strncpy(nCheck, "./puu.sh/\0", 10);
    strcat(nCheck, (char *)check);
    f3 = fopen("../privateFile.jpg", "r");
    f4 = fopen((char *)nCheck, "r");
    if (!f3 || !f4) {
      //printf("FILE FAILED\n");
      if (f3) {
	fclose(f3);
      }
      if (f4) {
	fclose(f4);
      }
      return NULL;
    }
    //printf("check = %s\n", (char *)check);
    //printf("nCheck = %s\n", nCheck);
    ch1 = getc(f3);
    ch2 = getc(f4);
    while ((ch1!=EOF) && (ch2!=EOF) && (ch1 == ch2)) {
      ch1 = getc(f3);
      ch2 = getc(f4);
    }
    if (ch1 == ch2) {
      char *rmVal = (char *)malloc(23 * sizeof(char));
      strncpy(rmVal, "rm \0", 4);
      strcat(rmVal, (char *)nCheck);
      //printf("Removing %s\n", rmVal);
      system(rmVal);
      free(rmVal);
      fclose(f3);
      fclose(f4);
      free(nCheck);
      return NULL;
    }
    fclose(f3);
    fclose(f4);
  }
  char *rmVal = (char *)malloc(23 * sizeof(char));
  strncpy(rmVal, "rm \0", 4);
  strcat(rmVal, (char *)nCheck);
  //printf("Removing %s\n", rmVal);
  system(rmVal);
  free(rmVal);
  char *tVal = (char *)malloc((6+strlen(nCheck))*sizeof(char));
  strncpy(tVal, "touch \0", 7);
  strcat(tVal, nCheck);
  printf("Creating %s\n", nCheck);
  system(tVal);
  free(tVal);
  free(nCheck);

  //free((char *)check);
  return NULL;
#endif
}
  

int main() {
  chdir("./bruteForce_results");
  char test[63];
  int i;
  for (i = 48; i < 58; i++) {
    test[i-48] = i;
    //printf("inserting at: %d, value = %c\n", i-48, test[i-48]);
  }
  for (i = 65; i < 91; i++) {
    test[i-55] = i;
    //printf("inserting at: %d, value = %c\n", i-55, test[i-55]);
  }
  for (i = 97; i < 123; i++) {
    test[i-61] = i;
    //printf("inserting at: %d, value = %c\n", i-61, test[i-61]);
  }
  test[62] = '\0';

  pthread_t *pthread = malloc(sizeof(pthread_t));
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  int a, b, c, d, e, f;
  char *value;
  char *rmVal = (char *)malloc(11 * sizeof(char));
#ifdef QUIET
  value = (char *)malloc(108 * sizeof(char));
  strcpy(value, "wget -q -r -l inf --follow-ftp --random-wait --no-check-certificate --no-dns-cache http://puu.sh/");
  value[103] = '.';
  value[104] = 'j';
  value[105] = 'p';
  value[106] = 'g';
  value[107] = '\0';
#endif
#ifdef VERBOSE
  value = (char *)malloc(109 * sizeof(char)); //string
  strcpy(value, "wget -nv -r -l inf --follow-ftp --random-wait --no-check-certificate --no-dns-cache http://puu.sh/");
  value[104] = '.';
  value[105] = 'j';
  value[106] = 'p';
  value[107] = 'g';
  value[108] = '\0';
#endif
  for (a = 0; a < 62; a++) {
    for (b = 0; b < 62; b++) {
      for (c = 0; c < 62; c++) {
	for (d = 0; d < 62; d++) {
	  for (e = 0; e < 62; e++) {
	    for (f = 0; f < 63; f++) {
#ifdef QUIET
	      value[97] = test[a];
	      value[98] = test[b];
	      value[99] = test[c];
	      value[100] = test[d];
	      value[101] = test[e];
	      value[102] = test[f];
	      if (test[f] == '\0') {
		value[102] = '.';
		value[103] = 'j';
		value[104] = 'p';
		value[105] = 'g';
		value[106] = '\0';
	      }
	      else {
		value[103] = '.';
		value[104] = 'j';
		value[105] = 'p';
		value[106] = 'g';
		value[107] = '\0';
	      }		
#endif
#ifdef VERBOSE
	      value[98] = test[a];
	      value[99] = test[b];
	      value[100] = test[c];
	      value[101] = test[d];
	      value[102] = test[e];
	      value[103] = test[f];
	      if (test[f] == '\0') {
		value[103] = '.';
		value[104] = 'j';
		value[105] = 'p';
		value[106] = 'g';
		value[107] = '\0';
	      }
	      else {
		value[104] = '.';
		value[105] = 'j';
		value[106] = 'p';
		value[107] = 'g';
		value[108] = '\0';
	      }		
#endif
	      system(value);
	      //printf("Value: %s\n", value);
	      rmVal[0] = test[a];
	      rmVal[1] = test[b];
	      rmVal[2] = test[c];
	      rmVal[3] = test[d];
	      rmVal[4] = test[e];
	      if (test[f] == '\0') {
		rmVal[5] = '.';
		rmVal[6] = 'j';
		rmVal[7] = 'p';
		rmVal[8] = 'g';
		rmVal[9] = '\0';
	      }
	      else {
		rmVal[5] = test[f];
		rmVal[6] = '.';
		rmVal[7] = 'j';
		rmVal[8] = 'p';
		rmVal[9] = 'g';
		rmVal[10] = '\0';
	      }
	      //printf("rmVal: %s\n", rmVal);
	      pthread_create(pthread, &attr, checkFile, (void *)(rmVal));
	    }
	  }
	}
      }
    }
  }
  free(value);
  free(pthread);
  free(rmVal);
  pthread_exit(NULL);
  //return EXIT_SUCCESS;;
}
