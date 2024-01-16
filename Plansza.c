#ifndef Plansza.c
//kolorki na Linuxa
#define KOLKO   "\x1b[32m"
#define KRZYZYK "\x1b[34m"
#define ZNAK "\x1b[31m"
#define RESET   "\x1b[0m"
#define TLO "\x1b[0m"

#define wiersze 9
#define kolumny 9
typedef struct plansza
{
    char* wartosci[wiersze * kolumny];    //reprezentacja stanu gry
    char* gracz_na_ruchu;
    int terytoriumX;
    int terytoriumO;
}plansza;
plansza* utworz_plansze(plansza* nowa,char gracz[2],char* pionki_na_polach[wiersze * kolumny],int czy_pusta){     
    plansza* nowa_plansza = (plansza*)malloc(sizeof(plansza));
    
    nowa_plansza->gracz_na_ruchu = gracz; 
    nowa_plansza->terytoriumO = 0;
    nowa_plansza->terytoriumX = 0;
    if(czy_pusta == 0)
    {
        for(int i = 0;i < wiersze * kolumny;i++)
        {
            nowa_plansza->wartosci[i] = pionki_na_polach[i];
        }
    }
    else
    {
        for(int i = 0;i < wiersze * kolumny;i++)
            nowa_plansza->wartosci[i] = " ";
    }
    return nowa_plansza;
}
typedef struct{
    int pozycja;
}ruchy;
//generator ruchow
typedef struct element{
    ruchy dostepne;
    struct element* nastepny;
    struct element* poprzedni;
}element;
element* utworz_element(element* glowa, ruchy dostepne)
{
    element* nowy = malloc(sizeof(element));
    *nowy = (element){ nowy->dostepne = dostepne, nowy->nastepny = NULL};
    if (glowa)
    {
        for(element* pom = glowa; pom->nastepny || !(pom->nastepny = nowy); pom = pom->nastepny);
            return glowa;
    }
    return nowy;
}
element* dostepne_ruchy(plansza* stol,element* glowa,int posuniecie,int czy_ko){
    for(int i = 0;i < wiersze * kolumny && czy_ko == 0;i++)
    {
        if(stol->wartosci[i] == " ")                        
        {
            glowa = utworz_element(glowa , (ruchy) { .pozycja = i});        
        }
    }
    if(czy_ko == 1){
            glowa = utworz_element(glowa,(ruchy){.pozycja = posuniecie});
    }
    return glowa;
}
void wypisz(plansza* stol){
    for(int i = 0;i < kolumny;i++)
        {
                printf("   %c  ",'A' + i); 
        }
    printf("\n");
    for(int i = 0;i < kolumny;i++)
        {
            printf(" _____");
        }
    for(int k = 0;k < wiersze;k++)
    {
        printf("\n|");
        for(int i = 0;i < kolumny;i++)
        {
            printf("     |");
        }
        printf("\n|");
        for(int i = 0;i < kolumny;i++)
        {
            if(stol->wartosci[k * kolumny + i] == "O")
                printf("  %s%s%s  |",KOLKO,stol->wartosci[k * kolumny + i],TLO);
            else if(stol->wartosci[k * kolumny + i] == "1")
                printf("  %s%s%s  |",ZNAK,stol->wartosci[k * kolumny + i],TLO);
            else
                printf("  %s%s%s  |",KRZYZYK,stol->wartosci[k * kolumny + i],TLO);
        }
        printf(" %d \n|",1 + k);
        for(int i = 0;i < kolumny;i++)
        {
            printf("_____|");
        }
    }
    printf("\n\n");
}

#endif