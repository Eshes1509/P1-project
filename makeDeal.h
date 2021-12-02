#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void makeDeal (int renterID, int ownerID);

FILE *tp;

typedef struct transactionData {
    int transactionID;
    int renterID;
    int ownerID;
    bool isDone = 0;
} tranDet;

void makeDeal (int renterID, int ownerID) {
    
  tranDet temptrans;
  
  temptrans.transactionID = ((rand() % 999999)+100000);
  temptrans.renterID = renterID;
  temptrans.ownerID = ownerID;

  //open file
  tp = fopen ("transactions.dat", "a");

  if (tp== NULL){
    fprintf(stderr, "\nError opened file\n");
    exit (1);
  }
  
  fwrite (&temptrans, sizeof(tranDet), 1, tp);

  if(fwrite != 0)
    printf("Transaction completed\n");

  else
    printf("Error writing to file !\n");

  // close file
  fclose (tp);
}

