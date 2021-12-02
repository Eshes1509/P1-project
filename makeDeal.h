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

typedef struct carOwnerData {
  // values set by user
  int     ID;
  char    name[50]; // Name of Cor Owner
  char    phoneNum[9]; // Phone number of CO
  char    Email[50]; // Email of CO
  int     age; // age of CO
  int     postCode; // postcode of CO
  int     price; // Price / h (dkk) of CO
  char    carName[50]; // Name of CO's car
  int     modelYear; // Model year of CO's car
  int     odometer; // kilometers driven by CO's car
  char    transmission; // CO's car's transmission | a = auto, b = manual
  // values set by program
  //double  rating[]; // rating of CO
} carOwner;

typedef struct carRenterData {
  int     ID;
  char    name[50]; // name of Car Renter
  char    phoneNum[9]; // Phone number of CR
  char    Email[50]; // Email of CR
  int     age; // Age of CR
  int     postCode; // Postcode of CR
  char    prefCarType; // CR's preffered car type | can be a,b or c, a most expensive, c least expensive
  char    prefTransmissionType; // CR's Preffered transmission type | can be a,b or c, a = auto, b = manual, c = both

  // values set by program
  //double  rating[]; // rating of CR
} carRenter;

//The function that fetches data for a car renter
carRenter carRenterData(void) {
  FILE *fp;
  carRenter tempCarRenter;
  char name[50];
  
  //ID
  tempCarRenter.ID = ((rand() % 1000000) + 100000);
  // Name
  printf("Please enter your name: ");
  fgets(tempCarRenter.name, 50, stdin);
  getName(name);
  strcpy(tempCarRenter.name, name);

  // Phonenumber
  printf("Enter phone number: ");
  scanf(" %s", &tempCarRenter.phoneNum);

  // Email
  printf("Enter E-mail: ");
  scanf(" %s", &tempCarRenter.Email);

  // Age
  printf("Enter age: ");
  scanf(" %d", &tempCarRenter.age);

  // Postcode
  printf("Enter postcode: ");
  scanf(" %d", &tempCarRenter.postCode);

  // Preffered car type
  printf("Enter preferred type of car (a: 0 to x kr, b: x+1 to y kr, c: y+1 to z kr): ");
  scanf(" %c", &tempCarRenter.prefCarType);

  // Preffered transmission type
  printf("Enter preferred transmission type (a = automatic, b = manual,  c = both)): ");
  scanf(" %c", &tempCarRenter.prefTransmissionType);

  // open file for writing
  fp = fopen ("renters.dat", "a");
  if (fp == NULL){
    fprintf(stderr, "\nError opened file\n");
    exit (1);
  }
  
  // write struct to file
  fwrite (&tempCarRenter, sizeof(tempCarRenter), 1, fp);

  if(fwrite != 0)
    printf("Account succesfully created !\n");
  else
    printf("Error writing to file !\n");

  // close file
  fclose (fp);
}

//The function that fetches data for a car owner
carOwner carOwnerData(void) {
  FILE *fp;
  carOwner tempCarOwner;
  char name[50];

  //ID
  tempCarOwner.ID = ((rand() % 1000000) + 100000);
  // Name
  printf("Please enter your name: ");
  fgets(tempCarOwner.name, 50, stdin);
  getName(name);
  strcpy(tempCarOwner.name, name);

  // Phonenumber
  printf("Enter phone number: ");
  scanf(" %s", &tempCarOwner.phoneNum);

  // Email
  printf("Enter E-mail: ");
  scanf(" %s", &tempCarOwner.Email);

  // Age
  printf("Enter age: ");
  scanf(" %d", &tempCarOwner.age);

  // Postcode
  printf("Enter postcode: ");
  scanf(" %d", &tempCarOwner.postCode);

  // Price of CO's car
  printf("Enter how much your car should cost per hour: ");
  scanf(" %d", &tempCarOwner.price);

  // CO's car's name
  printf("Enter name of your car: ");
  fgets(tempCarOwner.carName, 50, stdin);
  getName(name);
  strcpy(tempCarOwner.carName, name);

  // Model year of CO's car
  printf("Enter your car's model year: ");
  scanf(" %d", &tempCarOwner.modelYear);

  // Kilometers driven by CO's car
  printf("Enter your car's mileage: ");
  scanf(" %d", &tempCarOwner.odometer);

  // CO's car's transmission
  printf("Enter your car's transmission type (a = automatic, b = manual): ");
  scanf(" %c", &tempCarOwner.transmission);

      // open file for writing
  fp = fopen ("owners.dat", "a");
  if (fp== NULL){
    fprintf(stderr, "\nError opened file\n");
    exit (1);
  }
  
  // write struct to file
  fwrite (&tempCarOwner, sizeof(tempCarOwner), 1, fp);

  if(fwrite != 0)
    printf("Account succesfully created !\n");
  else
    printf("Error writing to file !\n");

  // close file
  fclose (fp);
}

carRenter carRenterDisplay(void){
  FILE *fp;
  carRenter tempCarRenter;
  char Email[50];
  int found = 0;

  // Open renter.dat for reading
  fp = fopen ("renters.dat", "rb");
  if (fp == NULL)
  {
    fprintf(stderr, "\nError opening file\n");
    exit (1);
  }

  printf("Please enter car renter's email: ");
  scanf("%s", &Email); 
  // read file contents till end of file
  while(1){
    fread(&tempCarRenter, sizeof(tempCarRenter), 1, fp);    
    if(feof(fp)){
      break;
    }
    if(!strcmp(tempCarRenter.Email, Email)){
      found = 1;
      printf ("Name: %s\nPhone number: %s\nEmail: %s\nAge: %d\nPostcode: %d\nPreferred car type: %c\nPreferred transmission type: %c\nID: %d",
      tempCarRenter.name, tempCarRenter.phoneNum, tempCarRenter.Email, tempCarRenter.age, tempCarRenter.postCode, tempCarRenter.prefCarType, tempCarRenter.prefTransmissionType,tempCarRenter.ID);   
    }	
  }
  if(found == 0){
    printf("Sorry no record found\n");
  }
  // close file
  fclose (fp);    
  return tempCarRenter;
}

carOwner carOwnerDisplay(void){
  FILE *fp;
  carOwner tempCarOwner;
  char Email[50];
  int found = 0;

  // Open owner.dat for reading
  fp = fopen ("owners.dat", "rb");
  if (fp == NULL)
  {
    fprintf(stderr, "\nError opening file\n");
    exit (1);
  }

  printf("Please enter car owner's email: ");
  scanf("%s", &Email); 
  // read file contents till end of file
  while(1){
    fread(&tempCarOwner, sizeof(tempCarOwner), 1, fp);    
    if(feof(fp)){
      break;
    }
    if(!strcmp(tempCarOwner.Email, Email)){
      found = 1;
      printf ("Name: %s\nPhone number: %s\nEmail: %s\nAge: %d\nPostcode: %d\nCar price: %d\nCar name: %s\nModel year: %d\nKilometers driven: %d\nTransmission type: %c\nID: %d",
      tempCarOwner.name, tempCarOwner.phoneNum, tempCarOwner.Email, tempCarOwner.age, tempCarOwner.postCode, tempCarOwner.price, tempCarOwner.carName, tempCarOwner.modelYear, tempCarOwner.odometer, tempCarOwner.transmission,tempCarOwner.ID);   
    }	
  }
  if(found == 0){
    printf("Sorry no record found");
  }
  // close file
  fclose (fp);    
  return tempCarOwner;
}

void makeDeal (int renterID, int ownerID) {

  FILE *fp;
  tranDet temptrans;
  
  temptrans.transactionID = ((rand() % 1000000)+100000);
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