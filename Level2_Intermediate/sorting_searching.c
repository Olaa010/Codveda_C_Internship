#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int arr[], int n) {
    for (int i=0;i<n;i++) printf("%d ", arr[i]);
    printf("\n");
}

void copyArray(int src[], int dest[], int n){
    for (int i=0;i<n;i++) dest[i]=src[i];
}

// Bubble Sort O(n^2)
void bubbleSort(int arr[], int n) {
    for (int i=0;i<n-1;i++){
        int swapped=0;
        for (int j=0;j<n-i-1;j++){
            if (arr[j]>arr[j+1]){
                int tmp=arr[j]; arr[j]=arr[j+1]; arr[j+1]=tmp;
                swapped=1;
            }
        }
        if (!swapped) break;
    }
}

// Quick Sort O(n log n) avg
int partition(int arr[], int low, int high){
    int pivot=arr[high];
    int i=low-1;
    for (int j=low;j<high;j++){
        if (arr[j]<=pivot){
            i++;
            int tmp=arr[i]; arr[i]=arr[j]; arr[j]=tmp;
        }
    }
    int tmp=arr[i+1]; arr[i+1]=arr[high]; arr[high]=tmp;
    return i+1;
}
void quickSort(int arr[], int low, int high){
    if (low<high){
        int pi=partition(arr,low,high);
        quickSort(arr,low,pi-1);
        quickSort(arr,pi+1,high);
    }
}

// Linear Search O(n)
int linearSearch(int arr[], int n, int key){
    for (int i=0;i<n;i++) if (arr[i]==key) return i;
    return -1;
}

// Binary Search O(log n) - requires sorted array
int binarySearch(int arr[], int n, int key){
    int l=0,r=n-1;
    while(l<=r){
        int mid=l+(r-l)/2;
        if (arr[mid]==key) return mid;
        else if (arr[mid]<key) l=mid+1;
        else r=mid-1;
    }
    return -1;
}

int main(){
    int n;
    printf("=== Sorting and Searching Algorithms - Level 2 Task 2 ===\n");
    printf("Enter array size: ");
    scanf("%d",&n);
    int *original = (int*)malloc(n*sizeof(int));
    int *arr = (int*)malloc(n*sizeof(int));
    
    printf("1. Manual input  2. Random generation\nChoice: ");
    int ch; scanf("%d",&ch);
    if (ch==1){
        printf("Enter %d integers:\n", n);
        for (int i=0;i<n;i++) scanf("%d",&original[i]);
    } else {
        srand(time(0));
        for (int i=0;i<n;i++) original[i]=rand()%1000;
        printf("Generated array: ");
        printArray(original,n);
    }

    int choice;
    do{
        printf("\n--- MENU ---\n");
        printf("1. Bubble Sort\n2. Quick Sort\n3. Linear Search\n4. Binary Search (sorts first)\n5. Compare Time Complexity\n6. Exit\nChoice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                copyArray(original,arr,n);
                clock_t start=clock();
                bubbleSort(arr,n);
                clock_t end=clock();
                printf("Sorted: "); printArray(arr,n);
                printf("Time: %f sec\n", (double)(end-start)/CLOCKS_PER_SEC);
                break;
            case 2:
                copyArray(original,arr,n);
                start=clock();
                quickSort(arr,0,n-1);
                end=clock();
                printf("Sorted: "); printArray(arr,n);
                printf("Time: %f sec\n", (double)(end-start)/CLOCKS_PER_SEC);
                break;
            case 3:{
                int key; printf("Enter key to search: "); scanf("%d",&key);
                copyArray(original,arr,n);
                int idx=linearSearch(arr,n,key);
                if (idx!=-1) printf("Found at index %d\n", idx);
                else printf("Not found\n");
                break;
            }
            case 4:{
                int key; printf("Enter key to search: "); scanf("%d",&key);
                copyArray(original,arr,n);
                quickSort(arr,0,n-1);
                printf("Sorted array: "); printArray(arr,n);
                int idx=binarySearch(arr,n,key);
                if (idx!=-1) printf("Found at sorted index %d\n", idx);
                else printf("Not found\n");
                break;
            }
            case 5:{
                copyArray(original,arr,n);
                clock_t s1=clock(); bubbleSort(arr,n); clock_t e1=clock();
                copyArray(original,arr,n);
                clock_t s2=clock(); quickSort(arr,0,n-1); clock_t e2=clock();
                printf("Bubble Sort: %f sec (O(n^2))\n", (double)(e1-s1)/CLOCKS_PER_SEC);
                printf("Quick Sort:  %f sec (O(n log n) avg)\n", (double)(e2-s2)/CLOCKS_PER_SEC);
                printf("Linear Search O(n) vs Binary Search O(log n) - Binary requires sorted array\n");
                break;
            }
            case 6: printf("Exiting.\n"); break;
            default: printf("Invalid.\n");
        }
    } while(choice!=6);
    
    free(original); free(arr);
    return 0;
}
