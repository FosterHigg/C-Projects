//Foster Higginbotham's File

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXTEAMS 10

struct Team {
    int id, wins, loss;
};

typedef struct user Team;

void overblotch();
void ConstructMaxTeams(struct Team teams[MAXTEAMS]);
bool CheckInput(int userInput);
int Menu();
int CheckNextSpot(struct Team teams[MAXTEAMS]);
void ESports(struct Team teams[MAXTEAMS]);
void DeleteTeam(struct Team teams[MAXTEAMS]);
void AddTeam(struct Team teams[MAXTEAMS]);
bool checkInputValue(int inputValue);
void UpdateData(struct Team teams[MAXTEAMS]);
void GetData(struct Team teams[MAXTEAMS]);



// checks the input of the userInput
bool CheckInput(int userInput){
    // if the userInput isn't the inputs that we want we will return false
    if (userInput != -1 && userInput != 1 && userInput != 2 && userInput != 3 && userInput != 4){
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
        printf("\n \nWhat function do you want to do?\n1 = Add New Team\n2 = Remove Team\n3 = Update Data\n4 = Get Data\n-1 = QUIT\n");
        scanf("%d", &userInput); // scan value from the user
        if (CheckInput(userInput)){ // our condition to break us out
            return userInput;
        }

    }
}

// check next spot checks the next empty array spot
int CheckNextSpot(struct Team teams[MAXTEAMS]){
    // loop through the amount of the list
    for (int i = 0; i < MAXTEAMS; i++){
        // check if the finalList has any space in it, if it is empty then return the value we're at on the counter
        if (teams[i].id == 0){
            return i;
        }
    }
    return -1;
}

// add team - adds a team
void AddTeam(struct Team teams[MAXTEAMS]){

    // find the next empty spot
    int availableIndex = CheckNextSpot(teams);

    if(availableIndex == -1){
        printf("\nunable to add a team, all teams spots are filled");
        ESports(teams);
    }


    int inputTeamID = 0;
    printf("\nEnter a team ID: ");
    scanf("%d", &inputTeamID);

    for (int i = 0; i < MAXTEAMS; i++){
        if(teams[i].id == inputTeamID){
            printf("\nERROR: Duplicate team ID");
            ESports(teams);
        }

    }

    teams[availableIndex].id = inputTeamID;

    ESports(teams);
}

// delete team - delete a team
void DeleteTeam(struct Team teams[MAXTEAMS]){

    int inputTeamID = 0;
    printf("\nEnter a team ID: ");
    scanf("%d", &inputTeamID);

    for (int i = 0; i < MAXTEAMS; i++){
        if(teams[i].id == inputTeamID){
            teams[i].id = 0;
            teams[i].loss = 0;
            teams[i].wins = 0;
        }
    }


    for (int i = 0; i < MAXTEAMS; i++){
        printf("%d\n", teams[i].id);
    }

    ESports(teams);
}

// updates data for a team
void UpdateData(struct Team teams[MAXTEAMS]){

    printf("Which team do you want to update data for? ");
    int inputValue = 0;
    scanf("%d", &inputValue);

    bool teamFound = false;
    int foundIndex = 0;
    for (int i = 0; i < MAXTEAMS; i++){
        if(teams[i].id == inputValue){
            foundIndex = i;
            teamFound = true;
            break;
        }
    }

    // if the team doesnt exist, return
    if(!teamFound){
        printf("\nERROR: Team does not exist");
        ESports(teams);
    }


    printf("What data do you want to update? (1 = win, 2 = loss)? ");
    scanf("%d", &inputValue);

    // if the input value is not 1 or 2
    if(!checkInputValue(inputValue)){
        while(!checkInputValue(inputValue)){ // check again for reassurance, not really needed
            printf("Invalid input, please enter (1) or (2)\n");
            printf("What data do you want to update? (1 = win, 2 = loss)? ");
            scanf("%d", &inputValue);
            if(checkInputValue(inputValue)){ // if the input value works break out
                break;
            }
        }
    }

    // wins
    if(inputValue == 1){
        printf("How many wins? ");
        scanf("%d", &inputValue);
        teams[foundIndex].wins = inputValue;

    } else { // losses
        printf("How many losses? ");
        scanf("%d", &inputValue);
        teams[foundIndex].loss = inputValue;
    }

    ESports(teams);
}

// get data
void GetData(struct Team teams[MAXTEAMS]){
    printf("Printing Data:\n");


    for (int i = 0; i < MAXTEAMS; i++){
        if(teams[i].id != 0){ // print the ids that we've added only
            printf("Team ID: %d\n", teams[i].id);
            printf("Team Wins: %d\n", teams[i].wins);
            printf("Team Losses: %d\n\n", teams[i].loss);
        }
    }

    ESports(teams);
}

// check input value for 1 or 2
bool checkInputValue(int inputValue){
    if(inputValue == 1 || inputValue == 2) {
        return true;
    } else {
        return false;
    }
}

// e-sports menu
void ESports(struct Team teams[MAXTEAMS]){
    switch (Menu()){ // switch base off the menu selection
        case -1: // exit
            printf("Goodbye!");
            exit(0);
        case 1: // Add a new team
            AddTeam(teams);
            break;
        case 2: // Remove a team
            DeleteTeam(teams);
            break;
        case 3: // Update Data
            UpdateData(teams);
            break;
        case 4: // Get Data
            GetData(teams);
            break;
    }
}

// constructor
void ConstructMaxTeams(struct Team teams[MAXTEAMS]){
    // set all values to 0
    for (int i = 0; i < MAXTEAMS; i++){
        teams[i].id = 0;
        teams[i].loss = 0;
        teams[i].wins = 0;
    }

    printf("Welcome to the Φverblotch E-Sports Win/Loss Tool!\n");
}

void overblotch(){
    // create teams
    struct Team *teams[MAXTEAMS];

    // construct max teams appending null to each
    ConstructMaxTeams((struct Team *) teams);

    // e-sports
    ESports((struct Team *) teams);

}

int main(){
    // overblotch
    overblotch();
}
