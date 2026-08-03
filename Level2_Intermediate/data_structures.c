#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ================= STACK using Linked List =================
typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

StackNode* top = NULL;

void push(int val){
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode){ printf("Memory allocation failed!\n"); return; }
    newNode->data = val;
    newNode->next = top;
    top = newNode;
    printf("%d pushed to stack.\n", val);
}

int pop(){
    if (top==NULL){ printf("Stack Underflow!\n"); return -1; }
    StackNode* temp = top;
    int val = temp->data;
    top = top->next;
    free(temp);
    printf("%d popped from stack.\n", val);
    return val;
}

void displayStack(){
    if (top==NULL){ printf("Stack is empty.\n"); return; }
    printf("Stack (top to bottom): ");
    StackNode* curr = top;
    while (curr){ printf("%d ", curr->data); curr=curr->next; }
    printf("\n");
}

// ================= QUEUE using Linked List =================
typedef struct QueueNode {
    int data;
    struct QueueNode* next;
} QueueNode;

QueueNode *front=NULL, *rear=NULL;

void enqueue(int val){
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (!newNode){ printf("Memory allocation failed!\n"); return; }
    newNode->data=val; newNode->next=NULL;
    if (rear==NULL){ front=rear=newNode; }
    else { rear->next=newNode; rear=newNode; }
    printf("%d enqueued.\n", val);
}

int dequeue(){
    if (front==NULL){ printf("Queue Underflow!\n"); return -1; }
    QueueNode* temp=front;
    int val=temp->data;
    front=front->next;
    if (front==NULL) rear=NULL;
    free(temp);
    printf("%d dequeued.\n", val);
    return val;
}

void displayQueue(){
    if (front==NULL){ printf("Queue is empty.\n"); return; }
    printf("Queue (front to rear): ");
    QueueNode* curr=front;
    while(curr){ printf("%d ", curr->data); curr=curr->next; }
    printf("\n");
}

// ================= MAIN MENU =================
int main(){
    int choice, val;
    printf("=== Basic Data Structure Implementation - Level 2 Task 3 ===\n");
    printf("Both Stack and Queue implemented via Linked List with dynamic memory\n");
    do{
        printf("\n--- MAIN MENU ---\n");
        printf("1. Push to Stack\n2. Pop from Stack\n3. Display Stack\n");
        printf("4. Enqueue to Queue\n5. Dequeue from Queue\n6. Display Queue\n7. Exit\n");
        printf("Choice: "); scanf("%d",&choice);
        switch(choice){
            case 1: printf("Value: "); scanf("%d",&val); push(val); break;
            case 2: pop(); break;
            case 3: displayStack(); break;
            case 4: printf("Value: "); scanf("%d",&val); enqueue(val); break;
            case 5: dequeue(); break;
            case 6: displayQueue(); break;
            case 7: printf("Exiting.\n"); break;
            default: printf("Invalid.\n");
        }
    } while(choice!=7);
    
    // Cleanup
    while(top) pop();
    while(front) dequeue();
    return 0;
}
