#pragma once

#include <string>
#include <vector>

namespace wordle {
	class Wordle {
	public:
		Wordle();
		void start();
		void stop();
		void reset();
	private:
		std::string user_{};
		std::string current_word_{};
		unsigned int current_round_{};
		std::vector<std::string> all_words_;
		unsigned int all_words_number_{};
		void set_new_word();
		void welcome_user();
		void game_loop();
	};
}