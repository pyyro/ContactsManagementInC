#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
// Contacts structure
struct contact {
    char name[40];
    char address[40];
    long long int phoneNumber;
    char email[40];
};

//Functions List
void mainMenu();
void addRecord();
void delRecord();
void editRecord();
void listRecords();
void searchRecords();

//filename in a variable if I want to change it later
char fname[]={"records.dll"};
char ftempname[]={"temp.dll"};

//__main__
int main(){
    system("color 06"); //colours wwoahh!!
                        /* First X for background, second for foreground.
                        0 = Black   8 = Gray
                        1 = Blue    9 = Light Blue
                        2 = Green   A = Light Green
                        3 = Aqua    B = Light Aqua
                        4 = Red     C = Light Red
                        5 = Purple  D = Light Purple
                        6 = Yellow  E = Light Yellow
                        7 = White   F = Bright White 
                        */
   mainMenu();
   return 0;
   
}
//For Main Menu
void mainMenu(){
    system("cls"); //clear screen before every call so it looks neeeat

    printf("\t\t\t\t\t\tMAIN MENU\n");
    printf("\t\t1.Add New Contact\t2.Edit Existing Contact\t\t3.Delete Contact\n");
    printf("\t\t4.Search Contact\t5.List All Contacts\t\t6.Exit Program\n\n");
    printf("\t\t\tChoose options by pressing their respective numbers!\n");
    
    switch(getch()){
        case '1': addRecord();
                  break;
        case '2': editRecord();
                  break;
        case '3': delRecord();
                  break;
        case '4': searchRecords();
                  break;
        case '5': listRecords();
                  break;
        case '6': system("exit");
                  break;
        default:
            printf("Press 1-6 only!!");
            printf("\nPress any key to try again.");
            getch();
    
    mainMenu();
        
    }
}

// For Adding New Contacts
void addRecord(){
    system("cls");

    struct contact c;
    
    FILE *f;
    f=fopen(fname,"ab");
    
    printf("\t\tADD NEW CONTACT\n");
    printf("\nEnter name: ");
    scanf("%[^\n]",&c.name);// so it looks like the %[^\n] waits until I press Enter to save the data so the last name doesnt get lost or overflow
    fflush(stdin); //apparently clears buffer so no value overflows, solved my problem so whatever 
    printf("\nEnter address: ");
    scanf("%[^\n]",&c.address);
    fflush(stdin);
    printf("\nEnter phone number: ");
    scanf("%lld",&c.phoneNumber);
    fflush(stdin);
    printf("\nEnter email address: ");
    scanf("%s",&c.email);
    fflush(stdin);
    
    fwrite(&c,sizeof(c),1,f);
    fclose(f);
    
    printf("\nRecord Saved!");
    printf("\nPress any key to go back!");
    getch();
    
    mainMenu();
}

//Listing Contacts
void listRecords(){
    system("cls");
    
    struct contact c;
    
    FILE *f;
    f=fopen(fname,"rb"); //binary read mode

    if (f==NULL){
        printf("\nERROR OPENING FILE, THE RECORD FILE DOES NOT EXIST!!!");
        getch();
        mainMenu();  
    }else{
        printf("\t\t\t========================================\n");
        printf("\t\t\t\t\tContacts\n");
        printf("\t\t\t========================================\n");
        while(fread(&c,sizeof(c),1,f)==1){ //okay this reads the file until it reaches the end, and when it does its return value is (i don't know).
        printf("\n\t\t\t\tName: %s\n\t\t\t\tAddress: %s\n\t\t\t\tMobile no: %lld\n\t\t\t\tE-mail: %s\n\n\t\t\t\t\t  --\n\n",c.name,c.address,c.phoneNumber,c.email);
        }
    }
    
    fclose(f);
    
    printf("\nPress any key to go back!");
    getch();
    mainMenu();
}

//Deleting Contacts
/*
-Ask for a name to delete.
-Read the file for the name.
-Write every other record in a temp file, except for that one match.
-Replace the temp file with the new file, which contains every record but the one matched.
-Contact Deleted!
*/
void delRecord(){
    char name[20];
    int recordExists;
    
    system("cls");
    fflush(stdin);
    
    struct contact c;
    
    FILE *fp;
    FILE *ftemp;
    
    fp = fopen(fname,"r");
    ftemp = fopen(ftempname,"w");
    
    printf("\t\tDELETE CONTACT\n");
    printf("Enter name of contact to delete: ");
    scanf("%[^\n]",&name);
    fflush(stdin);
    
    while (fread( &c, sizeof(c), 1, fp) == 1) {
        if (strcmp(c.name, name) != 0)
          fwrite(&c, sizeof(c), 1, ftemp);
        if (strcmp(c.name, name) == 0)
          recordExists = true;
    }
    
    fclose(fp);
    fclose(ftemp);
    
    if(recordExists!=true){
        printf("The contact does not exist!");
    }else{
        remove(fname);
        rename(ftempname, fname);
        printf("\t\tRECORD DELETED SUCCESSFULLY.");
    }
   
    printf("\n\nPress any key to go back!");
    getch();
    system("cls");
    
    mainMenu();
}

//Editing Contacts
/*
-Similar to deleting record, ask for a name, check for matches
-Write every unmatch in a temp file.
-When matched, ask for new info and write the new info in the temp file.
-Replace original file with the temp file.
-Contact modified!
*/
void editRecord(){
    char name[20];
    int found;

    system("cls");
    
    printf("\t\tEDIT CONTACT\n");
    fflush(stdin);
    
    struct contact c;
    
    FILE *fp;
    FILE *ftemp;
    fp = fopen(fname,"r");
    ftemp = fopen(ftempname,"w");

    printf("Enter name of contact to modify: ");
    scanf("%[^\n]",&name);
    fflush(stdin);

    while(fread(&c,sizeof(c),1,fp)==1){
            if(stricmp(name,c.name)!=0)
                fwrite(&c,sizeof(c),1,ftemp);
            if(stricmp(name,c.name)==0){
                found = 1;
            }
    }
    if (found == 1){
        printf("\nEnter name: ");
        scanf("%[^\n]",&c.name);
        fflush(stdin); 
        printf("\nEnter address: ");
        scanf("%s",&c.address);
        fflush(stdin);
        printf("\nEnter phone number: ");
        scanf("%lld",&c.phoneNumber);
        fflush(stdin);
        printf("\nEnter email address: ");
        scanf("%s",&c.email);
        fflush(stdin);
        fwrite(&c,sizeof(c),1,ftemp);
    }else if(found!=1){
        printf("The contact does not exist!");
    }
    

    
    fclose(fp);
    fclose(ftemp);
    remove(fname);
    rename(ftempname,fname);

    printf("\n\nPress any key to go back!");
    getch();
    system("cls");
    
    mainMenu();

}


//Searching contacts
void searchRecords(){
    char name[20];
    int found;
    
    struct contact c;
    
    FILE *fp;
    fp=fopen(fname,"rb");
    
    system("cls");
    
    printf("=========SEARCH CONTACT============\n");
    printf("Enter name of contact to search: ");
    scanf("%[^\n]",&name);
    fflush(stdin);

    while (fread( &c,sizeof(c),1,fp)==1){
        if (strcmp(c.name,name)==0){
            found = 1;
            printf("\n\tInfo about: %s",name);
            printf("\nName: %s\nAddress: %s\nMobile no: %lld\nE-mail: %s\n\n",c.name,c.address,c.phoneNumber,c.email);
            break;
        }
    }

    fclose(fp);
    if (found!=1){
        printf("No contact matches for that name!");
    }
    printf("\n\nPress any key to go back!");

    getch();
    mainMenu();

}
