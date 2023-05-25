#include "Tester/Tester.h"

void Tester::test(const Regex& lang, const Regex& regex, int step,
				  iLogTemplate* log) {
	// Logger::init_step("Test");
	// vector<double> times;
	// vector<int> lengths;
	// vector<bool> belongs;
	iLogTemplate::Table t;
	iLogTemplate::Plot plot;
	vector<long> steps;
	vector<long> words;
	// vector<string> data;
	// vector<string> row;
	FiniteAutomaton thompson = lang.to_thompson();
	FiniteAutomaton glushkov = lang.to_glushkov();
	FiniteAutomaton smallNfa = glushkov.reverse().merge_bisimilar().reverse().merge_bisimilar().remove_eps();
	FiniteAutomaton mindfa = smallNfa.minimize().remove_trap_states();
        bool it_belongs;
	string id; 
	using clock = std::chrono::high_resolution_clock;

	for (int type = 0; type < 4; type++) {
	steps.clear();
	for (int i = 0; i < 13; i++) {
		string word = regex.get_iterated_word(i * step);
		// cout << word;
		const auto start = clock::now();
		int counter;
		switch (type) {
		 case 0: it_belongs = thompson.parsing_by_nfa(word, counter); id = "Thompson"; break;
		 case 1: it_belongs = glushkov.parsing_by_nfa(word, counter); id = "Glushkov"; break;
		 case 2: it_belongs = smallNfa.parsing_by_nfa(word, counter); id = "smallNFA"; break;
		 default : it_belongs = mindfa.parsing_by_nfa(word, counter); id = "minDFA"; }
		const auto end = clock::now();
		const long long elapsed =
			std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
				.count();
		double time = (double)elapsed / 1000;
		// cout << is_belongs << " " << time << endl;
		// times.push_back(time);
		// lengths.push_back(word.length());
		// belongs.push_back(is_belongs);
		steps.push_back(counter);
		words.push_back(word.length()); 
		if (!type) {t.rows.push_back(to_string(i + 1));
		t.data.push_back(to_string(counter));
		t.data.push_back(to_string(word.length()));
		t.data.push_back(to_string(time));
		 if (it_belongs)
			t.data.push_back("true");
		 else
			t.data.push_back("false");
		}

		if (time >= 180) break;
	}
	for (int i = 0; i < steps.size(); i++)
		{
			plot.data.push_back(make_pair(make_pair(words[i], int(steps[i])),id));
		}

	}


	// vector<string> col;
	t.columns.push_back("Количество итераций");
	t.columns.push_back("Длина строки");
	t.columns.push_back("Время парсинга");
	t.columns.push_back("Принадлежность языку");
	if (log) {
		log->set_parameter("language", lang);
		log->set_parameter("regex", regex);
		log->set_parameter("step", step);
		log->set_parameter("table", t);
		log->set_parameter("plot", plot);
	}
	// Logger::log("Язык, основанный на регулярке", lang.to_txt());
	// Logger::log("Слова порождаются регуляркой", regex.to_txt());
	// Logger::log("Шаг итерации", to_string(step));
	// Logger::log(step, lengths, times, belongs);
	// Logger::finish_step();
}

void Tester::test(const FiniteAutomaton& lang, const Regex& regex, int step,
				  iLogTemplate* log) {
	// Logger::init_step("Test");
	// vector<double> times;
	vector<long> words, steps;
	FiniteAutomaton mindfa = lang.minimize().remove_trap_states();
	// vector<bool> belongs;
	iLogTemplate::Table t;
	iLogTemplate::Plot plot;
	using clock = std::chrono::high_resolution_clock;
	string id;
	int counter;
	bool it_belongs;
	for (int type = 0; type < 2; type ++)  {
	steps.clear();
		if (!type) {
			id = "NFA";
			} else
			{ id = "minDFA";} 
	for (int i = 0; i < 13; i++) {
		string word = regex.get_iterated_word(i * step);
		// cout << word <<endl;
		const auto start = clock::now();
		if (!type) {
			it_belongs = lang.parsing_by_nfa(word, counter);
			} else
			{it_belongs = mindfa.parsing_by_nfa(word, counter);
			} 
		const auto end = clock::now();
		const long long elapsed =
			std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
				.count();
		double time = (double)elapsed / 1000;
		// times.push_back(time);
		steps.push_back(counter);
		// belongs.push_back(is_belongs);
		if (!type) {
			t.rows.push_back(to_string(i + 1));
			t.data.push_back(to_string(counter));
			t.data.push_back(to_string(word.length()));
			t.data.push_back(to_string(time));
			words.push_back(word.length());
		  if (it_belongs)
			t.data.push_back("true");
	     	  else
			t.data.push_back("false"); 
			}
		// cout << is_belongs << " " << time << endl;
		if (time >= 180) return;
	}
	for (int i = 0; i < steps.size(); i++)
		{
			plot.data.push_back(make_pair(make_pair(words[i], int(steps[i])),id));
		}
	}
	t.columns.push_back("Количество итераций");
	t.columns.push_back("Длина строки");
	t.columns.push_back("Время парсинга");
	t.columns.push_back("Принадлежность языку");
	if (log) {
		log->set_parameter("language", lang);
		log->set_parameter("regex", regex);
		log->set_parameter("step", step);
		log->set_parameter("table", t);
		log->set_parameter("plot", plot);
	}
	// Logger::log("Автомат", lang);
	// Logger::log("Слова порождаются регуляркой", regex.to_txt());
	// Logger::log("Шаг итерации", to_string(step));
	// Logger::log(step, lengths, times, belongs);
	// Logger::finish_step();
}

bool Tester::parsing_by_regex(string reg, string word) {
	cmatch match_res;
	regex regular(reg);
	if (regex_match(word.c_str(), match_res, regular)) {
		// cout << match_res[0].str();
		return true;
	}
	return false;
}

/*
Продам шары для ночного катания по полу.
Б/у. Работают без нареканий.
Причина продажи: переезд на первый этаж.
*/