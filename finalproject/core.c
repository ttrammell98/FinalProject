#include<stdio.h>
#include<stdlib.h>
#include "types.h"
#include <time.h>
#include <unistd.h>

//char *GenerateFace();
//char *GenerateSuit();
Card GenerateCard();
int GetPointValue();
int GetDealerValue();
int DealerPlay();
void CheckResult();

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
	printf("\nDo you want to (P)lay or (Q)uit: ");
	scanf("%c",&result);

	int bet;
	char option;

	//bool lost = FALSE;
	int lost = 0;

	if((result != 'p') && ( result != 'P') && (result != 'q') && (result != 'Q'))
	{
		printf("\nNot a valid input");
	}

	while(result == 'P' || result == 'p')
	{
		int playerTotal = 0;
		int dealerTotal = 0;

		printf("\nHow much would you like to bet? ");
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
                        printf("%s\n",suit[c2.suit]);
			printf("Total Points: ");
			playerTotal += GetPointValue(c1.face);
			playerTotal += GetPointValue(c2.face);
			printf("%d\n\n", playerTotal);

                        dc1 = GenerateCard();
                        dc2 = GenerateCard();
			printf("The dealer's face-up card is a ");
			printf("%s",face[dc1.face-1]);
			printf(" of ");
			printf("%s\n", suit[dc1.suit]);
			int firstCardTotal = GetDealerValue(dc1.face);
			printf("Dealer Points Showing: ");
			printf("%d\n\n",firstCardTotal);

			printf("Would you like to (H)it or (S)tand? ");
			scanf(" %c", &option);

			while(option == 'h' || option == 'H'){
				Card temp;
				temp = GenerateCard();
				printf("\nCard: ");
                        	printf("%s",face[temp.face-1]);
                        	printf(" of ");
                        	printf("%s\n\n",suit[temp.suit]);
                        	printf("Player Points: ");
                        	playerTotal += GetPointValue(temp.face);
                        	printf("%d\n", playerTotal);

				if(playerTotal < 21 || playerTotal == 21){
					printf("(H)it or (S)tand? ");
                        		scanf(" %c", &option);

					/*if(option == 's' || option == 'S'){
						printf("The dealers second card is a ");
	                                	printf("%s",face[dc2.face-1]);
        	                        	printf(" of ");
                	                	printf("%s\n\n",suit[dc2.suit]);
                        	        	dealerTotal = firstCardTotal + GetDealerValue(dc2.face);
                                		printf("Dealer Total: ");
                                		printf("%d\n\n",dealerTotal);
						dealerTotal = DealerPlay(dealerTotal);
						if(dealerTotal > 21){
             						printf("Dealer Busted! You Win!\n");
             						p.amount += (2 * bet);
             						printf("%d",p.amount);
        					}
        					else{
            						if(dealerTotal > playerTotal){
            							printf("You Lose!\n");
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
               							printf("You Win!\n");
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
               							printf("Draw! Bet returned!\n");
               							printf("Would you like to (p)lay again or (q)uit? ");
               							scanf(" %c", &result);
            						}
        					}

					}*/

				}
				else if(playerTotal > 21){
					printf("You have busted!\n");
					option = 's';
					lost = 1;
					p.amount -= bet;
					printf("Current Money: $%d\n\n\n", p.amount);
					if(p.amount == 0){
						result = 'q';
					}
					else{
						printf("Would you like to (p)lay again or (q)uit? ");
						scanf(" %c", &result);
					}
				}

			}//end of while hit is selected
			if(lost == 0){
				printf("\nThe dealers second card is a ");
                                printf("%s",face[dc2.face-1]);
                                printf(" of ");
                                printf("%s\n\n",suit[dc2.suit]);
                                dealerTotal = firstCardTotal + GetDealerValue(dc2.face);
                                printf("Dealer Points: ");
                                printf("%d\n\n",dealerTotal);

				dealerTotal = DealerPlay(dealerTotal);

				printf("Dealer Final Points: %d", dealerTotal);

				if(dealerTotal > 21){
			             	printf("\nDealer Busted! You Win!\n");
           	  			p.amount += (2 * bet);
             				printf("Current Money: $%d",p.amount);
					if(p.amount == 0){
                                           result = 'q';
                                           break;
                                        }
                                        printf("Would you like to (p)lay again or (q)uit? ");
                                        scanf(" %c", &result);

        			}
        			else{
            				if(dealerTotal > playerTotal){
            					printf("\nYou Lose!\n\n");
            					p.amount -= bet;
            					printf("Current Money: $%d\n\n\n",p.amount);
        	    				if(p.amount == 0){
     	          					result = 'q';
               						break;
            					}
            					printf("Would you like to (p)lay again or (q)uit? ");
            					scanf(" %c", &result);
            				}
        	    			else if(dealerTotal < playerTotal){
       	        				printf("\nYou Win!\n\n");
              					p.amount += (2 * bet);
               					printf("Current Money: $%d\n\n\n",p.amount);
               					if(p.amount == 0){
                	 				result = 'q';
        	         				break;
   	            				}
               					printf("Would you like to (p)lay again or (q)uit? ");
               					scanf(" %c", &result);
            				}
            				else{
               					printf("\nDraw! Bet returned!\n");
						printf("Current Money: $%d\n\n\n", p.amount);
         	      				printf("Would you like to (p)lay again or (q)uit? ");
               					scanf(" %c", &result);
            				}
        			}
			}


		}//end of while result is play
	}
	printf("Game Over! Summary has been recorded!\n");


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
		sleep(1);
		printf("The dealer's next card is a ");
		printf("%s", face[temp.face-1]);
		printf(" of ");
		printf("%s", suit[temp.suit]);
		printf("\n\n");
		sleep(1);
		total += GetDealerValue(temp.face);
	}
	return total;
}
