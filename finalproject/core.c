#include<stdio.h>
#include<stdlib.h>
#include "types.h"
#include <time.h>

//char *GenerateFace();
//char *GenerateSuit();
Card GenerateCard();
int GetPointValue();
int GetDealerValue();
int DealerPlay();

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
	p.amount = atoi(money);
	p.count = 1;

	srand(time(NULL));

	Card c1;
	Card c2;
	Card dc1;
	Card dc2;

	char result = 'p';
	//printf("\nDo you want to (P)lay or (Q)uit: ");
	//scanf("%c",&result);

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

		printf("\nDo you want to (P)lay or (Q)uit: ");
	        scanf("%c",&result);

		if(result == 'Q' || result == 'q'){
			break;
		}


		printf("How much would you like to bet? ");
		scanf("%d", &bet);
		//printf("%d\n",bet);
		//printf("%d\n",p.amount);
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
			int firstCardTotal = GetDealerValue(dc1.face);
			printf("Dealer Total Showing: ");
			printf("%d\n\n",firstCardTotal);

			printf("Would you like to (H)it or (S)tand? ");
			scanf(" %c", &option);

			if(option == 's' || option == 'S'){
				result = 'q';
				break;
			}

			while(option == 'h' || option == 'H'){
				Card temp;
				temp = GenerateCard();
				printf("\nCard: ");
                        	printf("%s",face[temp.face-1]);
                        	printf(" of ");
                        	printf("%s\n\n",suit[temp.suit]);
                        	printf("Total Point Worth: ");
                        	playerTotal += GetPointValue(temp.face);
                        	printf("%d\n", playerTotal);

				if(playerTotal < 21){
					printf("(H)it or (S)tand? ");
                        		scanf(" %c", &option);

					if(option == 's' || option == 'S'){
						printf("The dealers second card is a ");
	                                	printf("%s",face[dc2.face-1]);
        	                        	printf(" of ");
                	                	printf("%s\n\n",suit[dc2.suit]);
                        	        	dealerTotal = firstCardTotal + GetDealerValue(dc2.face);
                                		printf("Dealer Total: ");
                                		printf("%d\n\n",dealerTotal);
						dealerTotal = DealerPlay(dealerTotal);
						if(dealerTotal > 21){
							printf("Dealer Busted! You Win!");
							p.amount += (2 * bet);
							printf("%d",p.amount);
						}
						else{
							if(dealerTotal > playerTotal){
								printf("You Lose!");
								p.amount -= bet;
								printf("%d\n",p.amount);
								if(p.amount == 0){
                                                			result = 'q';
                                                			break;
					                        }

								printf("Would you like to (p)lay again or (q)uit? ");
                                        			scanf(" %c", &result);
							}
							else if(dealerTotal < playerTotal){
								printf("You Win!");
                                                                p.amount += (2 * bet);
                                                                printf("%d\n",p.amount);
								if(p.amount == 0){
			                                                result = 'q';
                        			                        break;
                                        			}

								printf("Would you like to (p)lay again or (q)uit? ");
                                        			scanf(" %c", &result);
							}
							else{
								printf("Draw! Bet returned!");
								printf("Would you like to (p)lay again or (q)uit? ");
                                        			scanf(" %c", &result);
							}
						}

					}

				}
				else if(playerTotal > 21){
					printf("You have busted!\n");
					option = 's';
					p.amount -= bet;
					printf("%d\n", p.amount);
					if(p.amount == 0){
						result = 'q';
						break;
					}
					printf("Would you like to (p)lay again or (q)uit? ");
					scanf(" %c", &result);
				}

			}

			/*if(result != 'q'){
				printf("The dealers second card is a ");
				printf("%s",face[dc2.face-1]);
				printf(" of ");
                        	printf("%s\n\n",suit[dc2.suit]);
				dealerTotal = firstCardTotal + GetDealerValue(dc2.face);
				printf("Dealer Total: ");
				printf("%d\n",dealerTotal);
			}*/

		}
		//result = 'q';
	}
	printf("You have quit.\n");


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
	else if(faceVal == 1){
		printf("Would you like your Ace to be a (1) or (11)? ");
		scanf("%d", &realVal);
		//printf("%d\n", realVal);
		return realVal;
	}
	else
	{
		return faceVal;
	}

}

int GetDealerValue(int faceVal)
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


int DealerPlay(int curTotal){
	int total = curTotal;
	while(total < 17){
		Card temp;
		temp = GenerateCard();
		printf("The dealer's card is a ");
		printf("%s", face[temp.face-1]);
		printf(" of ");
		printf("%s", suit[temp.suit]);
		total += GetDealerValue(temp.face);
	}
	return total;
}

