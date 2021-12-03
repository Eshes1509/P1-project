#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>
#include "CarRentalFunctions.h"

carOwner carOwnerData(void);
carOwner carOwnerDisplay(void);
carRenter carRenterData(void);
carRenter carRenterDisplay(void);
void display_all_cars(void);
void edit_car_renter(void);
void edit_car_owner(void);
void transactionTest(void);
void dealConfirm(void);
void getName (char name[]);
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
  case 4: 
    edit_car_renter();
    break;
  case 5: 
    edit_car_owner();
    break;
  case 6: 
    carRenterDisplay();
    break;
  case 7: 
    carOwnerDisplay();
    break;
  case 8: 
    display_all_cars();
    break;
  case 9:
    transactionTest();
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

//The function that optains the name of the user and car. Use of dynamic memory allocation. Remember to free(); when done using it

void display_all_cars(void){
    FILE *fp;
    carOwner tempCarOwner;
    int n = 1;

    fp = fopen("owners.dat","rb");

    while(1){
      fread(&tempCarOwner, sizeof(tempCarOwner), 1, fp);
      if(feof(fp)){
        break;
      }
      printf("%d.", n++);
      printf ("\nCar price: %d dkk per hour\nCar name: %s\nModel year: %d\nKilometers driven: %d\nTransmission type: %c\n",
      tempCarOwner.price, tempCarOwner.carName, tempCarOwner.modelYear, tempCarOwner.odometer, tempCarOwner.transmission);
    }
    fclose(fp);
}

void edit_car_renter(void){
    FILE *fp;
    FILE *fp1;
    carRenter tempCarRenter;
    char Email[50];
    char name[50];
    int found = 0;

    fp = fopen("renters.dat","rb");
    fp1 = fopen("temp.dat","wb");

    printf("Enter your email: ");
    scanf("%s", &Email); 

    while(1){
      fread(&tempCarRenter, sizeof(tempCarRenter), 1, fp);
      if(feof(fp)){
        break;
      }
      if(!strcmp(tempCarRenter.Email, Email)){
        found = 1;
        printf("Enter name: ");
        fgets(tempCarRenter.name, 50, stdin);
        getName(name);
        strcpy(tempCarRenter.name, name);
        printf("Enter phone number: ");
        scanf(" %s", &tempCarRenter.phoneNum);
        printf("Enter E-mail: ");
        scanf(" %s", &tempCarRenter.Email);
        printf("Enter age: ");
        scanf(" %d", &tempCarRenter.age);
        printf("Enter postcode: ");
        scanf(" %d", &tempCarRenter.postCode);
        printf("Enter preferred type of car (a: 0 to x kr, b: x+1 to y kr, c: y+1 to z kr): ");
        scanf(" %c", &tempCarRenter.prefCarType);
        printf("Enter preferred transmission type (a = automatic, b = manual,  c = both)): ");
        scanf(" %c", &tempCarRenter.prefTransmissionType);
        fwrite(&tempCarRenter, sizeof(tempCarRenter), 1, fp1);
      }
      else{
        fwrite(&tempCarRenter, sizeof(tempCarRenter), 1, fp1);
      }
    }
    fclose(fp);
    fclose(fp1);

    if(found == 0){
      printf("Sorry, no record found");
    }
    else{
      fp = fopen("renters.dat","wb");
      fp1 = fopen("temp.dat","rb");

      while(1){
        fread(&tempCarRenter, sizeof(tempCarRenter), 1, fp1);

        if(feof(fp1)){
          break;
        }
        fwrite(&tempCarRenter, sizeof(tempCarRenter), 1, fp);
      }
    }
    fclose(fp);
    fclose(fp1);    
}

void edit_car_owner(void){
    FILE *fp, *fp1;
    carOwner tempCarOwner;
    char Email[50];
    char name[50];
    int found = 0;

    fp = fopen("owners.dat","rb");
    fp1 = fopen("temp.dat","wb");

    printf("Enter your email: ");
    scanf("%s", &Email); 

    while(1){
      fread(&tempCarOwner, sizeof(tempCarOwner), 1, fp);
      if(feof(fp)){
        break;
      }
      if(!strcmp(tempCarOwner.Email, Email)){
        found = 1;
        printf("Enter name: ");
        fgets(tempCarOwner.name, 50, stdin);
        getName(name);
        strcpy(tempCarOwner.name, name);
        printf("Enter phone number: ");
        scanf(" %s", &tempCarOwner.phoneNum);
        printf("Enter E-mail: ");
        scanf(" %s", &tempCarOwner.Email);
        printf("Enter age: ");
        scanf(" %d", &tempCarOwner.age);
        printf("Enter postcode: ");
        scanf(" %d", &tempCarOwner.postCode);
        printf("Enter how much your car should cost per hour: ");
        scanf(" %d", &tempCarOwner.price);
        printf("Enter name of your car: ");
        fgets(tempCarOwner.carName, 50, stdin);
        getName(name);
        strcpy(tempCarOwner.carName, name);
        printf("Enter your car's model year: ");
        scanf(" %d", &tempCarOwner.modelYear);
        printf("Enter your car's mileage: ");
        scanf(" %d", &tempCarOwner.odometer);
        printf("Enter your car's transmission type (a = automatic, b = manual): ");
        scanf(" %c", &tempCarOwner.transmission);
        fwrite(&tempCarOwner, sizeof(tempCarOwner), 1, fp1);
      }
      else{
        fwrite(&tempCarOwner, sizeof(tempCarOwner), 1, fp1);
      }
    }
    fclose(fp);
    fclose(fp1);

    if(found == 0){
      printf("Sorry, no record found");
    }
    else{
      fp = fopen("owners.dat","wb");
      fp1 = fopen("temp.dat","rb");

      while(1){
        fread(&tempCarOwner, sizeof(tempCarOwner), 1, fp1);

        if(feof(fp1)){
          break;
        }
        fwrite(&tempCarOwner, sizeof(tempCarOwner), 1, fp);
      }
    }
    fclose(fp);
    fclose(fp1);    
}

//Make deal between an existing car Renter and an existing car owner
void transactionTest (void) {
  carOwner    dealOwner;
  carRenter   dealRenter;

  dealRenter = carRenterDisplay();
  dealOwner = carOwnerDisplay();
  
  makeDeal(dealRenter.ID, dealOwner.ID, dealRenter.Email, dealOwner.Email);
}

void dealConfirm (void) {

  carOwner    dealOwner;
  carRenter   dealRenter;
  FILE*       fp;
  tranDet     tempTrans;
  bool        found;
  char        ans;
  
  printf("Have you rented or rented out a car?\na: rented a car\nb: rented out a car");

  do {
    scanf("%c", &ans);
    printf("\n");
  } while(ans != 'a' && ans != 'b');

  if (ans == 'a') {
    dealRenter = carRenterDisplay();
  }
  else {
    dealOwner = carOwnerDisplay();
  }

  fp = fopen ("transactions.dat", "r");
  if (fp == NULL)
  {
    fprintf(stderr, "\nError opening file\n");
    exit (1);
  }

  // read file contents till end of file
  while(1){
    
    fread(&tempTrans, sizeof(tempTrans), 1, fp);    

    if(feof(fp)){
      break;
    }

    if (ans == 'a' && tempTrans.renterID == dealRenter.ID && tempTrans.isDone == 0) {
    
      found = 1;
      identifyUser(dealRenter.Email, ans);
    }

    else if (ans == 'b' && tempTrans.ownerID == dealOwner.ID && tempTrans.isDone == 0) {
      
      found = 1;
      identifyUser(dealOwner.Email, ans);
    }

    else {
      printf("\nThe deal has already been rated");
    }

  }
  if(found == 0){
    printf("\nYou have no deals made");
  }
  // close file
  fclose (fp);

  if (found == 1) {
    printf("\nYou have made a deal with the transaction ID: %d\nDo you wish to rate this deal?", tempTrans.transactionID);
  }  

  do {
    scanf("%c", &ans);
    printf("\n");
  } while(ans != 'a' && ans != 'b');

}

void identifyUser(char userEmail[], char ans) {
  FILE *fp;
  carRenter tempCarRenter;
  carOwner tempCarOwner;
  int found = 0;

  // Open renter.dat for reading
  if (ans == 'a') {
    fp = fopen ("renters.dat", "rb");
  }

  else if (ans == 'b') {
    fp = fopen("owners.dat", "rb");
  }

  if (fp == NULL){
    fprintf(stderr, "\nError opening file\n");
    exit (1);
  }

  // read file contents till end of file
  while(1){
    if (ans == 'a') {
      fread(&tempCarRenter, sizeof(tempCarRenter), 1, fp);

      if(!strcmp(tempCarRenter.Email, userEmail)) {
        found = 1;
        printf("You made a deal with %s, what you would you to like rate this person?\n1: bad\n2: Not so good\n3: Decent\n4: Good\n5: Very good",tempCarRenter.name);
      }
    }

    else if (ans == 'b') {
      fread(&tempCarOwner, sizeof(tempCarOwner), 1, fp);

      if(!strcmp(tempCarOwner.Email, userEmail)) {
        found = 1;
        printf("You made a deal with %s, what you would you to like rate this person?\n1: bad\n2: Not so good\n3: Decent\n4: Good\n5: Very good",tempCarOwner.name);
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