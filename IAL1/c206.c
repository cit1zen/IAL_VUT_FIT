
/* c206.c **********************************************************}
{* Téma: Dvousmìrnì vázaný lineární seznam
**
**                   Návrh a referenèní implementace: Bohuslav Køena, øíjen 2001
**                            Pøepracované do jazyka C: Martin Tuèek, øíjen 2004
**                                            Úpravy: Bohuslav Køena, øíjen 2015
**
** Implementujte abstraktní datový typ dvousmìrnì vázaný lineární seznam.
** U¾iteèným obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datová abstrakce reprezentován promìnnou
** typu tDLList (DL znamená Double-Linked a slou¾í pro odli¹ení
** jmen konstant, typù a funkcí od jmen u jednosmìrnì vázaného lineárního
** seznamu). Definici konstant a typù naleznete v hlavièkovém souboru c206.h.
**
** Va¹ím úkolem je implementovat následující operace, které spolu
** s vý¹e uvedenou datovou èástí abstrakce tvoøí abstraktní datový typ
** obousmìrnì vázaný lineární seznam:
**
**      DLInitList ...... inicializace seznamu pøed prvním pou¾itím,
**      DLDisposeList ... zru¹ení v¹ech prvkù seznamu,
**      DLInsertFirst ... vlo¾ení prvku na zaèátek seznamu,
**      DLInsertLast .... vlo¾ení prvku na konec seznamu,
**      DLFirst ......... nastavení aktivity na první prvek,
**      DLLast .......... nastavení aktivity na poslední prvek,
**      DLCopyFirst ..... vrací hodnotu prvního prvku,
**      DLCopyLast ...... vrací hodnotu posledního prvku,
**      DLDeleteFirst ... zru¹í první prvek seznamu,
**      DLDeleteLast .... zru¹í poslední prvek seznamu,
**      DLPostDelete .... ru¹í prvek za aktivním prvkem,
**      DLPreDelete ..... ru¹í prvek pøed aktivním prvkem,
**      DLPostInsert .... vlo¾í nový prvek za aktivní prvek seznamu,
**      DLPreInsert ..... vlo¾í nový prvek pøed aktivní prvek seznamu,
**      DLCopy .......... vrací hodnotu aktivního prvku,
**      DLActualize ..... pøepí¹e obsah aktivního prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na dal¹í prvek seznamu,
**      DLPred .......... posune aktivitu na pøedchozí prvek seznamu,
**      DLActive ........ zji¹»uje aktivitu seznamu.
**
** Pøi implementaci jednotlivých funkcí nevolejte ¾ádnou z funkcí
** implementovaných v rámci tohoto pøíkladu, není-li u funkce
** explicitnì uvedeno nìco jiného.
**
** Nemusíte o¹etøovat situaci, kdy místo legálního ukazatele na seznam
** pøedá nìkdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodnì komentujte!
**
** Terminologická poznámka: Jazyk C nepou¾ívá pojem procedura.
** Proto zde pou¾íváme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozornìní na to, ¾e do¹lo k chybì.
** Tato funkce bude volána z nìkterých dále implementovaných operací.
**/
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* globální promìnná -- pøíznak o¹etøení chyby */
    return;
}

void DLInitList (tDLList *L) {
/*
** Provede inicializaci seznamu L pøed jeho prvním pou¾itím (tzn. ¾ádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádìt nad ji¾ inicializovaným
** seznamem, a proto tuto mo¾nost neo¹etøujte. V¾dy pøedpokládejte,
** ¾e neinicializované promìnné mají nedefinovanou hodnotu.
**/
    L=malloc(sizeof(tDLList));
    if(L==NULL)
        DLError();
    else
    {
        L->Act=NULL;
        L->First=NULL;
        L->Last=NULL;
    }


 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLDisposeList (tDLList *L) {
/*
** Zru¹í v¹echny prvky seznamu L a uvede seznam do stavu, v jakém
** se nacházel po inicializaci. Ru¹ené prvky seznamu budou korektnì
** uvolnìny voláním operace free.
**/

    //Ci vobec mame co mazat
    if(L!=NULL && L->First!=NULL)
    {
        //Samotne mazanie
        do
        {
            tDLElemPtr nasledujuci_prvok=L->First->rptr;
            free(L->First);
            L->First=nasledujuci_prvok;
        }while(L->First!=NULL);
        L->Act=NULL;
        L->Last=NULL;
    }


 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLInsertFirst (tDLList *L, int val) {
/*
** Vlo¾í nový prvek na zaèátek seznamu L.
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/
    tDLElemPtr nasledujuci_prvok=L->First;
    L->First=malloc(sizeof(struct tDLElem));
    if(L->First==NULL)
        DLError();
    else
    {
        L->First->rptr=nasledujuci_prvok;
        L->First->lptr=NULL;

        if(nasledujuci_prvok!=NULL)
            nasledujuci_prvok->lptr=L->First;
        else
            L->Last=L->First;
        L->First->data=val;
    }


 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLInsertLast(tDLList *L, int val) {
/*
** Vlo¾í nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/
    tDLElemPtr predchadzajuci_prvok=L->Last;
    L->Last=malloc(sizeof(struct tDLElem));
    if(L->Last==NULL)
        DLError();
    else
    {
        L->Last->lptr=predchadzajuci_prvok;
        L->Last->rptr=NULL;

        if(predchadzajuci_prvok!=NULL)
            predchadzajuci_prvok->rptr=L->Last;
        else
            L->First=L->Last;
        L->Last->data=val;
    }


 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLFirst (tDLList *L) {
/*
** Nastaví aktivitu na první prvek seznamu L.
** Funkci implementujte jako jediný pøíkaz (nepoèítáme-li return),
** ani¾ byste testovali, zda je seznam L prázdný.
**/
    L->Act=L->First;



 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLLast (tDLList *L) {
/*
** Nastaví aktivitu na poslední prvek seznamu L.
** Funkci implementujte jako jediný pøíkaz (nepoèítáme-li return),
** ani¾ byste testovali, zda je seznam L prázdný.
**/
    L->Act=L->Last;


 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLCopyFirst (tDLList *L, int *val) {
/*
** Prostøednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/
    if(L!=NULL && L->First!=NULL && L->Last!=NULL)
        *val=L->First->data;
    else
        DLError();



 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLCopyLast (tDLList *L, int *val) {
/*
** Prostøednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/

    if(L!=NULL && L->First!=NULL && L->Last!=NULL)
        *val=L->Last->data;
    else
        DLError();


 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLDeleteFirst (tDLList *L) {
/*
** Zru¹í první prvek seznamu L. Pokud byl první prvek aktivní, aktivita
** se ztrácí. Pokud byl seznam L prázdný, nic se nedìje.
**/

    if(L!=NULL && L->First!=NULL && L->Last!=NULL)
    {
        if(L->Act==L->First)
            L->Act=NULL;
        if(L->Last==L->First)
            L->Last=NULL;

        tDLElemPtr nasledujuci_prvok=L->First->rptr;
        free(L->First);
        L->First=nasledujuci_prvok;
        //Ked to nie je posledny prvok zoznamu
        if(L->First!=NULL)
            L->First->lptr=NULL;
    }


 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLDeleteLast (tDLList *L) {
/*
** Zru¹í poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se nedìje.
**/

    if(L!=NULL && L->First!=NULL && L->Last!=NULL)
    {
        if(L->Act==L->Last)
            L->Act=NULL;
        if(L->First==L->Last)
            L->First=NULL;

        tDLElemPtr predchadzajuci_prvok=L->Last->lptr;
        free(L->Last);
        L->Last=predchadzajuci_prvok;
        if(L->Last!=NULL)
            L->Last->rptr=NULL;
    }


 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLPostDelete (tDLList *L) {
/*
** Zru¹í prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se nedìje.
**/
    if(L->Act!=NULL && L->Act!=L->Last)
    {
        tDLElemPtr vymazavany_prvok=L->Act->rptr;

        L->Act->rptr=vymazavany_prvok->rptr;
        if(L->Act->rptr!=NULL)
            L->Act->rptr->lptr=L->Act;
        else
            L->Last=L->Act;

        free(vymazavany_prvok);
    }

 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLPreDelete (tDLList *L) {
/*
** Zru¹í prvek pøed aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se nedìje.
**/
    if(L->Act!=NULL && L->Act!=L->First)
    {
        tDLElemPtr vymazavany_prvok=L->Act->lptr;

        L->Act->lptr=vymazavany_prvok->lptr;
        if(L->Act->lptr!=NULL)
            L->Act->lptr->rptr=L->Act;
        else
            L->First=L->Act;

        free(vymazavany_prvok);
    }


 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLPostInsert (tDLList *L, int val) {
/*
** Vlo¾í prvek za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se nedìje.
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/
    if(L->Act==NULL)
        return;

    tDLElemPtr novy_prvok=malloc(sizeof(struct tDLElem));
    if(novy_prvok==NULL)
        DLError();
    else
    {
        //Ci sme neni nahodou na konci zoznamu
        if(L->Act!=L->Last)
            L->Act->rptr->lptr=novy_prvok;
        //Ak sme,musime pointer posledneho prvku prvku nastavit na novy prvok
        else
            L->Last=novy_prvok;

        novy_prvok->rptr=L->Act->rptr;

        L->Act->rptr=novy_prvok;
        novy_prvok->lptr=L->Act;

        novy_prvok->data=val;
    }


 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLPreInsert (tDLList *L, int val) {
/*
** Vlo¾í prvek pøed aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se nedìje.
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/
    if(L->Act==NULL)
        return;

    tDLElemPtr novy_prvok=malloc(sizeof(struct tDLElem));
    if(novy_prvok==NULL)
        DLError();
    else
    {
        //Ci sme neni nahodou na zaciatku zoznamu
        if(L->Act!=L->First)
            L->Act->lptr->rptr=novy_prvok;
        //Ak sme,musime pointer prveho prvku nastavit na novy prvok
        else
            L->First=novy_prvok;

        novy_prvok->lptr=L->Act->lptr;

        L->Act->lptr=novy_prvok;
        novy_prvok->rptr=L->Act;

        novy_prvok->data=val;
    }


 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLCopy (tDLList *L, int *val) {
/*
** Prostøednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam L není aktivní, volá funkci DLError ().
**/
    if(L->Act!=NULL)
        *val=L->Act->data;
    else
        DLError();



 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLActualize (tDLList *L, int val) {
/*
** Pøepí¹e obsah aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedìlá nic.
**/
    if(L->Act!=NULL)
        L->Act->data=val;

 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLSucc (tDLList *L) {
/*64 bytes from 192.168.12.35: icmp_seq=6 ttl=64 time=0.046 ms
** Posune aktivitu na následující prvek seznamu L.
** Není-li seznam aktivní, nedìlá nic.
** V¹imnìte si, ¾e pøi aktivitì na posledním prvku se seznam stane neaktivním.
**/
    if(L->Act!=NULL)
        L->Act=L->Act->rptr;


// solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}


void DLPred (tDLList *L) {
/*
** Posune aktivitu na pøedchozí prvek seznamu L.
** Není-li seznam aktivní, nedìlá nic.
** V¹imnìte si, ¾e pøi aktivitì na prvním prvku se seznam stane neaktivním.
**/
    if(L->Act!=NULL)
        L->Act=L->Act->lptr;


 //solved/ = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

int DLActive (tDLList *L) {
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Funkci je vhodné implementovat jedním pøíkazem return.
*/
    return (L->Act!=NULL?1:0);


// solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

/* Konec c206.c*/
