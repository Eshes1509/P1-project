#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>
#include "CarRentalFunctions.h"

void dealConfirm(void);

void identifyUser(char userEmail[], char ans);

int main(void) {
  int ans;
  srand(time(NULL));

  printf("1. Sign in\n2. Sign up as renter\n3. Sign up as owner\n4. Edit car renter\n5. Edit car owner\n6. Display car renter information\n7. Display car owner information\n8. Display all cars\n9. Make a deal\n10. Rate a Deal\n");
  do{
    scanf("%d", &ans);  
  } while(ans < 1 && ans > 9);
  
  switch (ans)
  {
  case 1: 
    break;
  case 2: 
    carRenterData();
    break;
  case 3: 
    carOwnerData();
    break;
  case 6: 
    carRenterDisplay();
    break;
  case 7: 
    carOwnerDisplay();
    break;
  case 9:
    makeDeal();
    break;
  case 10:
    dealConfirm();
    break;
    
  default:
    break;
  }
  fflush(stdin);
  return 0;
}

void dealConfirm (void) {

  carOwner    dealOwner;
  carOwner    tempOwner;
  carRenter   dealRenter;
  carRenter   tempRenter;
  FILE*       fp;
  tranDet     tempTrans;
  bool        found;
  char        ans;
  char        ans2;
  printf("Have you rented or rented out a car?\na: rented a car\nb: rented out a car");

  do {
    scanf("%c", &ans);
  } while(ans != 'a' && ans != 'b');

  if (ans == 'a') {
    dealRenter = carRenterDisplay();
  }
  else {
    dealOwner = carOwnerDisplay();
  }

  fp = fopen ("transactions.dat", "rb");

  if (fp == NULL) {
    fprintf(stderr, "\nError opening file\n");
    exit (1);
  }

  // read file contents till end of file
  while(1){
    
    fread(&tempTrans, sizeof(tempTrans), 1, fp);    

    if(feof(fp)) {
      break;
    }

    if (ans == 'a' && (!strcmp(tempTrans.renterEmail,dealRenter.Email)) && tempTrans.isDone == 0) {
     
      found = 1;
    }

    else if (tempTrans.ownerID == dealOwner.ID) {
      
      found = 1;
    }

    else {
      printf("\nNo unrated deals found");
    }
  }

  // close file
  fclose (fp);

  if (found == 1) {

    fflush(stdin);

    printf("\nYou have made a deal with the transaction ID: %d\nDo you wish to rate this deal?\ny: yes\nn: no\n", tempTrans.transactionID);

    do {

    scanf("%c", &ans2);
    printf("\n");

    if (ans == 'a') {
      identifyUser (dealOwner.Email, ans);
    }

    else if (ans == 'b') {
      identifyUser (dealRenter.Email, ans);
    }
    
    } while(ans2 != 'y' && ans2 != 'n');
  }  

  

}

void identifyUser(char userEmail[], char ans) {
  FILE *fp;
  FILE *fp1;
  carRenter tempCarRenter;
  carOwner tempCarOwner;
  int found = 0;
  int rate;

  // Open renter.dat for reading
  if (ans == 'a') {
    fp = fopen ("owners.dat", "rb");
  }

  else if (ans == 'b') {
    fp = fopen("renters.dat", "rb");
  }

  if (fp == NULL){
    fprintf(stderr, "\nError opening file\n");
    exit (1);
  }

  // read file contents till end of file
  while(1) {
    if (ans == 'a') {
      fread(&tempCarOwner, sizeof(tempCarOwner), 1, fp);

      if(!strcmp(tempCarOwner.Email, userEmail)) {
        found = 1;
        fp1 = fopen("temp.dat", "rw");
        
        if (fp1 == NULL) {
          fprintf(stderr, "\nError opening file\n");
          exit (1);
        }

        printf("You made a deal with %s. What would you like to rate this person?\n1: bad\n2: Not so good\n3: Decent\n4: Good\n5: Very good", tempCarOwner.name);
        scanf("%d" , &rate);

        tempCarOwner.rating = (double) (tempCarOwner.ratingAmount * tempCarOwner.rating + rate) / (tempCarOwner.ratingAmount + 1);
        tempCarOwner.ratingAmount++;

        fwrite(&tempCarOwner, sizeof(tempCarOwner), 1, fp1);
        
        while(1) {
          fread(&tempCarOwner, sizeof(tempCarOwner), 1, fp1);

          if(feof(fp1)) {
            break;
          }

          fwrite(&tempCarOwner, sizeof(tempCarOwner), 1, fp);
        } 
        fclose(fp1);
      }
      
    }

    if (ans == 'b') {
      fread(&tempCarRenter, sizeof(tempCarRenter), 1, fp);

      if(!strcmp(tempCarRenter.Email, userEmail)) {
        found = 1;
        fp1 = fopen("temp.dat", "rw");
        printf("You made a deal with %s. What would you like to rate this person?\n1: bad\n2: Not so good\n3: Decent\n4: Good\n5: Very good", tempCarRenter.name);
        scanf("%c" , &rate);

        tempCarRenter.rating = (double) (tempCarRenter.ratingAmount * tempCarRenter.rating + rate) / (tempCarRenter.ratingAmount + 1);
        tempCarRenter.ratingAmount++;

        fwrite(&tempCarRenter, sizeof(tempCarRenter), 1, fp1);
        
        while(1) {
          fread(&tempCarRenter, sizeof(tempCarRenter), 1, fp1);

          if(feof(fp1)) {
            break;
          }

          fwrite(&tempCarRenter, sizeof(tempCarRenter), 1, fp);
        } 
        fclose(fp1);
      }
    }
  
    if(feof(fp)) {
      break;
    }
  }

  if(found == 0) {
    printf("Sorry no record found\n");
  }
  // close file
  fclose (fp);   
}
