#ifndef _VARIABLES_H_
#define _VARIABLES_H_
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <winbgim.h>
#include <mmsystem.h>
#define BORDER 50
#define IF 2
#define ELSE 20
#define TRUECASE 21
#define FALSECASE 22
#define WHILE 3
#define SWITCH 4
#define STATEMENT 1
#define ENDIF -2
#define ENDWHILE -3
#define CASE 40
#define DEFAULT 41
#define DO 5
#define DOWHILE 50
#define EMPTY 100
#define FOR 31
#define LMAX 12
#define END 70
using namespace std;
extern int WIDTHMAX;
extern int HEIGHTMAX;
extern int HEIGHTPAG;
extern int WIDTHPAG;
struct node
{
    int type;
    unsigned int nrChildren,position;
    node* children[101];
    node* father;
    char text[101];
    float left,top,right,bottom;
};
typedef node* tree;
extern char file[LMAX];
extern char error_message[150];
extern float basewidth;
extern float baseheight;
extern tree last;
extern tree a;
extern bool ok,sound,settings,music,width_draw,height_draw;
struct meniu
{
    int left,top,right,bottom;
};
extern meniu Load_file,Open_diagram,Exit,Back,Settings,Sound,Size,Music,Apply,Reset,Width,Height;
extern char width[LMAX];
extern char height[LMAX];
extern char zero[LMAX];
extern bool end_program;
#endif

