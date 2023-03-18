#include "include/graph.h"
int main()
{
    HEIGHTPAG=GetSystemMetrics(SM_CYSCREEN);
    WIDTHPAG=GetSystemMetrics(SM_CXSCREEN);
    HEIGHTMAX=HEIGHTPAG;
    WIDTHMAX=WIDTHPAG;
    initwindow(WIDTHPAG,HEIGHTPAG,"Diagrama Nassi-Shneiderman");
    draw();
    while(true)
    {
        setactivepage(end_program);
        detect_mouse();
        update_draw();
        detect_mouse_settings();
        update_settings();
        delay(150);
    }
    getch();
    closegraph();
    return 0;
}
