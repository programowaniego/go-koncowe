#ifndef alfabeta.c
void zabij_ruchy(element* ofiara)
{
    if(ofiara){
        zabij_ruchy(ofiara->nastepny);
    }
    free(ofiara);

}
int alfaBeta(plansza* stol,int glebokosc,int alfa,int beta,int* debesciak)
{
    element* glowa = NULL;
    glowa = dostepne_ruchy(stol,glowa,0,0);
    if(!glebokosc || !glowa){
            zabij_ruchy(glowa);
            return ocena_pozycji(stol);
    }
    else{
        do 
        {
            plansza* kopia = utworz_plansze(kopia,stol->gracz_na_ruchu,stol->wartosci,0); 
            postaw_pionek(kopia,&glowa->dostepne.pozycja);
            int ocena_czymtasowa = -alfaBeta(kopia,glebokosc - 1,-alfa,-beta,debesciak);
            kopia->gracz_na_ruchu = stol->gracz_na_ruchu == "O" ? "X" : "O"; 
            if(ocena_czymtasowa > beta)         
                break;
            if(ocena_czymtasowa < alfa) 
            {
                alfa = ocena_czymtasowa;
                *debesciak = glowa->dostepne.pozycja;
            }
            glowa = glowa->nastepny;
            free(kopia);
        }while(glowa);
        zabij_ruchy(glowa);
        return alfa;
    }
}
#endif
