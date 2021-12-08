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
    char    carType; // Type of CO's car (a: city car/hatchback, b: sedan/station car, c: SUV/Van)
    int     modelYear; // Model year of CO's car
    int     odometer; // kilometers driven by CO's car
    char    transmission; // CO's car's transmission | a = auto, b = manual
    char    CarDescription; // Small description of the car
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
carRenter carRenterDisplay(carRenter carRenter1);
carOwner carOwnerDisplay(carOwner carOwner1);
carRenter carRenterEdit(carRenter carRenter1);
carOwner carOwnerEdit(carOwner carOwner1);
carRenter carRenterSelect(char Email[]);
carOwner carOwnerSelect(char Email[]);
int userSelect(char Email[]);

int main(void) {
    int ans = 0;
    int isRenter = -1;
    char Email[50];
    carRenter carRenter1;
    carOwner carOwner1;

    printf("1. Sign in\n2. Sign up\n");
    do{
      scanf("%d", &ans);  
    } while(ans < 1 && ans > 2);

    if(ans == 1){
      printf("Please enter your email: ");
      scanf("%s", &Email); 

      do{
        isRenter = userSelect(Email); 
      } while(isRenter < 0);
      
      if(isRenter == 1){
        carRenter1 = carRenterSelect(Email);
        printf("Welcome back %s!\n", carRenter1.name);
        
        printf("1. Rent a car\n2. View your profile\n3. Edit your profile\n");
        do{
          scanf("%d", &ans);  
        } while(ans < 1 && ans > 3);

        if(ans == 1){

        }
        else if(ans == 2){
          carRenterDisplay(carRenter1);
        }
        else if(ans == 3){
          carRenterEdit(carRenter1);
        }
      }
      else if(isRenter == 0){
        carOwner1 = carOwnerSelect(Email);
        printf("Welcome back %s!\n", carOwner1.name);

        printf("1. View your car rental history\n2. View your profile\n3. Edit your profile\n");
        do{
          scanf("%d", &ans);  
        } while(ans < 1 && ans > 3);

        if(ans == 1){

        }
        else if(ans == 2){
          carOwnerDisplay(carOwner1);
        }
        else if(ans == 3){
          carOwnerEdit(carOwner1);
        }
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
    printf("Enter preferred type of car a, b or c (a = city car/hatchback, b = sedan/station car, c = SUV/Van): ");
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

    // CO's car type
    printf("What type is your car? (a: city car/hatchback, b: sedan/station car, c: SUV/Van): ");
    scanf(" %c", &tempCarOwner.carType);

    // Model year of CO's car
    printf("Enter your car's model year: ");
    scanf(" %d", &tempCarOwner.modelYear);

    // Kilometers driven by CO's car
    printf("Enter your car's mileage: ");
    scanf(" %d", &tempCarOwner.odometer);

    // CO's car's transmission
    printf("Enter your car's transmission type (a = automatic, b = manual): ");
    scanf(" %c", &tempCarOwner.transmission);

    printf("Please give a small desription of your car:\n");
    scanf(" %s", &tempCarOwner.CarDescription);

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

int userSelect(char Email[]){
    FILE *fp, *fp1;
    carRenter tempCarRenter;
    carOwner tempCarOwner;
    int found = 0;
    
    // Open renters.dat for reading
    fp = fopen ("renters.dat", "rb");
    if (fp == NULL)
    {
    	fprintf(stderr, "\nError opening file\n");
    	exit (1);
    }
    // Open owners.dat for reading
    fp1 = fopen ("owners.dat", "rb");
    if (fp1 == NULL)
    {
    	fprintf(stderr, "\nError opening file\n");
    	exit (1);
    }

    // read file contents till end of file
    while(1){
      fread(&tempCarRenter, sizeof(tempCarRenter), 1, fp);    
      if(feof(fp)){
        break;
      }
      if(!strcmp(tempCarRenter.Email, Email)){
        found = 1;
        fclose(fp);
        fclose(fp1);
        return 1;
      }	
    }

    while(1){
      fread(&tempCarOwner, sizeof(tempCarOwner), 1, fp1);    
      if(feof(fp1)){
        break;
      }
      if(!strcmp(tempCarOwner.Email, Email)){
        found = 1;
        fclose(fp);
        fclose(fp1);        
        return 0; 
      }	
    }    

    if(found == 0){
      printf("Sorry no record found\n");
    }

    // close file
    fclose (fp);   
    fclose (fp1); 
    return -1;
}

carRenter carRenterSelect(char Email[]){
    FILE *fp;
    carRenter tempCarRenter;
    int found = 0;

    // Open renters.dat for reading
    fp = fopen ("renters.dat", "rb");
    if (fp == NULL)
    {
    	fprintf(stderr, "\nError opening file\n");
    	exit (1);
    }
 
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

carOwner carOwnerSelect(char Email[]){
    FILE *fp;
    carOwner tempCarOwner;
    int found = 0;

    // Open owners.dat for reading
    fp = fopen ("owners.dat", "rb");
    if (fp == NULL)
    {
    	fprintf(stderr, "\nError opening file\n");
    	exit (1);
    }

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

carRenter carRenterDisplay(carRenter carRenter1){

    printf ("Name: %s\nPhone number: %s\nEmail: %s\nAge: %d\nPostcode: %d\nPreferred car type: %c\nPreferred transmission type: %c\n",
    carRenter1.name, carRenter1.phoneNum, carRenter1.Email, carRenter1.age, carRenter1.postCode, carRenter1.prefCarType, carRenter1.prefTransmissionType);   

}

carOwner carOwnerDisplay(carOwner carOwner1){

    printf ("Name: %s\nPhone number: %s\nEmail: %s\nAge: %d\nPostcode: %d\nCar price: %d dkk per hour\nCar name: %s\nModel year: %d\nKilometers driven: %d\nTransmission type: %c\nDescription: %s",
    carOwner1.name, carOwner1.phoneNum, carOwner1.Email, carOwner1.age, carOwner1.postCode, carOwner1.price, carOwner1.carName, carOwner1.modelYear, carOwner1.odometer, carOwner1.transmission, carOwner1.CarDescription);   

}

carRenter carRenterEdit(carRenter carRenter1){
    FILE *fp, *fp1;
    carRenter tempCarRenter;
    char name[50];
    int found = 0;

    fp = fopen("renters.dat","rb");
    fp1 = fopen("temp.dat","wb");

    while(1){
      fread(&tempCarRenter, sizeof(tempCarRenter), 1, fp);
      if(feof(fp)){
        break;
      }
      if(!strcmp(tempCarRenter.Email, carRenter1.Email)){
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
        printf("Enter preferred type of car (a = city car/hatchback, b = sedan/station car, c = SUV/Van): ");
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

carOwner carOwnerEdit(carOwner carOwner1){
    FILE *fp, *fp1;
    carOwner tempCarOwner;
    char name[50];
    int found = 0;

    fp = fopen("owners.dat","rb");
    fp1 = fopen("temp.dat","wb");

    while(1){
      fread(&tempCarOwner, sizeof(tempCarOwner), 1, fp);
      if(feof(fp)){
        break;
      }
      if(!strcmp(tempCarOwner.Email, carOwner1.Email)){
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
        printf("What type is your car? (a: city car/hatchback, b: sedan/station car, c: SUV/Van): ");
        scanf(" %c", &tempCarOwner.carType);
        printf("Enter your car's model year: ");
        scanf(" %d", &tempCarOwner.modelYear);
        printf("Enter your car's mileage: ");
        scanf(" %d", &tempCarOwner.odometer);
        printf("Enter your car's transmission type (a = automatic, b = manual): ");
        scanf(" %c", &tempCarOwner.transmission);
        printf("Please give a small desription of your car:\n ");
        scanf(" %s", &tempCarOwner.CarDescription);
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