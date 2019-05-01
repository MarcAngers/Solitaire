#include "CImg.h"
// #include "D:\CImg_latest\CImg-2.0.0_pre020117\CImg.h" //SCHOOL
// #include "D:\Visual Studio\CImg\CImg-1.7.5\CImg.h" //HOME
// #include "C:\Users\Marc\Documents\Visual Studio 2017\CImg_latest\CImg-2.0.0_pre040717\CImg.h" //LAPTOP

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace cimg_library;
using namespace std;

class card {
public:
	card(int num = 0, char suit = ' ', bool flip = false, bool invis = true) { }

	bool operator== (const card& c) {
		if (this->flip == c.flip && this->invis == c.invis && this->num == c.num && this->suit == c.suit) return true;
		return false;
	}
	card operator-- () { card c; c.num = this->num-1; return c; }
	card operator++ () { card c; c.num = this->num+1; return c; }

	int num;
	char suit;
	bool flip;
	bool invis;
};

unsigned char black[] = { 0,0,0 };
unsigned char white[] = { 255,255,255 };
unsigned char blue[] = { 0,0,255 };
unsigned char green[] = { 50,120,50 };
unsigned char lightgreen[] = { 25,120,25 };

CImg<unsigned char>image(800, 1000, 1, 3);
CImgDisplay display(image, "Hopefullysolitaireatsomepoint");

card findcard(int, int, int);
int findlocation (card, int);

void title();
void solitaire();
void instructions();
void pause();
void endscreen();
void checkformove(int, char);
void checkmove(int, char, int, char);
void move(card, card);
void movestack (int, int, int);
void draw_card(card, int, int);

void draw_club(int, int);
void draw_diamond(int, int);
void draw_spade(int, int);
void draw_heart(int, int);

void draw_none(int, int);
void draw_back(int, int);
void draw_one(char, int, int);
void draw_two(char, int, int);
void draw_three(char, int, int);
void draw_four(char, int, int);
void draw_five(char, int, int);
void draw_six(char, int, int);
void draw_seven(char, int, int);
void draw_eight(char, int, int);
void draw_nine(char, int, int);
void draw_ten(char, int, int);
void draw_jack(char, int, int);
void draw_queen(char, int, int);
void draw_king(char, int, int);
void draw_ace(char, int, int);
void draw_Q(char, int, int);
void draw_W(char, int, int);
void draw_E(char, int, int);
void draw_R(char, int, int);
void draw_T(char, int, int);
void draw_Y(char, int, int);

void deal();
void play();
void refresh();
void init();

card top[4];
card row[8][20];
card deck[24];
card single;

card cards[52];
card temp;

int score = 10000;
int indeck = 23;

int main() {
	title();
}

void solitaire() {

	int counter = 0;
	int checknum = 0;
	char checkchar = ' ';
	int random = rand() % 52;
	int random2 = rand() % 52;

	for (int i = 1; i <= 13; i++) {
		for (int j = 0; j < 4; j++) {
			cards[counter].num = i;
			cards[counter].invis = false;
			if (j == 0) cards[counter].suit = 'C';
			if (j == 1) cards[counter].suit = 'D';
			if (j == 2) cards[counter].suit = 'S';
			if (j == 3) cards[counter].suit = 'H';
			counter++;
		}
	}

	for (int j = 0; j < 8; j++) { for (int i = 0; i < 20; i++) row[j][i].invis = true; }

	counter = 0;

	srand(time(NULL));

	while (counter < 250) {
		random = rand() % 52;
		random2 = rand() % 52;

		temp = cards[random];
		cards[random] = cards[random2];
		cards[random2] = temp;
		counter++;
	}

	counter = 0;

	for (int i = 0; i < 4; i++) { top[i].num = 0; top[i].suit = ' '; }

	for (int i = 0; i < 52; i++) {
		if (i <= 0) row[1][0] = cards[i];
		if (i <= 2 && i > 0) row[2][i - 1] = cards[i];
		if (i <= 5 && i > 2) row[3][i - 3] = cards[i];
		if (i <= 9 && i > 5) row[4][i - 6] = cards[i];
		if (i <= 14 && i > 9) row[5][i - 10] = cards[i];
		if (i <= 20 && i > 14) row[6][i - 15] = cards[i];
		if (i <= 27 && i > 20) row[7][i - 21] = cards[i];
		if (i > 27) deck[i - 28] = cards[i];
	}

	image.draw_rectangle(0, 0, 800, 1000, green);
	image.draw_rectangle(0, 0, 8, 1000, white);
	image.draw_rectangle(0, 0, 800, 8, white);
	image.draw_rectangle(792, 0, 800, 1000, white);
	image.draw_rectangle(0, 992, 800, 1000, white);
	image.draw_text(16, 968, "ESC: PAUSE", black, 0, 1, 24);

	deal();
	play();
}

void title() {
	
	srand(time(NULL));
	int x[10]; 
	for (int i = 0; i < 10; i++) x[i] = (rand() % 176) * 4;
	int y[10];
	for (int i = 0; i < 10; i++) y[i] = (rand() % 218) * 4;

	char randomchar[10];
	int randomvalue[10];
	int randomsuit[10];
	int counter = 0;

	card title[10]; 

	for (int i = 0; i < 10; i++) { title[i].invis = false; title[i].flip = false; }

	for (int i = 0; i < 10; i++) randomvalue[i] = rand() % 13 + 1;

	for (int i = 0; i < 10; i++) { randomsuit[i] = rand() % 4 + 1;
	switch (randomsuit[i]) {
	case 1: randomchar[i] = 'D'; break;
	case 2: randomchar[i] = 'H'; break;
	case 3: randomchar[i] = 'C'; break;
	case 4: randomchar[i] = 'S'; break; } }

	for (int i = 0; i < 10; i++) { title[i].num = randomvalue[i]; title[i].suit = randomchar[i]; }

	while (!display.is_keyP() && !display.is_keyI()) {

	if (counter >= 10) {
		randomvalue[counter%10] = rand() % 13 + 1;
		randomsuit[counter%10] = rand() % 4 + 1;
	switch (randomsuit[counter%10]) {
	case 1: randomchar[counter%10] = 'D'; break;
	case 2: randomchar[counter%10] = 'H'; break;
	case 3: randomchar[counter%10] = 'C'; break;
	case 4: randomchar[counter%10] = 'S'; break; }
		title[counter%10].num = randomvalue[counter%10];
		title[counter%10].suit = randomchar[counter%10];
		x[counter%10] = (rand() % 176) * 4;
		y[counter%10] = (rand() % 168) * 4;
	}

	image.draw_rectangle(0, 0, 800, 1000, green);
	image.draw_rectangle(0, 0, 8, 1000, white);
	image.draw_rectangle(0, 0, 800, 8, white);
	image.draw_rectangle(792, 0, 800, 1000, white);
	image.draw_rectangle(0, 992, 800, 1000, white);

	for (int i = 0; i <= counter && i < 10; i++) draw_card(title[i], x[i], y[i]);

	image.draw_text(100, 100, "SOLITAIRE!", black, 0, 1, 150);
	image.draw_text(350, 300, "P: PLAY", black, 0, 1, 50);
	image.draw_text(300, 400, "I: INSTRUCTIONS", black, 0, 1, 50);

	counter++;

	display.render(image);
	display.paint();
	display.wait(200);
	}

	if (display.is_keyP()) solitaire();
	if (display.is_keyI()) instructions();

}

void instructions() {
	image.draw_rectangle(0, 0, 800, 1000, green);
	image.draw_rectangle(0, 0, 8, 1000, white);
	image.draw_rectangle(0, 0, 800, 8, white);
	image.draw_rectangle(792, 0, 800, 1000, white);
	image.draw_rectangle(0, 992, 800, 1000, white);
	image.draw_text(16, 16, "INSTRUCTIONS:\n\nMOVE CARDS USING THE KEYBOARD,\n\nEACH COLUMN OF CARDS HAS A CORRESPONDING KEY TO IT.\n\nTHE FIRST KEY PRESSED IS THE CARD(S) THAT WILL BE MOVED,\n\nTHE CORRESPONDING KEY WILL TURN WHITE WHEN IT IS PRESSED.\n\nTHE SECOND KEY PRESSED IS WHERE THE CARD WILL BE MOVED TO.\n\nTHE GAME IS WON WHEN THERE ARE 4 FULL STACKS OF CARDS IN THE TOP SPACES.\n\nPOINTS ARE AWARDED BASED ON HOW FAST THE GAME IS COMPLETED,\n\nAND HOW MANY MOVES YOU MAKE.\n\n\n\nHAVE FUN!!!\n\nESC: BACK TO TITLE SCREEN", white, 0, 1, 20);
	display.render(image);
	display.paint();
	while (!display.is_keyESC()) display.wait(25);
	title();
}

void pause() {
	image.draw_rectangle(0, 0, 800, 1000, green);
	image.draw_rectangle(0, 0, 8, 1000, white);
	image.draw_rectangle(0, 0, 800, 8, white);
	image.draw_rectangle(792, 0, 800, 1000, white);
	image.draw_rectangle(0, 992, 800, 1000, white);
	image.draw_text(16, 16, "GAME PAUSED", white, 0, 1, 125);
	image.draw_text(300, 200, "R: RESUME\nQ: QUIT", white, 0, 1, 50);
	display.render(image);
	display.paint();

	while (!display.is_keyR() && !display.is_keyQ()) display.wait(25);
	if (display.is_keyR()) { refresh(); play(); }
	if (display.is_keyQ()) { init(); title(); }
}

void play() {

	display.render(image);
	display.paint();
	display.wait(100);

	int counter = 0;
	int checknum = 0;
	char checkchar = ' ';

	while (counter == 0) {

		checknum = 0;
		checkchar = ' ';
		card playtemp;

		score--;

		if (display.is_keyD() && top[0].num == 13 && top[1].num == 13 && top[2].num == 13 && top[3].num == 13) endscreen();
		if (display.is_keyQ()) { draw_Q('W', 50, 160); checkchar = 'Q'; checkformove(checknum, checkchar); }
		if (display.is_keyW()) { draw_W('W', 162, 160); checkchar = 'W'; checkformove(checknum, checkchar); }
		if (display.is_keyE()) { draw_E('W', 274, 160); checkchar = 'E'; checkformove(checknum, checkchar); }
		if (display.is_keyR()) { draw_R('W', 386, 160); checkchar = 'R'; checkformove(checknum, checkchar); }
		if (display.is_keyT()) { draw_T('W', 562, 160); checkchar = 'T'; checkformove(checknum, checkchar); }
		if (display.is_key1()) { draw_one('W', 50, 212); checknum = 1; checkformove(checknum, checkchar); }
		if (display.is_key2()) { draw_two('W', 162, 212); checknum = 2; checkformove(checknum, checkchar); }
		if (display.is_key3()) { draw_three('W', 274, 212); checknum = 3; checkformove(checknum, checkchar); }
		if (display.is_key4()) { draw_four('W', 386, 212); checknum = 4; checkformove(checknum, checkchar); }
		if (display.is_key5()) { draw_five('W', 498, 212); checknum = 5; checkformove(checknum, checkchar); }
		if (display.is_key6()) { draw_six('W', 610, 212); checknum = 6; checkformove(checknum, checkchar); }
		if (display.is_key7()) { draw_seven('W', 722, 212); checknum = 7; checkformove(checknum, checkchar); }
		if (display.is_keyESC()) pause();

		if (display.is_keyY()) {
			draw_Y('W', 722, 160);
			display.render(image);
			display.paint();
			display.wait(50);
			draw_Y('B', 722, 160);

			playtemp = single;
			playtemp.flip = true;
			single = deck[indeck];
			single.flip = false;
			for (int i = indeck; i > 0; i--) deck[i] = deck[i - 1];
			deck[0] = playtemp;

			refresh();
		}

		if (top[0].num == 13 && top[1].num == 13 && top[2].num == 13 && top[3].num == 13) endscreen();

		display.render(image);
		display.paint();
		display.wait(50);
	}
}

void checkformove(int num, char cha) {

	display.render(image);
	display.paint();
	display.wait();

	while (!display.is_keyQ() && !display.is_keyW() && !display.is_keyE() && !display.is_keyR() && !display.is_keyT() && !display.is_key1() && !display.is_key2() && !display.is_key3() && !display.is_key4() && !display.is_key5() && !display.is_key6() && !display.is_key7()) {
		display.wait(50);
	}
	if (display.is_keyQ() && cha != 'Q') { draw_Q('W', 50, 160); checkmove(num, cha, 0, 'Q'); }
	else if (display.is_keyQ() && cha == 'Q') { draw_Q('B', 50, 160); refresh(); play(); }
	if (display.is_keyW() && cha != 'W') { draw_W('W', 162, 160); checkmove(num, cha, 0, 'W'); }
	else if (display.is_keyW() && cha == 'W') { draw_W('B', 162, 160); refresh(); play(); }
	if (display.is_keyE() && cha != 'E') { draw_E('W', 274, 160); checkmove(num, cha, 0, 'E'); }
	else if (display.is_keyE() && cha == 'E') { draw_E('B', 274, 160); refresh(); play(); }
	if (display.is_keyR() && cha != 'R') { draw_R('W', 386, 160); checkmove(num, cha, 0, 'R'); }
	else if (display.is_keyR() && cha == 'R') { draw_R('B', 386, 160); refresh(); play(); }
	if (display.is_keyT() && cha == 'T') { draw_T('B', 562, 160); refresh(); play(); }
	if (display.is_key1() && num != 1) { draw_one('W', 50, 212); checkmove(num, cha, 1, ' '); }
	else if (display.is_key1() && num == 1) { draw_one('B', 50, 212); refresh(); play(); }
	if (display.is_key2() && num != 2) { draw_two('W', 162, 212); checkmove(num, cha, 2, ' '); }
	else if (display.is_key2() && num == 2) { draw_two('B', 162, 212); refresh(); play(); }
	if (display.is_key3() && num != 3) { draw_three('W', 274, 212); checkmove(num, cha, 3, ' '); }
	else if (display.is_key3() && num == 3) { draw_three('B', 274, 212); refresh(); play(); }
	if (display.is_key4() && num != 4) { draw_four('W', 386, 212); checkmove(num, cha, 4, ' '); }
	else if (display.is_key4() && num == 4) { draw_four('B', 386, 212); refresh(); play(); }
	if (display.is_key5() && num != 5) { draw_five('W', 498, 212); checkmove(num, cha, 5, ' '); }
	else if (display.is_key5() && num == 5) { draw_five('B', 498, 212); refresh(); play(); }
	if (display.is_key6() && num != 6) { draw_six('W', 610, 212); checkmove(num, cha, 6, ' '); }
	else if (display.is_key6() && num == 6) { draw_six('B', 610, 212); refresh(); play(); }
	if (display.is_key7() && num != 7) { draw_seven('W', 722, 212); checkmove(num, cha, 7, ' '); }
	else if (display.is_key7() && num == 7) { draw_seven('B', 722, 212); refresh(); play(); }
}

void checkmove(int x1, char c1, int x2, char c2) {

	card one;
	card two;
	bool moved = false;

	if (c1 == ' ') { one = findcard(x1, 1, 0); }
	else {
		switch (c1) {
		case 'Q': one = top[0]; break;
		case 'W': one = top[1]; break;
		case 'E': one = top[2]; break;
		case 'R': one = top[3]; break;
		case 'T': one = single; break;
		} }

	if (c2 == ' ') { two = findcard(x2, 1, 0); }
	else {
		switch (c2) {
		case 'Q': two = top[0]; break;
		case 'W': two = top[1]; break;
		case 'E': two = top[2]; break;
		case 'R': two = top[3]; break;
		} }

	display.is_keySPACE();
	refresh();

	if (c2 == 'Q' || c2 == 'W' || c2 == 'E' || c2 == 'R') {
		if ((one.num == two.num + 1 && one.suit == two.suit) || (two.num == 0 && one.num == 1)) { moved = true; move(one, two); }
	}
	if (x2 == 1 || x2 == 2 || x2 == 3 || x2 == 4 || x2 == 5 || x2 == 6 || x2 == 7) {
		if (one.num == (two.num - 1)) {
			switch (one.suit) {
			case 'D': if (two.suit == 'C' || two.suit == 'S' && two.num != 0) { moved = true; move(one, two); } break;
			case 'H': if (two.suit == 'C' || two.suit == 'S' && two.num != 0) { moved = true; move(one, two); } break;
			case 'C': if (two.suit == 'D' || two.suit == 'H' && two.num != 0) { moved = true; move(one, two); } break;
			case 'S': if (two.suit == 'D' || two.suit == 'H' && two.num != 0) { moved = true; move(one, two); } break;
			}
		}
	}
	if (two.num == 0 && c2 == ' ' && one.num == 13) { moved = true; move(one, two); }

	if (moved == false && c1 == ' ' && c2 == ' ') movestack(x1, x2, 0);

	play();

}

card findcard(int x, int mode, int number) {
	bool done;
	done = false;

	if (mode == 1) { for (int i = 0; i < 20; i++) { if (row[x][i].invis == true && done == false) { done = true; return row[x][i - 1]; } } } 
	
	else if (mode == 2) {
		while (number >= 0) {
			for (int i = 0; i < 20; i++) { if (row[x][i].invis == false && row[x][i].flip == false && done == false && number == 0) { done = true; return row[x][i]; } } 
		number--; }
	}
	else return deck[0];
}

void move(card one, card two) {

	bool done = false;

	if (one.num == top[0].num && one.suit == top[0].suit && done == false) { top[0].num--; done = true; }
	if (one.num == top[1].num && one.suit == top[1].suit && done == false) { top[1].num--; done = true; }
	if (one.num == top[2].num && one.suit == top[2].suit && done == false) { top[2].num--; done = true; }
	if (one.num == top[3].num && one.suit == top[3].suit && done == false) { top[3].num--; done = true; }

	if (one.num == single.num && one.suit == single.suit && done == false) { single = deck[0]; single.flip = false; for (int i = 0; i < indeck; i++) { deck[i] = deck[i + 1]; } indeck--; done = true; }

	for (int j = 1; j < 8; j++) { for (int i = 0; i < 20; i++) { if (one == row[j][i] && row[j][i].flip == false && done == false) { if (i == 1 && j == 2) { row[j][0].flip = false; row[j][1].invis = true; row[j][1].num = 14; done = true; } else if (i == 0) { row[j][0].num = 0; row[j][0].suit = ' '; done = true; } else { row[j][i - 1].flip = false; row[j][i].invis = true; row[j][i].num = 14; done = true; } } } }
	
	done = false;

	if (two.num == top[0].num && two.suit == top[0].suit && one.num == two.num + 1 && done == false) { top[0].num = one.num; top[0].suit = one.suit; done = true; }
	if (two.num == top[1].num && two.suit == top[1].suit && one.num == two.num + 1 && done == false) { top[1].num = one.num; top[1].suit = one.suit; done = true; }
	if (two.num == top[2].num && two.suit == top[2].suit && one.num == two.num + 1 && done == false) { top[2].num = one.num; top[2].suit = one.suit; done = true; }
	if (two.num == top[3].num && two.suit == top[3].suit && one.num == two.num + 1 && done == false) { top[3].num = one.num; top[3].suit = one.suit; done = true; }

	for (int j = 1; j < 8; j++) { for (int i = 0; i < 20; i++) { if (two == row[j][i] && row[j][i].flip == false && done == false) { if (i == 0 && row[j][0].num == 0) { row[j][0].num = one.num; row[j][0].suit = one.suit; done = true; } else { row[j][i + 1].num = one.num; row[j][i + 1].suit = one.suit; row[j][i + 1].invis = false; done = true; } } } }
	
	score += 5;

	display.wait(50);
	refresh();
}

void movestack (int x1, int x2, int number) {

	card one, two;
	
	if (number >= 21) {
		refresh();
		play();
	}

	one = findcard(x1, 2, number);
	two = findcard(x2, 1, 0);

	char colo = ' ', colt = ' ';
	char o = one.suit;
	char t = two.suit;
	int numo = one.num;
	int numt = two.num - 1;
	int a = 1;

	if (o == 'C' || o == 'S') colo = 'B';
	if (o == 'D' || o == 'H') colo = 'R';
	if (t == 'C' || t == 'S') colt = 'B';
	if (t == 'D' || t == 'H') colt = 'R';

	if ((numo == numt || (numt+1 == 0 && numo == 13)) && colo != colt) { display.wait(10); }
		else movestack (x1, x2, number + 1);

	int onelocation = findlocation(one, x1);
	int twolocation = findlocation(two, x2);

	if (twolocation == 0 && two.suit == ' ') a = 0;

	for (int i = twolocation + a; i < 20; i++) row[x2][i] = row[x1][i + onelocation - twolocation - a];
	for (int i = 0; i < 20; i++) if (row[x2][i].invis == true) twolocation = i+1;
	for (int i = twolocation; i < 20; i++) { row[x2][i].num = 14; row[x2][i].suit = ' '; row[x2][i].invis = true; }
	
	if (onelocation == 0) { row[x1][0].flip = false; row[x1][0].suit = ' '; row[x1][0].num = 0; }
	else row[x1][onelocation - 1].flip = false;

	for (int i = onelocation; i < 20; i++) { row[x1][i].invis = true; row[x1][i].num = 14; row[x1][i].suit = ' '; }
	if (onelocation == 0) { row[x1][0].num = 0; row[x1][0].invis = false; }

	score += 5;

	refresh();
}

int findlocation(card one, int column) {
	bool done = false;
	for (int i = 0; i < 20; i++) { if (row[column][i] == one && done == false) { done = true; return i; } } 
}

void draw_card(card x, int x1, int y1) {
	if (x.invis == false) {
		image.draw_rectangle(x1, y1, x1 + 96, y1 + 128, white);

		switch (x.num) {
		case 0: draw_none(x1, y1);
			break;
		case 1: draw_ace(x.suit, x1 + 4, y1 + 4);
			break;
		case 2: draw_two(x.suit, x1 + 4, y1 + 4);
			break;
		case 3: draw_three(x.suit, x1 + 4, y1 + 4);
			break;
		case 4: draw_four(x.suit, x1 + 4, y1 + 4);
			break;
		case 5: draw_five(x.suit, x1 + 4, y1 + 4);
			break;
		case 6: draw_six(x.suit, x1 + 4, y1 + 4);
			break;
		case 7: draw_seven(x.suit, x1 + 4, y1 + 4);
			break;
		case 8: draw_eight(x.suit, x1 + 4, y1 + 4);
			break;
		case 9: draw_nine(x.suit, x1 + 4, y1 + 4);
			break;
		case 10: draw_ten(x.suit, x1 + 4, y1 + 4);
			break;
		case 11: draw_jack(x.suit, x1 + 4, y1 + 4);
			break;
		case 12: draw_queen(x.suit, x1 + 4, y1 + 4);
			break;
		case 13: draw_king(x.suit, x1 + 4, y1 + 4);
			break;
		}

		switch (x.suit) {
		case 'C': draw_club(x1, y1);
			break;
		case 'D': draw_diamond(x1, y1);
			break;
		case 'S': draw_spade(x1, y1);
			break;
		case 'H': draw_heart(x1, y1);
			break;
		}

		if (x.flip == true) draw_back(x1, y1);
	}
}

void draw_none(int x, int y) {
	unsigned char lightgreen[] = { 127,255,0 };

	image.draw_rectangle(x, y, x + 96, y + 128, lightgreen);
}

void draw_back(int x, int y) {
	unsigned char white[] = { 255,255,255 };
	unsigned char blue[] = { 0,162,232 };

	image.draw_rectangle(x, y, x + 96, y + 128, white);
	image.draw_rectangle(x + 8, y + 8, x + 88, y + 120, blue);
}

void draw_zero(char color, int x, int y) {

	unsigned char colour[] = { 0,0,0 };
	if (color == 'W') { colour[0] = 255; colour[1] = 255; colour[2] = 255; }

	image.draw_rectangle(x, y, x + 4, y + 28, colour);
	image.draw_rectangle(x + 4, y, x + 16, y + 4, colour);
	image.draw_rectangle(x + 4, y + 24, x + 16, y + 28, colour);
	image.draw_rectangle(x + 16, y, x + 20, y + 28, colour);

}

void draw_one(char color, int x, int y) {

	unsigned char colour[] = { 0,0,0 };
	if (color == 'D' || color == 'H') colour[0] = 255;
	if (color == 'W') { colour[0] = 255; colour[1] = 255; colour[2] = 255; }

	image.draw_rectangle(x + 8, y, x + 12, y + 28, colour);
	image.draw_rectangle(x + 4, y + 4, x + 8, y + 8, colour);
	image.draw_rectangle(x + 4, y + 24, x + 8, y + 28, colour);
	image.draw_rectangle(x + 12, y + 24, x + 16, y + 28, colour);
}

void draw_two(char color, int x, int y) {

	unsigned char colour[] = { 0,0,0 };
	if (color == 'D' || color == 'H') colour[0] = 255;
	if (color == 'W') { colour[0] = 255; colour[1] = 255; colour[2] = 255; }

	image.draw_rectangle(x, y + 4, x + 4, y + 8, colour);
	image.draw_rectangle(x + 4, y, x + 16, y + 4, colour);
	image.draw_rectangle(x + 16, y + 4, x + 20, y + 12, colour);
	image.draw_rectangle(x + 8, y + 12, x + 16, y + 16, colour);
	image.draw_rectangle(x + 4, y + 16, x + 8, y + 20, colour);
	image.draw_rectangle(x, y + 20, x + 4, y + 24, colour);
	image.draw_rectangle(x, y + 24, x + 20, y + 28, colour);
}

void draw_three(char color, int x, int y) {

	unsigned char colour[] = { 0,0,0 };
	if (color == 'D' || color == 'H') colour[0] = 255;
	if (color == 'W') { colour[0] = 255; colour[1] = 255; colour[2] = 255; }

	image.draw_rectangle(x, y + 4, x + 4, y + 8, colour);
	image.draw_rectangle(x + 4, y, x + 16, y + 4, colour);
	image.draw_rectangle(x + 16, y + 4, x + 20, y + 12, colour);
	image.draw_rectangle(x + 8, y + 12, x + 16, y + 16, colour);
	image.draw_rectangle(x + 16, y + 16, x + 20, y + 24, colour);
	image.draw_rectangle(x + 4, y + 24, x + 16, y + 28, colour);
	image.draw_rectangle(x, y + 20, x + 4, y + 24, colour);
}

void draw_four(char color, int x, int y) {

	unsigned char colour[] = { 0,0,0 };
	if (color == 'D' || color == 'H') colour[0] = 255;
	if (color == 'W') { colour[0] = 255; colour[1] = 255; colour[2] = 255; }

	image.draw_rectangle(x, y, x + 4, y + 16, colour);
	image.draw_rectangle(x + 12, y, x + 16, y + 28, colour);
	image.draw_rectangle(x + 4, y + 16, x + 20, y + 20, colour);
}

void draw_five(char color, int x, int y) {

	unsigned char colour[] = { 0,0,0 };
	if (color == 'D' || color == 'H') colour[0] = 255;
	if (color == 'W') { colour[0] = 255; colour[1] = 255; colour[2] = 255; }

	image.draw_rectangle(x + 4, y, x + 20, y + 4, colour);
	image.draw_rectangle(x, y, x + 4, y + 8, colour);
	image.draw_rectangle(x, y + 8, x + 16, y + 12, colour);
	image.draw_rectangle(x + 16, y + 12, x + 20, y + 24, colour);
	image.draw_rectangle(x + 4, y + 24, x + 16, y + 28, colour);
	image.draw_rectangle(x, y + 20, x + 4, y + 24, colour);
}

void draw_six(char color, int x, int y) {

	unsigned char colour[] = { 0,0,0 };
	if (color == 'D' || color == 'H') colour[0] = 255;
	if (color == 'W') { colour[0] = 255; colour[1] = 255; colour[2] = 255; }

	image.draw_rectangle(x + 8, y, x + 20, y + 4, colour);
	image.draw_rectangle(x + 4, y + 4, x + 8, y + 8, colour);
	image.draw_rectangle(x, y + 8, x + 4, y + 24, colour);
	image.draw_rectangle(x + 4, y + 12, x + 16, y + 16, colour);
	image.draw_rectangle(x + 16, y + 16, x + 20, y + 24, colour);
	image.draw_rectangle(x + 4, y + 24, x + 16, y + 28, colour);
}

void draw_seven(char color, int x, int y) {

	unsigned char colour[] = { 0,0,0 };
	if (color == 'D' || color == 'H') colour[0] = 255;
	if (color == 'W') { colour[0] = 255; colour[1] = 255; colour[2] = 255; }

	image.draw_rectangle(x, y, x + 16, y + 4, colour);
	image.draw_rectangle(x + 16, y, x + 20, y + 12, colour);
	image.draw_rectangle(x + 8, y + 12, x + 16, y + 16, colour);
	image.draw_rectangle(x + 4, y + 16, x + 8, y + 20, colour);
	image.draw_rectangle(x, y + 20, x + 4, y + 28, colour);
}

void draw_eight(char color, int x, int y) {

	unsigned char colour[] = { 0,0,0 };
	if (color == 'D' || color == 'H') colour[0] = 255;
	if (color == 'W') { colour[0] = 255; colour[1] = 255; colour[2] = 255; }

	image.draw_rectangle(x + 4, y, x + 16, y + 4, colour);
	image.draw_rectangle(x, y + 4, x + 4, y + 12, colour);
	image.draw_rectangle(x + 16, y + 4, x + 20, y + 12, colour);
	image.draw_rectangle(x + 4, y + 12, x + 16, y + 16, colour);
	image.draw_rectangle(x, y + 16, x + 4, y + 24, colour);
	image.draw_rectangle(x + 16, y + 16, x + 20, y + 24, colour);
	image.draw_rectangle(x + 4, y + 24, x + 16, y + 28, colour);
}

void draw_nine(char color, int x, int y) {

	unsigned char colour[] = { 0,0,0 };
	if (color == 'D' || color == 'H') colour[0] = 255;
	if (color == 'W') { colour[0] = 255; colour[1] = 255; colour[2] = 255; }

	image.draw_rectangle(x + 4, y, x + 16, y + 4, colour);
	image.draw_rectangle(x, y + 4, x + 4, y + 12, colour);
	image.draw_rectangle(x + 16, y + 4, x + 20, y + 20, colour);
	image.draw_rectangle(x + 4, y + 12, x + 16, y + 16, colour);
	image.draw_rectangle(x + 12, y + 20, x + 16, y + 24, colour);
	image.draw_rectangle(x + 4, y + 24, x + 12, y + 28, colour);
}

void draw_ten(char color, int x, int y) {

	unsigned char colour[] = { 0,0,0 };
	if (color == 'D' || color == 'H') colour[0] = 255;

	image.draw_rectangle(x, y, x + 4, y + 28, colour);
	image.draw_rectangle(x + 8, y, x + 20, y + 28, colour);
	image.draw_rectangle(x + 12, y + 4, x + 16, y + 24, white);
}

void draw_jack(char color, int x, int y) {

	unsigned char colour[] = { 0,0,0 };
	if (color == 'D' || color == 'H') colour[0] = 255;

	image.draw_rectangle(x, y, x + 20, y + 4, colour);
	image.draw_rectangle(x + 12, y + 4, x + 16, y + 24, colour);
	image.draw_rectangle(x + 4, y + 24, x + 12, y + 28, colour);
	image.draw_rectangle(x, y + 20, x + 4, y + 24, colour);
}

void draw_queen(char color, int x, int y) {

	unsigned char colour[] = { 0,0,0 };
	if (color == 'D' || color == 'H') colour[0] = 255;
	if (color == 'W') { colour[0] = 255; colour[1] = 255; colour[2] = 255; }

	image.draw_rectangle(x, y, x + 20, y + 28, colour);
	image.draw_rectangle(x + 4, y + 4, x + 16, y + 24, white);
	image.draw_rectangle(x + 12, y + 20, x + 16, y + 24, colour);
}

void draw_king(char color, int x, int y) {

	unsigned char colour[] = { 0,0,0 };
	if (color == 'D' || color == 'H') colour[0] = 255;

	image.draw_rectangle(x, y, x + 4, y + 28, colour);
	image.draw_rectangle(x + 4, y + 12, x + 8, y + 16, colour);
	image.draw_rectangle(x + 8, y + 8, x + 12, y + 12, colour);
	image.draw_rectangle(x + 12, y + 4, x + 16, y + 8, colour);
	image.draw_rectangle(x + 16, y, x + 20, y + 4, colour);
	image.draw_rectangle(x + 8, y + 16, x + 12, y + 20, colour);
	image.draw_rectangle(x + 12, y + 20, x + 16, y + 24, colour);
	image.draw_rectangle(x + 16, y + 24, x + 20, y + 28, colour);
}

void draw_ace(char color, int x, int y) {

	unsigned char colour[] = { 0,0,0 };
	if (color == 'D' || color == 'H') colour[0] = 255;

	image.draw_rectangle(x, y, x + 4, y + 28, colour);
	image.draw_rectangle(x + 4, y, x + 16, y + 4, colour);
	image.draw_rectangle(x + 4, y + 16, x + 16, y + 20, colour);
	image.draw_rectangle(x + 16, y, x + 20, y + 28, colour);
}

void draw_Q(char color, int x, int y) {

	unsigned char colour[] = { 0,0,0 };
	if (color == 'W') { colour[0] = 255; colour[1] = 255; colour[2] = 255; }

	image.draw_rectangle(x, y, x + 4, y + 28, colour);
	image.draw_rectangle(x + 4, y, x + 16, y + 4, colour);
	image.draw_rectangle(x + 4, y + 24, x + 16, y + 28, colour);
	image.draw_rectangle(x + 16, y, x + 20, y + 28, colour);
	image.draw_rectangle(x + 12, y + 20, x + 16, y + 24, colour);

}

void draw_W(char color, int x, int y) {

	unsigned char colour[] = { 0,0,0 };
	if (color == 'W') { colour[0] = 255; colour[1] = 255; colour[2] = 255; }

	image.draw_rectangle(x, y, x + 4, y + 24, colour);
	image.draw_rectangle(x + 4, y + 24, x + 8, y + 28, colour);
	image.draw_rectangle(x + 8, y + 12, x + 12, y + 24, colour);
	image.draw_rectangle(x + 12, y + 24, x + 16, y + 28, colour);
	image.draw_rectangle(x + 16, y, x + 20, y + 24, colour);
}

void draw_E(char color, int x, int y) {

	unsigned char colour[] = { 0,0,0 };
	if (color == 'W') { colour[0] = 255; colour[1] = 255; colour[2] = 255; }

	image.draw_rectangle(x, y + 4, x + 4, y + 24, colour);
	image.draw_rectangle(x + 4, y, x + 20, y + 4, colour);
	image.draw_rectangle(x + 4, y + 12, x + 12, y + 16, colour);
	image.draw_rectangle(x + 4, y + 24, x + 20, y + 28, colour);
}

void draw_R(char color, int x, int y) {

	unsigned char colour[] = { 0,0,0 };
	if (color == 'W') { colour[0] = 255; colour[1] = 255; colour[2] = 255; }

	image.draw_rectangle(x, y, x + 4, y + 28, colour);
	image.draw_rectangle(x + 4, y, x + 16, y + 4, colour);
	image.draw_rectangle(x + 16, y + 4, x + 20, y + 12, colour);
	image.draw_rectangle(x + 4, y + 12, x + 16, y + 16, colour);
	image.draw_rectangle(x + 4, y + 16, x + 8, y + 20, colour);
	image.draw_rectangle(x + 8, y + 20, x + 16, y + 24, colour);
	image.draw_rectangle(x + 16, y + 24, x + 20, y + 28, colour);
}

void draw_T(char color, int x, int y) {

	unsigned char colour[] = { 0,0,0 };
	if (color == 'W') { colour[0] = 255; colour[1] = 255; colour[2] = 255; }

	image.draw_rectangle(x, y, x + 20, y + 4, colour);
	image.draw_rectangle(x + 8, y + 4, x + 12, y + 28, colour);
}

void draw_Y(char color, int x, int y) {

	unsigned char colour[] = { 0,0,0 };
	if (color == 'W') { colour[0] = 255; colour[1] = 255; colour[2] = 255; }

	image.draw_rectangle(x, y, x + 4, y + 8, colour);
	image.draw_rectangle(x + 16, y, x + 20, y + 8, colour);
	image.draw_rectangle(x + 4, y + 8, x + 8, y + 16, colour);
	image.draw_rectangle(x + 12, y + 8, x + 16, y + 16, colour);
	image.draw_rectangle(x + 8, y + 16, x + 12, y + 28, colour);
}

void draw_club(int x, int y) {

	unsigned char black[] = { 0,0,0 };
	unsigned char gray[] = { 127,127,127 };

	image.draw_rectangle(x + 40, y + 20, x + 56, y + 24, black);
	image.draw_rectangle(x + 36, y + 24, x + 60, y + 28, black);
	image.draw_rectangle(x + 32, y + 28, x + 64, y + 36, black);
	image.draw_rectangle(x + 28, y + 36, x + 68, y + 44, black);
	image.draw_rectangle(x + 32, y + 44, x + 64, y + 48, black);
	image.draw_rectangle(x + 36, y + 48, x + 60, y + 52, black);
	image.draw_rectangle(x + 40, y + 52, x + 56, y + 60, black);
	image.draw_rectangle(x + 20, y + 52, x + 32, y + 56, black);
	image.draw_rectangle(x + 64, y + 52, x + 76, y + 56, black);
	image.draw_rectangle(x + 12, y + 56, x + 36, y + 60, black);
	image.draw_rectangle(x + 60, y + 56, x + 84, y + 60, black);
	image.draw_rectangle(x + 8, y + 60, x + 88, y + 80, black);
	image.draw_rectangle(x + 40, y + 80, x + 56, y + 96, black);
	image.draw_rectangle(x + 12, y + 80, x + 36, y + 84, black);
	image.draw_rectangle(x + 60, y + 80, x + 84, y + 84, black);
	image.draw_rectangle(x + 20, y + 84, x + 32, y + 88, black);
	image.draw_rectangle(x + 64, y + 84, x + 76, y + 88, black);
	image.draw_rectangle(x + 32, y + 96, x + 64, y + 100, black);
	image.draw_rectangle(x + 24, y + 100, x + 72, y + 104, black);
	image.draw_rectangle(x + 16, y + 104, x + 80, y + 108, black);
	image.draw_rectangle(x + 44, y + 24, x + 48, y + 28, gray);
	image.draw_rectangle(x + 40, y + 28, x + 44, y + 32, gray);
	image.draw_rectangle(x + 36, y + 32, x + 40, y + 36, gray);
	image.draw_rectangle(x + 32, y + 36, x + 36, y + 44, gray);
	image.draw_rectangle(x + 16, y + 64, x + 24, y + 68, gray);
	image.draw_rectangle(x + 12, y + 68, x + 16, y + 76, gray);
	image.draw_rectangle(x + 64, y + 64, x + 72, y + 68, gray);
	image.draw_rectangle(x + 60, y + 68, x + 64, y + 76, gray);
}

void draw_spade(int x, int y) {

	unsigned char black[] = { 0,0,0 };
	unsigned char gray[] = { 127,127,127 };

	image.draw_rectangle(x + 44, y + 24, x + 52, y + 28, black);
	image.draw_rectangle(x + 40, y + 28, x + 56, y + 32, black);
	image.draw_rectangle(x + 36, y + 32, x + 60, y + 36, black);
	image.draw_rectangle(x + 32, y + 36, x + 64, y + 40, black);
	image.draw_rectangle(x + 28, y + 40, x + 68, y + 44, black);
	image.draw_rectangle(x + 24, y + 44, x + 72, y + 48, black);
	image.draw_rectangle(x + 20, y + 48, x + 76, y + 52, black);
	image.draw_rectangle(x + 16, y + 52, x + 80, y + 56, black);
	image.draw_rectangle(x + 12, y + 56, x + 84, y + 60, black);
	image.draw_rectangle(x + 8, y + 60, x + 88, y + 68, black);
	image.draw_rectangle(x + 4, y + 68, x + 92, y + 88, black);
	image.draw_rectangle(x + 8, y + 88, x + 88, y + 92, black);
	image.draw_rectangle(x + 12, y + 92, x + 36, y + 96, black);
	image.draw_rectangle(x + 60, y + 92, x + 84, y + 96, black);
	image.draw_rectangle(x + 16, y + 96, x + 28, y + 100, black);
	image.draw_rectangle(x + 68, y + 96, x + 80, y + 100, black);
	image.draw_rectangle(x + 40, y + 92, x + 56, y + 100, black);
	image.draw_rectangle(x + 36, y + 100, x + 60, y + 104, black);
	image.draw_rectangle(x + 28, y + 104, x + 68, y + 108, black);
	image.draw_rectangle(x + 20, y + 108, x + 76, y + 112, black);
	image.draw_rectangle(x + 44, y + 36, x + 48, y + 40, gray);
	image.draw_rectangle(x + 40, y + 40, x + 44, y + 44, gray);
	image.draw_rectangle(x + 36, y + 44, x + 40, y + 48, gray);
	image.draw_rectangle(x + 32, y + 48, x + 36, y + 52, gray);
	image.draw_rectangle(x + 28, y + 52, x + 32, y + 56, gray);
	image.draw_rectangle(x + 24, y + 56, x + 28, y + 60, gray);
	image.draw_rectangle(x + 20, y + 60, x + 24, y + 64, gray);
	image.draw_rectangle(x + 16, y + 64, x + 20, y + 72, gray);
	image.draw_rectangle(x + 12, y + 72, x + 16, y + 80, gray);
}

void draw_diamond(int x, int y) {

	unsigned char black[] = { 0,0,0 };
	unsigned char red[] = { 255,0,0 };
	unsigned char pink[] = { 255,174,201 };
	unsigned char darkred[] = { 200,0,0 };

	image.draw_rectangle(x + 44, y + 32, x + 52, y + 40, black);
	image.draw_rectangle(x + 40, y + 40, x + 56, y + 48, black);
	image.draw_rectangle(x + 44, y + 40, x + 52, y + 48, red);
	image.draw_rectangle(x + 36, y + 48, x + 60, y + 56, black);
	image.draw_rectangle(x + 40, y + 48, x + 44, y + 56, pink);
	image.draw_rectangle(x + 44, y + 48, x + 56, y + 56, red);
	image.draw_rectangle(x + 32, y + 56, x + 64, y + 60, black);
	image.draw_rectangle(x + 36, y + 56, x + 40, y + 60, pink);
	image.draw_rectangle(x + 40, y + 56, x + 60, y + 60, red);
	image.draw_rectangle(x + 24, y + 60, x + 72, y + 64, black);
	image.draw_rectangle(x + 32, y + 60, x + 36, y + 64, pink);
	image.draw_rectangle(x + 36, y + 60, x + 64, y + 64, red);
	image.draw_rectangle(x + 16, y + 64, x + 80, y + 68, black);
	image.draw_rectangle(x + 24, y + 64, x + 32, y + 68, pink);
	image.draw_rectangle(x + 32, y + 64, x + 72, y + 68, red);
	image.draw_rectangle(x + 8, y + 68, x + 88, y + 76, black);
	image.draw_rectangle(x + 16, y + 68, x + 80, y + 76, red);
	image.draw_rectangle(x + 72, y + 72, x + 80, y + 76, darkred);
	image.draw_rectangle(x + 16, y + 76, x + 80, y + 80, black);
	image.draw_rectangle(x + 24, y + 76, x + 72, y + 80, red);
	image.draw_rectangle(x + 64, y + 76, x + 72, y + 80, darkred);
	image.draw_rectangle(x + 24, y + 80, x + 72, y + 84, black);
	image.draw_rectangle(x + 32, y + 80, x + 64, y + 84, red);
	image.draw_rectangle(x + 60, y + 80, x + 64, y + 84, darkred);
	image.draw_rectangle(x + 32, y + 84, x + 64, y + 88, black);
	image.draw_rectangle(x + 36, y + 84, x + 60, y + 88, red);
	image.draw_rectangle(x + 56, y + 84, x + 60, y + 88, darkred);
	image.draw_rectangle(x + 36, y + 88, x + 60, y + 96, black);
	image.draw_rectangle(x + 40, y + 88, x + 56, y + 96, red);
	image.draw_rectangle(x + 52, y + 88, x + 56, y + 96, darkred);
	image.draw_rectangle(x + 40, y + 96, x + 56, y + 104, black);
	image.draw_rectangle(x + 44, y + 96, x + 52, y + 104, red);
	image.draw_rectangle(x + 48, y + 96, x + 52, y + 104, darkred);
	image.draw_rectangle(x + 44, y + 104, x + 52, y + 112, black);

}

void draw_heart(int x, int y) {

	unsigned char black[] = { 0,0,0 };
	unsigned char red[] = { 255,0,0 };
	unsigned char pink[] = { 255,174,201 };
	unsigned char darkred[] = { 127,0,0 };

	image.draw_rectangle(x + 20, y + 36, x + 36, y + 40, black);
	image.draw_rectangle(x + 60, y + 36, x + 76, y + 40, black);
	image.draw_rectangle(x + 16, y + 40, x + 44, y + 44, black);
	image.draw_rectangle(x + 20, y + 40, x + 36, y + 44, red);
	image.draw_rectangle(x + 52, y + 40, x + 80, y + 44, black);
	image.draw_rectangle(x + 60, y + 40, x + 76, y + 44, red);
	image.draw_rectangle(x + 12, y + 44, x + 84, y + 52, black);
	image.draw_rectangle(x + 16, y + 44, x + 44, y + 52, red);
	image.draw_rectangle(x + 52, y + 44, x + 80, y + 52, red);
	image.draw_rectangle(x + 24, y + 44, x + 32, y + 48, pink);
	image.draw_rectangle(x + 20, y + 48, x + 24, y + 52, pink);
	image.draw_rectangle(x + 8, y + 52, x + 88, y + 68, black);
	image.draw_rectangle(x + 12, y + 52, x + 84, y + 68, red);
	image.draw_rectangle(x + 16, y + 52, x + 20, y + 64, pink);
	image.draw_rectangle(x + 12, y + 68, x + 84, y + 76, black);
	image.draw_rectangle(x + 16, y + 68, x + 80, y + 76, red);
	image.draw_rectangle(x + 76, y + 72, x + 80, y + 76, darkred);
	image.draw_rectangle(x + 16, y + 76, x + 80, y + 84, black);
	image.draw_rectangle(x + 20, y + 76, x + 76, y + 84, red);
	image.draw_rectangle(x + 72, y + 76, x + 76, y + 84, darkred);
	image.draw_rectangle(x + 20, y + 84, x + 76, y + 88, black);
	image.draw_rectangle(x + 24, y + 84, x + 72, y + 88, red);
	image.draw_rectangle(x + 68, y + 84, x + 72, y + 88, darkred);
	image.draw_rectangle(x + 24, y + 88, x + 72, y + 92, black);
	image.draw_rectangle(x + 28, y + 88, x + 68, y + 92, red);
	image.draw_rectangle(x + 64, y + 88, x + 68, y + 92, darkred);
	image.draw_rectangle(x + 28, y + 92, x + 68, y + 96, black);
	image.draw_rectangle(x + 32, y + 92, x + 64, y + 96, red);
	image.draw_rectangle(x + 60, y + 92, x + 64, y + 96, darkred);
	image.draw_rectangle(x + 32, y + 96, x + 64, y + 100, black);
	image.draw_rectangle(x + 36, y + 96, x + 60, y + 100, red);
	image.draw_rectangle(x + 56, y + 96, x + 60, y + 100, darkred);
	image.draw_rectangle(x + 36, y + 100, x + 60, y + 104, black);
	image.draw_rectangle(x + 40, y + 100, x + 56, y + 104, red);
	image.draw_rectangle(x + 52, y + 100, x + 56, y + 104, darkred);
	image.draw_rectangle(x + 40, y + 104, x + 56, y + 108, black);
	image.draw_rectangle(x + 44, y + 104, x + 52, y + 108, red);
	image.draw_rectangle(x + 48, y + 104, x + 52, y + 108, darkred);
	image.draw_rectangle(x + 44, y + 108, x + 52, y + 112, black);

}

void deal() {

	draw_card(top[0], 16, 16);
	draw_card(top[1], 128, 16);
	draw_card(top[2], 240, 16);
	draw_card(top[3], 352, 16);

	row[2][0].flip = true;
	for (int i = 0; i < 2; i++) row[3][i].flip = true;
	for (int i = 0; i < 3; i++) row[4][i].flip = true;
	for (int i = 0; i < 4; i++) row[5][i].flip = true;
	for (int i = 0; i < 5; i++) row[6][i].flip = true;
	for (int i = 0; i < 6; i++) row[7][i].flip = true;

	draw_card(row[1][0], 16, 248);
	draw_card(row[2][0], 128, 248); draw_card(row[2][1], 128, 284);
	draw_card(row[3][0], 240, 248); draw_card(row[3][1], 240, 284); draw_card(row[3][2], 240, 320);
	draw_card(row[4][0], 352, 248); draw_card(row[4][1], 352, 284); draw_card(row[4][2], 352, 320); draw_card(row[4][3], 352, 356);
	draw_card(row[5][0], 464, 248); draw_card(row[5][1], 464, 284); draw_card(row[5][2], 464, 320); draw_card(row[5][3], 464, 356); draw_card(row[5][4], 464, 392);
	draw_card(row[6][0], 576, 248); draw_card(row[6][1], 576, 284); draw_card(row[6][2], 576, 320); draw_card(row[6][3], 576, 356); draw_card(row[6][4], 576, 392); draw_card(row[6][5], 576, 428);
	draw_card(row[7][0], 688, 248); draw_card(row[7][1], 688, 284); draw_card(row[7][2], 688, 320); draw_card(row[7][3], 688, 356); draw_card(row[7][4], 688, 392); draw_card(row[7][5], 688, 428); draw_card(row[7][6], 688, 464);

	for (int i = 0; i < 24; i++) deck[i].flip = true;

	draw_none(528, 16); draw_card(deck[23], 688, 16);

	draw_Q('B', 50, 160); draw_W('B', 162, 160); draw_E('B', 274, 160); draw_R('B', 386, 160); draw_T('B', 562, 160); draw_Y('B', 722, 160);
	draw_one('B', 50, 212); draw_two('B', 162, 212); draw_three('B', 274, 212); draw_four('B', 386, 212); draw_five('B', 498, 212); draw_six('B', 610, 212); draw_seven('B', 722, 212);
}

void refresh() {

	image.draw_rectangle(0, 0, 800, 1000, green);
	image.draw_rectangle(0, 0, 8, 1000, white);
	image.draw_rectangle(0, 0, 800, 8, white);
	image.draw_rectangle(792, 0, 800, 1000, white);
	image.draw_rectangle(0, 992, 800, 1000, white);
	image.draw_text(16, 968, "ESC: PAUSE", black, 0, 1, 24);

	draw_card(top[0], 16, 16);
	draw_card(top[1], 128, 16);
	draw_card(top[2], 240, 16);
	draw_card(top[3], 352, 16);

	draw_card(single, 528, 16); draw_card(deck[23], 688, 16);

	for (int j = 1; j < 8; j++) { for (int i = 0; i < 20; i++) draw_card(row[j][i], 112*(j-1) + 16, 248 + (i * 36)); }

	draw_Q('B', 50, 160); draw_W('B', 162, 160); draw_E('B', 274, 160); draw_R('B', 386, 160); draw_T('B', 562, 160); draw_Y('B', 722, 160);
	draw_one('B', 50, 212); draw_two('B', 162, 212); draw_three('B', 274, 212); draw_four('B', 386, 212); draw_five('B', 498, 212); draw_six('B', 610, 212); draw_seven('B', 722, 212);

	display.render(image);
	display.paint();
	display.wait(100);

}

void init() {
score = 10000.00;
indeck = 23;
single.num = 0; single.suit = ' ';
}

void endscreen() {
	card king[4];
	int scores[5];
	if (score > 10000) scores[0] = score/10000;
	if (score > 1000) scores[1] = (score%10000)/1000;
	if (score > 100) scores[2] = (score%1000)/100;
	if (score > 10) scores[3] = (score%100)/10;
	scores[4] = score%10;

	int x[4] = {162, 356, 542, 348}, y[4] = {560, 372, 568, 752};
	bool dirx[4] = { true, true, false, false };
	bool diry[4] = { true, false, false, true };
	for (int i = 0; i < 4; i++) { king[i].num = 13; king[i].invis = false; king[i].flip = false; }
	king[0].suit = 'C'; king[1].suit = 'D'; king[2].suit = 'S'; king[3].suit = 'H';

	while (!display.is_keyESC()) {

	image.draw_rectangle(0, 0, 800, 1000, green);
	image.draw_rectangle(0, 0, 8, 1000, white);
	image.draw_rectangle(0, 0, 800, 8, white);
	image.draw_rectangle(792, 0, 800, 1000, white);
	image.draw_rectangle(0, 992, 800, 1000, white);
	image.draw_text(16, 60, "CONGRATULATIONS!!!", white, 0, 1, 85);
	image.draw_text(300, 200, "YOU WIN!", white, 0, 1, 50);
	image.draw_text(200, 300, "SCORE IS: ", white, 0, 1, 50);

		for (int i = 0; i < 5; i++) {
		switch (scores[i]) {
		case 0: draw_zero('W', 370 + i * 28, 310); break;
		case 1: draw_one('W', 370 + i * 28, 310); break;
		case 2: draw_two('W', 370 + i * 28, 310); break;
		case 3: draw_three('W', 370 + i * 28, 310); break;
		case 4: draw_four('W', 370 + i * 28, 310); break;
		case 5: draw_five('W', 370 + i * 28, 310); break;
		case 6: draw_six('W', 370 + i * 28, 310); break;
		case 7: draw_seven('W', 370 + i * 28, 310); break;
		case 8: draw_eight('W', 370 + i * 28, 310); break;
		case 9: draw_nine('W', 370 + i * 28, 310); break;
		}
	}
	
	image.draw_text(16, 900, "ESC: RETURN TO TITLE", white, 0, 1, 24);

		draw_card(king[0], x[0], y[0]);
		draw_card(king[1], x[1], y[1]);
		draw_card(king[2], x[2], y[2]);
		draw_card(king[3], x[3], y[3]);

		for (int i = 0; i < 4; i++) {
			if (dirx[i] == true) x[i] += 4; else x[i] -= 4;
			if (diry[i] == true) y[i] += 4; else y[i] -= 4;
			if (x[i] <= 158) dirx[i] = true;
			if (x[i] >= 546) dirx[i] = false;
			if (y[i] >= 756) diry[i] = false;
			if (y[i] <= 368) diry[i] = true; }

		display.render(image);
		display.paint();
		display.wait(25);

	}

	title();
}