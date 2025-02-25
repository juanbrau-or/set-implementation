#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <queue>

using namespace std;

class Card {
private:
	int number; // 1(0), 2(1), 3(2)
	int shape; // diamond (0), squiggle (1), oval (2)
	int shading; // solid (0), striped (1), open (2)
	int color; // red (0), green (1), purple (2)
public:
	Card():number(0),shape(0),shading(0),color(0){}
	Card(int, int, int, int);
	string toString();
	int getNumber(){ return number; }
	int getShape(){ return shape; }
	int getShading(){ return shading; }
	int getColor(){ return color; }
	
	bool operator==(const Card& other) const {
        return (number == other.number &&
                shape == other.shape &&
                shading == other.shading &&
                color == other.color);
    }
};

Card::Card(int number, int shape, int shading, int color) {
	this->number = number;
	this->shape = shape;
	this->shading = shading;
	this->color = color;
}

string Card::toString() {
	
	stringstream ss;
		
	if( number == 0 ) ss << "1 ";
	else if( number == 1 ) ss << "2 ";
	else ss << "3 ";
	
	if( shape == 0 ) ss << "diamond ";
	else if( shape == 1 ) ss << "squiggle ";
	else ss << "oval ";
	
	if( shading == 0 ) ss << "solid ";
	else if( shading == 1 ) ss << "striped ";
	else ss << "open ";
	
	if( color == 0 ) ss << "red";
	else if( color == 1 ) ss << "green";
	else ss << "purple";
	
	return ss.str();
}

bool checkSet(Card a, Card b, Card c) {
	int number = a.getNumber()+b.getNumber()+c.getNumber();
	int shape = a.getShape()+b.getShape()+c.getShape();
	int shading = a.getShading()+b.getShading()+c.getShading();
	int color = a.getColor()+b.getColor()+c.getColor();
	return (number%3 || shape%3 || shading%3 || color%3 ? false:true);
}

Card findSet(Card a, Card b) {
	int number = 6-a.getNumber()-b.getNumber();
	int shape = 6-a.getShape()-b.getShape();
	int shading = 6-a.getShading()-b.getShading();
	int color = 6-a.getColor()-b.getColor();
	return Card(number%3, shape%3, shading%3, color%3);
}

int checkPlanet(Card a, Card b, Card c, Card d) {
	if( findSet(a, b) == findSet(c, d) )
		return 1;
	if( findSet(a, c) == findSet(b, d) )
		return 2;
	if( findSet(a, d) == findSet(b, c) )
		return 3;
	return 0;
}

void play() {
	
	vector<Card> deck(81);
	
	for( int a=0; a<3; a++ )
		for( int b=0; b<3; b++ )
			for( int c=0; c<3; c++ )
				for( int d=0; d<3; d++ )
					deck.push_back(Card(a, b, c, d));
	
	// Initialize random number generator
	random_device rd;
	mt19937 g(rd());
	
	// Shuffle the vector
	shuffle(deck.begin(), deck.end(), g);
	
	queue<Card> game;
	for( int i=0; i<81; i++ ) {
		game.push(deck[i]);
	}
	
	while( !game.empty() ) {
		;
	}
}

int countPlanets(vector<Card> deck) {
	int n = deck.size(), ans = 0;
	
	for( int i=0; i<n; i++ )
		for( int j=i+1; j<n; j++ )
			for( int k=j+1; k<n; k++ )
				for( int l=k+1; l<n; l++ ) {
					int aux = checkPlanet(deck[i], deck[j], deck[k], deck[l]);
					if( aux ) {
						/*cout << "Planet #" << ans+1 << ":\n";
						cout << "Type: " << aux << "\n"; 
						cout << deck[i].toString() << "\n" <<
							deck[j].toString() << "\n" <<
							deck[k].toString() << "\n" <<
							deck[l].toString() << "\n\n";*/
						++ans;
					}
				}
	
	return ans;
}

int main() {
	cout << "\n";
	
	vector<Card> deck;
	
	for( int a=0; a<3; a++ )
		for( int b=0; b<3; b++ )
			for( int c=0; c<3; c++ )
				for( int d=0; d<3; d++ )
					deck.push_back(Card(a, b, c, d));
	
	// Initialize random number generator
	random_device rd;
	mt19937 g(rd());
	
	int iterations = 100, cardsDrawn = 12;
	int sum = 0;
	for( int i=0; i<iterations; i++ ) {
		shuffle(deck.begin(), deck.end(), g);
		
		//vector<Card> vec(deck.begin(), deck.begin()+cardsDrawn);
		// cout << "Cards in deck:\n"; for( Card x:deck ) cout << x.toString() << "\n"; cout << "\n";
		//cout << "Cards drawn:\n"; for( Card x: vec ) { cout << x.toString() << "\n"; } cout << "\n";
		
		int aux = countPlanets(vector<Card>(deck.begin(), deck.begin()+cardsDrawn));
		cout << aux << " planets found \n";
		sum+=aux;
	}
	cout << "In average, " << (float)sum/(float)iterations << " planets were found in 12 cards\n";
	return 0;
}