#include "../include/fops.h"
int type(char line[])
{
    int type=0;
    if(strstr(line,"daca") || strstr(line,"if"))
    {
        if(type==0)
            type=IF;
        else
            return -1;
        if(strstr(line,"end"))
            type=-1*type;
    }
    if(strstr(line,"altfel") || strstr(line,"else"))
    {
        if(type==0)
            type=ELSE;
        else
            return -1;
    }
    if(strstr(line,"while") || (strstr(line,"cat") && strstr(line,"timp")))
    {
        if(type==0)
            type=WHILE;
        else
            return -1;
        if(strstr(line,"end"))
            type=-1*type;
    }
    if((strstr(line,"repeta") && !strstr(line,"pentru")) || (strstr(line,"do") && !strstr(line,"for")))
    {
        if(type==0)
            type=DO;
        else if(type!=WHILE)
            return -1;
        if(strstr(line,"end"))
            type=-1*type;
    }
    if(strstr(line,"until") || (strstr(line,"pana") && strstr(line,"cand")))
    {
        if(type==0)
            type=DOWHILE;
        else
            return -1;
        if(strstr(line,"end"))
            type=-1*type;
    }
    if(strstr(line,"switch"))
    {
        if(type==0)
            type=SWITCH;
        else
            return -1;
        if(strstr(line,"end"))
            type=-1*type;
    }
    if(strstr(line,"case"))
    {
        if(type==0)
            type=CASE;
        else
            return -1;
        if(strstr(line,"end"))
            type=-1*type;
    }
    if(strstr(line,"pentru") || strstr(line,"for"))
    {
        if(type==0)
            type=FOR;
        else
            return -1;
        if(strstr(line,"end"))
            type=-1*type;
    }
    if(strstr(line,"default"))
    {
        if(type==0)
            type=DEFAULT;
        else
            return -1;
        if(strstr(line,"end"))
            type=-1*type;
    }
    if(strstr(line,"citeste"))
    {
        if(type==0)
            type=STATEMENT;
        else
            return -1;
        if(strstr(line,"end"))
            return -1;
    }
    if(strstr(line,"<-") && !strstr(line,"for"))
    {
        if(type==0)
            type=STATEMENT;
        else
            return -1;
        if(strstr(line,"end"))
            return -1;
    }
    if(strcmp(line,"end")==0)
        type=END;
    if(type==0 && !strstr(line,"end") && !strstr(line,"begin"))
        type=STATEMENT;
    return type;
}
void build(tree &a,char message_error[])
{

    FILE *fis;
    char instruction[301];
    fis=fopen(file,"r+");
    tree p;
    p=a;
    int linie=0;
    while(!feof(fis))
    {

        fgets(instruction,301,fis);
        instruction[strlen(instruction)-1]=NULL;
        char *line=strtok(instruction,";");
        if(line==NULL)
            linie++;
        while(line)
        {

            linie++;
            if(type(line)==-1)
            {
                strcpy(error_message,"ERROR: INCORECT STATEMENT LINE ");
                char c[5];
                itoa(linie,c,10);
                strcat(error_message,c);
                a=NULL;
                break;
            }
            if(type(line)==IF)
            {
                initNode(p->children[p->nrChildren+1],p);
                p=p->children[p->nrChildren];
                p->type=IF;
                strcpy(p->text,line);
                initNode(p->children[1],p);
                initNode(p->children[2],p);
                p->children[1]->type=TRUECASE;
                strcpy(p->children[1]->text,"T");
                strcpy(p->children[2]->text,"F");
                p->children[2]->type=FALSECASE;
                p=p->children[1];
            }
            else if(type(line)==ELSE)
            {
                p=p->father->children[2];
            }
            else if(type(line)==WHILE)
            {
                initNode(p->children[p->nrChildren+1],p);
                p=p->children[p->nrChildren];
                strcpy(p->text,line);
                p->type=WHILE;
            }
            else if(type(line)==FOR)
            {
                initNode(p->children[p->nrChildren+1],p);
                p=p->children[p->nrChildren];
                char *s=strstr(line,"for");
                s=s+4;
                p->type=STATEMENT;
                char text1[30];
                strcpy(text1,s);
                int i=0;
                while(text1[i]!=' ')
                    i++;
                text1[i]='\0';
                strcpy(p->text,text1);
                p=p->father;
                initNode(p->children[p->nrChildren+1],p);
                p=p->children[p->nrChildren];
                char text2[30];
                text2[0]=s[0];
                if(strstr(s,"downto"))
                {
                    text2[1]='>';
                    text2[2]='=';
                    s=strstr(s,"downto");
                    s=s+7;
                }
                else
                {
                    text2[1]='<';
                    text2[2]='=';
                    s=strstr(s,"to");
                    s=s+3;
                }
                i=3;
                int j=0;
                while(s[j]!=' ')
                {
                    text2[i]=s[j];
                    i++;
                    j++;
                }
                text2[i]='\0';
                strcpy(p->text,text2);
                p->type=WHILE;
            }

            else if(type(line)==DO)
            {
                initNode(p->children[p->nrChildren+1],p);
                p=p->children[p->nrChildren];
                p->type=DO;
                strcpy(p->text,"startdo");
            }
            else if(type(line)==SWITCH)
            {
                initNode(p->children[p->nrChildren+1],p);
                p=p->children[p->nrChildren];
                p->type=SWITCH;
                strcpy(p->text,line);
            }
            else if(type(line)==CASE || type(line)==DEFAULT)
            {
                initNode(p->children[p->nrChildren+1],p);
                p=p->children[p->nrChildren];
                p->type=type(line);
                strcpy(p->text,line);
            }
            else if(type(line)==END)
            {
                initNode(p->children[p->nrChildren+1],p);
                p=p->children[p->nrChildren];
                p->type=type(line);
                p=p->father;
            }
            else if(type(line)<0 && type(line)!=-IF && type(line)!=-FOR)
            {
                if(p->type!=-1*type(line))
                {
                    a=NULL;
                    strcpy(error_message,"ERROR: INCORECT CLOSING STATEMENT LINE ");
                    char c[5];
                    itoa(linie,c,10);
                    strcat(error_message,c);
                    break;
                }
                if(p->nrChildren==0 && (p->type==DEFAULT))
                {
                    initNode(p->children[1],p);
                    p->children[1]->type=EMPTY;
                }
                p=p->father;
            }
            else if(type(line)==-FOR)
            {
                initNode(p->children[p->nrChildren+1],p);
                p=p->children[p->nrChildren];
                p->type=STATEMENT;
                char text[10];

                text[0]=p->father->text[0];
                text[1]='<';
                text[2]='-';
                text[3]=text[0];
                if(strchr(p->father->text,'>'))
                    text[4]='+';
                else
                    text[4]='-';
                text[5]='1';
                text[6]='\0';
                strcpy(p->text,text);
                p=p->father->father;
            }
            else if(type(line)==-IF)
            {
                if(p->type!=FALSECASE && p->type!=TRUECASE)
                {
                    a=NULL;
                    strcpy(error_message,"ERROR: INCORECT CLOSING STATEMENT LINE ");
                    char c[5];
                    itoa(linie,c,10);
                    strcat(error_message,c);
                    break;

                }
                else  if(p->father->children[2]->nrChildren==0)
                {
                    initNode(p->father->children[2]->children[1],p->father->children[2]);
                    p->father->children[2]->children[1]->type=EMPTY;
                }
                p=p->father->father;
            }
            else if(type(line)==DOWHILE)
            {
                initNode(p->children[p->nrChildren+1],p);
                p=p->children[p->nrChildren];
                p->type=DOWHILE;
                strcpy(p->text,line);
                if(p->father->type!=DO)
                {
                    a=NULL;
                    strcpy(error_message,"ERROR: INCORECT CLOSING STATEMENT LINE ");
                    char c[5];
                    itoa(linie,c,10);
                    strcat(error_message,c);
                }
                p=p->father->father;
            }
            else if(!strchr(line,'{') && !strchr(line,'}') && type(line)==STATEMENT)
            {
                initNode(p->children[p->nrChildren+1],p);
                p=p->children[p->nrChildren];
                p->type=STATEMENT;
                strcpy(p->text,line);
                p=p->father;
            }
            if(a==NULL)
                break;
            line=strtok(NULL,";");
        }
        if(a==NULL)
            break;
    }
    if(p!=a && a!=NULL)
    {
        a=NULL;
        strcpy(error_message,"ERROR: STATEMENT LEFT UNCLOSED LINE ");
        char c[5];
        itoa(linie,c,10);
        strcat(error_message,c);
    }
    fclose(fis);
}
