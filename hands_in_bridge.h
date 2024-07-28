#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct hand
{
    char NUMBER[13];
    char COLOR[13];
};

int readFromInput(struct hand name[])
{
    int N;
    scanf("%d ",&N);
    for (int i=0;i<N;i++)
    {
        scanf("%c%c ",&name[i].NUMBER[0], &name[i].COLOR[0]);
        for (int j=1;j<13;j++)
        {
            scanf("%c%c ",&name[i].NUMBER[j], &name[i].COLOR[j]);
        }
    }
    return N;
}

void printHand(struct hand name)
{
    char SPADES[13];
    int s=0;
    char HEARTS[13];
    int h=0;
    char DIAMONDS[13];
    int d=0;
    char CLUBS[13];
    int c=0;
    for (int j=0; j<13; j++)
    {
        if (name.COLOR[j]=='S')
        {
            SPADES[s]=name.NUMBER[j];
            s++;
        }
        if (name.COLOR[j]=='H')
        {
            HEARTS[h]=name.NUMBER[j];
            h++;
        }
        if (name.COLOR[j]=='D')
        {
            DIAMONDS[d]=name.NUMBER[j];
            d++;
        }
        if (name.COLOR[j]=='C')
        {
            CLUBS[c]=name.NUMBER[j];
            c++;
        }
    }
    printf("SPADES:   ");
    for(int i=0; i<s; i++)
    {
        printf("%c ",SPADES[i]);
    }
    printf("\n");
    printf("HEARTS:   ");
    for(int i=0; i<h; i++)
    {
        printf("%c ",HEARTS[i]);
    }
    printf("\n");
    printf("DIAMONDS: ");
    for(int i=0; i<d; i++)
    {
        printf("%c ",DIAMONDS[i]);
    }
    printf("\n");
    printf("CLUBS:    ");
    for(int i=0; i<c; i++)
    {
        printf("%c ",CLUBS[i]);
    }
    printf("\n");
}

int balanced(struct hand name)
{
    int s=0;
    int d=0;
    int h=0;
    int c=0;
    bool x=true;
    for (int i=0;i<13;i++)
    {
       if (name.COLOR[i]=='S')
            s++;
       else if (name.COLOR[i]=='D')
            d++;
      else if (name.COLOR[i]=='H')
            h++;
      else if (name.COLOR[i]=='C')
            c++;
    }
    if (s<2 || d<2 || h<2 || c<2 || (s==2 && (d==2 || h==2 || c==2)) || (d==2 && (h==2 || c==2) ) || (h==2 && c==2))
        x=false;
    return x;
}

int hcp(struct hand name)
{
    int oner=0;
    for (int i=0;i<13;i++)
    {
        if (name.NUMBER[i]=='A')
        {
            oner+=4;
        }
        else if (name.NUMBER[i]=='K')
        {
            oner+=3;
        }
        else if (name.NUMBER[i]=='Q')
        {
            oner+=2;
        }
        else if (name.NUMBER[i]=='J')
        {
            oner+=1;
        }
    }
    return oner;
}

int declarer(struct hand name)
{
    int declarer=0;
    int s=0;
    int h=0;
    int d=0;
    int c=0;
    for (int j=0; j<13; j++)
    {
        if (name.COLOR[j]=='S')
        {
            s++;
            if (s>4)
                declarer++;
        }
        if (name.COLOR[j]=='H')
        {
            h++;
            if (h>4)
                declarer++;
        }
        if (name.COLOR[j]=='D')
        {
            d++;
            if (d>4)
                declarer++;
        }
        if (name.COLOR[j]=='C')
        {
            c++;
            if (c>4)
                declarer++;
        }
    }
    return declarer;
}

void response(struct hand name)
{
    
    int h_and_d=hcp(name)+declarer(name);
    int hcp_=hcp(name);
    int declarer_=declarer(name);
    bool balanced_=balanced(name);

    if (balanced_ && (hcp_==15 || hcp_==16 || hcp_==17))
        printf("1NT\n");
    else if (balanced_ && (hcp_==20 || hcp_==21))
        printf("2NT\n");
    else if (hcp_>=22)
        printf("2 CLUBS\n");
    else if (hcp_<22 && h_and_d>=13)
    {
        int s=0,h=0,d=0,c=0;
        for (int j=0; j<13; j++)
        {
            if (name.COLOR[j]=='S')
            {
                s++;
            }
            if (name.COLOR[j]=='H')
            {
                h++;
            }
            if (name.COLOR[j]=='D')
            {
                d++;
            }
            if (name.COLOR[j]=='C')
            {
                c++;
            }
        }
        if (s>=5 && h<5)
            printf("1 SPADES\n");
        else if (h>=5 && s<h)
            printf("1 HEARTS\n");
        else if (d>=4 && (s<5 && h<5 && c<5))
            printf("1 DIAMONDS\n");
        else if (s<5 && h<5 && d<4)
            printf("1 CLUBS\n");
    }
    else if (h_and_d<13)
        printf("PASS\n");
}



////part2



#include <string.h>
int readFromFile(struct hand name[])
{
    char S[100];
    FILE *fp; 
    scanf("%s", S); 
    fp=fopen(S,"r");
    
    int N;
    if(fp!=NULL)
    {
        fscanf(fp,"%d",&N);
    }
    
    for (int i=0;i<N;i++)
    {
        fscanf(fp," %c%c",&name[i].NUMBER[0], &name[i].COLOR[0]);
        for (int j=1;j<13;j++)
        {
            fscanf(fp," %c%c",&name[i].NUMBER[j], &name[i].COLOR[j]);
        }
    }
    fclose(fp);
    return N;
}

void saveData(struct hand name[],int n)
{
    char S[100];
    FILE *fp; 
    scanf("%s", S); 
    fp=fopen(S,"w");

    char SPADES[13];
    char HEARTS[13];
    char DIAMONDS[13];
    char CLUBS[13];

    for (int k=0; k<n; k++)
    { 
        int s=0;
        int h=0;
        int d=0;
        int c=0; 

        for (int j=0; j<13; j++)
        {
            if (name[k].COLOR[j]=='S')
            {
                SPADES[s]=name[k].NUMBER[j];
                s++;
            }
            if (name[k].COLOR[j]=='H')
            {
                HEARTS[h]=name[k].NUMBER[j];
                h++;
            }
            if (name[k].COLOR[j]=='D')
            {
                DIAMONDS[d]=name[k].NUMBER[j];
                d++;
            }
            if (name[k].COLOR[j]=='C')
            {
                CLUBS[c]=name[k].NUMBER[j];
                c++;
            }
        }

        fprintf(fp,"SPADES:   ");
        for(int i=0; i<s; i++)
        {
            fprintf(fp,"%c ",SPADES[i]);
        }
        fprintf(fp,"\n");

        fprintf(fp,"HEARTS:   ");
        for(int i=0; i<h; i++)
        {
            fprintf(fp,"%c ",HEARTS[i]);
        }
        fprintf(fp,"\n");

        fprintf(fp,"DIAMONDS: ");
        for(int i=0; i<d; i++)
        {
            fprintf(fp,"%c ",DIAMONDS[i]);
        }
        fprintf(fp,"\n");

        fprintf(fp,"CLUBS:    ");
        for(int i=0; i<c; i++)
        {
            fprintf(fp,"%c ",CLUBS[i]);
        }
        fprintf(fp,"\n");

        fprintf(fp,"\n");
    }

    fclose(fp);
}


