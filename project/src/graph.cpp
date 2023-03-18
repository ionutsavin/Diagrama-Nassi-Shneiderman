#include "../include/tree.h"
float basewidth, baseheight;
int WIDTHMAX, HEIGHTMAX, HEIGHTPAG, WIDTHPAG;
tree a, last;
char file[LMAX];
char error_message[150];
bool ok=1,sound,settings,music,width_draw,height_draw;
meniu Load_file,Open_diagram,Exit,Back,Settings,Sound,Size,Music,Apply,Reset,Width,Height;
char width[LMAX];
char height[LMAX];
char zero[LMAX];
bool end_program=0;
void draw_statement(tree a,float offsety,float offsetx)
{

    char row[301];
    strcpy(row,a->text);
    int nr_spaces=0;
    while(row[nr_spaces]==' ') nr_spaces++;
    strcpy(row,row+nr_spaces);
    float left,top,right,bottom;
    left=a->left-offsetx;
    top=a->top-offsety;
    right=a->right-offsetx;
    bottom=a->bottom-offsety;
    rectangle(left,top,right,bottom);
    float mid_x=(left+right-textwidth(row))/2;
    float mid_y=(top+bottom-textheight(row))/2;
    outtextxy(mid_x,mid_y,row);
}
void draw_empty(tree a,float offsety,float offsetx)
{

    float left,top,right,bottom;
    left=a->left-offsetx;
    top=a->top-offsety;
    right=a->right-offsetx;
    bottom=a->bottom-offsety;
    rectangle(left,top,right,bottom);
}
void draw_if(tree a, float offsety,float offsetx)
{

    char row[301];
    strcpy(row,a->text);
    float left,top,right,bottom;
    left=a->left-offsetx;
    top=a->top-offsety;
    right=a->right-offsetx;
    bottom=a->bottom-offsety;
    char *p=strstr(row,"daca");
    char text[301];
    p=p+4;
    int lg=strlen(p)-6;
    p[lg]='\0';
    strcpy(text,p);
    float mid_x=(left+right-textwidth(text))/2;
    float mid_y=(top+bottom-textheight(text))/2;
    outtextxy(mid_x,mid_y,text);
    rectangle(left,top,right,bottom);
    mid_x=(left+right)/2;
    mid_y=(top+bottom)/2;
    line(mid_x,bottom,left,top);
    line(mid_x,bottom,right,top);
    float mid_true_x=(left+mid_x)/2;
    float mid_false_x=(right+mid_x)/2;
    float mid_y_true_false=(mid_y+bottom)/2;
    outtextxy(mid_true_x,mid_y_true_false,"T");
    outtextxy(mid_false_x,mid_y_true_false,"F");
}
void draw_switch(tree a,float offsety,float offsetx)
{

    char row[301];
    strcpy(row,a->text);
    char *p=strstr(row,"switch");
    p=p+7;
    int lg=strlen(p)-1;
    p[lg]='\0';
    char text[301];
    strcpy(text,p);
    float left,top,right,bottom;
    left=a->left-offsetx;
    top=a->top-offsety;
    right=a->right-offsetx;
    bottom=a->bottom-offsety;
    unsigned int nr_cazuri=a->nrChildren;
    float distanta_case=(top-bottom)/(nr_cazuri-1);
    rectangle(left,top,right,bottom);
    float mid_x=(left+right-textwidth(text))/2;
    float mid_y=(top+bottom-textheight(text))/2;
    outtextxy(mid_x,mid_y,text);
    int i=1;
    float top_case=top;
    nr_cazuri--;
    while(i<=nr_cazuri)
    {
        float right_case=a->children[i]->right-offsetx;
        float left_case=a->children[i]->left-offsetx;
        top_case-=distanta_case;
        line(right_case,bottom,right_case,top_case);
        i++;
    }
    float right_case=a->children[i]->right-offsetx;
    float left_case=a->children[i]->left-offsetx;
    line(left,top,left_case,bottom);
    line(left_case,bottom,right,top);
    mid_x=(left_case+right_case)/2;
    top-=distanta_case;
    mid_y=(top+bottom+textheight("else")/2)/2;
    outtextxy(mid_x,mid_y,"else");
    i=1;
    while(i<=nr_cazuri)
    {
        float right_case=a->children[i]->right-offsetx;
        float left_case=a->children[i]->left-offsetx;
        char row[301];
        strcpy(row,a->children[i]->text);
        char *p=strstr(row,"case");
        p=p+5;
        int lg=strlen(p)-1;
        p[lg]='\0';
        char text[301];
        strcpy(text,p);
        float mid_x=(right_case+left_case-textwidth(text))/2;
        outtextxy(mid_x,mid_y,text);
        i++;
    }
}
void draw_while(tree a,float offsety,float offsetx)
{

    char row[301];
    strcpy(row,a->text);
    float left,top,right,bottom;
    left=a->left-offsetx;
    top=a->top-offsety;
    right=a->right-offsetx;
    bottom=a->bottom-offsety;
    char text[301];
    if(strstr(row,"cat timp"))
    {
        char *p=strstr(row,"cat timp");
        p=p+8;
        int lg=strlen(p)-7;
        p[lg]='\0';
        strcpy(text,p);
    }
    else
    {
        strcpy(text,row);
    }
    float mid_x=(left+right-textwidth(text))/2;
    float mid_y=(top+bottom-textheight(text))/2;
    outtextxy(mid_x,mid_y,text);
    line(right,top,right,bottom);
    line(left,top,right,top);
    int nr_instructiuni=tree_height(a)-1;
    bottom+=nr_instructiuni*(bottom-top);
    line(left,top,left,bottom);
    line(left,bottom,right,bottom);
    line(left,top,right,top);
}
void draw_do_while(tree a,float offsety,float offsetx)
{
    char row[301];
    strcpy(row,a->text);
    float left,top,right,bottom;
    left=a->left-offsetx;
    top=a->top-offsety;
    right=a->right-offsetx;
    bottom=a->bottom-offsety;
    strcpy(row,row+9);
    float mid_x=(left+right-textwidth(row))/2;
    float mid_y=(top+bottom-textheight(row))/2;
    outtextxy(mid_x,mid_y,row);
    float bottom_repeta=a->father->bottom-offsety;
    float left_repeta=a->father->father->left-offsetx;
    line(left_repeta,bottom_repeta,left_repeta,bottom);
    line(left_repeta,bottom,right,bottom);
    line(right,top,right,bottom);
}
void draw(tree a,float offsety,float offsetx)
{

    if(a->type==STATEMENT) draw_statement(a,offsety,offsetx);
    else if(a->type==EMPTY) draw_empty(a,offsety,offsetx);
    else if(a->type==IF) draw_if(a,offsety,offsetx);
    else if(a->type==WHILE) draw_while(a,offsety,offsetx);
    else if(a->type==DOWHILE) draw_do_while(a,offsety,offsetx);
    else if(a->type==SWITCH) draw_switch(a,offsety,offsetx);

    for(int i=1; i<=a->nrChildren; i++)
    {
        draw(a->children[i],offsety,offsetx);
    }
}
void display(tree a)
{
    float offy=0, offx=0, z=0;
    tree last=new node;
    measurements(a,last,basewidth,baseheight);
    draw(a,offy,offx);
    int W=min(WIDTHMAX,WIDTHPAG);
    int H=min(HEIGHTMAX,HEIGHTPAG);
    while(kbhit())
        getch();
    while(true)
    {
        while(!kbhit() && !ismouseclick(WM_LBUTTONDBLCLK))
            delay(100);
        if(kbhit())
        {
            int c1=getch();
            if(c1==0 && z==0)
            {
                int c2=getch();
                if(c2==80)
                {
                    offy=offy+200;
                    if(offy>HEIGHTMAX+BORDER-HEIGHTPAG)
                        offy=max(HEIGHTMAX+BORDER-HEIGHTPAG,0);
                }
                else if(c2==72)
                {
                    offy=offy-200;
                    if(offy<0)
                        offy=0;
                }
                else if(c2==77)
                {
                    offx=offx+200;
                    if(offx>WIDTHMAX+BORDER-WIDTHPAG)
                        offx=max(WIDTHMAX+BORDER-WIDTHPAG,0);
                }
                else if(c2==75)
                {
                    offx=offx-200;
                    if(offx<0)
                        offx=0;
                }
                cleardevice();
                draw(a,offy,offx);
            }
            else if(c1==13)
            {
                int baseheight=(float)(HEIGHTPAG-2*BORDER)/tree_height(a);
                int basewidth=(float)(WIDTHPAG-2*BORDER);
                last=new node;
                measurements(a,last,basewidth,baseheight);
                cleardevice();
                draw(a,0,0);
                writeimagefile(NULL,0,0,WIDTHMAX,HEIGHTMAX);
                baseheight=(float)(HEIGHTMAX-2*BORDER)/tree_height(a);
                basewidth=(float)(WIDTHMAX-2*BORDER);
                measurements(a,last,basewidth,baseheight);
                cleardevice();
                draw(a,offy,offx);
            }
            else if(c1==27)
            {
                end_program=1-end_program;
                clearmouseclick(WM_LBUTTONDOWN);
                break;
            }
        }
        else
        {
            cleardevice();
            if(z==0)
            {
                tree last1= new node;
                measurements(a,last1,2*basewidth,2*baseheight);
                int xm,ym;
                getmouseclick(WM_LBUTTONDBLCLK,xm,ym);
                draw(a,2*(offy-H/2+ym)+H/2,2*(offx-W/2+xm)+W/2);
                z=1;
            }
            else
            {
                tree last2= new node;
                measurements(a,last2,basewidth,baseheight);
                draw(a,offy,offx);
                z=0;
                clearmouseclick(WM_LBUTTONDBLCLK);
            }
        }
    }
}
void draw()
{
    ok=1;
    settings=0;
    readimagefile("assets/background.jpg",0,0,WIDTHPAG,HEIGHTPAG);
    int left,top,right,bottom;
    left=WIDTHPAG/2-4*BORDER;
    right=WIDTHPAG/2+4*BORDER;
    top=HEIGHTPAG/2-4*BORDER;
    bottom=HEIGHTPAG/2-2*BORDER;
    Load_file.left=left;
    Load_file.top=top;
    Load_file.right=right;
    Load_file.bottom=bottom;
    int mid_x=(left+right-textwidth("LOAD FILE"))/2;
    int mid_y=(top+bottom-textheight("LOAD FILE"))/2;
    outtextxy(mid_x,mid_y,"LOAD FILE");
    top=bottom;
    bottom+=2*BORDER;
    Open_diagram.left=left;
    Open_diagram.top=top;
    Open_diagram.right=right;
    Open_diagram.bottom=bottom;
    mid_x=(left+right-textwidth("OPEN DIAGRAM"))/2;
    mid_y=(top+bottom-textheight("OPEN DIAGRAM"))/2;
    outtextxy(mid_x,mid_y,"OPEN DIAGRAM");
    top=bottom;
    bottom+=2*BORDER;
    Settings.left=left;
    Settings.top=top;
    Settings.right=right;
    Settings.bottom=bottom;
    mid_x=(left+right-textwidth("SETTINGS"))/2;
    mid_y=(top+bottom-textheight("SETTINGS"))/2;
    outtextxy(mid_x,mid_y,"SETTINGS");
    top=bottom;
    bottom+=2*BORDER;
    Exit.left=left;
    Exit.top=top;
    Exit.right=right;
    Exit.bottom=bottom;
    rectangle(left,Load_file.top,right,bottom);
    setfillstyle(SOLID_FILL,BLACK);
    floodfill(left+1,Load_file.top+1,WHITE);
    mid_x=(left+right-textwidth("EXIT"))/2;
    mid_y=(top+bottom-textheight("EXIT"))/2;
    outtextxy(mid_x,mid_y,"EXIT");
}

void draw_open_file()
{
    readimagefile("assets/background_open_file.jpg",0,0,400,200);
    rectangle(50,100,250,150);
    rectangle(275,100,350,150);
    int mid_x=(275+350-textwidth("ENTER"))/2;
    int mid_y=(100+150-textheight("ENTER"))/2;
    outtextxy(mid_x,mid_y,"ENTER");
}
void draw_open_file_enter()
{
    rectangle(50,100,250,150);
    setcolor(BLUE);
    rectangle(275,100,350,150);
    int mid_x=(275+350-textwidth("ENTER"))/2;
    int mid_y=(100+150-textheight("ENTER"))/2;
    outtextxy(mid_x,mid_y,"ENTER");
}
void error()
{
    int errorcode;
    errorcode=graphresult();
    if (errorcode!=grOk)
    {
        exit(1);
    }
    getch();
    closegraph();
    initwindow(WIDTHMAX,HEIGHTMAX,"Diagrama Nassi Shneiderman");
}
void update_write_file()
{
    draw_open_file();
    bool the_end=0;
    int position=0;
    if(strlen(file))
    {
        strcpy(file,zero);
    }
    while(!the_end)
    {
        outtextxy(75,125,file);
        char c=getch();
        switch(c)
        {
        case 8:
            if (position)
            {
                cleardevice();
                draw_open_file();
                position--;
                file[position]=0;
            }
            break;
        case 13:
            draw_open_file_enter();
            the_end=1;
            break;
        default:
            if (position<80 && c>=' ' && c<='~')
            {
                file[position]=c;
                position++;
                file[position]='\0';
            }
        }
        if(position!=0 && the_end==0)
        {
            line(75+textwidth(file),125,75+textwidth(file),123+textheight(file));
        }
    }
    error();
    draw();
}
void clear_draw()
{
    int x,y;
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        x=mousex();
        y=mousey();
        if(x>=Back.left && x<=Back.right && y>=Back.top && y<=Back.bottom)
        {
            if(sound==1)
            {
                Beep(750,800);
            }
            cleardevice();
            draw();
        }
    }
}
void draw_back()
{
    setcolor(WHITE);
    int x_1,x_2,y_1,dif_x;
    x_1=BORDER,x_2=2*BORDER;
    y_1=HEIGHTPAG-2*BORDER;
    int dif=(x_2-x_1)/2;
    line(x_1,y_1,x_2,y_1);
    line(x_1,y_1,x_2-dif,y_1-BORDER/2);
    line(x_1,y_1,x_2-dif,y_1+BORDER/2);
    Back.left=x_1;
    Back.top=y_1-BORDER/2;
    Back.right=x_2;
    Back.bottom=y_1+BORDER/2;
}
void draw_sound()
{
    int left,top,right,bottom;
    left=2*BORDER;
    right=WIDTHPAG/2-4*BORDER;
    top=HEIGHTPAG/2;
    bottom=HEIGHTPAG/2+BORDER;
    int mid_x=(left+right-textwidth("SOUND"))/2;
    int mid_y=(top+bottom-textheight("SOUND"))/2;
    outtextxy(mid_x,mid_y,"SOUND");
    bottom+=BORDER;
    rectangle(left,top,right,bottom);
    Sound.left=left;
    Sound.top=top;
    Sound.right=right;
    Sound.bottom=bottom;
    top+=BORDER;
    if(sound==1)
    {
        mid_x=(left+right-textwidth("ON"))/2;
        mid_y=(top+bottom-textheight("ON"))/2;
        outtextxy(mid_x,mid_y,"ON");
    }
    else
    {
        mid_x=(left+right-textwidth("OFF"))/2;
        mid_y=(top+bottom-textheight("OFF"))/2;
        outtextxy(mid_x,mid_y,"OFF");
    }
}
void draw_music()
{
    int left,top,right,bottom;
    left=WIDTHPAG/2+4*BORDER;;
    right=WIDTHPAG-2*BORDER;;
    top=HEIGHTPAG/2;
    bottom=HEIGHTPAG/2+BORDER;
    int mid_x=(left+right-textwidth("MUSIC"))/2;
    int mid_y=(top+bottom-textheight("MUSIC"))/2;
    outtextxy(mid_x,mid_y,"MUSIC");
    bottom+=BORDER;
    rectangle(left,top,right,bottom);
    Music.left=left;
    Music.top=top;
    Music.right=right;
    Music.bottom=bottom;
    top+=BORDER;
    if(music==1)
    {
        mid_x=(left+right-textwidth("ON"))/2;
        mid_y=(top+bottom-textheight("ON"))/2;
        outtextxy(mid_x,mid_y,"ON");
    }
    else
    {
        mid_x=(left+right-textwidth("OFF"))/2;
        mid_y=(top+bottom-textheight("OFF"))/2;
        outtextxy(mid_x,mid_y,"OFF");
    }
}
void draw_size()
{
    int left,top,right,bottom;
    top=HEIGHTPAG/2-4*BORDER;
    bottom=HEIGHTPAG/2-3*BORDER;
    left=Sound.left;
    right=Sound.right;
    int mid_x=(left+right-textwidth("SIZE OF DIAGRAM"))/2;
    int mid_y=(top+bottom-textheight("SIZE OF DIAGRAM"))/2;
    outtextxy(mid_x,mid_y,"SIZE OF DIAGRAM");
    rectangle(left,top,right,bottom);
    Size.left=left;
    Size.top=top;
    Size.right=right;
    Size.bottom=bottom;
}
void draw_width()
{
    int left,top,right,bottom;
    left=Sound.right+BORDER;
    right=left+2*BORDER;
    top=Size.top;
    bottom=Size.bottom;
    rectangle(left,top,right,bottom);
    char text[10]="WIDTH";
    outtextxy((right+left-textwidth(text))/2,(bottom+top-textheight(text))/2-BORDER,text);
    Width.left=left;
    Width.top=top;
    Width.right=right;
    Width.bottom=bottom;
    if(width_draw==1)
    {
        outtextxy(Width.left+20,Width.top+25,width);
    }
}
void draw_height()
{
    int left,top,right,bottom;
    left=Width.right+BORDER;
    right=left+2*BORDER;
    top=Size.top;
    bottom=Size.bottom;
    rectangle(left,top,right,bottom);
    char text[10]="HEIGHT";
    outtextxy((right+left-textwidth(text))/2,(bottom+top-textheight(text))/2-BORDER,text);
    Height.left=left;
    Height.top=top;
    Height.right=right;
    Height.bottom=bottom;
    if(height_draw==1)
    {
        outtextxy(Height.left+20,Height.top+25,height);
    }
}
void draw_apply()
{
    int left,top,right,bottom;
    left=Height.right+BORDER;
    right=left+2*BORDER;
    top=Size.top;
    bottom=Size.bottom;
    rectangle(left,top,right,bottom);
    int mid_x=(left+right-textwidth("APPLY"))/2;
    int mid_y=(top+bottom-textheight("APPLY"))/2;
    outtextxy(mid_x,mid_y,"APPLY");
    Apply.left=left;
    Apply.top=top;
    Apply.right=right;
    Apply.bottom=bottom;
}
void draw_reset()
{
    int left,top,right,bottom;
    left=Apply.right+BORDER;
    right=left+2*BORDER;
    top=Size.top;
    bottom=Size.bottom;
    rectangle(left,top,right,bottom);
    int mid_x=(left+right-textwidth("RESET"))/2;
    int mid_y=(top+bottom-textheight("RESET"))/2;
    outtextxy(mid_x,mid_y,"RESET");
    Reset.left=left;
    Reset.top=top;
    Reset.right=right;
    Reset.bottom=bottom;
}
void draw_settings()
{
    draw_sound();
    draw_music();
    draw_size();
    draw_width();
    draw_height();
    draw_apply();
    draw_reset();
    draw_back();
}
void text_Load_file()
{
    setcolor(WHITE);
    int mid_x=(Load_file.left+Load_file.right-textwidth("LOAD FILE"))/2;
    int mid_y=(Load_file.top+Load_file.bottom-textheight("LOAD FILE"))/2;
    outtextxy(mid_x,mid_y,"LOAD FILE");
}
void text_Open_diagram()
{
    setcolor(WHITE);
    int mid_x=(Open_diagram.left+Open_diagram.right-textwidth("OPEN DIAGRAM"))/2;
    int mid_y=(Open_diagram.top+Open_diagram.bottom-textheight("OPEN DIAGRAM"))/2;
    outtextxy(mid_x,mid_y,"OPEN DIAGRAM");
}
void text_Exit()
{
    setcolor(WHITE);
    int mid_x=(Exit.left+Exit.right-textwidth("EXIT"))/2;
    int mid_y=(Exit.top+Exit.bottom-textheight("EXIT"))/2;
    outtextxy(mid_x,mid_y,"EXIT");
}
void text_Settings()
{
    setcolor(WHITE);
    int mid_x=(Settings.left+Settings.right-textwidth("SETTINGS"))/2;
    int mid_y=(Settings.top+Settings.bottom-textheight("SETTINGS"))/2;
    outtextxy(mid_x,mid_y,"SETTINGS");
}
void detect_mouse()
{
    int x,y;
    if(ismouseclick(WM_MOUSEMOVE)&& ok==1 && end_program==0)
    {
        clearmouseclick(WM_MOUSEMOVE);
        x=mousex();
        y=mousey();
        if(x>=Load_file.left && x<=Load_file.right && y>=Load_file.top && y<=Load_file.bottom)
        {
            setcolor(YELLOW);
            int mid_x=(Load_file.left+Load_file.right-textwidth("LOAD FILE"))/2;
            int mid_y=(Load_file.top+Load_file.bottom-textheight("LOAD FILE"))/2;
            outtextxy(mid_x,mid_y,"LOAD FILE");
            delay(150);
            text_Load_file();
        }
        else if(x>=Open_diagram.left && x<=Open_diagram.right && y>=Open_diagram.top && y<=Open_diagram.bottom)
        {
            setcolor(YELLOW);
            int mid_x=(Open_diagram.left+Open_diagram.right-textwidth("OPEN DIAGRAM"))/2;
            int mid_y=(Open_diagram.top+Open_diagram.bottom-textheight("OPEN DIAGRAM"))/2;
            outtextxy(mid_x,mid_y,"OPEN DIAGRAM");
            delay(150);
            text_Open_diagram();
        }
        else if(x>=Settings.left && x<=Settings.right && y>=Settings.top && y<=Settings.bottom)
        {
            setcolor(YELLOW);
            int mid_x=(Settings.left+Settings.right-textwidth("SETTINGS"))/2;
            int mid_y=(Settings.top+Settings.bottom-textheight("SETTINGS"))/2;
            outtextxy(mid_x,mid_y,"SETTINGS");
            delay(150);
            text_Settings();
        }
        else if(x>=Exit.left && x<=Exit.right && y>=Exit.top && y<=Exit.bottom)
        {
            setcolor(YELLOW);
            int mid_x=(Exit.left+Exit.right-textwidth("EXIT"))/2;
            int mid_y=(Exit.top+Exit.bottom-textheight("EXIT"))/2;
            outtextxy(mid_x,mid_y,"EXIT");
            delay(150);
            text_Exit();
        }
    }
}
void update_draw()
{
    int x,y;
    if(ismouseclick(WM_LBUTTONDOWN)&& ok==1 && end_program==0)
    {
        clearmouseclick(WM_LBUTTONDOWN);
        x=mousex();
        y=mousey();
        if(sound==1)
        {
            if(x>=Load_file.left && x<=Load_file.right && y>=Load_file.top && y<=Load_file.bottom)
            {
                Beep(750,800);
                setcolor(YELLOW);
                int mid_x=(Load_file.left+Load_file.right-textwidth("LOAD FILE"))/2;
                int mid_y=(Load_file.top+Load_file.bottom-textheight("LOAD FILE"))/2;
                outtextxy(mid_x,mid_y,"LOAD FILE");
                initwindow(400,200,"Open file");
                update_write_file();
                system(file);
                initTree(a);
                build(a,error_message);
                if(a==NULL)
                {
                    cleardevice();
                    setcolor(WHITE);
                    draw_back();
                    outtextxy((WIDTHPAG-textwidth(error_message))/2,(HEIGHTPAG-textheight(error_message))/2,error_message);
                    while(!ismouseclick(WM_LBUTTONDOWN))
                        delay(100);
                    clear_draw();
                }

            }
            else if(x>=Open_diagram.left && x<=Open_diagram.right && y>=Open_diagram.top && y<=Open_diagram.bottom)
            {
                Beep(750,800);
                ok=0;
                setcolor(YELLOW);
                int mid_x=(Open_diagram.left+Open_diagram.right-textwidth("OPEN DIAGRAM"))/2;
                int mid_y=(Open_diagram.top+Open_diagram.bottom-textheight("OPEN DIAGRAM"))/2;
                outtextxy(mid_x,mid_y,"OPEN DIAGRAM");
                text_Open_diagram();
                cleardevice();
                if(a!=NULL)
                {
                    end_program=end_program-1;
                    baseheight=(float)(HEIGHTMAX-2*BORDER)/tree_height(a);
                    basewidth=(float)(WIDTHMAX-2*BORDER);
                    last=new node;
                    measurements(a,last,basewidth,baseheight);
                    display(a);
                }
                else
                {
                    char message[100]="NO FILE LOADED";
                    outtextxy((WIDTHPAG-textwidth(message))/2,(HEIGHTPAG-textheight(message))/2,message);
                    draw_back();
                    while(!ismouseclick(WM_LBUTTONDOWN))
                        delay(100);
                    clear_draw();
                }
                draw();
            }
            else if(x>=Settings.left && x<=Settings.right && y>=Settings.top && y<=Settings.bottom)
            {
                Beep(750,800);
                ok=0;
                settings=1;
                setcolor(YELLOW);
                int mid_x=(Settings.left+Settings.right-textwidth("SETTINGS"))/2;
                int mid_y=(Settings.top+Settings.bottom-textheight("SETTINGS"))/2;
                outtextxy(mid_x,mid_y,"SETTINGS");
                text_Settings();
                cleardevice();
                draw_settings();
            }
            else if(x>=Exit.left && x<=Exit.right && y>=Exit.top && y<=Exit.bottom)
            {
                Beep(750,800);
                setcolor(YELLOW);
                int mid_x=(Exit.left+Exit.right-textwidth("EXIT"))/2;
                int mid_y=(Exit.top+Exit.bottom-textheight("EXIT"))/2;
                outtextxy(mid_x,mid_y,"EXIT");
                text_Exit();
                exit(0);
            }
        }
        else
        {
            if(x>=Load_file.left && x<=Load_file.right && y>=Load_file.top && y<=Load_file.bottom)
            {
                setcolor(YELLOW);
                int mid_x=(Load_file.left+Load_file.right-textwidth("LOAD FILE"))/2;
                int mid_y=(Load_file.top+Load_file.bottom-textheight("LOAD FILE"))/2;
                outtextxy(mid_x,mid_y,"LOAD FILE");
                initwindow(400,200,"Open file");
                update_write_file();
                system(file);
                initTree(a);
                build(a,error_message);
                if(a==NULL)
                {
                    cleardevice();
                    setcolor(WHITE);
                    draw_back();
                    outtextxy((WIDTHPAG-textwidth(error_message))/2,(HEIGHTPAG-textheight(error_message))/2,error_message);
                    while(!ismouseclick(WM_LBUTTONDOWN))
                        delay(100);
                    clear_draw();
                }
            }
            else if(x>=Open_diagram.left && x<=Open_diagram.right && y>=Open_diagram.top && y<=Open_diagram.bottom)
            {
                ok=0;
                setcolor(YELLOW);
                int mid_x=(Open_diagram.left+Open_diagram.right-textwidth("OPEN DIAGRAM"))/2;
                int mid_y=(Open_diagram.top+Open_diagram.bottom-textheight("OPEN DIAGRAM"))/2;
                outtextxy(mid_x,mid_y,"OPEN DIAGRAM");
                text_Open_diagram();
                cleardevice();
                if(a!=NULL)
                {
                    end_program=end_program-1;
                    baseheight=(float)(HEIGHTMAX-2*BORDER)/tree_height(a);
                    basewidth=(float)(WIDTHMAX-2*BORDER);
                    last=new node;
                    measurements(a,last,basewidth,baseheight);
                    display(a);
                }
                else
                {
                    char message[100]="NO FILE LOADED";
                    outtextxy((WIDTHPAG-textwidth(message))/2,(HEIGHTPAG-textheight(message))/2,message);
                    draw_back();
                    while(!ismouseclick(WM_LBUTTONDOWN))
                        delay(100);
                    clear_draw();
                }
                draw();
            }
            else if(x>=Settings.left && x<=Settings.right && y>=Settings.top && y<=Settings.bottom)
            {
                ok=0;
                settings=1;
                setcolor(YELLOW);
                int mid_x=(Settings.left+Settings.right-textwidth("SETTINGS"))/2;
                int mid_y=(Settings.top+Settings.bottom-textheight("SETTINGS"))/2;
                outtextxy(mid_x,mid_y,"SETTINGS");
                text_Settings();
                cleardevice();
                draw_settings();
            }
            else if(x>=Exit.left && x<=Exit.right && y>=Exit.top && y<=Exit.bottom)
            {
                setcolor(YELLOW);
                int mid_x=(Exit.left+Exit.right-textwidth("EXIT"))/2;
                int mid_y=(Exit.top+Exit.bottom-textheight("EXIT"))/2;
                outtextxy(mid_x,mid_y,"EXIT");
                text_Exit();
                exit(0);
            }
        }
    }
}
void detect_mouse_settings()
{
    int x,y;
    if(ismouseclick(WM_MOUSEMOVE)&& ok==0 && settings==1)
    {
        clearmouseclick(WM_MOUSEMOVE);
        x=mousex();
        y=mousey();
        if(x>=Sound.left && x<=Sound.right && y>=Sound.top && y<=Sound.bottom)
        {
            setcolor(GREEN);
            draw_sound();
            delay(150);
            setcolor(WHITE);
            draw_sound();
        }
        else if(x>=Music.left && x<=Music.right && y>=Music.top && y<=Music.bottom)
        {
            setcolor(GREEN);
            draw_music();
            delay(150);
            setcolor(WHITE);
            draw_music();
        }
        else if(x>=Apply.left && x<=Apply.right && y>=Apply.top && y<=Apply.bottom)
        {
            setcolor(YELLOW);
            draw_apply();
            delay(150);
            setcolor(WHITE);
            draw_apply();
        }
        else if(x>=Reset.left && x<=Reset.right && y>=Reset.top && y<=Reset.bottom)
        {
            setcolor(BLUE);
            draw_reset();
            delay(150);
            setcolor(WHITE);
            draw_reset();
        }
    }
}
void update_settings()
{
    int x,y;
    if(ismouseclick(WM_LBUTTONDOWN)&& ok==0 && settings==1)
    {
        clearmouseclick(WM_LBUTTONDOWN);
        x=mousex();
        y=mousey();
        if(sound==1)
        {
            if(x>=Sound.left && x<=Sound.right && y>=Sound.top && y<=Sound.bottom)
            {
                Beep(750,800);
                sound=1-sound;
                cleardevice();
                draw_settings();
            }
            else if(x>=Music.left && x<=Music.right && y>=Music.top && y<=Music.bottom)
            {
                Beep(750,800);
                music=1-music;
                if(music==1)
                {
                    PlaySound(TEXT("assets/music.wav"),NULL,SND_ASYNC);
                }
                else
                {
                    PlaySound(NULL,NULL,0);
                }
                cleardevice();
                draw_settings();
            }
            else if(x>=Width.left && x<=Width.right && y>=Width.top && y<=Width.bottom)
            {
                Beep(750,800);
                bool the_end=0;
                int position=0;
                if(strlen(width))
                {
                    strcpy(width,zero);
                    width_draw=0;
                    cleardevice();
                    draw_settings();
                }
                while(!the_end)
                {
                    outtextxy(Width.left+20,Width.top+25,width);
                    char c=getch();
                    switch(c)
                    {
                    case 8:
                        if (position)
                        {
                            cleardevice();
                            draw_settings();
                            position--;
                            width[position]=0;
                        }
                        break;
                    case 13:
                        the_end=1;
                        width_draw=1;
                        cleardevice();
                        draw_settings();
                        break;
                    default:
                        if (position<LMAX && c>='0' && c<='9')
                        {
                            width[position]=c;
                            position++;
                            width[position]='\0';
                        }
                    }
                    if(position!=0 && the_end==0)
                    {
                        line(Width.left+20+textwidth(width),Width.top+25,Width.left+20+textwidth(width),Width.top+23+textheight(width));
                    }
                }
                if(strlen(width))
                {
                    width_draw=1;
                }
            }
            else if(x>=Height.left && x<=Height.right && y>=Height.top && y<=Height.bottom)
            {
                Beep(750,800);
                bool the_end=0;
                int position=0;
                if(strlen(height))
                {
                    strcpy(height,zero);
                    height_draw=0;
                    cleardevice();
                    draw_settings();
                }
                while(!the_end)
                {
                    outtextxy(Height.left+20,Height.top+25,height);
                    char c=getch();
                    switch(c)
                    {
                    case 8:
                        if (position)
                        {
                            cleardevice();
                            draw_settings();
                            position--;
                            height[position]=0;
                        }
                        break;
                    case 13:
                        the_end=1;
                        height_draw=1;
                        cleardevice();
                        draw_settings();
                        break;
                    default:
                        if (position<LMAX && c>='0' && c<='9')
                        {
                            height[position]=c;
                            position++;
                            height[position]='\0';
                        }
                    }
                    if(position!=0 && the_end==0)
                    {
                        line(Height.left+20+textwidth(height),Height.top+25,Height.left+20+textwidth(height),Height.top+23+textheight(height));
                    }
                }
                if(strlen(height))
                {
                    height_draw=1;
                }
            }
            else if(x>=Apply.left && x<=Apply.right && y>=Apply.top && y<=Apply.bottom)
            {
                Beep(750,800);
                if(width_draw && height_draw)
                {
                    width_draw=0;
                    height_draw=0;
                    WIDTHMAX=atoi(width);
                    HEIGHTMAX=atoi(height);
                }
            }
            else if(x>=Reset.left && x<=Reset.right && y>=Reset.top && y<=Reset.bottom)
            {
                Beep(750,800);
                width_draw=0;
                height_draw=0;
                strcpy(width,zero);
                strcpy(height,zero);
                WIDTHMAX=GetSystemMetrics(SM_CXSCREEN);
                HEIGHTMAX=GetSystemMetrics(SM_CYSCREEN);
            }
            else if(x>=Back.left && x<=Back.right && y>=Back.top && y<=Back.bottom)
            {
                Beep(750,800);
                cleardevice();
                draw();
            }
        }
        else
        {
            if(x>=Sound.left && x<=Sound.right && y>=Sound.top && y<=Sound.bottom)
            {
                sound=1-sound;
                cleardevice();
                draw_settings();
            }
            else if(x>=Music.left && x<=Music.right && y>=Music.top && y<=Music.bottom)
            {
                music=1-music;
                if(music==1)
                {
                    PlaySound(TEXT("assets/music.wav"),NULL,SND_ASYNC);
                }
                else
                {
                    PlaySound(NULL,NULL,0);
                }
                cleardevice();
                draw_settings();
            }
            else if(x>=Width.left && x<=Width.right && y>=Width.top && y<=Width.bottom)
            {
                bool the_end=0;
                int position=0;
                if(strlen(width))
                {
                    strcpy(width,zero);
                    width_draw=0;
                    cleardevice();
                    draw_settings();
                }
                while(!the_end)
                {
                    outtextxy(Width.left+20,Width.top+25,width);
                    char c=getch();
                    switch(c)
                    {
                    case 8:
                        if (position)
                        {
                            cleardevice();
                            draw_settings();
                            position--;
                            width[position]=0;
                        }
                        break;
                    case 13:
                        the_end=1;
                        width_draw=1;
                        cleardevice();
                        draw_settings();
                        break;
                    default:
                        if (position<LMAX && c>='0' && c<='9')
                        {
                            width[position]=c;
                            position++;
                            width[position]='\0';
                        }
                    }
                    if(position!=0 && the_end==0)
                    {
                        line(Width.left+20+textwidth(width),Width.top+25,Width.left+20+textwidth(width),Width.top+23+textheight(width));
                    }
                }
                if(strlen(width))
                {
                    width_draw=1;
                }
            }
            else if(x>=Height.left && x<=Height.right && y>=Height.top && y<=Height.bottom)
            {
                bool the_end=0;
                int position=0;
                if(strlen(height))
                {
                    strcpy(height,zero);
                    height_draw=0;
                    cleardevice();
                    draw_settings();
                }
                while(!the_end)
                {
                    outtextxy(Height.left+20,Height.top+25,height);
                    char c=getch();
                    switch(c)
                    {
                    case 8:
                        if (position)
                        {
                            cleardevice();
                            draw_settings();
                            position--;
                            height[position]=0;
                        }
                        break;
                    case 13:
                        the_end=1;
                        height_draw=1;
                        cleardevice();
                        draw_settings();
                        break;
                    default:
                        if (position<LMAX && c>='0' && c<='9')
                        {
                            height[position]=c;
                            position++;
                            height[position]='\0';
                        }
                    }
                    if(position!=0 && the_end==0)
                    {
                        line(Height.left+20+textwidth(height),Height.top+25,Height.left+20+textwidth(height),Height.top+23+textheight(height));
                    }
                }
                if(strlen(height))
                {
                    height_draw=1;
                }
            }
            else if(x>=Apply.left && x<=Apply.right && y>=Apply.top && y<=Apply.bottom)
            {
                if(width_draw && height_draw)
                {
                    width_draw=0;
                    height_draw=0;
                    WIDTHMAX=atoi(width);
                    HEIGHTMAX=atoi(height);
                }
            }
            else if(x>=Reset.left && x<=Reset.right && y>=Reset.top && y<=Reset.bottom)
            {
                width_draw=0;
                height_draw=0;
                strcpy(width,zero);
                strcpy(height,zero);
                WIDTHMAX=GetSystemMetrics(SM_CXSCREEN);
                HEIGHTMAX=GetSystemMetrics(SM_CYSCREEN);
            }
            else if(x>=Back.left && x<=Back.right && y>=Back.top && y<=Back.bottom)
            {
                cleardevice();
                draw();
            }
        }
    }
}

