
/* c206.c **********************************************************}
{* T�ma: Dvousm�rn� v�zan� line�rn� seznam
**
**                   N�vrh a referen�n� implementace: Bohuslav K�ena, ��jen 2001
**                            P�epracovan� do jazyka C: Martin Tu�ek, ��jen 2004
**                                            �pravy: Bohuslav K�ena, ��jen 2015
**
** Implementujte abstraktn� datov� typ dvousm�rn� v�zan� line�rn� seznam.
** U�ite�n�m obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datov� abstrakce reprezentov�n prom�nnou
** typu tDLList (DL znamen� Double-Linked a slou�� pro odli�en�
** jmen konstant, typ� a funkc� od jmen u jednosm�rn� v�zan�ho line�rn�ho
** seznamu). Definici konstant a typ� naleznete v hlavi�kov�m souboru c206.h.
**
** Va��m �kolem je implementovat n�sleduj�c� operace, kter� spolu
** s v��e uvedenou datovou ��st� abstrakce tvo�� abstraktn� datov� typ
** obousm�rn� v�zan� line�rn� seznam:
**
**      DLInitList ...... inicializace seznamu p�ed prvn�m pou�it�m,
**      DLDisposeList ... zru�en� v�ech prvk� seznamu,
**      DLInsertFirst ... vlo�en� prvku na za��tek seznamu,
**      DLInsertLast .... vlo�en� prvku na konec seznamu,
**      DLFirst ......... nastaven� aktivity na prvn� prvek,
**      DLLast .......... nastaven� aktivity na posledn� prvek,
**      DLCopyFirst ..... vrac� hodnotu prvn�ho prvku,
**      DLCopyLast ...... vrac� hodnotu posledn�ho prvku,
**      DLDeleteFirst ... zru�� prvn� prvek seznamu,
**      DLDeleteLast .... zru�� posledn� prvek seznamu,
**      DLPostDelete .... ru�� prvek za aktivn�m prvkem,
**      DLPreDelete ..... ru�� prvek p�ed aktivn�m prvkem,
**      DLPostInsert .... vlo�� nov� prvek za aktivn� prvek seznamu,
**      DLPreInsert ..... vlo�� nov� prvek p�ed aktivn� prvek seznamu,
**      DLCopy .......... vrac� hodnotu aktivn�ho prvku,
**      DLActualize ..... p�ep��e obsah aktivn�ho prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na dal�� prvek seznamu,
**      DLPred .......... posune aktivitu na p�edchoz� prvek seznamu,
**      DLActive ........ zji��uje aktivitu seznamu.
**
** P�i implementaci jednotliv�ch funkc� nevolejte ��dnou z funkc�
** implementovan�ch v r�mci tohoto p��kladu, nen�-li u funkce
** explicitn� uvedeno n�co jin�ho.
**
** Nemus�te o�et�ovat situaci, kdy m�sto leg�ln�ho ukazatele na seznam
** p�ed� n�kdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodn� komentujte!
**
** Terminologick� pozn�mka: Jazyk C nepou��v� pojem procedura.
** Proto zde pou��v�me pojem funkce i pro operace, kter� by byly
** v algoritmick�m jazyce Pascalovsk�ho typu implemenov�ny jako
** procedury (v jazyce C procedur�m odpov�daj� funkce vracej�c� typ void).
**/

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozorn�n� na to, �e do�lo k chyb�.
** Tato funkce bude vol�na z n�kter�ch d�le implementovan�ch operac�.
**/
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* glob�ln� prom�nn� -- p��znak o�et�en� chyby */
    return;
}

void DLInitList (tDLList *L) {
/*
** Provede inicializaci seznamu L p�ed jeho prvn�m pou�it�m (tzn. ��dn�
** z n�sleduj�c�ch funkc� nebude vol�na nad neinicializovan�m seznamem).
** Tato inicializace se nikdy nebude prov�d�t nad ji� inicializovan�m
** seznamem, a proto tuto mo�nost neo�et�ujte. V�dy p�edpokl�dejte,
** �e neinicializovan� prom�nn� maj� nedefinovanou hodnotu.
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


 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLDisposeList (tDLList *L) {
/*
** Zru�� v�echny prvky seznamu L a uvede seznam do stavu, v jak�m
** se nach�zel po inicializaci. Ru�en� prvky seznamu budou korektn�
** uvoln�ny vol�n�m operace free.
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


 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLInsertFirst (tDLList *L, int val) {
/*
** Vlo�� nov� prvek na za��tek seznamu L.
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
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


 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLInsertLast(tDLList *L, int val) {
/*
** Vlo�� nov� prvek na konec seznamu L (symetrick� operace k DLInsertFirst).
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
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


 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLFirst (tDLList *L) {
/*
** Nastav� aktivitu na prvn� prvek seznamu L.
** Funkci implementujte jako jedin� p��kaz (nepo��t�me-li return),
** ani� byste testovali, zda je seznam L pr�zdn�.
**/
    L->Act=L->First;



 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLLast (tDLList *L) {
/*
** Nastav� aktivitu na posledn� prvek seznamu L.
** Funkci implementujte jako jedin� p��kaz (nepo��t�me-li return),
** ani� byste testovali, zda je seznam L pr�zdn�.
**/
    L->Act=L->Last;


 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLCopyFirst (tDLList *L, int *val) {
/*
** Prost�ednictv�m parametru val vr�t� hodnotu prvn�ho prvku seznamu L.
** Pokud je seznam L pr�zdn�, vol� funkci DLError().
**/
    if(L!=NULL && L->First!=NULL && L->Last!=NULL)
        *val=L->First->data;
    else
        DLError();



 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLCopyLast (tDLList *L, int *val) {
/*
** Prost�ednictv�m parametru val vr�t� hodnotu posledn�ho prvku seznamu L.
** Pokud je seznam L pr�zdn�, vol� funkci DLError().
**/

    if(L!=NULL && L->First!=NULL && L->Last!=NULL)
        *val=L->Last->data;
    else
        DLError();


 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLDeleteFirst (tDLList *L) {
/*
** Zru�� prvn� prvek seznamu L. Pokud byl prvn� prvek aktivn�, aktivita
** se ztr�c�. Pokud byl seznam L pr�zdn�, nic se ned�je.
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


 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLDeleteLast (tDLList *L) {
/*
** Zru�� posledn� prvek seznamu L. Pokud byl posledn� prvek aktivn�,
** aktivita seznamu se ztr�c�. Pokud byl seznam L pr�zdn�, nic se ned�je.
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


 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLPostDelete (tDLList *L) {
/*
** Zru�� prvek seznamu L za aktivn�m prvkem.
** Pokud je seznam L neaktivn� nebo pokud je aktivn� prvek
** posledn�m prvkem seznamu, nic se ned�je.
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

 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLPreDelete (tDLList *L) {
/*
** Zru�� prvek p�ed aktivn�m prvkem seznamu L .
** Pokud je seznam L neaktivn� nebo pokud je aktivn� prvek
** prvn�m prvkem seznamu, nic se ned�je.
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


 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLPostInsert (tDLList *L, int val) {
/*
** Vlo�� prvek za aktivn� prvek seznamu L.
** Pokud nebyl seznam L aktivn�, nic se ned�je.
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
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


 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLPreInsert (tDLList *L, int val) {
/*
** Vlo�� prvek p�ed aktivn� prvek seznamu L.
** Pokud nebyl seznam L aktivn�, nic se ned�je.
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
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


 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLCopy (tDLList *L, int *val) {
/*
** Prost�ednictv�m parametru val vr�t� hodnotu aktivn�ho prvku seznamu L.
** Pokud seznam L nen� aktivn�, vol� funkci DLError ().
**/
    if(L->Act!=NULL)
        *val=L->Act->data;
    else
        DLError();



 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLActualize (tDLList *L, int val) {
/*
** P�ep��e obsah aktivn�ho prvku seznamu L.
** Pokud seznam L nen� aktivn�, ned�l� nic.
**/
    if(L->Act!=NULL)
        L->Act->data=val;

 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLSucc (tDLList *L) {
/*64 bytes from 192.168.12.35: icmp_seq=6 ttl=64 time=0.046 ms
** Posune aktivitu na n�sleduj�c� prvek seznamu L.
** Nen�-li seznam aktivn�, ned�l� nic.
** V�imn�te si, �e p�i aktivit� na posledn�m prvku se seznam stane neaktivn�m.
**/
    if(L->Act!=NULL)
        L->Act=L->Act->rptr;


// solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}


void DLPred (tDLList *L) {
/*
** Posune aktivitu na p�edchoz� prvek seznamu L.
** Nen�-li seznam aktivn�, ned�l� nic.
** V�imn�te si, �e p�i aktivit� na prvn�m prvku se seznam stane neaktivn�m.
**/
    if(L->Act!=NULL)
        L->Act=L->Act->lptr;


 //solved/ = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

int DLActive (tDLList *L) {
/*
** Je-li seznam L aktivn�, vrac� nenulovou hodnotu, jinak vrac� 0.
** Funkci je vhodn� implementovat jedn�m p��kazem return.
*/
    return (L->Act!=NULL?1:0);


// solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

/* Konec c206.c*/
