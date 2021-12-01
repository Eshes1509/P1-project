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

carRenter carRenterData();
carOwner carOwnerData();
carRenter carRenterSelect();
carOwner carOwnerSelect();

int main(void) {
    int ans;
    carRenter tempCarRenter;
    carOwner tempCarOwner;

    printf("1. Sign in\n2. Sign up\n");
    do{
      scanf("%d", &ans);  
    } while(ans < 1 && ans > 2);

    if(ans == 1){
      printf("1. Sign in as renter\n2. Sign in as owner\n");
      do{
        scanf("%d", &ans);  
      } while(ans < 1 && ans > 2);      

      if(ans == 1){
        tempCarRenter = carRenterSelect();
        printf("Welcome back %s!", tempCarRenter.name);
      }
      else if(ans == 2){
        tempCarOwner = carOwnerSelect();
        printf("Welcome back %s!", tempCarOwner.name);
      }
    }
    else if(ans == 2){
      printf("1. Sign up as renter\n2. Sign up as owner\n");
      do{
        scanf("%d", &ans);  
      } while(ans < 1 && ans > 2);      

      if(ans == 1){
        carRenterData();
      }
      else if(ans == 2){
        carOwnerData();
      }
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

carRenter carRenterSelect(){
    FILE *fp;
    carRenter tempCarRenter;
    char Email[50];
    int found = 0;

    // Open renters.dat for reading
    fp = fopen ("renters.dat", "rb");
    if (fp == NULL)
    {
    	fprintf(stderr, "\nError opening file\n");
    	exit (1);
    }

    printf("Please enter your email: ");
    scanf("%s", &Email); 
    // read file contents till end of file
    while(1){
      fread(&tempCarRenter, sizeof(tempCarRenter), 1, fp);    
      if(feof(fp)){
        break;
      }
      if(!strcmp(tempCarRenter.Email, Email)){
        found = 1;  
        break;
      }	
    }
    if(found == 0){
      printf("Sorry no record found\n");
    }
    // close file
    fclose (fp);    
    return tempCarRenter;
}

carOwner carOwnerSelect(){
    FILE *fp;
    carOwner tempCarOwner;
    char Email[50];
    int found = 0;

    // Open owners.dat for reading
    fp = fopen ("owners.dat", "rb");
    if (fp == NULL)
    {
    	fprintf(stderr, "\nError opening file\n");
    	exit (1);
    }

    printf("Please enter your email: ");
    scanf("%s", &Email); 
    // read file contents till end of file
    while(1){
      fread(&tempCarOwner, sizeof(tempCarOwner), 1, fp);    
      if(feof(fp)){
        break;
      }
      if(!strcmp(tempCarOwner.Email, Email)){
        found = 1; 
        break; 
      }	
    }
    if(found == 0){
      printf("Sorry no record found\n");
    }
    // close file
    fclose (fp);    
    return tempCarOwner;
}