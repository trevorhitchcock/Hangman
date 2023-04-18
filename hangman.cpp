/**
Trevor Hitchcock
Dr. Silvera
3/10/2023
This is a simplified version of the game hangman.
**/
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

int wins = 0;
int losses = 0;

// will return true if user won game, else false
bool playGame(std::vector<string> const & wordVector){
	
	int randomWordIndex = rand() % wordVector.size();
	string wordToGuess = wordVector.at(randomWordIndex);
	bool guessedYet = false;
	
	cout << "\n";
	
	// creates boolean vector
	// true if index has been guessed
	// false if not
	vector<bool> indexGuessedYet;
	for(int i=0;i<wordToGuess.length()-1;i++){
		indexGuessedYet.push_back(false); // false because nothing has been guessed yet
	}
	
	vector<char> lettersGuessed;
	int guessesLeft = 7; // from prompt
	int guessMatches = 0;
	
	while(!guessedYet && guessesLeft>0){
		cout << "\n";
		cout << "Here is what you have so far:\n";
		
		// prints out the word with guessed letters
		//cout << "wordToGuess length:" << wordToGuess.length();
		for(int i=0; i <wordToGuess.length()-1;i++){
			if(indexGuessedYet.at(i)==1){
				cout << wordToGuess.at(i) << " ";
			}
			else{
				cout<< "_ ";
			}
		}
		
		char curGuess;
		cout<<"\n";
		if(!guessedYet){
			cout << "Enter your guess: ";
			cin>> curGuess;
			
			/** Testing purposes
			cout << "This is the lettersGuessed vector:\n";
			for(int i=0; i < lettersGuessed.size(); i++)
				std::cout << lettersGuessed.at(i) << "\n";
			**/
			
			// checks to see if guess is valid
			if(lettersGuessed.size() == 0){
				lettersGuessed.push_back(curGuess);
			}
			else{
				guessMatches = 0;
				for(int i=0; i<lettersGuessed.size();i++){
					if(curGuess == lettersGuessed.at(i)){ // char has already been guessed
						guessMatches = guessMatches+1;
					}
				}
	
				if(guessMatches==0){ // letter has not been guessed yet
					// so we push it into lettersGuessed vector
					lettersGuessed.push_back(curGuess);
				}else{
					cout<< "That letter has been guessed already. Try again\n";
				}
			} 
		}
		
		// checks to see if guess is in the string
		int matches = 0;
		for(int i=0;i<wordToGuess.length();i++){
			if(curGuess == wordToGuess.at(i)){ // there is a match
				indexGuessedYet.at(i) = true;
				matches = matches +1;
			}
		}
		
		cout << "\n";
		if(guessMatches ==0){
			if(matches==0){// letter not in word
				guessesLeft = guessesLeft -1;
				cout << "That letter isn't in the word. You have " << guessesLeft << " guesses left.\n";
			}
			else{ // letter in the word
				cout << "That letter is in the word! Nice!\n";
			}
		}
		
		// this for loop checks to see if all of the letters have been guessed
		int totalCorrectLetters = 0;
		for(int i=0; i < indexGuessedYet.size(); i++){
			if(indexGuessedYet.at(i)==1){
				totalCorrectLetters = totalCorrectLetters+1;
			}
		}
		if(totalCorrectLetters == wordToGuess.length()-1){ // word was guessed
			cout << "You guessed the word! The word was "<< wordToGuess<<"\n";
			guessedYet=true;
			return true;
		}
	}
	cout << "You lose! The word was " << wordToGuess;
	cout << "\n";
	return false;
}

int main(){
	// open file
	ifstream wordsFile("words.txt");
	
	// creates vector to store words in
	vector<string> wordsVector;
	
	// adds words from file into vector
	string word;
	while (getline (wordsFile, word)){
		wordsVector.push_back(word);
	}
	wordsFile.close();
	
	// print out vector. for testing purposes
	/**
	cout << "This is the vector:\n";
	for(int i=0; i < wordsVector.size(); i++)
		std::cout << wordsVector.at(i) << "\n";
	**/
	

	//create menu
	int input;
	
	do{
		cout << "\n";
		cout << "Welcome to hangman!\n";
		cout << "1. Play\n";
		cout << "2. Score\n"; 
		cout << "3. Add word\n"; 
		cout << "4. Exit\n"; 
		cout << "Enter what you would like to do: ";
		
		cin >> input; // user enters input here
		
		if(input == 1){ // PLAY
			bool didUserWin;
			didUserWin = playGame(wordsVector); // win/loss status stored here
			if(didUserWin)
				wins = wins + 1;
			else
				losses = losses +1;
		}
		else if(input ==2){ // print wins and losses
			cout << "You have won " << wins << " times.\n";
			cout << "You have lost " << losses << " times.\n";
		}
		else if(input==3){ // enter a string
			cout << "Enter a string. This string must have less than 10 characters,\n";
			cout << "doesn't have spaces, and isn't already in the file.\n";
			
			string wordToEnter;
			
			cin >> wordToEnter;
			
			// checks for spaces
			int numSpaces =0;
			for(int i=0;i<wordToEnter.length();i++){
				if(isspace(wordToEnter.at(i))){
					numSpaces = numSpaces+1;
				}
			}
			
			// checks if in vector
			int userWordMatches = 0;
			
			for(int i=0;i<wordsVector.size();i++){
				int sameChar = 0;
				
				if(wordToEnter.length()==wordsVector.at(i).length()-1){// words are same length
					for(int j=0; j<wordToEnter.length(); j++){ // comparing each index
						if(wordToEnter.at(j)==wordsVector.at(i).at(j)){
							sameChar=sameChar+1;
						}
					}
					
					if(sameChar == wordToEnter.length()){
						cout << "Word found in vector!\n";
						userWordMatches = userWordMatches+1;
					}
				}
				
			}

			// all conditions must be met for input to be valid
			
			if((wordToEnter.length()<10)and(numSpaces==0)and(userWordMatches==0)){
				//input valid
				wordsVector.push_back(wordToEnter);
				cout << "Word is valid and has been entered.\n";
			}
			else{
				cout << "Word is not valid.\n"; 
			}
			
			cout << "This is the current word vector:\n";
			for(int i=0; i < wordsVector.size(); i++)
				std::cout << wordsVector.at(i) << "\n";
			
			
		}
		else{
			cin.clear();
			fflush(stdin);
			// I have no idea why this prints when the program ends by inputting 4
			cout << "Input is not valid. Enter 1,2,3, or 4.\n";
		}
		cin.clear();
		fflush(stdin);
	}while(input != 4);
};