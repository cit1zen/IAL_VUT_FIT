
/* c402.c: ********************************************************************}
{* Téma: Nerekurzivní implementace operací nad BVS 
**                                     Implementace: Petr Přikryl, prosinec 1994
**                                           Úpravy: Petr Přikryl, listopad 1997
**                                                     Petr Přikryl, květen 1998
**			  	                        Převod do jazyka C: Martin Tuček, srpen 2005
**                                         Úpravy: Bohuslav Křena, listopad 2009
**                                         Úpravy: Karel Masařík, říjen 2013
**                                         Úpravy: Radek Hranický, říjen 2014
**                                         Úpravy: Radek Hranický, listopad 2015
**
** S využitím dynamického přidělování paměti, implementujte NEREKURZIVNĚ
** následující operace nad binárním vyhledávacím stromem (předpona BT znamená
** Binary Tree a je u identifikátorů uvedena kvůli možné kolizi s ostatními
** příklady):
**
**     BTInit .......... inicializace stromu
**     BTInsert ........ nerekurzivní vložení nového uzlu do stromu
**     BTPreorder ...... nerekurzivní průchod typu pre-order
**     BTInorder ....... nerekurzivní průchod typu in-order
**     BTPostorder ..... nerekurzivní průchod typu post-order
**     BTHeight ........ výpočet výšky stromu
**     BTDisposeTree ... zruš všechny uzly stromu
**
** U všech funkcí, které využívají některý z průchodů stromem, implementujte
** pomocnou funkci pro nalezení nejlevějšího uzlu v podstromu. Tyto pomocné
** funkce jsou:
**
**     Leftmost_Preorder
**     Leftmost_Inorder
**     Leftmost_Postorder
**
** Ve vaší implementaci si můžete definovat pomocné zásobníky pro uložení
** ukazetelů na uzly stromu (tStackP)
** nebo pro uložení booleovských hodnot TRUE/FALSE (tStackB).
** Pro práci s pomocnými zásobníky můžete použít následující funkce:
**
**     SInitP / SInitB ....... inicializace zásobníku
**     SPushP / SPushB ....... vložení prvku na vrchol zásobníku
**     SPopP / SPopB ......... odstranění prvku z vrcholu zásobníku
**     STopP / STopB ......... získání hodonty prvku na vrcholu zásobníku
**     STopPopP / STopPopB ... kombinace předchozích dvou funkcí 
**     SSizeP / SSizeB ....... zjištění počtu prvků v zásobníku
**     SEmptyP / SEmptyB ..... zjištění, zda je zásobník prázdný 
** 
** Pomocné funkce pro práci ze zásobníky je zakázáno upravovat!
** 
** Přesné definice typů naleznete v souboru c402.h. Uzel stromu je typu tBTNode,
** ukazatel na něj je typu tBTNodePtr. Jeden uzel obsahuje položku int Cont,
** která současně slouží jako užitečný obsah i jako vyhledávací klíč 
** a ukazatele na levý a pravý podstrom (LPtr a RPtr).
**
** Příklad slouží zejména k procvičení nerekurzivních zápisů algoritmů
** nad stromy. Než začnete tento příklad řešit, prostudujte si důkladně
** principy převodu rekurzivních algoritmů na nerekurzivní. Programování
** je především inženýrská disciplína, kde opětné objevování Ameriky nemá
** místo. Pokud se Vám zdá, že by něco šlo zapsat optimálněji, promyslete
** si všechny detaily Vašeho řešení. Povšimněte si typického umístění akcí
** pro různé typy průchodů. Zamyslete se nad modifikací řešených algoritmů
** například pro výpočet počtu uzlů stromu, počtu listů stromunebo pro
** vytvoření zrcadlového obrazu stromu (pouze popřehazování ukazatelů
** bez vytváření nových uzlů a rušení starých).
**
** Při průchodech stromem použijte ke zpracování uzlu funkci BTWorkOut().
** Pro zjednodušení práce máte předem připraveny zásobníky pro hodnoty typu
** bool a tBTNodePtr. Pomocnou funkci BTWorkOut ani funkce pro práci
** s pomocnými zásobníky neupravujte 
** Pozor! Je třeba správně rozlišovat, kdy použít dereferenční operátor *
** (typicky při modifikaci) a kdy budeme pracovat pouze se samotným ukazatelem 
** (např. při vyhledávání). V tomto příkladu vám napoví prototypy funkcí.
** Pokud pracujeme s ukazatelem na ukazatel, použijeme dereferenci.
**/

#include "c402.h"
int solved;

void BTWorkOut (tBTNodePtr Ptr)		{
/*   ---------
** Pomocná funkce, kterou budete volat při průchodech stromem pro zpracování
** uzlu určeného ukazatelem Ptr. Tuto funkci neupravujte.
**/
			
	if (Ptr==NULL) 
    printf("Chyba: Funkce BTWorkOut byla volána s NULL argumentem!\n");
  else 
    printf("Výpis hodnoty daného uzlu> %d\n",Ptr->Cont);
}
	
/* -------------------------------------------------------------------------- */
/*
** Funkce pro zásobník hotnot typu tBTNodePtr. Tyto funkce neupravujte.
**/

void SInitP (tStackP *S)  
/*   ------
** Inicializace zásobníku.
**/
{
	S->top = 0;  
}	

void SPushP (tStackP *S, tBTNodePtr ptr)
/*   ------
** Vloží hodnotu na vrchol zásobníku.
**/
{ 
                 /* Při implementaci v poli může dojít k přetečení zásobníku. */
  if (S->top==MAXSTACK) 
    printf("Chyba: Došlo k přetečení zásobníku s ukazateli!\n");
  else {  
		S->top++;  
		S->a[S->top]=ptr;
	}
}	

tBTNodePtr STopPopP (tStackP *S)
/*         --------
** Odstraní prvek z vrcholu zásobníku a současně vrátí jeho hodnotu.
**/
{
                            /* Operace nad prázdným zásobníkem způsobí chybu. */
	if (S->top==0)  {
		printf("Chyba: Došlo k podtečení zásobníku s ukazateli!\n");
		return(NULL);	
	}	
	else {
		return (S->a[S->top--]);
	}	
}

tBTNodePtr STopP (tStackP *S)
/*         --------
** Vrátí hodnotu prvku na vrcholu zásobníku
**/
{
                            /* Operace nad prázdným zásobníkem způsobí chybu. */
	if (S->top==0)  {
		printf("Chyba: Došlo k podtečení zásobníku s ukazateli!\n");
		return(NULL);	
	}	
	else {
		return (S->a[S->top]);
	}	
}

void SPopP (tStackP *S)
/*         --------
** Odstraní prvek z vrcholu zásobníku
**/
{
                            /* Operace nad prázdným zásobníkem způsobí chybu. */
	if (S->top==0)  {
		printf("Chyba: Došlo k podtečení zásobníku s ukazateli!\n");
	}	
	else {
		S->top--;
	}	
}

int SSizeP (tStackP *S) {
/*   -------
** Vrátí počet prvků v zásobníku
**/
  return(S->top);
}

bool SEmptyP (tStackP *S)
/*   -------
** Je-li zásobník prázdný, vrátí hodnotu true.
**/
{
  return(S->top==0);
}	

/* -------------------------------------------------------------------------- */
/*
** Funkce pro zásobník hotnot typu bool. Tyto funkce neupravujte.
*/

void SInitB (tStackB *S) {
/*   ------
** Inicializace zásobníku.
**/

	S->top = 0;  
}	

void SPushB (tStackB *S,bool val) {
/*   ------
** Vloží hodnotu na vrchol zásobníku.
**/
                 /* Při implementaci v poli může dojít k přetečení zásobníku. */
	if (S->top==MAXSTACK) 
		printf("Chyba: Došlo k přetečení zásobníku pro boolean!\n");
	else {
		S->top++;  
		S->a[S->top]=val;
	}	
}

bool STopPopB (tStackB *S) {
/*   --------
** Odstraní prvek z vrcholu zásobníku a současně vrátí jeho hodnotu.
**/
                            /* Operace nad prázdným zásobníkem způsobí chybu. */
	if (S->top==0) {
		printf("Chyba: Došlo k podtečení zásobníku pro boolean!\n");
		return(NULL);	
	}	
	else {  
		return(S->a[S->top--]); 
	}	
}

bool STopB (tStackB *S)
/*         --------
** Vrátí hodnotu prvku na vrcholu zásobníku
**/
{
                            /* Operace nad prázdným zásobníkem způsobí chybu. */
	if (S->top==0)  {
		printf("Chyba: Došlo k podtečení zásobníku s ukazateli!\n");
		return(NULL);	
	}	
	else {
		return (S->a[S->top]);
	}	
}

void SPopB (tStackB *S)
/*         --------
** Odstraní prvek z vrcholu zásobníku
**/
{
                            /* Operace nad prázdným zásobníkem způsobí chybu. */
	if (S->top==0)  {
		printf("Chyba: Došlo k podtečení zásobníku s ukazateli!\n");
	}	
	else {
		S->top--;
	}	
}

int SSizeB (tStackB *S) {
/*   -------
** Vrátí počet prvků v zásobníku
**/
  return(S->top);
}

bool SEmptyB (tStackB *S) {
/*   -------
** Je-li zásobník prázdný, vrátí hodnotu true.
**/
  return(S->top==0);
}

/* -------------------------------------------------------------------------- */
/*
** Následuje jádro domácí úlohy - funkce, které máte implementovat. 
*/

void BTInit (tBTNodePtr *RootPtr)	{
/*   ------
** Provede inicializaci binárního vyhledávacího stromu.
**
** Inicializaci smí programátor volat pouze před prvním použitím binárního
** stromu, protože neuvolňuje uzly neprázdného stromu (a ani to dělat nemůže,
** protože před inicializací jsou hodnoty nedefinované, tedy libovolné).
** Ke zrušení binárního stromu slouží procedura BTDisposeTree.
**	
** Všimněte si, že zde se poprvé v hlavičce objevuje typ ukazatel na ukazatel,	
** proto je třeba při práci s RootPtr použít dereferenční operátor *.
**/
	(*RootPtr)=NULL;
	
	
	 //solved = FALSE;		  /* V případě řešení smažte tento řádek! */	
}

void BTInsert (tBTNodePtr *RootPtr, int Content) {
/*   --------
** Vloží do stromu nový uzel s hodnotou Content.
**
** Z pohledu vkládání chápejte vytvářený strom jako binární vyhledávací strom,
** kde uzly s hodnotou menší než má otec leží v levém podstromu a uzly větší
** leží vpravo. Pokud vkládaný uzel již existuje, neprovádí se nic (daná hodnota
** se ve stromu může vyskytnout nejvýše jednou). Pokud se vytváří nový uzel,
** vzniká vždy jako list stromu. Funkci implementujte nerekurzivně.
**/

	if((*RootPtr)==NULL)
	{
		(*RootPtr)=malloc(sizeof(struct tBTNode));
		(*RootPtr)->Cont=Content;
		(*RootPtr)->LPtr=NULL;
		(*RootPtr)->RPtr=NULL;
		return;
	}

	tBTNodePtr posuvny_ukazatel=(*RootPtr);
	while(1)
	{
		if(Content==posuvny_ukazatel->Cont)
		{
			return;
		}
		else
		{
			//Lavy podstrom
			if(posuvny_ukazatel->Cont>Content)
			{
				if(posuvny_ukazatel->LPtr==NULL)
				{
					posuvny_ukazatel->LPtr=malloc(sizeof(struct tBTNode));
					posuvny_ukazatel->LPtr->Cont=Content;
					posuvny_ukazatel->LPtr->LPtr=NULL;
					posuvny_ukazatel->LPtr->RPtr=NULL;
					return;
				}
				posuvny_ukazatel=posuvny_ukazatel->LPtr;
			}
			else if(posuvny_ukazatel->Cont<Content)
			{
				if(posuvny_ukazatel->RPtr==NULL)
				{
					posuvny_ukazatel->RPtr=malloc(sizeof(struct tBTNode));
					posuvny_ukazatel->RPtr->Cont=Content;
					posuvny_ukazatel->RPtr->LPtr=NULL;
					posuvny_ukazatel->RPtr->RPtr=NULL;
					return;
				}
				posuvny_ukazatel=posuvny_ukazatel->RPtr;
			}
		}
	}	
	
		
	 //solved = FALSE;		  /* V případě řešení smažte tento řádek! */	
}

/*                                  PREORDER                                  */

void Leftmost_Preorder (tBTNodePtr ptr, tStackP *Stack)	{
/*   -----------------
** Jde po levě větvi podstromu, dokud nenarazí na jeho nejlevější uzel.
**
** Při průchodu Preorder navštívené uzly zpracujeme voláním funkce BTWorkOut()
** a ukazatele na ně is uložíme do zásobníku.
**/
	while(ptr!=NULL)
	{
		SPushP(Stack,ptr);
		BTWorkOut(STopP(Stack));
		ptr=ptr->LPtr;
	}
	//solved = FALSE;		  /* V případě řešení smažte tento řádek! */	
}

void BTPreorder (tBTNodePtr RootPtr)	{
/*   ----------
** Průchod stromem typu preorder implementovaný nerekurzivně s využitím funkce
** Leftmost_Preorder a zásobníku ukazatelů. Zpracování jednoho uzlu stromu
** realizujte jako volání funkce BTWorkOut(). 
**/
	if(RootPtr==NULL)
		return;

	tStackP zasobnik;
	SInitP(&zasobnik);

	Leftmost_Preorder(RootPtr,&zasobnik);

	while(1)
	{
		if(STopP(&zasobnik)->RPtr==NULL)
		{
			SPopP(&zasobnik);
			if(SEmptyP(&zasobnik))
				return;
		}
		else
		{
			Leftmost_Preorder(STopPopP(&zasobnik)->RPtr,&zasobnik);
		}

	}
	//solved = FALSE;		  /* V případě řešení smažte tento řádek! */	
}


/*                                  INORDER                                   */ 

void Leftmost_Inorder(tBTNodePtr ptr, tStackP *Stack)		{
/*   ----------------
** Jde po levě větvi podstromu, dokud nenarazí na jeho nejlevější uzel.
**
** Při průchodu Inorder ukládáme ukazatele na všechny navštívené uzly do
** zásobníku. 
**/
	while(ptr!=NULL)
	{
		SPushP(Stack,ptr);
		ptr=ptr->LPtr;
	}	
	//solved = FALSE;		  /* V případě řešení smažte tento řádek! */	
	
}

void BTInorder (tBTNodePtr RootPtr)	{
/*   ---------
** Průchod stromem typu inorder implementovaný nerekurzivně s využitím funkce
** Leftmost_Inorder a zásobníku ukazatelů. Zpracování jednoho uzlu stromu
** realizujte jako volání funkce BTWorkOut(). 
**/
	if(RootPtr==NULL)
		return;

	tStackP zasobnik;
	SInitP(&zasobnik);
	Leftmost_Inorder(RootPtr,&zasobnik);

	while(1)
	{
		if(STopP(&zasobnik)->RPtr==NULL)
		{
			BTWorkOut(STopPopP(&zasobnik));
			if(SEmptyP(&zasobnik))
				return;
		}
		else
		{
			BTWorkOut(STopP(&zasobnik));
			Leftmost_Inorder(STopPopP(&zasobnik)->RPtr,&zasobnik);
		}

	}	
	//solved = FALSE;		  /* V případě řešení smažte tento řádek! */	
}

/*                                 POSTORDER                                  */ 

void Leftmost_Postorder (tBTNodePtr ptr, tStackP *StackP, tStackB *StackB) {
/*           --------
** Jde po levě větvi podstromu, dokud nenarazí na jeho nejlevější uzel.
**
** Při průchodu Postorder ukládáme ukazatele na navštívené uzly do zásobníku
** a současně do zásobníku bool hodnot ukládáme informaci, zda byl uzel
** navštíven poprvé a že se tedy ještě nemá zpracovávat. 
**/

	while(ptr!=NULL)
	{
		SPushP(StackP,ptr);
		SPushB(StackB,FALSE);
		ptr=ptr->LPtr;
	}	
	 //solved = FALSE;		  /* V případě řešení smažte tento řádek! */	
}

void BTPostorder (tBTNodePtr RootPtr)	{
/*           -----------
** Průchod stromem typu postorder implementovaný nerekurzivně s využitím funkce
** Leftmost_Postorder, zásobníku ukazatelů a zásobníku hotdnot typu bool.
** Zpracování jednoho uzlu stromu realizujte jako volání funkce BTWorkOut(). 
**/

	if(RootPtr==NULL)
		return;

	tStackP zasobnik;
	SInitP(&zasobnik);

	//Ak sme danym prvkov presli tak bude TRUE
	tStackB zasobnik_prechodu;
	SInitB(&zasobnik_prechodu);

	Leftmost_Postorder(RootPtr,&zasobnik,&zasobnik_prechodu);

	while(1)
	{
		if(STopP(&zasobnik)->RPtr==NULL || STopB(&zasobnik_prechodu))
		{
			BTWorkOut(STopPopP(&zasobnik));
			SPopB(&zasobnik_prechodu);
			if(SEmptyP(&zasobnik))
				return;
		}
		else
		{
			SPopB(&zasobnik_prechodu);
			SPushB(&zasobnik_prechodu,TRUE);
			Leftmost_Postorder(STopP(&zasobnik)->RPtr,&zasobnik,&zasobnik_prechodu);

		}

	}	
		
	//solved = FALSE;		  /* V případě řešení smažte tento řádek! */	
}


int BTHeight (tBTNodePtr RootPtr) {	
/*   ----------
** Vypočítá výšku BVS bez použití rekurze
**
** Návratová hodnota je výška stromu. Funkci implementujte nerekurzivně
** bez deklarování jakékoli další pomocné funkce, která není v zadání.
** Využijte pomocných zásobníků. Je doporučeno použít jeden ze zásobníků
** pro průběžné ukládání cesty od kořene stromu. Počet uzlů na takovéto
** cestě můžete zjistit použitím funkce SSizeP. Výška stromu je rovna
** délce (počtu hran) nejdelší cesty  od kořene k lisu.
**
** Výška prázdného stromu však není definována. V případě prázdného stromu
** bude funkce vracet hodnotu -1.  
**/

	if(RootPtr==NULL)
		return -1;

	int maximalna_vyska=0;

	tStackP zasobnik;
	SInitP(&zasobnik);

	tStackB historia_prechadzania;
	SInitB(&historia_prechadzania);

	//V podstate som len znova pouzil Postorder, lebo ten najviac pripomina vypocitavanie vysky
	Leftmost_Postorder(RootPtr,&zasobnik,&historia_prechadzania);

	while(1)
	{
		if(STopP(&zasobnik)->RPtr==NULL || STopB(&historia_prechadzania))
		{
			
			if(SSizeB(&historia_prechadzania)>maximalna_vyska)
				maximalna_vyska=SSizeB(&historia_prechadzania);
			SPopP(&zasobnik);
			SPopB(&historia_prechadzania);
			if(SEmptyP(&zasobnik))
				return (--maximalna_vyska);
		}
		else
		{
			SPopB(&historia_prechadzania);
			SPushB(&historia_prechadzania,TRUE);
			Leftmost_Postorder(STopP(&zasobnik)->RPtr,&zasobnik,&historia_prechadzania);

		}

	}

	//solved = FALSE;		  /* V případě řešení smažte tento řádek! */	

}


void BTDisposeTree (tBTNodePtr *RootPtr)	{
/*   -------------
** Zruší všechny uzly stromu a korektně uvolní jimi zabranou paměť.
**
** Funkci implementujte nerekurzivně s využitím zásobníku ukazatelů.
**/
	if((*RootPtr)==NULL)
		return;

	tStackP zasobnik;
	SInitP(&zasobnik);

	//Ak sme danym prvkov presli tak bude TRUE
	tStackB zasobnik_prechodu;
	SInitB(&zasobnik_prechodu);

	Leftmost_Postorder((*RootPtr),&zasobnik,&zasobnik_prechodu);

	while(1)
	{
		if(STopP(&zasobnik)->RPtr==NULL || STopB(&zasobnik_prechodu))
		{
			free(STopPopP(&zasobnik));
			SPopB(&zasobnik_prechodu);
			if(SEmptyP(&zasobnik))
			{
				(*RootPtr)=NULL;	
				return;
			}
		}
		else
		{
			SPopB(&zasobnik_prechodu);
			SPushB(&zasobnik_prechodu,TRUE);
			Leftmost_Postorder(STopP(&zasobnik)->RPtr,&zasobnik,&zasobnik_prechodu);

		}

	}
	
	//solved = FALSE;		  /* V případě řešení smažte tento řádek! */	
}

/* konec c402.c */

