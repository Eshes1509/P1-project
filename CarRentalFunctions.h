#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>

typedef struct transactionData {
  int     transactionID;
  int     renterID;
  char    renterName[50];
  char    renterEmail[50];
  int     ownerID;
  char    ownerName[50];
  char    ownerEmail[50];
  char    carName[50];
  bool    ownerRated;
  bool    renterRated;
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
  char    carType;
  int     modelYear; // Model year of CO's car
  int     odometer; // kilometers driven by CO's car
  char    transmission; // CO's car's transmission | a = auto, b = manual
  char    CarDescription[100];
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

//user logins
carRenter     carRenter1;
carOwner      carOwner1;
bool          RenterLoggedIn = 0;
bool          OwnerLoggedIn = 0;

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

//Function that creates and stores a deal between two users 
void makeDeal (carOwner tempCarOwner) {

  FILE                            *fp;
  tranDet                         tempTrans;
  
  //ID's
  tempTrans.transactionID =       ((rand() % 1000000)+100000);
  tempTrans.renterID =            carRenter1.ID;
  tempTrans.ownerID =             tempCarOwner.ID;

  tempTrans.renterRated =         0;
  tempTrans.ownerRated =          0;
  //emails
  strcpy(tempTrans.renterEmail,   carRenter1.Email);
  strcpy(tempTrans.ownerEmail,    tempCarOwner.Email);
  //names
  strcpy(tempTrans.renterName,    carRenter1.name);
  strcpy(tempTrans.ownerName,     tempCarOwner.name);
  strcpy(tempTrans.carName,       tempCarOwner.carName);

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
  FILE      *fp;
  FILE      *fp1;
  carRenter tempCarRenter;
  carOwner tempCarOwner;
  int found = 0;
  double rate;
  long int pos;
  //If the person rating is a renter, the person that has to be rated is an owner, therefore open owner.dat

  // read file contents till end of file
  fp1 = fopen("temp.dat", "wb");

  if (ans == 'a') {

    fp = fopen ("owners.dat", "rb");

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

    fp = fopen ("renters.dat", "rb");

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
  
  if (RenterLoggedIn == 1) {
    ans = 'a';
  }

  else if (OwnerLoggedIn == 1) {
    ans = 'b';
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

    if (ans == 'a' && (!strcmp(tempTrans.renterEmail , carRenter1.Email)) && tempTrans.renterRated == 0) {
     
      found = 1;
    }

    else if (ans == 'b' && (!strcmp(tempTrans.ownerEmail , carOwner1.Email)) && tempTrans.ownerRated == 0) {
      
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
    if (RenterLoggedIn = 1) {
      printf("\nYou have made a deal with the transaction details:\nID: %d\nCounter Part Name: %s\nCounter Part Email: %s\nCar name: %s\nDo you wish to rate this deal?\ny: yes\nn: no\n", 
      tempTrans.transactionID, tempTrans.ownerName, tempTrans.ownerEmail, tempTrans.carName);
    }
    else if(OwnerLoggedIn = 1) {
      printf("\nYou have made a deal with the transaction details:\nID: %d\nCounter Part Name: %s\nCounter Part Email: %s\nDo you wish to rate this deal?\ny: yes\nn: no\n", 
      tempTrans.transactionID, tempTrans.renterName, tempTrans.renterEmail);
    }
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