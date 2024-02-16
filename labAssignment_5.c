#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char letter;
    struct node *next;
} node;
// Returns number of nodes in the linkedList.
int length(node *head)
{
    struct node *current = head;
    int count = 0;
    while (current != NULL)
    {
        current = current->next;
        count++;
    }
    return count;
}
// parses the string in the linkedList
// if the linked list is head -> |a|->|b|->|c|
// then toCString function wil return "abc"
char *toCString(node *head)
{
    struct node *current = head;
    int length = 0;

    // Calculate the length of the linked list
    struct node *temp = head;
    while (temp != NULL)
    {
        length++;
        temp = temp->next;
    }

    // Allocate memory for the string
    char *result = (char *)malloc((length + 1) * sizeof(char)); // Plus one for the null terminator

    if (result == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    int i = 0;
    while (current != NULL)
    {
        result[i] = current->letter;
        current = current->next;
        i++;
    }

    // Add null terminator at the end of the string
    result[i] = '\0';

    return result;
}
// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node **pHead, char c)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed");
        return;
    }
    newNode->letter = c;
    newNode->next = NULL;

    if (*pHead == NULL)
    {
        *pHead = newNode;
        return;
    }

    struct node *current = *pHead;
    while (current->next != NULL)
    {
        current = current->next;
    }

    // Change the next of the last node
    current->next = newNode;
}
// deletes all nodes in the linkedList.
void deleteList(node **pHead)
{
    struct node *current = *pHead;
    struct node *next;

    while (current != NULL)
    {
        next = current->next; // Store the next node before deleting the current node
        free(current);        // Free the memory allocated for the current node
        current = next;       // Move to the next node
    }

    *pHead = NULL; // Set the head pointer to NULL to indicate that the list is empty
}
int main(void)
{
    int i, strLen, numInputs;
    node *head = NULL;
    char *str;
    char c;
    FILE *inFile = fopen("input.txt", "r");
    fscanf(inFile, " %d\n", &numInputs);
    while (numInputs-- > 0)
    {
        fscanf(inFile, " %d\n", &strLen);
        for (i = 0; i < strLen; i++)
        {
            fscanf(inFile, " %c", &c);
            insertChar(&head, c);
        }
        str = toCString(head);
        printf("String is : %s\n", str);
        free(str);
        deleteList(&head);
        if (head != NULL)
        {
            printf("deleteList is not correct!");
            break;
        }
    }
    fclose(inFile);
}