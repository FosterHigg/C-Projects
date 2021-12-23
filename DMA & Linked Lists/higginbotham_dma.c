//Foster Higginbotham's File


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Start by initializing our 'struct' outside of the main.
 * We can also initialize our variables as well.
 */

struct House
{
    struct House* next;
    char* name;
    int numPeeps;
};

typedef struct House house;
house *makeNewHouse();
void insertHouse(house * cornerHouse, house * newHouse);
void printNeighborhood(house * cornerHouse);
void countResidents(house * cornerHouse);

/*
 * Our main function which starts out by making our corner house and filling it with info. Then we can start our menu
 * process and see what the user intends to do.
 */

int main()
{
    char name[20];
    int amount, choice = 0;
    house *cornerHouse, *newHouse;

    printf("Let's make the corner house.\nWho lives at this house?\n");
    scanf("%s", name);
    printf("How many people live there?\n");
    scanf("%d", &amount);

    cornerHouse = makeNewHouse();
    strcpy(cornerHouse->name, name);
    cornerHouse->numPeeps = amount;

    while(choice != -1)
    {
        printf("\nWhat do you want to do?\n"
               "1 = Add New House\n"
               "2 = Get Number of Residents\n"
               "3 = Print Neighborhood\n"
               "-1 = Quit\n\n");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("\nWho lives at this house?\n");
                scanf("%s", name);
                printf("How many people live there?\n");
                scanf("%d", &amount);
                newHouse = makeNewHouse();
                strcpy(newHouse->name, name);
                newHouse->numPeeps = amount;
                insertHouse(cornerHouse, newHouse);
                break;
            case 2:
                countResidents(cornerHouse);
                break;
            case 3:
                printNeighborhood(cornerHouse);
                break;
            case -1:
                printf("\nGoodbye\n");
                break;
        }
    }
    return 0;
}

/*
 * Creates a new house by allocating space for a house then filling it.
 */

house *makeNewHouse()
{
    house *newHouse = (house*)malloc(sizeof(house));
    newHouse->next = NULL;
    newHouse->name = (char*)calloc(20, sizeof(char));
    newHouse->numPeeps = 0;
}

/*
 * Insert a new house into our linked list.
 */

void insertHouse(house *cornerHouse, house *newHouse)
{
    house *tempNode = cornerHouse;
    while(tempNode->next != NULL)
        {
        tempNode = tempNode->next;
        }
        tempNode->next = newHouse;
}

/*
 * Prints out the neighborhood and its residents by traversing the linked list until we reach NULL.
 */

void printNeighborhood(house *cornerHouse)
{
    house *tempNode = cornerHouse;
    printf("\n");
    while(tempNode != NULL)
    {
        printf("House Information: %s with %d residents.\n", tempNode->name, tempNode->numberOfPeople);
        tempNode = tempNode->next;
    }
}

/*
 * Counts up all the residents by traversing the list and adding to a sum value outside the loop.
 */

void countResidents(house *cornerHouse)
{
    house *tempNode = cornerHouse;
    int sum = 0;
    while(tempNode != NULL)
        {
        sum += tempNode->numPeeps;
        tempNode = tempNode->next;
        }
    printf("\nThis many people live on the block: %d\n", sum);
}
