#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>	
#include <utility>

//Needed to sort the scores
bool sortbysec(const std::pair<std::string, int>& a,
	const std::pair<std::string, int>& b)
{
	return (a.second > b.second);
}

//Handles the score input and makes sure it is reasonable
int getScore() {
	//Too avoid complictions with input containing whitespaces, commas or dots.
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	int  tempScore{};
	while (true) {
		std::cout << "Please enter score with only numbers and press Enter \n";
		std::cin >> tempScore;
		//If bad input, restrt loop
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
			std::cout << "You did not enter a number \n";
		}
		//Makes sure no score is negative
		else if (tempScore < 0) {
			std::cout << "You can't have a negative score... \n";
		}
		//Just something silly I wanted to add for the case if someone would get more than the "max possible score"
		else if (tempScore > 999) {
			std::cout << "That score is too good to be true \n";
			break;
		}
		//Here the appropiate scores goes
		else if (tempScore < 1000) {
			break;
		}
	}
	return tempScore;
}

//Takes care of the name and formats it so it fits well with the scoreboard by removing letters or adding whitespace
std::string getName() {
	int perfectNameLength{ 9 };
	std::string tempName{};
	//Too avoid complictions with input containing whitespaces, commas or dots.
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (true) {
		std::cout << "Please enter name and press Enter \n";
		std::getline(std::cin, tempName);
		//If bad input, restrt loop
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "You did enter something weird \n";
		}
		//If the name is to long the end of it gets erased
		else if (tempName.size() > perfectNameLength) {
			std::cout << "Your name is too long and will be cut \n";
			tempName.erase(9, tempName.size());
			break;
		}
		//If the name is too short it adds whitespace so the scoreboard keeps its shape
		else if (tempName.size() < perfectNameLength) {
			while (tempName.size() < perfectNameLength) {
				tempName = tempName + " ";
			}
			break;
		}
		//Here the names that already have the correct length goes
		else   {
			break;
		}
	}
	return tempName;
}

//Creates a vector with 10 example scores
std::vector< std::pair<std::string, int>> startScore() {
	std::vector< std::pair<std::string, int>> temp;
	temp.push_back({ "Name     ", 100 });
	temp.push_back({ "Bond     ", 7 });
	temp.push_back({ "David    ", 307 });
	temp.push_back({ "Anders   ", 500 });
	temp.push_back({ "Police   ", 112 });
	temp.push_back({ "Bad luck ", 0 });
	temp.push_back({ "test     ", 50 });
	temp.push_back({ "Luke     ", 54 });
	temp.push_back({ "Year     ", 19 });
	temp.push_back({ "Pro      ", 499 });
	return temp;
}

//Makes a scoreboard in the command window with some very simple "graphics"
//This one is really messy but added for the fun of it so the scores can be shown in more visual way
//As this solution is very dependent on whitespaces to keep its shape there is a lot of if cases to make sure it keeps its shape
void drawTopTen(std::vector< std::pair<std::string, int>> score) {
	std::cout << "|--------------------------|\n";
	std::cout << "|Place:  |Name:    |Score: |\n";
	std::cout << "|--------------------------|\n";
	for (int i = 0; i < 10; i++) {
		if (i + 1 < 10) {
			std::cout << "|" << i + 1 << "       ";
		}
		else if (i + 1 < 100) {
			std::cout << "|" << i + 1 << "      ";
		}
		std::cout << "|" << score[i].first << "|";
		if (score[i].second < 10) {
			std::cout << 0 << 0;
		}
		else if (score[i].second < 100) {
			std::cout << 0;
		}
		if (score[i].second < 1000) {
			std::cout << score[i].second;
		}
		//Little note for the people with too good scores to be true
		else {
			std::cout << "Cheater|\n";
		}
		if (score[i].second < 1000) {
			std::cout << "    |\n";
		}
		std::cout << "|--------------------------|\n";
	}
}

int main()
{
	int input{ }, tempScore{};
	std::string tempName{};
	//Load some scores so it does not start empty
	std::vector< std::pair<std::string, int>> score;
	score = startScore();
	//Sort the scoreboard after the scores
	sort(score.begin(), score.end(), sortbysec);
	drawTopTen(score);
	while (true) {
		std::cout << "Do you want to add a new High Score? At placement 10 the score is: " << score[9].second << " by player "<< score[9].first << "\n";
		std::cout << "Press 1 and Enter for Yes, press 2 and Enter for No: \n";
		std::cin >> input;
		//If bad input, restrt loop
		if (!std::cin) 
		{
			std::cin.clear(); 
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input, try again \n";
		}
		//Insert new score
		else if (input == 1) {
			//Gets the players score
			tempScore = getScore();
			//Gets the players name
			tempName = getName();
			//Puts the players name and score into the score vector
			score.push_back({ tempName,tempScore });
			//Sort the scoreboard after the scores
			sort(score.begin(), score.end(), sortbysec);
			//Removes the worst score, this also does so a new score that is not too good will not be shown
			score.pop_back();
			//Create a new scorebord in the command window to see
			drawTopTen(score);
		}
		//Get out of scoreboard
		else if (input == 2) {
			std::cout << "Thank you for playing! \n";
			break;
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input, try again \n";
		}
	}
}