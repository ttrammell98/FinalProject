typedef struct Player
{
	const char * name;  //string
	int amount;
	int count;
} Player;

typedef struct Dealer
{
	int count;
	int amountTaken;  //the amount the player has lost
} Dealer;

typedef enum
{
	Ace = 1,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King
} Face;
typedef enum
{
	Spades,
	Clubs,
	Hearts,
	Diamond
}Suit;

typedef struct Card
{
	Face face;
	Suit suit;
} Card;
