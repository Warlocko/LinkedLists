#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    char nameData[100];
    int numData;
    struct Node *next;
}item;

void iterateList(item *element){
    while(element != NULL){
        printf("|Name:\t%s\t|\n|Age:\t%d\t|\n\n", element->nameData, element->numData);
        element = element->next;
    }
    puts("");
}

void push(int newNumData, char newNameData[], item **headPtr){
    item *newItem = (item*) malloc(sizeof(item));
    newItem->numData = newNumData;
    strcpy(newItem->nameData, newNameData);
    newItem->next = (*headPtr);
    (*headPtr) = newItem;
    puts("");
}

void append(int newNumData, char newNameData[], item **headPtr){
    item *newItem = (item*) malloc(sizeof(item));
    item *tail = (*headPtr);
    newItem->numData = newNumData;
    strcpy(newItem->nameData, newNameData);
    newItem->next = NULL;
    if((*headPtr)==NULL){
        (*headPtr) = newItem;
    }else{
        while(tail->next != NULL){
            tail = tail->next;
        }
        tail->next = newItem;
    }
    puts("");
}

//Useless since you can call the deleteNode() function using the position 0
/*
void pop(item **headPtr){
    if(*headPtr == NULL) return;
    item *oldHeadPtr = (*headPtr);
    (*headPtr) = oldHeadPtr->next;
    free(oldHeadPtr);
    puts("");
}
*/

void prepend(item **headPtr){
    if(*headPtr == NULL){
        puts("There are no elements in the list.");
        puts("");
        return;
    }
    item *oldHeadPtr = (*headPtr);
    if(oldHeadPtr->next == NULL){
        free(oldHeadPtr);
        oldHeadPtr = NULL;
        return;
    }
    while(oldHeadPtr->next->next != NULL ){
            oldHeadPtr = oldHeadPtr->next;
    }
    free(oldHeadPtr->next);
    oldHeadPtr->next = NULL;
    puts("");
}

void deleteNode(int position, item **headPtr){
    if((*headPtr) == NULL){
        puts("There are no elements in the list.\n");
        puts("");
        return;
    }
    item *oldHeadPtr = (*headPtr);
    int i;
    if (position == 0){
        (*headPtr) = oldHeadPtr->next;
        free(oldHeadPtr);
    }else{
        for(i=0;oldHeadPtr != NULL && i<position-1; i++){
            oldHeadPtr = oldHeadPtr->next;
        }
        if(oldHeadPtr == NULL) {
            puts("The list doesn't have that many elements.\n");
            return;
        }
        item *contHeadPtr = oldHeadPtr->next->next;
        free(oldHeadPtr->next);
        oldHeadPtr->next = contHeadPtr;
    }
    puts("");
}

void getSize(item *element){
    int i=0;
    if(element == NULL){
        printf("0 elements.\n");
        puts("");
    return;
    }
    while(element != NULL){
        i++;
        element = element->next;
    }
    printf("%d element(s).\n", i);
    puts("");
}

void infoNode(int position, item **headPtr){
    int i;
    if((*headPtr) == NULL){
        printf("There are no elements in the list.\n");
        return;
    }
    item *traverseHeadPtr = (*headPtr);
    for(i=0;traverseHeadPtr != NULL && i<position; i++){
        traverseHeadPtr = traverseHeadPtr->next;
    }
    if(traverseHeadPtr == NULL) {
        puts("The list doesn't have that many elements.");
    }else{
        printf("|Name:\t%s\t|\n|Age:\t%d\t\n\n", traverseHeadPtr->nameData, traverseHeadPtr->numData);
    }
    puts("");
}

void emptyList(item **headPtr){
    if((*headPtr) == NULL){
        printf("The list is already empty.\n\n");
        return;
    }
    item *oldHeadPtr = (*headPtr);
    item *nextHeadPtr;
    do{
        nextHeadPtr = oldHeadPtr->next;
        free(oldHeadPtr);
        oldHeadPtr = nextHeadPtr;
    }while(oldHeadPtr != NULL);
    *headPtr = NULL;
    printf("List empty!");
    puts("");
}

int main()
{
    int option, numValue, position;
    char nameValue[100];
    item *head = NULL;

    do{
        puts("What would you like to do?");
        puts("1. Iterate the list.");
        puts("2. Add an item to the beginning of the list.");
        puts("3. Add an item to the end of the list.");
        puts("4. Remove the first item in the list.");
        puts("5. Remove the last item in the list.");
        puts("6. Remove a specific item in the list.");
        puts("7. Get the size of the list.");
        puts("8. Get information of a specific item in the list.");
        puts("9. Empty the list.");
        puts("10. End the program.");
        scanf("%d", &option);

        switch(option){
            case 1:
                iterateList(head);
                break;
            case 2:
                //If we use scanf() on numValue and then on nameValue, numValue turns to 0?
                puts("Introduce a name.");
                scanf("%s", nameValue);
                puts("Introduce a number.");
                scanf("%d", &numValue);
                push(numValue, nameValue, &head);
                break;
            case 3:
                puts("Introduce a name.");
                scanf("%s", nameValue);
                puts("Introduce a number.");
                scanf("%d", &numValue);
                append(numValue, nameValue, &head);
                break;
            case 4:
                deleteNode(0, &head);
                break;
            case 5:
                prepend(&head);
                break;
            case 6:
                puts("Which element would you like to remove? (0 being the first element)");
                scanf("%d", &position);
                deleteNode(position, &head);
                break;
            case 7:
                getSize(head);
                break;
            case 8:
                puts("Which element would you like to get information about? (0 being the first element)");
                scanf("%d", &position);
                infoNode(position, &head);
                break;
            case 9:
                emptyList(&head);
                break;
            case 10:
                puts("See you next time!");
                break;
            default:
                printf("Invalid option. Please try again.");
        }
    }while(option != 10);
    return 0;
}
