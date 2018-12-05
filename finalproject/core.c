'#include<stdio.h>
#include<stdlib.h>
#include "types.h"
#include <time.h>

//char *GenerateFace();
//char *GenerateSuit();
Card GenerateCard();

const char * suit[] = { "Hearts", "Clubs", "Spades", "Diamonds"};
const char * face[] ={ "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
 "Nine", "Ten" , "Jack", "Queen", "King"};

int main(int argc, const char * argv[])
{
	const char * name = argv[1];
	const char * money = argv[2];
	printf("\n\n\nWELCOME TO BLACK JACK! \nCurrent Player:  %s",name);
	printf("\nCurrent Balance: $%s",money);
	printf("\n\n\n");

	Player p;
	p.name = name;
	p.amount =(int) money;
	p.count = 1;

	srand(time(NULL));

	Card c1;
	Card c2;
	Card dc1;
	Card dc2;

	char result;
	printf("\nDo you want to (P)lay or (Q)uit: ");
	scanf("%c",&result);

	int bet;
	char option;
	if((result != 'p') && ( result != 'P') && (result != 'q') && (result != 'Q'))
	{
		printf("\nNot a valid input");
	}

	while(result == 'P' || result == 'p')
	{
		int playerTotal = 0;
		int dealerTotal = 0;
		printf("How much would you like to bet? ");
		scanf("%d", &bet);
		if (bet > p.amount)
		{
			printf("\nIllegal bet\n");
		}
		else
		{
			c1 = GenerateCard();
			c2 = GenerateCard();
			printf("\nCard 1: ");
			printf("%s",face[c1.face-1]);
			printf(" of ");
			printf("%s",suit[c1.suit]);
			printf("\nCard 2: ");
			printf("%s",face[c2.face-1]);
			printf(" of ");
                        printf("%s\n\n",suit[c2.suit]);
			printf("Total Point Worth: ");
			playerTotal += GetPointValue(c1.face);
			playerTotal += GetPointValue(c2.face);
			printf("%d\n", playerTotal);

                        dc1 = GenerateCard();
                        dc2 = GenerateCard();
			printf("The dealer's face-up card is a ");
			printf("%s",face[dc1.face-1]);
			printf(" of ");
			printf("%s\n", suit[dc1.suit]);
			int firstCardTotal = GetPointValue(dc1.face);
			printf("Dealer Total Showing: ");
			printf("%d\n\n",firstCardTotal);

			printf("Would you like to (H)it or (S)tand? ");
			scanf("%c", option);

			printf("%c", option);


		}
		result = 'q';
	}



	return 0;
}

Card GenerateCard()
{
        Card temp;
	//int randFace = rand() % 13 + 1;
	//temp.Face.randFace;
        int r1 = rand() % 13 + 1; 
	int r2 = rand() % 4;

	const char * face1 = face[r1];
	const char * suit1 = suit[r2];

	temp.face = r1;
	temp.suit = r2;
	return temp;
}


int GetPointValue(int faceVal)
{
	int realVal;
	if(faceVal == 11 || faceVal == 12 || faceVal == 13)
	{
		realVal = 10;
		return realVal;
	}
	else
	{
		return faceVal;
	}

}







/*
char *GenerateFace()
{
	Card->Face = rand() % 13 + 1;

	switch(randVal){
		case 1:
			return "Ace";
			break;
		case 2:
                        return "Two";
                        break;
		case 3:
                        return "Three";
                        break;
		case 4:
                        return "Four";
                        break;
		case 5:
                        return "Five";
                        break;
		case 6:
                        return "Six";
                        break;
		case 7:
                        return "Seven";
                        break;
		case 8:
                        return "Eight";
                        break;
		case 9:
                        return "Nine";
                        break;
		case 10:
                        return "Ten";
                        break;
		case 11:
                        return "Jack";
                        break;
		case 12:
                        return "Queen";
                        break;
		case 13:
                        return "King";
                        break;
	}
}

char *GenerateSuit(){
	int randVal = rand() % 4;

	switch(randVal){
                case 0:
                        return "Spades";
                        break;
                case 1:
                        return "Hearts";
                        break;
                case 2:
                        return "Clubs";
                        break;
                case 3:
                        return "Diamonds";
                        break;
        }
*/




