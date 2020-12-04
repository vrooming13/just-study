#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>

////////////////////////////////////////////////////////////////////////////////////////

void ValidID();
void ValidID_save(char *ID);

char* Login();
void LoginFile(char *ID);

void gameboard();

/////////////////////////////////////////////////////////////////////////////////////////

char *userid;

typedef struct *loc{
    char *loc;
    int x;
    int y;
}LOC;


typedef struct * player{
    LOC *location;
    char weapon[5];
    int power;
}PLAYER;


//////////////////////////////////////////////////////////////////////////////////////////

int main(void){

    int menu;

    printf("\n%30s", "Welcome To GameWorld\n\n");

    printf("-------------- 1. Signup --------------\n" );
    printf("-------------- 2. Login  --------------\n" );

    printf("\n###### Select The Menu ########\n");
    printf("Select Number : ");
    scanf("%d",&menu);

    switch (menu){

    case 1:
        ValidID();
        break;

    case 2:
        Login();
        LoginFile(userid);
        gameboard();
        break;

    default:
        printf("\nEnter correct number!\n\n");
        main();
        break;
    }

    return 1;
}


void ValidID(){

    int user_num = 0;
    int num_cnt = 0;
    int ko_cnt = 0;
    userid = (char *)malloc(20);


    printf("Create ID For Join\n\n");
    printf("ID : ");

    scanf("%s",userid);

    if(strlen(userid) < 3 ){
        printf("Too short For Create ID!\n\n");
        ValidID();
        return;
    } 

    else if(strlen(userid) > 8){
        printf("Too Long For Create ID\n\n");
        ValidID();
        return;
    }

    else if( 3 <= strlen(userid)  && strlen(userid) <= 8 ){
        for(int i = 0; i < strlen(userid); i++){
            if (isalnum(userid[i]) != 0){
                if(isdigit(userid[i]) != 0){
                    num_cnt++;
                }
            } 

            else if(isalnum(userid[i]) == 0){
                ko_cnt++;
            }
        }

        if(ko_cnt > 0){
            printf("Sorry, We can't service Korean \n\n");
            printf("%d\n",ko_cnt);
            ValidID();
            return;
        } 
        
        else if(num_cnt == 0){
            printf("%d\n",num_cnt);
            printf("Input Number Character 1 or more \n\n");
            ValidID();
            return;
        }
    }


    ValidID_save(userid);

    printf("\n\n ----- Thank You To Join! ----- \n\n");
    
    Sleep(1000);
    system("cls");
    
    main();
    return;
}



void ValidID_save(char * ID){
    FILE *save = NULL;

    save = fopen("ids.txt", "a+t");
        fprintf(save, "|| User_ID : %s || \n", ID);
    fclose(save);
    return;
}

char* Login(){
    userid = (char *)malloc(20);

    printf("\nInput Your ID : ");

    scanf("%s", userid);
    return userid;
}

void LoginFile(char *ID){
    FILE *fp;
    int end;
    char f_id[256];
    fp = fopen("ids.txt", "r");
    
    while(fgets(f_id,256,fp))
    {
        printf("Checking.....\n\n");
        Sleep(300);
        if(strstr(f_id,ID) != 0){
            printf("%36s", "Login Confirmation Complete!\n\n");
            printf("%20s [%s]!!\n\n","Welcome",ID);
            return;
        }
    }

    //NO Valid ID
    fclose(fp);
    
    printf("Sorry, Please Sign up as a member\n\n"); 
    main();
    return;
}

void gameboard(){
    LOC *location;
    PLAYER *pichachu;

    

    pichachu -> power = 50;
    pichachu -> weapon = 'Knife';
    pichachu -> location = LOC -> space[20][30];

    printf("Weapon : %s\n", pichachu -> weapon);
    printf("Power  : %d\n", pichachu -> power);
    printf("------------------------------------------\n\n");
}