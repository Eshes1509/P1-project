#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void makeDeal (int renterID, int ownerID);

typedef struct transactionData {
    int transactionID;
    int renterID;
    int ownerID;
    bool isDone;
} tranDet;

void makeDeal (int renterID, int ownerID) {
  FILE *fp;
  tranDet temptrans;
  
  temptrans.transactionID = ((rand() % 999999)+100000);
  temptrans.renterID = renterID;
  temptrans.ownerID = ownerID;
  temptrans.isDone = 0;

  //open file
  fp = fopen ("transactions.dat", "a");

  if (fp== NULL){
    fprintf(stderr, "\nError opened file\n");
    exit (1);
  }
  
  fwrite (&temptrans, sizeof(tranDet), 1, fp);

  if(fwrite != 0)
    printf("Transaction completed\n");

  else
    printf("Error writing to file !\n");

  // close file
  fclose (fp);
}

