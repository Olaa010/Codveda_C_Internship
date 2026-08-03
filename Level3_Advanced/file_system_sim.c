#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define FILENAME_LEN 50
#define CONTENT_LEN 500
#define META_FILE "fs_meta.dat"

typedef struct {
    char name[FILENAME_LEN];
    char content[CONTENT_LEN];
    int size;
    int exists;
} SimFile;

SimFile files[MAX_FILES];
int fileCount = 0;

void saveMeta(){
    FILE *fp=fopen(META_FILE,"wb");
    if(!fp){ perror("Meta save failed"); return; }
    fwrite(&fileCount,sizeof(int),1,fp);
    fwrite(files,sizeof(SimFile),fileCount,fp);
    fclose(fp);
}

void loadMeta(){
    FILE *fp=fopen(META_FILE,"rb");
    if(!fp){ printf("No existing file system. Starting new.\n"); fileCount=0; return; }
    fread(&fileCount,sizeof(int),1,fp);
    fread(files,sizeof(SimFile),fileCount,fp);
    fclose(fp);
    printf("Loaded file system with %d files.\n", fileCount);
}

int findFileIndex(char *name){
    for(int i=0;i<fileCount;i++) if(files[i].exists && strcmp(files[i].name,name)==0) return i;
    return -1;
}

void createFile(){
    if(fileCount>=MAX_FILES){ printf("File system full!\n"); return; }
    char name[FILENAME_LEN];
    printf("Enter file name to create: "); scanf("%s",name);
    if(findFileIndex(name)!=-1){ printf("Error: File '%s' already exists!\n", name); return; }
    SimFile f;
    strcpy(f.name,name);
    printf("Enter file content (single line, max 500 chars): ");
    while(getchar()!='\n');
    fgets(f.content, CONTENT_LEN, stdin);
    f.content[strcspn(f.content,"\n")]=0;
    f.size=strlen(f.content);
    f.exists=1;
    files[fileCount++]=f;
    saveMeta();
    // Also create real file for demo of file I/O
    FILE *real=fopen(name,"w");
    if(real){ fputs(f.content, real); fclose(real); }
    printf("File '%s' created (size %d bytes).\n", name, f.size);
}

void readFile(){
    char name[FILENAME_LEN];
    printf("Enter file name to read: "); scanf("%s",name);
    int idx=findFileIndex(name);
    if(idx==-1){ printf("Error: File '%s' not found!\n", name); return; }
    printf("\n--- File: %s ---\n", files[idx].name);
    printf("Size: %d bytes\nContent: %s\n", files[idx].size, files[idx].content);
    printf("---------------------\n");
}

void deleteFile(){
    char name[FILENAME_LEN];
    printf("Enter file name to delete: "); scanf("%s",name);
    int idx=findFileIndex(name);
    if(idx==-1){ printf("Error: File '%s' not found!\n", name); return; }
    files[idx].exists=0;
    // shift
    for(int i=idx;i<fileCount-1;i++) files[i]=files[i+1];
    fileCount--;
    saveMeta();
    remove(name); // delete real file too
    printf("File '%s' deleted.\n", name);
}

void listFiles(){
    if(fileCount==0){ printf("File system empty.\n"); return; }
    printf("\n%-20s %-6s %s\n", "Name", "Size", "Preview");
    printf("------------------------------------------------\n");
    for(int i=0;i<fileCount;i++) if(files[i].exists){
        char preview[21]; strncpy(preview, files[i].content, 20); preview[20]=0;
        if(strlen(files[i].content)>20) strcat(preview,"...");
        printf("%-20s %-6d %s\n", files[i].name, files[i].size, preview);
    }
}

void writeToFile(){
    char name[FILENAME_LEN];
    printf("Enter file name to append/write: "); scanf("%s",name);
    int idx=findFileIndex(name);
    if(idx==-1){ printf("Error: File not found. Use create first.\n"); return; }
    printf("Enter new content to append: ");
    while(getchar()!='\n');
    char extra[CONTENT_LEN];
    fgets(extra, CONTENT_LEN, stdin);
    extra[strcspn(extra,"\n")]=0;
    if(strlen(files[idx].content)+strlen(extra) < CONTENT_LEN-1){
        strcat(files[idx].content, extra);
        files[idx].size=strlen(files[idx].content);
        saveMeta();
        FILE *real=fopen(name,"w");
        if(real){ fputs(files[idx].content, real); fclose(real); }
        printf("Content updated.\n");
    } else {
        printf("Error: Content would exceed max size!\n");
    }
}

int main(){
    loadMeta();
    printf("\n=== Simple File System Simulation - Level 3 Task 1 ===\n");
    int choice;
    do{
        printf("\n1. Create File\n2. Read File\n3. Write/Append to File\n4. Delete File\n5. List All Files\n6. Exit\nChoice: ");
        if(scanf("%d",&choice)!=1){ printf("Invalid input!\n"); while(getchar()!='\n'); choice=0; continue; }
        switch(choice){
            case 1: createFile(); break;
            case 2: readFile(); break;
            case 3: writeToFile(); break;
            case 4: deleteFile(); break;
            case 5: listFiles(); break;
            case 6: printf("Exiting file system simulation.\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice!=6);
    return 0;
}
