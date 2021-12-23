//Foster Higginbotham's File.
//This project will demonstrate the ability to write and apply C code to create a command-line game.
//In this case, i have created a "Vacation Generator".

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>


/* i use a 'struct' to create a grouped list of variables under one name
 * counter which is used as a max of 5, with a balance that is held for the user
 * balance which is used for the balance of wins during the simulator's runtime
 * probability is a reused value that is used to store the probability value
*/

struct user{
    int counter, balance;
    float probability;
};

typedef struct user Player;

// function prototypes
void Vacation(Player *p);
int Menu();
void Simulator();
Player *ConstructPlayer();
void FishingActivity(Player *p);
void SellFish(char finalList[5][10]);
void GemActivity(Player *p);
void SellGems(char finalList[5][10]);
void BirdWatching(Player *p);
void SellBirdPhoto(char finalList[5][10]);
void ResetCounter(Player *p);
int CheckNextSpot(char finalList [5][10]);

// constructor for player
Player *ConstructPlayer(){
    // malloc the memory of the player to the pointer
    Player *p = malloc(sizeof(Player)*1);
    // initialize the variables
    p->counter = 0;
    p->balance = 0;
    p->probability = 0;
    // greet the user
    printf("Welcome to your island vacation!!!");
    return p;
}

// vacation - handles the switch case logic for the menu input
void Vacation(Player *p){
    switch (Menu()){ // switch base off the menu selection
        case -1: // exit
            printf("Your final wallet size was: %d\nThank you for playing!!", p->balance);
            exit(0);
        case 1: // fishing activity
            FishingActivity(p);
            break;
        case 2: // gem activity
            GemActivity(p);
            break;
        case 3: // bird photo activity
            BirdWatching(p);
            break;
    }
}

// checks the input of the userInput
bool CheckInput(int userInput){
    // if the userInput isn't the inputs that we want we will return false
    if (userInput != -1 && userInput != 1 && userInput != 2 && userInput != 3){
        return false;
    } else { // else we return true
        return true;
    }
}

// the menu that the user sees
int Menu() {
    // initialize the value to 0
    int userInput = 0;
    while(true){ // while loop keeps checking
        printf("\n \nWhat activity do you want to perform?\n1 = Fishing\n2 = Gem Digging\n3 = Birdwatching\n-1 = QUIT\n");
        scanf("%d", &userInput); // scan value from the user
        if (CheckInput(userInput)){ // our condition to break us out
            return userInput;
        }

    }
}

// fishing activity
void FishingActivity(Player *p){

    char fishList[5][10]={"nothing","snooks","trouts", "catfish", "koi"}; // all of the fish
    char finalList [5][10] = { "", "", "", "", ""}; // final list of the fish, which is empty - gets filled in later

    int userInput = 0; // collect user input with this value
    while(true){ // while the condition is true we'll keep looping

        // check if our counter is up to five
        if(p->counter == 5) {
            ResetCounter(p); //reset the counter back to 0
            SellFish(finalList); // sell fish
            Vacation(p); // go back to the menu
            return;
        } else if (p->counter == 0){ // the first message, should be displayed once!
            printf("\nLet's go fishing! ");
        }

        printf("Are you ready to cast your line?\n(1 = yes,-1 = quit) ");
        scanf("%d", &userInput); // collect userInput

        if (userInput == -1){ // if the user wants to quit
            ResetCounter(p); // reset the counter
            SellFish(finalList); // sell fish from the fish lists
            Vacation(p); // go back to the menu
        }

        p->counter++; // increment the counter
        p->probability = (float)rand()/(float)(RAND_MAX/100); // perform some probability

        // check the probability & add balance to player
        if(p->probability >= 50){
            printf("You caught a %s!!!!\n", fishList[0]);
            strcpy(finalList[CheckNextSpot(finalList)], fishList[0]);
        } else if (p->probability >= 25){
            printf("You caught a %s!!!!\n", fishList[1]);
            strcpy(finalList[CheckNextSpot(finalList)], fishList[1]);
            p->balance += 500;
        } else if (p->probability >= 15){
            printf("You caught a %s!!!!\n", fishList[2]);
            strcpy(finalList[CheckNextSpot(finalList)], fishList[2]);
            p->balance += 1000;
        } else if (p->probability >= 7.5){
            printf("You caught a %s!!!!\n", fishList[3]);
            strcpy(finalList[CheckNextSpot(finalList)], fishList[3]);
            p->balance += 3500;
        } else if ((p->probability >= 2.5) || (p->probability < 2.5)) {
            printf("You caught a %s!!!!\n", fishList[4]);
            strcpy(finalList[CheckNextSpot(finalList)], fishList[4]);
            p->balance += 5000;
        }
    }
}

// sell fish
void SellFish(char finalList[5][10]){
    // counters for each fish
    int snooksCounter = 0, troutsCounter = 0, catfishCounter = 0, koiCounter = 0;
    for(int i = 0; i < 5; i++){ // loop through the size of the finalList
        printf("%s\n", finalList[i]);
        // check which fish is in the value
        if (strcmp(finalList[i], "snooks") == 0){
            snooksCounter++;
        } else if (strcmp(finalList[i], "trouts") == 0){
            troutsCounter++;
        } else if (strcmp(finalList[i], "catfish") == 0){
            catfishCounter++;
        } else if (strcmp(finalList[i], "koi") == 0){
            koiCounter++;
        }
    }
    // output the fish sold
    printf("Selling this many fish: %d snooks, %d trouts, %d catfish, %d koi", snooksCounter, troutsCounter, catfishCounter, koiCounter);
}

// gem activity
void GemActivity(Player *p){

    char gemList[5][10]={"nothing","ruby","sapphire", "emerald", "diamond"}; // array of gems
    char finalList [5][10] = { "", "", "", "", ""}; // array of empty values
    int chance, userInput = 0; // chance is a random Number from one value to another, due to multiple values in the list containing the same percentage, we choose random

    while(true){

        if(p->counter == 5) { // check if the counter reaches to five
            ResetCounter(p); // reset the counter
            SellGems(finalList); // sell the gems
            Vacation(p); // go back to the menu
            return;
        } else if (p->counter == 0){
            printf("\n\nLet's go digging for gems! "); // prompt first message
        }

        printf("Are you ready to dig?\n(1 = yes,-1 = quit) ");
        scanf("%d", &userInput); // prompt user input
        if (userInput == -1){ // if the user wants to quit
            ResetCounter(p); // reset the counter
            SellGems(finalList); // sell the gems
            Vacation(p); // go back to the menu
        }

        p->counter++;
        p->probability = (float)rand()/(float)(RAND_MAX/100); // grab a random number from 0-100

        // check the probability & add balance to player
        if(p->probability >= 80){
            printf("Dang, you didn't dig anything up :( \n", gemList[0]);
            strcpy(finalList[CheckNextSpot(finalList)], gemList[0]);
        } else if (p->probability >= 6) {
            chance = rand() % (3 + 1 - 0) + 1;
            printf("WOW!! You dug up a %s\n", gemList[chance]);
            strcpy(finalList[CheckNextSpot(finalList)], gemList[chance]);
            p->balance += 10000;
        } else if ((p->probability >= 2) || (p->probability < 2)) {
            printf("WOW!! You dug up a %s\n", gemList[4]);
            strcpy(finalList[CheckNextSpot(finalList)], gemList[4]);
            p->balance += 20000;
        }
    }
}

// sell gems
void SellGems(char finalList[5][10]){
    // each counter for each gem
    int rubyCouter = 0, sapphireCounter = 0, emeraldCounter = 0, diamondCounter = 0;
    for(int i = 0; i < 5; i++){ // loop through the amount of gems in the list
        printf("%s\n", finalList[i]);
        // check which gem matches through conditionals
        if (strcmp(finalList[i], "ruby") == 0){
            rubyCouter++;
        } else if (strcmp(finalList[i], "sapphire") == 0){
            sapphireCounter++;
        } else if (strcmp(finalList[i], "emerald") == 0){
            emeraldCounter++;
        } else if (strcmp(finalList[i], "diamond") == 0){
            diamondCounter++;
        }
    }
    // print count
    printf("Selling this many gems: %d rubies, %d sapphires, %d emeralds, %d dimaonds", rubyCouter, sapphireCounter, emeraldCounter, diamondCounter);
}

// bird watching
void BirdWatching(Player *p){

    char birdList[5][10]={"nothing","dove","crow", "seagull", "blue jay"}; // array of birds
    char finalList [5][10] = { "", "", "", "", ""};  // array of empty values
    int chance, userInput = 0; // chance is a random Number from one value to another, due to multiple values in the list containing the same percentage, we choose random

    while(true){
        if(p->counter == 5) { // check if the counter reaches to five
            ResetCounter(p); // reset the counter
            SellBirdPhoto(finalList); // sell bird photo
            Vacation(p); // go back to the menu
            return;
        } else if (p->counter == 0){
            printf("\nLet's go birdwatching!"); // prompt first message
        }

        printf("\nAre you ready to snap a photo?\n(1 = yes,-1 = quit) ");
        scanf("%d", &userInput); // prompt user input
        if (userInput == -1){  // if the user wants to quit
            ResetCounter(p); // reset the counter
            SellBirdPhoto(finalList); // sell bird photo
            Vacation(p); //go back to the menu
        }

        p->counter++; // increase the counter
        p->probability = (float)rand()/(float)(RAND_MAX/100); // grab a random number from 0-100

        // check the probability & add balance to player
        if(p->probability <= 10){
            printf("WOW!! You did not take a picture of anything!\n");
            strcpy(finalList[CheckNextSpot(finalList)], birdList[0]);
        } else if (p->probability >= 25) {
            chance = rand() % (3 + 1 - 0) + 1;
            printf("WOW!! You took a picture of a %s!!!\n", birdList[chance]);
            strcpy(finalList[CheckNextSpot(finalList)], birdList[chance]);
            p->balance += 500;
        } else if ((p->probability >= 15)){
            printf("WOW!! You took a picture of a %s\n", birdList[4]);
            strcpy(finalList[CheckNextSpot(finalList)], birdList[4]);
            p->balance += 1000;
        }
    }
}


// sell bird photo
void SellBirdPhoto(char finalList[5][10]){
    // counters for all of the values in the list
    int doveCounter = 0, crowCounter = 0, seagullCounter = 0, blueJayCounter = 0;
    for(int i = 0; i < 5; i++){ // loop through amount of values in the list
        printf("%s\n", finalList[i]);
        // check which bird matches through conditionals
        if (strcmp(finalList[i], "dove") == 0){
            doveCounter++;
        } else if (strcmp(finalList[i], "crow") == 0){
            crowCounter++;
        } else if (strcmp(finalList[i], "seagull") == 0){
            seagullCounter++;
        } else if (strcmp(finalList[i], "blue jay") == 0){
            blueJayCounter++;
        }
    }

    printf("Our inventory is full! That's enough birdwatching for now :)\n Selling this many photos: %d doves, %d crows, %d seagull, %d blue jays", doveCounter, crowCounter, seagullCounter, blueJayCounter);
}

// check next spot checks the next empty array sppot
int CheckNextSpot(char finalList [5][10]){
    // loop through the amount of the list
    for (int i = 0; i < 5; i++){
        // check if the finalList has any space in it, if it is empty then return the value we're at on the counter
        if (strcmp(finalList[i], "") == 0){
            return i;
        }
    }
    return 0;
}

// reset counter
void ResetCounter(Player *p){
    // reset the player counter to 0
    p->counter = 0;
}

void Simulator(){
    // construct a player for the simulator
    Player *p = ConstructPlayer();
    // start the island vacation
    Vacation(p);
    // free all allocated memory from p (if, any)
    free(p);
}

int main() {
    // seed the time
    srand((time(NULL)));
    // the main function
    Simulator();
    return 0;
}
