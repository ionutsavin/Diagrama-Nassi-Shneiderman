#include "../include/parser.h"
void measurements(tree &a,tree &last,float basewidth,float baseheight)
{

    if(a->type==0)
    {
        a->left=BORDER;
        a->right=BORDER+basewidth;
        a->top=a->bottom=BORDER;
    }
    else if(a->type==TRUECASE)
    {
        a->left=a->father->left;
        a->right=a->father->left+(a->father->right-a->father->left)/2;
        a->top=a->bottom=a->father->bottom;
    }
    else  if(a->type==FALSECASE)
    {
        a->right=a->father->right;
        a->left=a->father->left+(a->father->right-a->father->left)/2;
        a->top=a->bottom=a->father->bottom;
    }
    else if(a->type==CASE || a->type==DEFAULT)
    {
        float latime=(a->father->right-a->father->left)/a->father->nrChildren;
        a->left=a->father->left+latime*(a->position-1);
        a->right=a->father->left+latime*a->position;
        a->top=a->bottom=a->father->bottom;
    }
    else if(a->type==DO)
    {
        if(a->father->type==0)
            a->left=a->father->left+baseheight;
        else if(a->father->type==WHILE)
            a->left=a->father->left+(a->father->bottom-a->father->top);
        else if(a->father->type==DO)
            a->left=a->father->left+(a->father->left-a->father->father->left);
        else if(a->father->type==TRUECASE || a->father->type==FALSECASE || a->father->type==CASE || a->father->type==DEFAULT)
            a->left=(float)(a->father->left+(a->father->father->bottom-a->father->father->top)/a->father->father->nrChildren)*(((tree_height(a->father->father))-a->father->father->nrChildren)/tree_height(a->father));
        a->right=last->right;
        a->top=a->bottom=last->bottom;
    }
    if(a->type==STATEMENT || a->type==EMPTY || a->type==WHILE || a->type==DOWHILE)
    {
        a->top=last->bottom;
        if(a->father->type==0)
        {
            a->bottom=a->top+baseheight;
            a->left=a->father->left;
            a->right=a->father->right;
        }
        else if(a->father->type==WHILE)
        {
            a->bottom=a->top+(a->father->bottom-a->father->top);
            a->left=a->father->left+(a->father->bottom-a->father->top);
            a->right=a->father->right;
        }
        else if(a->father->type==DO)
        {
            a->bottom=a->top+(a->father->left-a->father->father->left);
            a->left=a->father->left;
            a->right=a->father->right;
        }
        else if(a->father->type==TRUECASE || a->father->type==FALSECASE)
        {
            a->left=a->father->left;
            a->right=a->father->right;
            float r=(float)(tree_height(a->father->father)-2)/tree_height(a->father);
            a->bottom=(float)a->top+r*(a->father->father->bottom-a->father->father->top)/2;
        }
        else if(a->father->type==CASE || a->father->type==DEFAULT)
        {
            a->left=a->father->left;
            a->right=a->father->right;
            float r=(float)(tree_height(a->father->father)-a->father->father->nrChildren)/tree_height(a->father);
            a->bottom=(float)a->top+r*(a->father->father->bottom-a->father->father->top)/a->father->father->nrChildren;
        }
    }
    else if(a->type==IF || a->type==SWITCH)
    {

        a->top=last->bottom;
        if(a->father->type==0)
        {
            a->bottom=a->top+baseheight*a->nrChildren;
            a->left=a->father->left;
            a->right=a->father->right;
        }
        else if(a->father->type==WHILE)
        {
            a->bottom=a->top+(a->father->bottom-a->father->top)*a->nrChildren;
            a->left=a->father->left+(a->father->bottom-a->father->top);
            a->right=a->father->right;
        }
        else if(a->father->type==DO)
        {
            a->bottom=a->top+(a->father->left-a->father->father->left)*a->nrChildren;
            a->left=a->father->left;
            a->right=a->father->right;
        }
        else if(a->father->type==TRUECASE || a->father->type==FALSECASE)
        {
            a->left=a->father->left;
            a->right=a->father->right;
            float r=(float)(tree_height(a->father->father)-2)/tree_height(a->father);
            a->bottom=(float)a->top+r*(a->father->father->bottom-a->father->father->top)/2*a->nrChildren;
        }
        else if(a->father->type==CASE || a->father->type==DEFAULT)
        {
            a->left=a->father->left;
            a->right=a->father->right;
            float r=(float)(tree_height(a->father->father)-a->father->father->nrChildren)/tree_height(a->father);
            a->bottom=(float)a->top+r*(a->father->father->bottom-a->father->father->top)/a->father->father->nrChildren*a->nrChildren;
        }
    }
    else if(a->type==END)
    {
        a->left=BORDER;
        a->right=BORDER+basewidth;
        a->top=last->bottom;
        a->bottom=a->top+2*baseheight;
    }
    last=a;
    for(int i=1; i<=a->nrChildren; i++)
        measurements(a->children[i],last,basewidth,baseheight);
}

