#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>
#include "CarRentalFunctions.h"

void findTransaction(void);

void UserRating(char userEmail[], char ans);

int main(void) {
  int ans;
  srand(time(NULL));

  printf("1. Sign in\n2. Sign up as renter\n3. Sign up as owner\n6. Display car renter information\n7. Display car owner information\n9. Make a deal\n10. Rate a Deal\n");
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
    findTransaction();
    break;
    
  default:
    break;
  }
  fflush(stdin);
  return 0;
}

void findTransaction (void) {

  carOwner    dealOwner;
  carOwner    tempOwner;
  carRenter   dealRenter;
  carRenter   tempRenter;
  FILE*       fp;
  tranDet     tempTrans;
  bool        found;
  char        ans;
  char        ans2;
  printf("Have you rented or rented out a car?\na: rented a car\nb: rented out a car\n");

  do {
    scanf("%c", &ans);
  } while(ans != 'a' && ans != 'b');

  if (ans == 'a') {
    dealRenter = carRenterDisplay();
  }
  else if (ans == 'b') {
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

    if (ans == 'a' && (!strcmp(tempTrans.renterEmail , dealRenter.Email)) && tempTrans.isDone == 0) {
     
      found = 1;
    }

    else if (ans == 'b' && (!strcmp(tempTrans.ownerEmail , dealOwner.Email)) && tempTrans.isDone == 0) {
      
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

    if (ans == 'a' && ans2 == 'y') {
      UserRating (tempTrans.ownerEmail, ans);
    }

    else if (ans == 'b' && ans2 == 'y') {
      UserRating (tempTrans.renterEmail, ans);
    }

    else if (ans2 == 'n') {
      exit(1);
    }

    } while(ans2 != 'y' && ans2 != 'n');
  }  

}

void UserRating(char userEmail[], char ans) {
  FILE *fp;
  FILE *fp1;
  carRenter tempCarRenter;
  carOwner tempCarOwner;
  int found = 0;
  double rate;
  long int pos;
  //If the person rating is a renter, the person that has to be rated is an owner, therefore open owner.dat

  // read file contents till end of file
  fp1 = fopen("temp.dat", "wb");

  if (ans == 'a') {

    fp = fopen ("owners.dat", "rb+");

    if (fp == NULL){
      fprintf(stderr, "\nError opening file\n");
      exit (1);
    }

    while (1) {
      fread(&tempCarOwner, sizeof(tempCarOwner), 1, fp);

      if(feof(fp)) {
        break;
      }

      if(!strcmp(tempCarOwner.Email, userEmail)) {
        
        found = 1;

        //saves the position of the pointer in the file, so that the position of the found user can be used later
        pos = ftell(fp);
        
        printf("You have made a deal with %s. What do you wish to rate this user?\n1: bad\n2: not good\n3: decent\n4: good\n5: very good\n", tempCarOwner.name);
        do {
          scanf("%lf", &rate);
        } while (rate < 1 && rate > 5);

        tempCarOwner.rating = ((tempCarOwner.rating * tempCarOwner.ratingAmount + rate) / ((double)tempCarOwner.ratingAmount + 1.00));
        tempCarOwner.ratingAmount++;
        fwrite(&tempCarOwner, sizeof(tempCarOwner), 1, fp1);
      }
    }
    fclose(fp);
  }

  if (ans == 'b') {

    fp = fopen ("renters.dat", "rb+");

    if (fp == NULL){
      fprintf(stderr, "\nError opening file\n");
      exit (1);
    }

    while (1) {
      fread(&tempCarRenter, sizeof(tempCarRenter), 1, fp);

      if(feof(fp)) {
        break;
      }

      if(!strcmp(tempCarRenter.Email, userEmail)) {
        
        found = 1;

        //saves the position of the pointer in the file, so that the position of the found user can be used later
        pos = ftell(fp);
        
        printf("You have made a deal with %s. What do you wish to rate this user?\n1: bad\n2: not good\n3: decent\n4: good\n5: very good\n", tempCarRenter.name);
        do {
          scanf("%lf", &rate);
        } while (rate < 1 && rate > 5);

        tempCarRenter.rating = ((tempCarRenter.rating * tempCarRenter.ratingAmount + rate) / ((double)tempCarRenter.ratingAmount + 1.00));
        tempCarRenter.ratingAmount++;

        fwrite(&tempCarRenter, sizeof(tempCarRenter), 1, fp1);
      }
    }
    fclose(fp);
  }

  fclose(fp1);

  if (ans == 'a') {
    
    fp = fopen("owners.dat","wb");

    //moves the file pointer to the desired user
    fseek(fp, pos, SEEK_SET);

    fp1 = fopen ("temp.dat","rb");

    while (1) {
      fread(&tempCarOwner, sizeof(tempCarOwner), 1, fp1);

      if (feof(fp1)) {
        break;
      }
      fwrite(&tempCarOwner, sizeof(tempCarOwner), 1, fp);
    }
  }

  if (ans == 'b')  {
    
    fp = fopen("renters.dat", "wb");
    
    //moves the file pointer to the desired user
    fseek(fp, pos, SEEK_SET);

    fp1 = fopen("temp.dat", "rb");

    while (1) {
      fread(&tempCarRenter, sizeof(tempCarRenter), 1, fp1);

      if (feof(fp1)) {
        break;
      }
      fwrite(&tempCarRenter, sizeof(tempCarRenter), 1, fp);
    }
  }

  else if (found == 0) {
   
    printf("No unrated user in your transaction!");
  }

  fclose(fp);
  fclose(fp1);
    
}
