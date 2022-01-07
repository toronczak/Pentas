#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
int cardsInDeck = 60, playerWin = 0, enemyWin = 0;
bool gameOver = false, mute = false;
char playerCardInfo[4], playerCardAttribute[4], enemyCardInfo[4], enemyCardAttribute[4];
char playerUsedInfo, playerUsedAttribute, enemyUsedInfo, enemyUsedAttribute;

int calc(){
	int playerAdvantage = playerUsedInfo - enemyUsedInfo;
	int playerBonus = 0, enemyBonus = 0;
	if(playerUsedAttribute == 'O' && enemyUsedAttribute=='W'){playerBonus = -1; enemyBonus = 1;}
	else if(playerUsedAttribute == 'O' && enemyUsedAttribute=='Z'){playerBonus = 2;}
	else if(playerUsedAttribute == 'O' && enemyUsedAttribute=='E'){playerBonus = -1;}
	
	else if(playerUsedAttribute == 'W' && enemyUsedAttribute=='O'){playerBonus = 1; enemyBonus = -1;}
	else if(playerUsedAttribute == 'W' && enemyUsedAttribute=='Z'){playerBonus = -2; enemyBonus = 2;}
	else if(playerUsedAttribute == 'W' && enemyUsedAttribute=='E'){playerBonus = 1; enemyBonus = -2;}
	
	else if(playerUsedAttribute == 'Z' && enemyUsedAttribute=='O'){enemyBonus = 2;}
	else if(playerUsedAttribute == 'Z' && enemyUsedAttribute=='W'){playerBonus = 2; enemyBonus = -2;}
	else if(playerUsedAttribute == 'Z' && enemyUsedAttribute=='E'){playerBonus = -2; enemyBonus = 2;}
	
	else if(playerUsedAttribute == 'E' && enemyUsedAttribute=='O'){enemyBonus = -1;}
	else if(playerUsedAttribute == 'E' && enemyUsedAttribute=='W'){playerBonus = -2; enemyBonus = 1;}
	else if(playerUsedAttribute == 'E' && enemyUsedAttribute=='Z'){playerBonus = 2; enemyBonus = -2;}

	cout << endl << "Sila twojej karty: " << playerUsedInfo-48 << " z bonusem " << playerBonus;
	cout << endl << "Sila karty przeciwnika: " << enemyUsedInfo-48 << " z bonusem " << enemyBonus;
	playerAdvantage = playerAdvantage+playerBonus-enemyBonus;
	cout << endl << "Twoja przewaga: " << playerAdvantage << endl;
	if(playerAdvantage > 0){
		playerWin++;
		cout << "Wygrywasz runde!" << endl << endl << endl;
	}
	else if(playerAdvantage < 0){
		enemyWin++;
		cout << "Przeciwnik wygrywa runde!" << endl << endl << endl;
	}
	else cout << "Remis!" << endl << endl << endl;
}

int playerDeal(int card, bool ifPlayer, bool startMute){
	srand(time(NULL)-cardsInDeck);
	
	if(cardsInDeck>0){
		if(rand()%20<=16){
		 	char arrayNormType[4] = {'O', 'W', 'Z', 'E'};
			char randInfo = 49+rand()%6;
			char randAttribute = arrayNormType[rand()%4];
			if(ifPlayer == true){
				playerCardInfo[card] = randInfo;
				playerCardAttribute[card] = randAttribute;
				if(startMute == false)	cout << ", dobrano " << randInfo << randAttribute;
			}
			else{
				enemyCardInfo[card] = randInfo;
				enemyCardAttribute[card] = randAttribute;
			}
 	   }
  	else{
			char arraySpellType[5] = {'O', 'W', 'Z', 'E', '1'};
			char randAttribute = arraySpellType[rand()%5];

			if(ifPlayer == true){
				playerCardInfo[card] = 'C';
				playerCardAttribute[card] = randAttribute;
				if(startMute == false)	cout << ", dobrano " << 'C' << randAttribute << " ";   
			}
			else{
				enemyCardInfo[card] = 'C';
				enemyCardAttribute[card] = randAttribute;
			}
		}
	}
	else{
		if(ifPlayer == true){
			playerCardInfo[card] = ' ';
			playerCardAttribute[card] = ' ';
			cout << endl << "Brak dalszych kart w talii. Nie dobrano karty!" << endl;   
		}
		else{
			enemyCardInfo[card] = ' ';
			enemyCardAttribute[card] = ' ';
		}
	}
	cardsInDeck--;
}

int spellDecision(int card){
	char ifSpellPlay;
   	cout << endl << "Zagrac czar " << playerCardInfo[card] << playerCardAttribute[card] << "? [T/N] ";
   	cin >> ifSpellPlay;
   	if(ifSpellPlay == 'T' || ifSpellPlay == 't'){
   		cout << "Zagrano czar " << playerCardInfo[card] << playerCardAttribute[card];
   		if(playerCardAttribute[card] == '1') playerUsedInfo++;
   		else playerUsedAttribute = playerCardAttribute[card];
   		cout << ", nowa postac karty to " << playerUsedInfo << playerUsedAttribute;
		playerDeal(card, true, false);
	}
	else if(ifSpellPlay == 'N' || ifSpellPlay == 'n'){
		cout << "Nie zagrano czaru";
	}
	else{
		spellDecision(card);
	}
}

int nullChecker(){
	int nullCheck = 0;
	for(int i=0; i<=3; i++){
		if(playerCardInfo[i] == 'C' || playerCardInfo[i] == ' ') nullCheck++;
		if(enemyCardInfo[i] == 'C' || enemyCardInfo[i] == ' ') nullCheck++;
	}
	if(nullCheck == 8){
			cout << "--------------------------------" << endl << "KONIEC GRY-KONIEC GRY-KONIEC GRY" << endl << "Wynik: Ty " << playerWin << ":" << enemyWin << " Przeciwnik";
			gameOver = true;
			return 0;
	}
}

int enemyTurn(){
	srand(time(NULL)-cardsInDeck);
	int randCard = rand()%4;
	int enemyAllSpellCheck = 0;
	
	for(int i=0; i<=3; i++)	if(enemyCardInfo[i] == 'C' || enemyCardInfo[i] == ' ') enemyAllSpellCheck++;
	if(enemyAllSpellCheck == 4){
		enemyAllSpellCheck = 0;
		cout << endl << "Wszystkie karty przeciwnika to czary." << endl << "Nastepuje dobranie nowej reki";
		for(int i=0; i<=3; i++){
			playerDeal(i, false, false);	
			if(enemyCardInfo[i] == 'C' || enemyCardInfo[i] == ' ') enemyAllSpellCheck++;
		}
	}

	while(enemyCardInfo[randCard] == 'C' || enemyCardInfo[randCard] == ' ' && enemyAllSpellCheck < 4){
		if(randCard==3) randCard = 0;
		else randCard++;
	}

	if(enemyAllSpellCheck == 4){
		enemyAllSpellCheck = 0;
		cout << endl << "Wszystkie dobrane karty przeciwnika to znowu czary." << endl << "Nastepuje przekazanie tobie tury!" << endl;
	}
	
	else{
   		cout << endl << "Karta zagrana przez przeciwnika: " << enemyCardInfo[randCard] << enemyCardAttribute[randCard];
   		enemyUsedInfo = enemyCardInfo[randCard];
   		enemyUsedAttribute = enemyCardAttribute[randCard];
   		playerDeal(randCard, false, false);
   		calc();
	}
}

int gameInfo(){
	if(cardsInDeck > 0) cout << "Pozostalo " << cardsInDeck << " kart w talii." << endl;
	else cout << "Talia jest pusta." << endl;
	cout << "Twoje karty:";
	for(int i=0; i<=3; i++) cout << " | " << playerCardInfo[i] << playerCardAttribute[i];
	cout << endl;
}

int playerTurn(){
	int allSpellCheck = 0;
	for(int i=0; i<=3; i++)	if(playerCardInfo[i] == 'C' || playerCardInfo[i] == ' ') allSpellCheck++;
	if(allSpellCheck == 4){
		allSpellCheck = 0;
		cout << "Twoje wszystkie kart to czary!" << endl << "Nastepuje dobranie nowej reki";
		for(int i=0; i<=3; i++){
			playerDeal(i, true, false);
			if(playerCardInfo[i] == 'C' || playerCardInfo[i] == ' ') allSpellCheck++;
		}
		if(allSpellCheck == 4){
			cout << endl << "Wszystkie twoje karty to znowu czary!" << endl << "Nastepuje przekazanie przeciwnikowi tury!" << endl;
			enemyTurn;
			return 0;
		}
	}

	if(mute == false) cout << endl << "Zagrywam karte: [1/2/3/4] ";
	char card;
	cin >> card;

	if(card >= 49 && card <= 52 && playerCardInfo[card-49] != 'C'){
		cout << "Twoja zagrana karta: " << playerCardInfo[card-49] << playerCardAttribute[card-49];
		playerUsedInfo = playerCardInfo[card-49];
		playerUsedAttribute = playerCardAttribute[card-49];
		for(int i=0; i<=3; i++) if(playerCardInfo[i]=='C') spellDecision(i);
		playerDeal(card-49, true, false);
		mute = false;
		system("cls");
		enemyTurn();
	}
   	else{
   		if (mute == false) cout << "Niepoprawna karta." << endl;
   		mute = true;
		playerTurn();
	}
}

int main(){
	for(int i=0; i<=3; i++){
		playerDeal(i, true, true);
		playerDeal(i, false, true);
	}
	while(gameOver == false){
		gameInfo();
		nullChecker();
		if(gameOver == false) playerTurn();
	}
	return 0;
}
