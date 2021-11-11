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
    
    printf("Hej, og velkommen til vores app, lad os starte med dit fulde navn:");
    getName(fullName);
    
    printf("Hej %s!. Det foerste der skal ske er, at du skal vaelge om du vil leje eller udleje en bil\n", fullName);

    do {
        printf("Oensker du at leje eller udleje en bil?\n'a': Lej en bil\n'b': Udlej en bil");
        ans = getchar();
    } while(ans !='a' && ans != 'b');

    if (ans == 'a')  {
        //the custom datatype carRenter was defined earlier.

        carRenter tempCarRenter = carRenterData(fullName);
        printf("Fulde navn: %s\nAlder: %d\nPostnummer: %d\nE-mail: %s\nTelefonnummer: %s\nForetrukne biltype: %s", tempCarRenter.name,tempCarRenter.age,tempCarRenter.postalCode, tempCarRenter.Email, tempCarRenter.phoneNum, tempCarRenter.prefCarType);
    }

    else if (ans == 'b') {
        //the custom datatype carOwner was defined earlier.
        carOwner tempCarOwner = carOwnerData(fullName);
        printf("Fulde navn: %s\nAlder: %d\nPostnummer: %d\nE-mail: %s\nTelefonnummer: %s\nDin biltype: %s", tempCarOwner.name,tempCarOwner.age,tempCarOwner.postalCode, tempCarOwner.Email, tempCarOwner.phoneNum, tempCarOwner.carType);
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

    printf("Hej %s, for at kommme godt i gang, skal vi have noget mere data om dig, venligst foelg instrukserne:\n lad os starte med din alder:", carOwner1.name);
    scanf("%d",&carOwner1.age);
    //Postnummer
    printf("Indtast her postkoden for det omraade i Aalborg, som du oensker at leje en bil i:");
    scanf("%d", &carOwner1.postalCode);
    //Email
    printf("Der skal derudover bruges nogle personlige oplysninger omkring dig. Indtast nu din E-mail:");
    scanf("%s",&carOwner1.Email);
    //Tlf.nr.
    printf("Indtast nu tlf.nr.:");
    scanf("%s",&carOwner1.phoneNum);
    //Foretrukne bil type
    printf("Indtast nu den oenskede type bil, du oensker at leje:");
    scanf("%s",&carOwner1.carType);
    
    return carOwner1;
}

//The function that fetches data for a car renter
carRenter carRenterData(char userName[]) {
    carRenter carRenter1;
    
    //copies the username that was given earlier to the renter struct name
    strcpy(carRenter1.name,userName);

    //alder
    printf("Hej %s, for at kommme godt i gang, skal vi have noget mere data om dig, venligst foelg instrukserne:\n lad os starte med din alder:", carRenter1.name);
    scanf("%d",&carRenter1.age);
    //Postnummer
    printf("Indtast her postkoden for det omraade i Aalborg, som du oensker at leje en bil i:");
    scanf("%d", &carRenter1.postalCode);
    //Email
    printf("Der skal derudover bruges nogle personlige oplysninger omkring dig. Indtast nu din E-mail:");
    scanf("%s",&carRenter1.Email);
    //Tlf.nr.
    printf("Indtast nu tlf.nr.:");
    scanf("%s",&carRenter1.phoneNum);
    //Foretrukne bil type
    printf("Indtast nu den oenskede type bil, du oensker at leje:");
    scanf("%s",&carRenter1.prefCarType);

    return carRenter1;
}
