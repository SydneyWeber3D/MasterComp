#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include <windows.h>

void menu();

void combinationGenerator(char* computerCombination);
void playerRound(char* computerCombination, const int COMBINATION_COUNT, int roundCount);
std::string conformInput(std::string playerInput, const int COMBINATION_COUNT);
void stringToChar(std::string playerInput, char* playerCombination, const int COMBINATION_COUNT);
void combinationComparison(char* computerCombination, char* playerCombination, int roundCount);
void victory(int roundCount);
void defeat();

void startGame()
{
	const int COMBINATION_COUNT = 4, COMBINATION_CHOICES = 6;
	int roundCount = 0;
	std::cout << "\n========Game Starting========\n"
		<< "Reminder: A (aqua), B (blue), F (fuschia), R (red), Y (yellow), L (lime)." << std::endl;

	char computerCombination[COMBINATION_COUNT];
	combinationGenerator(computerCombination);

	//Uncomment this section to have the game print the solution after setting up the game.
	std::cout << "Solution: ";
	for (int i = 0; i < COMBINATION_COUNT; i++)
	{
		std::cout << computerCombination[i];
	}
	std::cout << std::endl << std::endl;


	do
	{
		playerRound(computerCombination, COMBINATION_COUNT, roundCount);
		roundCount++;
	} while (roundCount < 12);

	roundCount = 0;
	defeat();
}

void combinationGenerator(char* computerCombination)
{
	const int COMBINATION_COUNT = 4, COMBINATION_CHOICES = 6;
	static const char combinationColors[COMBINATION_CHOICES] = { 'A', 'B', 'F', 'R', 'Y', 'L' };

	srand(time(0));

	for (int i = 0; i < COMBINATION_COUNT; i++)
	{
		computerCombination[i] = combinationColors[rand() % COMBINATION_CHOICES];
	}
}

void playerRound(char* computerCombination, const int COMBINATION_COUNT, int roundCount)
{
	std::cout << "Round " << ++roundCount << "\/12: ";
	std::string playerInput;
	char playerCombination[4];

	std::getline(std::cin, playerInput);

	if (playerInput.length() < 4)
	{
		for (int i = playerInput.length(); i < 4; i++)
		{
			playerInput += 'X';
		}
	}

	playerInput = conformInput(playerInput, COMBINATION_COUNT);
	stringToChar(playerInput, playerCombination, COMBINATION_COUNT);

	for (int j = 0; j < COMBINATION_COUNT; j++)
	{
		std::cout << playerCombination[j];
	}
	std::cout << '\t';

	combinationComparison(computerCombination, playerCombination, roundCount);
}

std::string conformInput(std::string playerInput, const int COMBINATION_COUNT)
{
	for (int i = 0; i < COMBINATION_COUNT; i++)
	{
		playerInput[i] = toupper(playerInput[i]);
	}

	return playerInput;
}

void stringToChar(std::string playerInput, char* playerCombination, const int COMBINATION_COUNT)
{
	for (int i = 0; i < COMBINATION_COUNT; i++)
	{
		playerCombination[i] = playerInput[i];
	}
}

void combinationComparison(char* computerCombination, char* playerCombination, int roundCount)
{
	const int RE_COMB_COUNT = 4;
	int whitePeg = 0, redPeg = 0;
	char combinationBuffer[RE_COMB_COUNT];

	for (int x = 0; x < RE_COMB_COUNT; x++)
		combinationBuffer[x] = computerCombination[x];

	for (int i = 0; i < RE_COMB_COUNT; i++)
	{
		if (playerCombination[i] == combinationBuffer[i])
		{
			redPeg++;
			playerCombination[i] = '0';
			combinationBuffer[i] = '1';
		}
	}

	for (int j = 0; j < RE_COMB_COUNT; j++)
	{
		for (int k = 0; k < RE_COMB_COUNT; k++)
		{
			if (playerCombination[j] == combinationBuffer[k] && j != k)
			{
				whitePeg++;
				playerCombination[j] = '2';
				combinationBuffer[k] = '3';
			}
		}
		playerCombination[j] = '4';
	}

	std::cout << "\[" << whitePeg << "w " << redPeg << "r\]\n" << std::endl;

	if (redPeg == 4)
		victory(roundCount);
}

void victory(int roundCount)
{
	std::cout << "VICTORY!\n" << std::endl;
	std::ofstream runLog;
	runLog.open("playerLogs.txt", std::ios::app);

	if (roundCount == 1)
		runLog << "Flawless Victory!\n";
	else
		runLog << "Victory in " << roundCount << " rounds\n";

	runLog.close();
	menu();
}

void defeat()
{
	std::cout << "DEFEAT!\n" << std::endl;
	std::ofstream runLog;
	runLog.open("playerLogs.txt", std::ios::app);
	runLog << "Defeat\n";
	runLog.close();
	menu();
}
