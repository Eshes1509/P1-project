#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void makeDeal (int renterID, int ownerID);

FILE *tp;

typedef struct transactionData {
    int transactionID;
    int renterID;
    int ownerID;
    bool isSame;
} transactionDetails;

void makeDeal (int renterID, int ownerID) {
    //open file
    tp = fopen ("transactions.dat", "a");

    if (tp== NULL){
      fprintf(stderr, "\nError opened file\n");
      exit (1);
    }
    transactionDetails temptrans;
    
    fwrite (&temptrans, sizeof(transactionDetails), 1, tp);

    if(fwrite != 0)
      printf("Transaction completed\n");

    else
      printf("Error writing to file !\n");
 
    // close file
    fclose (tp);
}

