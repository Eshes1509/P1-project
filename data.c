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
    double  rating[]; // rating of CO
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
    double  rating[]; // rating of CR
} carRenter;

void getName (char name[]);
carOwner carOwnerData(char userName[]);
carRenter carRenterData(char userName[]);


int main(void) {
    carOwner *allOwners = (carOwner*) malloc(sizeof(carOwner) * 3);

    char fullName[50];
    char ans;

    FILE *output_file_pointer; // pointer to a file

    printf("Hej, og velkommen til vores app, lad os starte med dit fulde navn: ");
    getName(fullName);

    printf("Hej %s!. Det foerste der skal ske er, at du skal vaelge om du vil leje eller udleje en bil\n", fullName);

    do {
        printf("Oensker du at leje eller udleje en bil?\n'a': Lej en bil\n'b': Udlej en bil:\n");
        ans = getchar();
    } while(ans !='a' && ans != 'b');

    if (ans == 'a')  {
        //the custom datatype carRenter was defined earlier.

        carRenter tempCarRenter = carRenterData(fullName);
        output_file_pointer = fopen("renters.txt", "a");
        fprintf(output_file_pointer, "%s, %s, %s, %d, %d, %c, %c, %fl.\n", tempCarRenter.name, tempCarRenter.phoneNum, tempCarRenter.Email, tempCarRenter.age, tempCarRenter.postCode, tempCarRenter.prefCarType, tempCarRenter.prefTransmissionType, tempCarRenter.rating[0]);
        fclose(output_file_pointer);
        printf("Fulde navn: %s\n"
               "Telefonnummer: %s\n"
               "E-mail: %s\n"
               "Alder: %d\n"
               "Postnummer: %d\n"
               "Foretrukket prisklasse: %c\n"
               "Gearskift type: %c\n"
               "Stjerner: %fl.\n", tempCarRenter.name, tempCarRenter.phoneNum, tempCarRenter.Email, tempCarRenter.age, tempCarRenter.postCode, tempCarRenter.prefCarType, tempCarRenter.prefTransmissionType, tempCarRenter.rating[0]);
    }

    else if (ans == 'b') {
        //the custom datatype carOwner was defined earlier.
        carOwner tempCarOwner = carOwnerData(fullName);
        output_file_pointer = fopen("owners.txt", "a");
        fprintf(output_file_pointer, "%s, %s, %s, %d, %d, %d, %s, %d, %d, %c, %fl.\n", tempCarOwner.name, tempCarOwner.phoneNum, tempCarOwner.Email, tempCarOwner.age, tempCarOwner.postCode, tempCarOwner.price, tempCarOwner.carName, tempCarOwner.modelYear, tempCarOwner.odometer, tempCarOwner.transmission, tempCarOwner.rating[0]);
        fclose(output_file_pointer);
        printf("Fulde navn: %s\n"
               "Telefonnummer: %s\n"
               "E-mail: %s\n"
               "Alder: %d\n"
               "Postnummer: %d\n"
               "Pris/time: %d\n"
               "Bil navn: %s\n"
               "Modelaar: %d\n"
               "Kilometer koert: %d\n"
               "Gearskift type: %c\n"
               "Stjerner: %fl.\n", tempCarOwner.name, tempCarOwner.phoneNum, tempCarOwner.Email, tempCarOwner.age, tempCarOwner.postCode, tempCarOwner.price, tempCarOwner.carName, tempCarOwner.modelYear, tempCarOwner.odometer, tempCarOwner.transmission, tempCarOwner.rating[0]);
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
    char temp;


    // Name
    strcpy(carOwner1.name,userName);

    // Phonenumber
    printf("Indtast nu tlf.nr.: ");
    scanf("%s", &carOwner1.phoneNum);

    // Email
    printf("Der skal derudover bruges nogle personlige oplysninger omkring dig. Indtast nu din E-mail: ");
    scanf("%s", &carOwner1.Email);

    // Age
    printf("Hej %s, for at kommme godt i gang, skal vi have noget mere data om dig, venligst foelg instrukserne:\nLad os starte med din alder: ", carOwner1.name);
    scanf("%d", &carOwner1.age);

    // Postcode
    printf("Indtast her postkoden for det omraade i Aalborg, som du oensker at udleje din bil i: ");
    scanf("%d", &carOwner1.postCode);

    // Price of CO's car
    printf("Indtast hvor meget din bil skal koste at udleje per time: ");
    scanf("%d", &carOwner1.price);

    // CO's car's name
    printf("Intast navnet af din bil: ");
    scanf("%c",&temp);
    scanf("%[^\n]", carOwner1.carName);

    // Model year of CO's car
    printf("Indtast modelaar af din bil: ");
    scanf("%d", &carOwner1.modelYear);

    // Kilometers driven by CO's car
    printf("Indtast kilometertallet af din bil: ");
    scanf("%d", &carOwner1.odometer);

    // CO's car's transmission
    printf("Intast om din bil har automat eller manuelt gear (a = auto, b = manuelt): ");
    scanf("%c", &temp);
    scanf("%c", &carOwner1.transmission);

    return carOwner1;
}

//The function that fetches data for a car renter
carRenter carRenterData(char userName[]) {
    carRenter carRenter1;
    char temp; // Used in 'scanf("%c", &temp);' It clears the print buffer

    // Name
    strcpy(carRenter1.name,userName);

    // Phonenumber
    printf("Indtast nu tlf.nr.: ");
    scanf("%s", &carRenter1.phoneNum);

    // Email
    printf("Der skal derudover bruges nogle personlige oplysninger omkring dig. Indtast nu din E-mail: ");
    scanf("%s", &carRenter1.Email);

    // Age
    printf("Hej %s, for at kommme godt i gang, skal vi have noget mere data om dig, venligst foelg instrukserne:\nLad os starte med din alder: ", carRenter1.name);
    scanf("%d", &carRenter1.age);

    // Postcode
    printf("Indtast her postkoden for det omraade i Aalborg, som du oensker at leje en bil i: ");
    scanf("%d", &carRenter1.postCode);


    // Preffered car type
    printf("Indtast nu den oenskede type bil, du oensker at leje (a = 0 til x kr, b = x+1 til y kr, c = y+1 til z kr): ");
    scanf("%c", &temp);
    scanf("%c", &carRenter1.prefCarType);

    // Preffered transmission type
    printf("Indtast din foretrukne gearskift (a = automat, b = manuelt,  c = begge)): ");
    scanf("%c", &temp);
    scanf("%c", &carRenter1.prefTransmissionType);

    return carRenter1;
}

/* Idéer til programmet */
/* - Mulighed for at sortere biler efter pris,
når man har valgt hvilken type bil du gerne vil have og listen med dem er kommet frem */
