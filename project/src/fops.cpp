#include "../include/variables.h"
void initTree(tree& a)
{
    a=new node;
    a->type=0;
    a->nrChildren=0;
    strcpy(a->text,"ROOT");
    a->left=a->right=BORDER;
    a->top=a->bottom=BORDER;
}
void initNode(tree &a,tree &p)
{
    a=new node;
    a->type=0;
    a->nrChildren=0;
    a->father=p;
    a->position=p->nrChildren+1;
    a->left=a->right=0;
    a->top=a->bottom=0;
    p->children[p->nrChildren+1]=a;
    p->nrChildren++;
}
int tree_height(tree a)
{
    if(a==NULL)
        return 0;
    else
    {
        if(a->type==IF)
            return 2+max(tree_height(a->children[1]),tree_height(a->children[2]));
        else if(a->type==WHILE)
        {
            int s=0;
            for(int i=1; i<=a->nrChildren; i++)
                s=s+tree_height(a->children[i]);
            return 1+s;
        }
        else if(a->type==SWITCH)
        {
            int mx=0,h;
            for(int i=1; i<=a->nrChildren; i++)
            {
                h=tree_height(a->children[i]);
                if(h>mx)
                    mx=h;
            }
            return a->nrChildren+mx;
        }
        else if(a->type==STATEMENT || a->type==DOWHILE || a->type==EMPTY)
            return 1;
        else if(a->type==END)
            return 2;
        else
        {
            int s=0;
            for(int i=1; i<=a->nrChildren; i++)
                s=s+tree_height(a->children[i]);
            return s;
        }
    }
}
void read(tree a,FILE *fisout)
{
    for(int i=1; i<=a->nrChildren; i++)
    {
        fprintf(fisout,"%d %s %d\n",a->children[i]->type,a->children[i]->text,tree_height(a->children[i]));
        read(a->children[i],fisout);
    }
}
