#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>

typedef struct transactionData {
  int transactionID;
  int renterID;
  char renterEmail[50];
  int ownerID;
  char ownerEmail[50];
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
  double  rating;
  int     ratingAmount;
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
  double  rating;
  int     ratingAmount;
  // values set by program
  //double  rating[]; // rating of CR
} carRenter;

void getName (char name[]) {

  char *fullName = (char*) malloc(50);

  /*Checks if memory allocation was sucessfull*/
  if (fullName == NULL) {
    printf("Memory allocation failed");
    exit(0);
  }

  //Is able to obtain a string including spaces
  gets(fullName);

  strcpy(name, fullName);

  free(fullName);
}

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

  //Rating
  tempCarRenter.rating = 0;
  tempCarRenter.ratingAmount = 0;
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

  tempCarOwner.rating = 0;
  tempCarOwner.ratingAmount = 0;

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

//finds a renter in renter data file
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
      printf ("Name: %s\nPhone number: %s\nEmail: %s\nAge: %d\nPostcode: %d\nPreferred car type: %c\nPreferred transmission type: %c\nID: %d\nRating: %lf(%d ratings)\n",
      tempCarRenter.name, tempCarRenter.phoneNum, tempCarRenter.Email, tempCarRenter.age, tempCarRenter.postCode, tempCarRenter.prefCarType, tempCarRenter.prefTransmissionType,tempCarRenter.ID, tempCarRenter.rating, tempCarRenter.ratingAmount);   
    }	
  }
  if(found == 0){
    printf("Sorry no record found\n");
  }
  // close file
  fclose (fp);    
  return tempCarRenter;
}

//finds an owner in owner data file
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
      printf ("Name: %s\nPhone number: %s\nEmail: %s\nAge: %d\nPostcode: %d\nCar price: %d\nCar name: %s\nModel year: %d\nKilometers driven: %d\nTransmission type: %c\nID: %d\nRating: %lf (%d Ratings)\n",
      tempCarOwner.name, tempCarOwner.phoneNum, tempCarOwner.Email, tempCarOwner.age, tempCarOwner.postCode, tempCarOwner.price, tempCarOwner.carName, tempCarOwner.modelYear, tempCarOwner.odometer, tempCarOwner.transmission,tempCarOwner.ID, tempCarOwner.rating, tempCarOwner.ratingAmount);   
    }	
  }
  if(found == 0){
    printf("Sorry no record found");
  }
  // close file
  fclose (fp);    
  return tempCarOwner;
}

//Function that creates and stores a deal between two users 
void makeDeal (void) {

  FILE                            *fp;
  tranDet                         tempTrans;
  carOwner                        dealOwner;
  carRenter                       dealRenter;
  tempTrans.transactionID =       ((rand() % 1000000)+100000);
  tempTrans.isDone =              0;
  dealRenter =                    carRenterDisplay();
  dealOwner =                     carOwnerDisplay();
  strcpy(tempTrans.renterEmail,   dealRenter.Email);
  strcpy(tempTrans.ownerEmail,    dealOwner.Email);
  //open file
  fp = fopen ("transactions.dat", "wb");

  if (fp== NULL){
    fprintf(stderr, "\nError opened file\n");
    exit (1);
  }
  
  fwrite (&tempTrans, sizeof(tempTrans), 1, fp);

  if(fwrite != 0) {
    printf("Transaction completed\n");
  }

  else {
    printf("Error writing to file !\n");
  }

  // close file
  fclose (fp);
}

//Function that enables a user to rate another, if they have had a deal with them
void userRating(char userEmail[], char ans) {
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

//Function that finds transactions for a user
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
      userRating (tempTrans.ownerEmail, ans);
    }

    else if (ans == 'b' && ans2 == 'y') {
      userRating (tempTrans.renterEmail, ans);
    }

    else if (ans2 == 'n') {
      exit(1);
    }

    } while(ans2 != 'y' && ans2 != 'n');
  }  

}

