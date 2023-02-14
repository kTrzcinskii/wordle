#pragma once

#include <string>
#include <vector>

namespace wordle {
	class Wordle {
	public:
		Wordle();
		void start();
	private:
		std::string user_{};
		std::string current_word_{};
		unsigned int current_round_{};
		std::vector<std::string> all_words_;
		unsigned int all_words_number_{};
		bool win_{};

		void set_new_word();
		void welcome_user();
		void game_loop();
		bool check_word(std::string word);

		void win();
		void lose();
		void stop();
		void reset();

		std::string get_correct_word();
		bool is_valid_word(std::string word);

		int get_correct_number();
		bool is_valid_number(std::string num);

		const unsigned int MAX_ROUNDS = 5;
		const size_t WORD_LEN = 5;

		enum LetterOption {
			WRONG,
			SOMEWHERE_ELSE,
			CORRECT,
		};
	};
}