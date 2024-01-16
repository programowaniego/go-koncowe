#ifndef ocena.c
int dlugosc(char wejscie[]){    
    int k = 0;
    while(wejscie[k])
        k++;
    return k;
}
int ile_pol(plansza* stol){     
    int k = 0;
    for(int i = 0;i < wiersze * kolumny;i++){
        if(stol->wartosci[i] == "1")
            k++;
    }
    return k;
}
int terytorium(plansza* stol,int pole,int moje_pole[],char *napotkane){
    int dodatki[] = {1,-1,kolumny,-kolumny};
    moje_pole[pole] = 1;
    stol->wartosci[pole] = "1";
     
    for(int i = 0;i < 4;i++){
        if(pole + dodatki[i] >= 0 && pole + dodatki[i] < wiersze * kolumny && moje_pole[pole + dodatki[i]] == 0){   
            if((pole + dodatki[i] - (pole + dodatki[i]) % kolumny)/kolumny == (pole - pole % kolumny)/kolumny || (pole + dodatki[i])% kolumny == pole % kolumny){ 
                if(stol->wartosci[pole + dodatki[i]] != " " && stol->wartosci[pole + dodatki[i]] != "1"){                              
                    if(*stol->wartosci[pole + dodatki[i]] != napotkane[dlugosc(napotkane) - 1] && dlugosc(napotkane) < 2){                    
                        napotkane[dlugosc(napotkane)] = *stol->wartosci[pole + dodatki[i]];
                    }
                }
                if(stol->wartosci[pole + dodatki[i]] == " "){         
                    terytorium(stol, pole + dodatki[i],moje_pole,napotkane);
                }    
            }
        }
    }
}
int terytorium_po_calosci(plansza* stol,char gracz[2]){
    int moje_pole[wiersze * kolumny] = {};
    for(int i = 0;i < wiersze * kolumny;i++){         
        if(moje_pole[i] == 0 && stol->wartosci[i] == " "){   
            char napotkane[2] = "";
            terytorium(stol,i,moje_pole,napotkane);          
            if(dlugosc(napotkane) == 1 && *gracz == napotkane[0]){  
                if(napotkane[0] == 'O'){    
                    stol->terytoriumO += ile_pol(stol);
                }            
                if(napotkane[0] == 'X'){
                    stol->terytoriumX += ile_pol(stol);
                }
            }  
            for(int j = 0;j < wiersze * kolumny;j++){      
                if(stol->wartosci[j] == "1")
                    stol->wartosci[j] = " ";
            }
        }
    }
}
int ile_pionkow(plansza* stol, char* gracz)     
{
    int k = 0;
        for(int i = 0 ; i < wiersze * kolumny ; i++ )
        {
        if(stol->wartosci[i] == gracz) k++; 
        }
    return k;
}
int odleglosc_od_srodka(int srodek,int pozycja){
    int odlegloscx = srodek % kolumny - pozycja % kolumny;
    int odlegloscy = (srodek - srodek % kolumny)/kolumny - (pozycja - pozycja % kolumny)/kolumny;
    if(odlegloscx < 0)
        odlegloscx *= -1;
    if(odlegloscy < 0)
        odlegloscy *= -1;    
    return odlegloscx + odlegloscy;
}
int ocena_pozycji(plansza* stol){
    int ocena = 0,oddechy_grupy = 0;
    int moje_pole[wiersze * kolumny] = {};
    ocena += 10 * ile_pionkow(stol,stol->gracz_na_ruchu);
    for(int i = 0;i < wiersze * kolumny; i++){
        int sprawdzone[wiersze * kolumny] = {};
        if(stol->wartosci[i] == stol->gracz_na_ruchu){
            liczenie_oddechow_grupy(stol,i,sprawdzone,&oddechy_grupy);
        }
        if(stol->wartosci[i] == stol->gracz_na_ruchu && ile_pionkow(stol,stol->gracz_na_ruchu) < (wiersze * kolumny - wiersze * kolumny % 13) / 13)
            ocena -= odleglosc_od_srodka(wiersze*kolumny/2,i) * 5;   
        //dwoje oczu    
        if(i % kolumny == kolumny - 1 && stol->wartosci[i] == stol->gracz_na_ruchu )  
        {
        if(stol->wartosci[i - 1] == stol->gracz_na_ruchu && stol->wartosci[i - 1 + kolumny] == stol->gracz_na_ruchu && stol->wartosci[i - 1 + 2*kolumny] == stol->gracz_na_ruchu && stol->wartosci[i + 2*kolumny] == stol->gracz_na_ruchu && stol->wartosci[i - 1 + 3*kolumny] == stol->gracz_na_ruchu && stol->wartosci[i - 1 + 4*kolumny] == stol->gracz_na_ruchu&& stol->wartosci[i + 4*kolumny] == stol->gracz_na_ruchu) ocena+=30;
        }
        if(i % kolumny == 0 && stol->wartosci[i] == stol->gracz_na_ruchu)  
        {
            if(stol->wartosci[i + 1] == stol->gracz_na_ruchu && stol->wartosci[i + 1 + kolumny] == stol->gracz_na_ruchu && stol->wartosci[i + 1 + 2*kolumny] == stol->gracz_na_ruchu && stol->wartosci[i + 2*kolumny] == stol->gracz_na_ruchu && stol->wartosci[i + 1 + 3*kolumny] == stol->gracz_na_ruchu && stol->wartosci[i + 1 + 4*kolumny] == stol->gracz_na_ruchu&& stol->wartosci[i + 4*kolumny] == stol->gracz_na_ruchu) ocena+=30;
        }
        if(i < kolumny && stol->wartosci[i] == stol->gracz_na_ruchu)    
        {
            if(stol->wartosci[i + kolumny ] == stol->gracz_na_ruchu && stol->wartosci[i + kolumny + 1] == stol->gracz_na_ruchu && stol->wartosci[i + kolumny + 2 ] == stol->gracz_na_ruchu && stol->wartosci[i + 2 ] == stol->gracz_na_ruchu && stol->wartosci[i + kolumny + 3] == stol->gracz_na_ruchu&& stol->wartosci[i + kolumny + 4] == stol->gracz_na_ruchu && stol->wartosci[i + 4] == stol->gracz_na_ruchu) ocena+=30;
        }
        if(i > kolumny * (kolumny - 1) && stol->wartosci[i] == stol->gracz_na_ruchu)
        {
            if(stol->wartosci[i - kolumny ] == stol->gracz_na_ruchu && stol->wartosci[i - kolumny + 1] == stol->gracz_na_ruchu && stol->wartosci[i - kolumny + 2] == stol->gracz_na_ruchu && stol->wartosci[i + 2] == stol->gracz_na_ruchu&& stol->wartosci[i - kolumny + 3] == stol->gracz_na_ruchu && stol->wartosci[i - kolumny + 4] == stol->gracz_na_ruchu&& stol->wartosci[i + 4] == stol->gracz_na_ruchu ) ocena+=30;
        }
        //schody
         if(stol->wartosci[i] == stol->gracz_na_ruchu)
        {
            if (stol->wartosci[i - kolumny - 1] == stol->gracz_na_ruchu && stol->wartosci[i - 2 * kolumny - 2] == stol->gracz_na_ruchu && stol->wartosci[i - kolumny + 1] == stol->gracz_na_ruchu && stol->wartosci[i - 2 * kolumny + 2] == stol->gracz_na_ruchu ) ocena+=30;
            if (stol->wartosci[i - kolumny + 1] == stol->gracz_na_ruchu && stol->wartosci[i - 2 * kolumny + 2] == stol->gracz_na_ruchu && stol->wartosci[i + kolumny + 1] == stol->gracz_na_ruchu && stol->wartosci[i + 2 * kolumny + 2] == stol->gracz_na_ruchu ) ocena+=30;
            if (stol->wartosci[i + kolumny - 1] == stol->gracz_na_ruchu && stol->wartosci[i + 2 * kolumny - 2] == stol->gracz_na_ruchu && stol->wartosci[i + kolumny + 1] == stol->gracz_na_ruchu && stol->wartosci[i + 2 * kolumny + 2] == stol->gracz_na_ruchu ) ocena+=30;
            if (stol->wartosci[i + kolumny + 1] == stol->gracz_na_ruchu && stol->wartosci[i + 2 * kolumny + 2] == stol->gracz_na_ruchu && stol->wartosci[i - kolumny + 1] == stol->gracz_na_ruchu && stol->wartosci[i - 2 * kolumny + 2] == stol->gracz_na_ruchu ) ocena+=30;
        }
    }
        terytorium_po_calosci(stol,stol->gracz_na_ruchu);
        ocena += stol->terytoriumO*30; 
        ocena += stol->terytoriumX*30;
        stol->terytoriumO = 0;
        stol->terytoriumX = 0;
    int pomocnicza = 0;
    pomocnicza = ocena;
    ocena += oddechy_grupy;
    return ocena;
}
#endif
