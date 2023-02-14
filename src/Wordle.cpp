#include "Wordle.h"
#include "TerminalManager.h"
#include <iostream>
#include <fstream>
#include <random>

namespace wordle {
	terminal_manager::TerminalManager tm;

	Wordle::Wordle()
	{
		tm.change_color(tm.Cyan);
		std::cout << "Loading data...\n";
		tm.sleep_for(300);

		//TODO: add option to select between those files

		//std::ifstream file("./res/words.txt");
		std::ifstream file("./res/words_short.txt");
		std::string temp;
		while (std::getline(file, temp))
		{
			all_words_.push_back(temp);
			all_words_number_++;
		}
		file.close();
		tm.change_color(tm.Green);
		std::cout << "Data loaded successfully!\n";
		tm.sleep_for(500);
		tm.clear_terminal();
	}

	void Wordle::welcome_user()
	{
		tm.change_color(tm.White);
		std::cout << "\nWelcome to Worlde - terminal version!\n\n";
		tm.change_color(tm.Cyan);
		std::cout << "Enter your name to continue: ";
		tm.change_color(tm.Violet);
		std::getline(std::cin, user_);
		tm.sleep_for(500);
		tm.clear_terminal();
		tm.change_color(tm.White);
 	}

	void Wordle::set_new_word()
	{
		std::random_device rd;  // Seed the random number generator
		std::mt19937 mt(rd()); // Use Mersenne Twister algorithm
		std::uniform_int_distribution<> dis(0, all_words_number_ - 1);
		size_t index = dis(mt);
		current_word_ = all_words_[index];
	}

	void Wordle::game_loop()
	{
		tm.clear_terminal();

		//TODO: delete this line later, only for testing
		std::cout << current_word_;
		while (current_round_ < MAX_ROUNDS)
		{
			tm.change_color(tm.White);
			std::string word;
			std::cout << "\nEnter word: ";
			//todo:
			//check if a given string is only alpha and exactly 5 letters
			std::cin >> std::ws; //delete any whitespaces
			//when user entered 1 via cin to restart game the \n is left in memory, so we have to delete it
			std::getline(std::cin, word);

			//TODO:::
			//here i want to call
			//get_correct_word()

			current_round_++;
			bool check = check_word(word);
			if (check)
			{
				win_ = true;
				break;
			}
			int tries_left = MAX_ROUNDS - current_round_;
			if (tries_left <= 1) tm.change_color(tm.Red);
			else if (tries_left < MAX_ROUNDS / 2 + 1) tm.change_color(tm.Yellow);
			std::cout << "\n\nYou have " + std::to_string(tries_left);
			if (tries_left == 1) std::cout << " try left!\n";
			else std::cout << " tries left!\n";
			tm.change_color(tm.White);
		}
		if (win_) win();
		else lose();

		std::cout << "What do you want to do now?\n";
		std::cout << "1) Play again\n";
		std::cout << "2) Exit\n";
		std::cout << "Enter number: ";
		
		//TODO: check if given number is 1 or 2
		//by calling get_correct_number()
		int choice{};
		std::cin >> choice;
		if (choice == 1) reset();
		else stop();
	}

	bool Wordle::check_word(std::string word)
	{
		if (word.length() != WORD_LEN) return false;
		LetterOption* match = new LetterOption[WORD_LEN] {}; //here we store information about the letter
		//it can be CORRECT(green), SOMEWHERE_ELSE(yellow) or WRONG(red)

		bool* already_used = new bool[WORD_LEN] {}; //in this array we store the information if a letter has been already used
		//it's useful when checking if a letter is SOMEWHERE_ELSE, as there could be 2 or more same letters in one word

		for (size_t i = 0; i < WORD_LEN; i++)
		{
			if (current_word_[i] == word[i])
			{
				match[i] = CORRECT;
				already_used[i] = true;
			}
		}

		bool all_correct = true;
		for (size_t i = 0; i < WORD_LEN; i++) if (match[i] != CORRECT) all_correct = false;

		if (!all_correct)
		{
			for (size_t i = 0; i < WORD_LEN; i++)
			{
				if (match[i] != CORRECT)
				{
					char c = word[i];
					bool somewhere_else{};
					for (size_t j = 0; j < WORD_LEN; j++)
					{
						if (c == current_word_[j] && !already_used[j])
						{
							match[i] = SOMEWHERE_ELSE;
							already_used[j] = true;
							somewhere_else = true;
						}
					}
					if (!somewhere_else) match[i] = WRONG;
				}
			}
		}

		for (int i = 0; i < WORD_LEN; i++)
		{
			if (match[i] == CORRECT) tm.change_color(tm.Green);
			if (match[i] == SOMEWHERE_ELSE) tm.change_color(tm.Yellow);
			if (match[i] == WRONG) tm.change_color(tm.Red);
			std::cout << word[i];
		}
		tm.change_color(tm.White);

		delete[] match;
		delete[] already_used;

		return all_correct;
	}

	void Wordle::win()
	{
		std::cout << "\n\nCongratulations ";
		tm.change_color(tm.Violet);
		std::cout << user_;
		tm.change_color(tm.White);
		std::cout << "!\nYou successfully guessed word \"";
		tm.change_color(tm.Yellow);
		std::cout<< current_word_;
		tm.change_color(tm.White);
		std::cout << "\"\nIt took you ";
		tm.change_color(tm.Cyan);
		std::cout << current_round_;
		tm.change_color(tm.White);
		if (current_round_ == 1) std::cout << " try.\n";
		else std::cout << " tries.\n";
	}

	void Wordle::lose()
	{
		std::cout << "\n\nUnfortunately, you didn't manage to guess the word.\n";
		std::cout << "The word you were looking for was \"";
		tm.change_color(tm.Red);
		std::cout << current_word_;
		tm.change_color(tm.White);
		std::cout << "\"\n";
	}

	void Wordle::start()
	{
		welcome_user();
		reset();
	}

	void Wordle::reset()
	{
		current_round_ = 0;
		win_ = false;
		tm.clear_terminal();
		tm.change_color(tm.Cyan);
		std::cout << "\nSelecting a word for you...\n\n";
		tm.sleep_for(500);
		set_new_word();
		tm.change_color(tm.Green);
		std::cout << "Word has been selected!\n\n";
		tm.change_color(tm.White);
		tm.pause();

		game_loop();
	}

	void Wordle::stop()
	{
		std::cout << "I hope you enjoy your game ";
		tm.change_color(tm.Violet);
		std::cout << user_;
		tm.change_color(tm.White);
		std::cout << "\nSee you next time!\n\n";
	}

	void Wordle::get_correct_word()
	{
		//TODO:
	}

	void Wordle::get_correct_number()
	{
		//TODO
	}
}