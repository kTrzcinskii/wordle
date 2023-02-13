#pragma once

#include <string>

namespace wordle {
	class Wordle {
	public:
		void start();
		void stop();
		void reset();
	private:
		std::string user_;
		std::string current_word_;
		unsigned int current_round_;
		void set_new_word();
		void welcome_user();
		void game_loop();
	};
}