#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct carOwnerData {
    // values set by user
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

carOwner carOwnerData();
carOwner carOwnerDisplay();
carRenter carRenterData();
carRenter carRenterDisplay();
void display_all_cars();
void edit_car_renter();
void edit_car_owner();

int main(void) {
  int ans;

  printf("1. Sign in\n2. Sign up as renter\n3. Sign up as owner\n4. Edit car renter\n5. Edit car owner\n6. Display car renter information\n7. Display car owner information\n8. Display all cars\n");
  do{
    scanf("%d", &ans);  
  } while(ans < 1 && ans > 8);
  
  switch (ans)
  {
  case 1: 
    break;
  case 2: carRenterData();
    break;
  case 3: carOwnerData();
    break;
  case 4: edit_car_renter();
    break;
  case 5: edit_car_owner();
    break;
  case 6: carRenterDisplay();
    break;
  case 7: carOwnerDisplay();
    break;
  case 8: display_all_cars();
    break;
  }

  return 0;
}

//The function that optains the name of the user and car. Use of dynamic memory allocation. Remember to free(); when done using it
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

//The function that fetches data for a car owner
carOwner carOwnerData() {
    FILE *fp;
    carOwner tempCarOwner;
    char name[50];

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

//The function that fetches data for a car renter
carRenter carRenterData() {
    FILE *fp;
    carRenter tempCarRenter;
    char name[50];
    
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

carRenter carRenterDisplay(){
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
        printf ("Name: %s\nPhone number: %s\nEmail: %s\nAge: %d\nPostcode: %d\nPreferred car type: %c\nPreferred transmission type: %c\n",
        tempCarRenter.name, tempCarRenter.phoneNum, tempCarRenter.Email, tempCarRenter.age, tempCarRenter.postCode, tempCarRenter.prefCarType, tempCarRenter.prefTransmissionType);   
      }	
    }
    if(found == 0){
      printf("Sorry no record found");
    }
    // close file
    fclose (fp);    
    return tempCarRenter;
}

carOwner carOwnerDisplay(){
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
        printf ("Name: %s\nPhone number: %s\nEmail: %s\nAge: %d\nPostcode: %d\nCar price: %d\nCar name: %s\nModel year: %d\nKilometers driven: %d\nTransmission type: %c\n",
        tempCarOwner.name, tempCarOwner.phoneNum, tempCarOwner.Email, tempCarOwner.age, tempCarOwner.postCode, tempCarOwner.price, tempCarOwner.carName, tempCarOwner.modelYear, tempCarOwner.odometer, tempCarOwner.transmission);   
      }	
    }
    if(found == 0){
      printf("Sorry no record found");
    }
    // close file
    fclose (fp);    
    return tempCarOwner;
}

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

void edit_car_renter(){
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

void edit_car_owner(){
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