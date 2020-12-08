#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <Windows.h>



////////////////////////////////////////////////////////////////////////////////////////

char *userid;
int call_back = 0;

typedef struct loc{
    char area[10];
    int x;
    int y;
}LOC;


typedef struct player{
    struct loc *location;
    char weapon[20];
    int power;
}PLAYER;

LOC *map;
PLAYER *pichachu;

////////////////////////////////////////////////////////////////////////////////////////

void ValidID();
void ValidID_save(char *ID);

char* Login();
void LoginFile(char *ID);

void gameboard(int call);
void move(struct player *character, struct loc *map);
void ConvertSpace(struct loc *map);
void Moveall(struct player *character, struct loc *map);

/////////////////////////////////////////////////////////////////////////////////////////

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
        printf("Run Game \n\n");
        gameboard(call_back);
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
    BOOL valid = FALSE;
    char f_id[256];
    fp = fopen("ids.txt", "r");
    
    while(fgets(f_id,256,fp))
    {
        printf("Checking.....\n\n");
        Sleep(300);
        if(strstr(f_id,ID) != 0){
            valid = TRUE;
            break;
        }
    }

    //Valid ID
    if(valid == TRUE){
        fclose(fp);

        printf("%36s", "Login Confirmation Complete!\n\n");
        printf("%20s [%s]!!\n\n","Welcome",ID);

        return;
    }

    //NO Valid ID
    else if(valid == FALSE){
        fclose(fp);

        printf("Sorry, Please Sign up as a member\n\n"); 
        main();

        return;
    }
}

void gameboard(int call){
    if(call != 0)
        goto BACK;

    printf("------------------------------------------\n\n");
    
    map = (LOC *)malloc(sizeof(LOC));
    pichachu =(PLAYER *)malloc(sizeof(PLAYER));

    strcpy(map -> area, "Space");
    map -> x = 25;
    map -> y = 15;

    pichachu -> power = 50;
    strcpy(pichachu -> weapon, "Knife");
    pichachu -> location = map;
    
    BACK:
        printf("Weapon : %s\n", pichachu -> weapon);
        printf("Power  : %d\n", pichachu -> power);
        printf("Current Area : %s >> (x: %d, y: %d)\n\n", map->area, map -> x, map ->y);
        printf("------------------------------------------\n\n");

        Moveall(pichachu, map);
        return;
}

void move(PLAYER *character, LOC *location){

    printf("Move Character\n");
    char key;
    int count = 0;

    while(1){
        key = getch();
        printf("%c\n",key);
        location -> x = 50;
        location -> y = 20;
        printf("Current Area : %s >> (x: %d, y: %d)\n\n", location ->area, location->x, location->y );
        count ++;

        if(count > 5){
            break;
        }
    }
    return;
}

void ConvertSpace(LOC *location){

    printf("Oops... You fall into a black hole\n\n");
    int bhole[100][50];
    srand(time(NULL));

    int convert_x = (rand() % 100);
    int convert_y = (rand() % 50);
    int convert;

    for(int x = 0; x<100; x++){
        for(int y = 0; y<50; y++){
            int random = rand() % 2;
            bhole[x][y] = random;
        }
    }

    if(bhole[convert_x][convert_y] == 1){
        
        convert = (rand() % 60) +1;
        if(convert <= 20){
            strcpy(location -> area, "Deep Sea");
        } 
        else if(20 < convert && convert <= 40 ){
            strcpy(location -> area, "Earth");
        }
        else if(40 < convert){
            strcpy(location -> area, "Space");
        }
    } 

    return;
}

void Moveall(PLAYER *character, LOC *location){
    move(character,location);
    ConvertSpace(location);
    call_back ++;
    gameboard(call_back);
    return;
}