#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include "cachelab.h"

#define WORDSIZE (sizeof(void*)*8)

struct block{
  bool valid;
  int tag;
  int timestamp;
};

int hits = 0;
int misses = 0;
int evictions = 0;

int timestamp = 0;
bool verbose = false;
int s, E, b;
int S, B, t;
int C;
FILE *fp;
struct block ***cache;
char operationStr[256];

void printHelp(){
	printf("Usage: ./csim-ref [-hv] -s <num> -E <num> -b <num> -t <file>\n"
			   "Options: \n"
				 "  -h        Print the usage massage.\n"
				 "  -v        Verbose flag that display trace info.\n"
				 "  -s <num>  Number of set index bits.\n"
				 "  -E <num>  Number of lines per set.\n"
				 "  -b <num>  Number of block offset bits.\n"
				 "  -t <file> Trace file.\n"
				 "Example: \n"
				 " linux>  ./csim-ref -s 4 -E 1 -b 4 -t traces/yi.trace\n"
				 " linux>  ./csim-ref -v -s 8 -E 2 -b 4 -t traces/yi.trace\n");
}

void getOptions(int argc, char* argv[]){
  int opt;
  while((opt=getopt(argc, argv, "hvs:E:b:t:"))!=-1){
    switch (opt)
    {
      case 'h':
        printHelp();
        exit(0);
      case 'v':
        verbose = true;
        break;
      case 's':
 	      s = atoi(optarg);
        S = 1<<s;
        break;
      case 'E':
        E = atoi(optarg);
        break;
      case 'b':
        b = atoi(optarg);
        B = 1<<b;
        break;
      case 't':
        fp = fopen(optarg, "r");
        if(fp == NULL){
          fprintf(stderr, "Open file failed");
          exit(-1);
        }
        break;
      default:
				printf("Invalid argument!");
        break;
    }
  }
  t = WORDSIZE - (s+b);
  C = B*E*S;
}

void initCache(){
  cache = malloc(sizeof(void*)*S);
  for(int i = 0; i < S; i++){
    cache[i] = malloc(sizeof(void*)*E);
    for(int j = 0; j < E; j++){
      struct block *pBlock = malloc(sizeof(struct block));
      pBlock->valid = false;
      pBlock->tag = 0;
      pBlock->timestamp = 0;
      cache[i][j] = pBlock;
    }
  }
}

void freeCache(){
  for(int i = 0; i < S; i++){
		for (int j = 0; j < E; j++) {
			free(cache[i][j]);
		}
    free(cache[i]);
  }
  free(cache);
}

void callCache(unsigned long long address){
  int setAddress = address<<t>>(t+b);
  int tagAddress = address>>(s+b);
  struct block **pSet = cache[setAddress];
  struct block *pHitBlock = NULL;
  struct block *pEmptyBlock = NULL;
  struct block *pLRUBlock = NULL;

  for(int i = 0; i < E; i++){
    struct block *pBlock = pSet[i];
    if(pHitBlock == NULL && pBlock->valid && pBlock->tag == tagAddress){
      pHitBlock = pBlock;
    }
    if(pEmptyBlock == NULL && !pBlock->valid){
      pEmptyBlock = pBlock;
     }
    if(pBlock->valid && (pLRUBlock == NULL || pLRUBlock->timestamp > pBlock->timestamp)){
      pLRUBlock = pBlock;
    }
  }

  if(pHitBlock != NULL){
    hits++;
    if(verbose){
      printf(" hit");
    }
    pHitBlock->timestamp = timestamp;
  }
  else{
    misses++;
    if(verbose){
      printf(" miss");
    }
    if(pEmptyBlock!=NULL){
      pEmptyBlock->valid = true;
      pEmptyBlock->tag = tagAddress;
      pEmptyBlock->timestamp = timestamp;
    }
    else{
      if(pLRUBlock == NULL){
        printf("LRU Error\n");
        exit(-1);
      }
      evictions++;
      if(verbose){
        printf(" eviction");
      }
      pLRUBlock->tag = tagAddress;
      pLRUBlock->timestamp = timestamp;
    }
  }
}

void handleOpertaion(){
  timestamp++;
  char opType;
  unsigned long long address;
  int size;
  int count = sscanf(operationStr, " %c %llx,%d", &opType, &address, &size);

  if(count==0){
    return;
  }
  if(verbose){
    printf("%s", operationStr);
  }
  switch (opType)
  {
    case 'L':
      callCache(address);
      break;
    case 'S':
      callCache(address);
      break;
    case 'M':
      callCache(address);
      callCache(address);
      break;
    default:
      break;
    }
    if(verbose){
      printf("\n");
    }
}

void handleInput(){
  while(fgets(operationStr, 256, fp)){
    if(operationStr[strlen(operationStr)-1]=='\n'){
      operationStr[strlen(operationStr)-1]='\0';
    }
    handleOpertaion();
  }
}

int main(int argc, char* argv[])
{
  getOptions(argc, argv);
  initCache();
  handleInput();
  fclose(fp);
  freeCache();
  printSummary(hits, misses, evictions);
  return 0;
}

