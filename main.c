#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct carOwnerData {
    char    name[50];
    char    phoneNum[9];
    char    Email[50];
    char    carType[50];
    int     age;
    int     postalCode;
    double  rating[];
} carOwner;

typedef struct carRenterData {
    char    name[50];
    char    phoneNum[9];
    char    Email[50];
    char    prefCarType[50];
    int     age;
    int     postalCode;
    double  rating[];
} carRenter;

void getName (char name[]);
carOwner carOwnerData(char userName[]);
carRenter carRenterData(char userName[]);

int main(void) {
    carOwner *allOwners = (carOwner*) malloc(sizeof(carOwner) * 3);

    char fullName[50];
    char ans;
    
    printf("Hello and welcome to our, please enter your full name: ");
    getName(fullName);
    
    printf("Hello %s!. First off, we would like to know whether you would want to rent a car or rent out a car\n", fullName);

    do {
        printf("'a': Rent a  car\n'b': Rent out a car\n");
        ans = getchar();
    } while(ans !='a' && ans != 'b');

    if (ans == 'a')  {
        //the custom datatype carRenter was defined earlier.

        carRenter tempCarRenter = carRenterData(fullName);
        printf("Full name: %s\nAge: %d\nPostal code: %d\nE-mail: %s\nPhone number: %s\nPreffered car type: %s\n", tempCarRenter.name,tempCarRenter.age,tempCarRenter.postalCode, tempCarRenter.Email, tempCarRenter.phoneNum, tempCarRenter.prefCarType);
    }

    else if (ans == 'b') {
        //the custom datatype carOwner was defined earlier.
        carOwner tempCarOwner = carOwnerData(fullName);
        printf("Full name: %s\nAge: %d\nPostal code: %d\nE-mail: %s\nPhone Number: %s\nYour car type: %s\n", tempCarOwner.name,tempCarOwner.age,tempCarOwner.postalCode, tempCarOwner.Email, tempCarOwner.phoneNum, tempCarOwner.carType);
    }
    
}
//The function that optains the name of the user. Use of dynamic memory allocation. Remember to free(); when done using it
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
carOwner carOwnerData(char userName[]) {
    carOwner carOwner1;

    strcpy(carOwner1.name,userName);

    printf("Hello %s, we would like to know more about you.\nLet us start off with your age: ", carOwner1.name);
    scanf("%d",&carOwner1.age);
    //Postnummer
    printf("Enter the postal code, you would like to rent out your car in: ");
    scanf("%d", &carOwner1.postalCode);
    //Email
    printf("Furthermore, we would like to gather some more personal details as well. Please enter your E-mail: ");
    scanf("%s",&carOwner1.Email);
    //Tlf.nr.
    printf("Please enter your Phone number: ");
    scanf("%s",&carOwner1.phoneNum);
    //Foretrukne bil type
    printf("What car type is the car you are renting out?: "); /* Type A - dyre B - middel C - billige */
    scanf("%s",&carOwner1.carType);
    
    return carOwner1;
}

//The function that fetches data for a car renter
carRenter carRenterData(char userName[]) {
    carRenter carRenter1;
    
    //copies the username that was given earlier to the renter struct name
    strcpy(carRenter1.name,userName);

    //alder
    printf("Hello %s, we would like to know more about you.\nLet us start off with your age: ", carRenter1.name);
    scanf("%d",&carRenter1.age);
    //Postnummer
    printf("Enter the postal code, you would like to rent a car in: ");
    scanf("%d", &carRenter1.postalCode);
    //Email
    printf("Furthermore, we would like to gather some more personal details as well. Please enter your E-mail: ");
    scanf("%s",&carRenter1.Email);
    //Tlf.nr.
    printf("Please enter your Phone number: ");
    scanf("%s",&carRenter1.phoneNum);
    //Foretrukne bil type
    printf("What car type is the car you want to rent?: ");
    scanf("%s",&carRenter1.prefCarType);

    return carRenter1;
}

/* Idéer til programmet */
/* - Mulighed for at sortere biler efter pris, 
når man har valgt hvilken type bil du gerne vil have og listen med dem er kommet frem */