#include <iostream>
#include <sstream>
#include <string>

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

int main() {
	Card deck[81];
	int cnt = 0;
	for( int a=0; a<3; a++ )
		for( int b=0; b<3; b++ )
			for( int c=0; c<3; c++ )
				for( int d=0; d<3; d++ ) {
					deck[cnt] = Card(a, b, c, d);
					// cout << deck[cnt].toString() << "\n";
					++cnt;
				}
	int a, b;
	while( cin >> a >> b ) {
		Card aux = findSet(deck[a], deck[b]);
		cout << deck[a].toString() << "\n";
		cout << deck[b].toString() << "\n";
		cout << aux.toString() << "\n";
	}
	return 0;
}