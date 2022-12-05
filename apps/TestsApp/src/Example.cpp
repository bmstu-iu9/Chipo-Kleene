#include "TestsApp/Example.h"

void Example::determinize() {
	vector<State> states;
	for (int i = 0; i < 6; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states.push_back(s);
	}

	states[0].set_transition(5, "x");
	states[0].set_transition(5, "y");
	states[0].set_transition(1, "eps");
	states[1].set_transition(2, "eps");
	states[1].set_transition(3, "eps");
	states[1].set_transition(4, "eps");
	states[3].set_transition(3, "x");
	states[4].set_transition(4, "y");
	states[4].set_transition(4, "y");
	states[5].set_transition(5, "z");
	states[5].set_transition(1, "eps");

	states[2].is_terminal = true;
	states[3].is_terminal = true;
	states[4].is_terminal = true;

	FiniteAutomaton nfa(0, states, {"x", "y", "z"});
	cout << nfa.determinize().to_txt();
}

void Example::remove_eps() {
	vector<State> states;
	for (int i = 0; i < 3; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states.push_back(s);
	}

	states[0].set_transition(0, "0");
	states[0].set_transition(1, "eps");
	states[1].set_transition(1, "1");
	states[1].set_transition(2, "eps");
	states[2].set_transition(2, "0");
	states[2].set_transition(2, "1");

	states[2].is_terminal = true;

	FiniteAutomaton nfa(0, states, {"0", "1"});
	cout << nfa.remove_eps().to_txt();
}

void Example::minimize() {
	vector<State> states;
	for (int i = 0; i < 8; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states.push_back(s);
	}

	states[0].set_transition(7, "0");
	states[0].set_transition(1, "1");
	states[1].set_transition(0, "1");
	states[1].set_transition(7, "0");
	states[2].set_transition(4, "0");
	states[2].set_transition(5, "1");
	states[3].set_transition(4, "0");
	states[3].set_transition(5, "1");
	states[4].set_transition(5, "0");
	states[4].set_transition(6, "1");
	states[5].set_transition(5, "0");
	states[5].set_transition(5, "1");
	states[6].set_transition(6, "0");
	states[6].set_transition(5, "1");
	states[7].set_transition(2, "0");
	states[7].set_transition(2, "1");

	states[5].is_terminal = true;
	states[6].is_terminal = true;

	FiniteAutomaton nfa(0, states, {"0", "1"});
	cout << nfa.minimize().to_txt();
}

void Example::intersection() {
	vector<State> states1;
	for (int i = 0; i < 3; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states1.push_back(s);
	}
	vector<State> states2;
	for (int i = 0; i < 3; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states2.push_back(s);
	}

	states1[0].set_transition(0, "b");
	states1[0].set_transition(1, "a");
	states1[1].set_transition(1, "b");
	states1[1].set_transition(2, "a");
	states1[2].set_transition(2, "a");
	states1[2].set_transition(2, "b");

	states1[1].is_terminal = true;

	states2[0].set_transition(0, "a");
	states2[0].set_transition(1, "b");
	states2[1].set_transition(1, "a");
	states2[1].set_transition(2, "b");
	states2[2].set_transition(2, "a");
	states2[2].set_transition(2, "b");

	states2[1].is_terminal = true;

	FiniteAutomaton dfa1 = FiniteAutomaton(0, states1, {"a", "b"});
	FiniteAutomaton dfa2 = FiniteAutomaton(0, states2, {"a", "b"});

	cout << FiniteAutomaton::intersection(dfa1, dfa2).to_txt();
}

void Example::regex_parsing() {
	string regl = "a(bbb*aaa*)*bb*|aaa*(bbb*aaa*)*|b(aaa*bbb*)*aa*|";
	string regr = "bbb*(aaa*bbb*)*"; //"((a|)*c)";
	regl = regl + regr;
	// egl = "a()a))";			  // regl + regr;
	// regl = "a1456|b244444444444";
	//  regl = "(ab|b)*ba"; //"bbb*(aaa*bbb*)*";
	Regex r(regl);
	cout << r.to_txt() << "\n";
	// cout << r.pump_length() << "\n";
	FiniteAutomaton a;
	FiniteAutomaton b;
	FiniteAutomaton c;
	FiniteAutomaton d;

	cout << "to_tompson ------------------------------\n";
	c = r.to_tompson(); // to_tompson(-1);
	cout << c.to_txt();

	cout << "to_glushkov ------------------------------\n";
	a = r.to_glushkov();
	cout << a.to_txt();
	cout << "to_ilieyu  ------------------------------\n";
	b = r.to_ilieyu();
	cout << b.to_txt();

	// FiniteAutomaton d;
	cout << "to_antimirov  ------------------------------\n";
	d = r.to_antimirov();
	cout << d.to_txt();
	//  cout << r.deannote().to_txt();

	//  cout << FiniteAutomaton::equal(b.minimize(), c.minimize()) << endl;

	// cout << a.to_regex().to_txt();
}

void Example::parsing_nfa() {
	string regl = "a(bbb*aaa*)*bb*|aaa*(bbb*aaa*)*|b(aaa*bbb*)*aa*|";
	string regr = "bbb*(aaa*bbb*)*"; //"((a|)*c)";
	regl = regl + regr;
	regl = "a*bc*"; //"bbb*(aaa*bbb*)*";
	Regex r(regl);

	FiniteAutomaton a;
	FiniteAutomaton b;
	FiniteAutomaton c;

	cout << "to_tompson ------------------------------\n";
	c = r.to_ilieyu(); // to_tompson(-1);
	cout << c.to_txt();
	cout << "Parsing: aaaaaaaaaaaaaaaaaaabccccc\n";
	cout << c.parsing_by_nfa("aaaaaaaaaaaaaaaaaaabccccc")
		 << endl; // true если распознал слово
}

void Example::regex_generating() {
	cout << RegexGenerator(20, 100, 3, 3).generate_regex() << "\n";
	cout << RegexGenerator().generate_regex() << "\n";
	cout << RegexGenerator(9, 2, 2).generate_regex() << "\n";
}

void Example::tasks_generating() {
	TasksGenerator TG;
	cout << "\n" << TG.generate_task(10, 3, false, false); // корректные задачи
	// cout << "\n" << TG.generate_task(15, 1, false, false);
	cout << "\n" << TG.generate_task(3, 6, true, false); // для стат. тайпчека
	cout << "\n" << TG.generate_task(5, 6, false, true); // для динам. тайпчека
}

void Example::random_regex_parsing() {
	RegexGenerator r1(8, 10, 3, 2);
	for (int i = 0; i < 5; i++) {
		string str = r1.generate_regex();
		cout << "\n" << str << "\n";
		Regex r(str);
		cout << r.to_txt() << endl;
	}
}

void Example::parsing_regex(string str) {
	cout << str << endl;
	Regex r(str);
	cout << r.to_txt() << endl;
}

void Example::transformation_monoid_example() {
	FiniteAutomaton fa = Regex("(ba)*bc").to_ilieyu();
	vector<State> states1;
	for (int i = 0; i < 3; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states1.push_back(s);
	}
	// states1[0].set_transition(0, "b");
	states1[0].set_transition(1, "a");
	states1[1].set_transition(0, "b");
	states1[0].set_transition(1, "c");
	states1[1].set_transition(2, "c");
	states1[2].is_terminal = true;
	// states1[2].set_transition(2, "a");
	// states1[2].set_transition(2, "b");
	FiniteAutomaton dfa1 = FiniteAutomaton(0, states1, {"a", "b", "c"});
	cout << "-----\n";
	cout << dfa1.to_txt();
	cout << "-----\n";
	TransformationMonoid a(dfa1);
	cout << a.get_equalence_classes_txt() << endl;
	cout << a.get_rewriting_rules_txt() << endl;
	a.class_card();
	a.class_length();
	a.is_minimal();
	a.get_classes_number_MyhillNerode();
}

void Example::fa_subset_check() {
	vector<State> states1;
	for (int i = 0; i < 4; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states1.push_back(s);
	}
	states1[0].set_transition(1, "a");
	states1[0].set_transition(1, "b");
	states1[0].set_transition(2, "a");
	states1[1].set_transition(3, "b");
	states1[2].set_transition(3, "c");
	states1[3].is_terminal = true;
	FiniteAutomaton fa1(0, states1, {"a", "b", "c"});

	vector<State> states2;
	for (int i = 0; i < 3; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states2.push_back(s);
	}
	states2[0].set_transition(1, "b");
	states2[1].set_transition(2, "b");
	states2[2].is_terminal = true;
	FiniteAutomaton fa2(0, states2, {"a", "b", "c"});

	cout << fa1.subset(fa2) << endl;
}

void Example::normalize_regex() {
	string regl = "a(bbb*aaa*)*bb*|aaa*(bbb*aaa*)*|b(aaa*bbb*)*aa*|";
	string regr = "bbb*(aaa*bbb*)*"; //"((a|)*c)";
	regl = regl + regr;
	// regl = "abc"; //"bbb*(aaa*bbb*)*";
	Regex r(regl);
	r.normalize_regex("./../temp/Rules.txt");
	cout << r.to_txt();
}
void Example::to_image() {
	vector<State> states1;
	for (int i = 0; i < 3; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states1.push_back(s);
	}
	states1[0].set_transition(1, "a");
	states1[0].set_transition(1, "eps");
	states1[0].set_transition(2, "b");
	states1[1].set_transition(2, "a");
	states1[1].set_transition(1, "b");
	states1[2].set_transition(1, "a");
	states1[2].set_transition(1, "eps");
	states1[2].set_transition(0, "b");
	states1[0].is_terminal = true;
	states1[2].is_terminal = true;
	FiniteAutomaton fa1(1, states1, {"a", "b"});

	string s1 = fa1.to_txt();

	FiniteAutomaton fa2 = fa1.merge_bisimilar();

	string s2 = fa2.to_txt();

	AutomatonToImage::to_image(s1, 1);
	AutomatonToImage::to_image(s2, 2);
}

void Example::step() {
	vector<State> states1;
	for (int i = 0; i < 3; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states1.push_back(s);
	}
	states1[0].set_transition(1, "a");
	states1[0].set_transition(1, "eps");
	states1[0].set_transition(2, "b");
	states1[1].set_transition(2, "a");
	states1[1].set_transition(1, "b");
	states1[2].set_transition(1, "a");
	states1[2].set_transition(1, "eps");
	states1[2].set_transition(0, "b");
	states1[0].is_terminal = true;
	states1[2].is_terminal = true;
	FiniteAutomaton fa1(1, states1, {"a", "b"});

	// string f1 = fa1.to_txt();

	FiniteAutomaton fa2 = fa1.merge_bisimilar();
	// string f2 = fa2.to_txt();
	FiniteAutomaton fa3 = fa2.remove_eps();
	// string f3 = fa3.to_txt();
	string s = "merge\\_bisimilar";
	Logger::activate();
	Logger::init();
	Logger::init_step(s);
	Logger::log("Автомат1", "Автомат2", fa1, fa2);
	Logger::finish_step();
	s = "skip";
	Logger::activate();
	Logger::init_step(s);
	Logger::log("Автомат1", "Автомат2", fa1, fa1);
	Logger::finish_step();
	s = "remove\\_eps";
	Logger::init_step(s);
	Logger::log("Автомат1", "Автомат2", fa2, fa3);
	Logger::finish_step();
	Logger::finish();
	Logger::deactivate();
}

void Example::tester() {
	Regex r("ab(ab|a)*ababa");
	FiniteAutomaton dfa1 = r.to_tompson();
	// cout << dfa1.parsing_by_nfa("abaaabaaababa");
	// cout << dfa1.to_txt();
	Regex r1("((ab)*a)*");
	Regex r2("ab(ab|a)*ababa");
	Tester::test(dfa1, r1, 1);
	Tester::test(r2, r1, 1);
}

void Example::step_interection() {
	vector<State> states1;
	for (int i = 0; i < 3; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states1.push_back(s);
	}
	vector<State> states2;
	for (int i = 0; i < 3; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states2.push_back(s);
	}

	states1[0].set_transition(0, "b");
	states1[0].set_transition(1, "a");
	states1[1].set_transition(1, "b");
	states1[1].set_transition(2, "a");
	states1[2].set_transition(2, "a");
	states1[2].set_transition(2, "b");

	states1[1].is_terminal = true;

	states2[0].set_transition(0, "a");
	states2[0].set_transition(1, "b");
	states2[1].set_transition(1, "a");
	states2[1].set_transition(2, "b");
	states2[2].set_transition(2, "a");
	states2[2].set_transition(2, "b");

	states2[1].is_terminal = true;

	FiniteAutomaton dfa1 = FiniteAutomaton(0, states1, {"a", "b"});
	FiniteAutomaton dfa2 = FiniteAutomaton(0, states2, {"a", "b"});

	// string f1 = dfa1.to_txt();
	// string f2 = dfa2.to_txt();
	FiniteAutomaton dfa3 = FiniteAutomaton::intersection(dfa1, dfa2);
	string s = "interection";
	Logger::activate();
	Logger::init();
	Logger::init_step(s);
	Logger::log("Автомат1", "Автомат2", "Пересечение автоматов", dfa1, dfa2,
				dfa3);
	Logger::finish_step();
	Logger::finish();
	Logger::deactivate();
}

void Example::arden_example() {

	Regex r1("b((b(b|)ab*))*");
	// cout << r1.to_tompson().to_txt();
	Regex temp = r1.to_tompson().to_regex();
	// cout << temp.to_txt() << "\n";
	//  cout << temp.to_tompson().to_txt();
}

void Example::table() {
	vector<State> states1;
	for (int i = 0; i < 3; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states1.push_back(s);
	}
	vector<State> states2;
	for (int i = 0; i < 3; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states2.push_back(s);
	}

	states1[0].set_transition(0, "b");
	states1[0].set_transition(1, "a");
	states1[1].set_transition(1, "b");
	states1[1].set_transition(2, "a");
	states1[2].set_transition(2, "a");
	states1[2].set_transition(2, "b");

	states1[1].is_terminal = true;

	states2[0].set_transition(0, "a");
	states2[0].set_transition(1, "b");
	states2[1].set_transition(1, "a");
	states2[1].set_transition(2, "b");
	states2[2].set_transition(2, "a");
	states2[2].set_transition(2, "b");

	states2[1].is_terminal = true;

	FiniteAutomaton dfa1 = FiniteAutomaton(0, states1, {"a", "b"});
	FiniteAutomaton dfa2 = FiniteAutomaton(0, states2, {"a", "b"});

	// string f1 = dfa1.to_txt();
	// string f2 = dfa2.to_txt();
	FiniteAutomaton dfa3 = FiniteAutomaton::intersection(dfa1, dfa2);

	// vector<Tester::word> words;
	// for(int i=0; i<12;i++) {
	// 	words.push_back({
	// 		i, i*100, true
	// 	});
	// }
	// string s = "test";
	Logger::activate();
	Logger::init();
	// Logger::init_step(s);
	tester();
	// Logger::finish_step();
	Logger::finish();
	Logger::deactivate();
}

void Example::fa_semdet_check() {
	vector<State> states;
	for (int i = 0; i < 4; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states.push_back(s);
	}
	states[0].set_transition(1, "a");
	states[1].set_transition(1, "a");
	states[1].set_transition(2, "b");
	states[2].set_transition(1, "a");
	states[2].set_transition(3, "b");
	states[3].set_transition(1, "a");
	states[3].set_transition(3, "b");
	states[0].is_terminal = true;
	states[1].is_terminal = true;
	states[2].is_terminal = true;

	FiniteAutomaton NDM(0, states, {"a", "b"});

	auto sdet = NDM.semdet();

	cout << "Semdet?: " << sdet << "\n";
}

void Example::classes_number_GlaisterShallit() {
	Regex r("abc");
	r.pump_length();
	FiniteAutomaton fa = r.to_glushkov();
	cout << fa.get_classes_number_GlaisterShallit() << endl;
	fa.is_nfa_minimal();
}

void Example::all_examples() {
	// determinize();
	// remove_eps();
	// minimize();
	// intersection();
	// regex_parsing();
	// regex_generating();
	// random_regex_parsing();
	// tasks_generating();
	// parsing_regex("b(ab)*b");
	// transformation_monoid_example();
	normalize_regex();
	// step();
	parsing_nfa();
	fa_subset_check();
	arden_example();
	//  to_image();
	//  tester();
	//  step_interection();
	//  table();
	fa_semdet_check();
	Regex("abaa").pump_length();
	cout << "all the examlples are successful" << endl;
}
// TEST

void Example::test_all() {
	test_fa_equal();
	test_fa_equiv();
	test_bisimilar();
	test_merge_bisimilar();
	test_regex_subset();
	test_regex_equal();
	test_ambiguity();
	test_arden();
	test_pump_length();
	test_is_one_unambiguous();
	test_interpreter();
	test_TransformationMonoid();
	test_GlaisterShallit();
	cout << "all tests passed\n\n";
}

void Example::test_fa_equal() {
	vector<State> states1;
	for (int i = 0; i < 6; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states1.push_back(s);
	}
	states1[0].set_transition(1, "b");
	states1[0].set_transition(2, "b");
	states1[0].set_transition(5, "c");
	states1[1].set_transition(3, "a");
	states1[1].set_transition(4, "c");
	states1[2].set_transition(4, "a");
	states1[5].set_transition(4, "a");
	states1[3].is_terminal = true;
	states1[4].is_terminal = true;
	FiniteAutomaton fa1(0, states1, {"a", "b", "c"});

	vector<State> states2;
	for (int i = 0; i < 6; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states2.push_back(s);
	}
	states2[0].set_transition(1, "b");
	states2[0].set_transition(2, "b");
	states2[0].set_transition(5, "c");
	states2[1].set_transition(3, "a");
	states2[1].set_transition(3, "c");
	states2[2].set_transition(4, "a");
	states2[5].set_transition(4, "a");
	states2[3].is_terminal = true;
	states2[4].is_terminal = true;
	FiniteAutomaton fa2(0, states2, {"a", "b", "c"});

	vector<State> states3;
	for (int i = 0; i < 6; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states3.push_back(s);
	}
	states3[5].set_transition(4, "b");
	states3[5].set_transition(3, "b");
	states3[5].set_transition(0, "c");
	states3[4].set_transition(2, "a");
	states3[4].set_transition(1, "c");
	states3[3].set_transition(1, "a");
	states3[0].set_transition(1, "a");
	states3[2].is_terminal = true;
	states3[1].is_terminal = true;
	FiniteAutomaton fa3(5, states3, {"a", "b", "c"});

	assert(FiniteAutomaton::equal(fa1, fa1));
	assert(!FiniteAutomaton::equal(fa1, fa2));
	assert(FiniteAutomaton::equal(fa1, fa3));
}

void Example::test_fa_equiv() {
	vector<State> states1;
	for (int i = 0; i < 3; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states1.push_back(s);
	}
	states1[0].set_transition(0, "c");
	states1[0].set_transition(1, "d");
	states1[1].set_transition(2, "c");
	states1[1].set_transition(0, "d");
	states1[2].set_transition(1, "c");
	states1[2].set_transition(2, "d");
	states1[0].is_terminal = true;
	FiniteAutomaton fa1(0, states1, {"c", "d"});

	vector<State> states2;
	for (int i = 0; i < 4; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states2.push_back(s);
	}
	states2[0].set_transition(0, "c");
	states2[0].set_transition(1, "d");
	states2[1].set_transition(2, "c");
	states2[1].set_transition(0, "d");
	states2[2].set_transition(3, "c");
	states2[2].set_transition(2, "d");
	states2[3].set_transition(2, "c");
	states2[3].set_transition(0, "d");
	states2[0].is_terminal = true;
	FiniteAutomaton fa2(0, states2, {"c", "d"});

	assert(FiniteAutomaton::equivalent(fa1, fa2));
}

void Example::test_bisimilar() {
	vector<State> states1;
	for (int i = 0; i < 3; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states1.push_back(s);
	}
	states1[0].set_transition(1, "a");
	states1[0].set_transition(1, "eps");
	states1[0].set_transition(2, "b");
	states1[1].set_transition(2, "a");
	states1[1].set_transition(1, "b");
	states1[2].set_transition(1, "a");
	states1[2].set_transition(1, "eps");
	states1[2].set_transition(0, "b");
	states1[0].is_terminal = true;
	states1[2].is_terminal = true;
	FiniteAutomaton fa1(1, states1, {"a", "b"});

	vector<State> states2;
	for (int i = 0; i < 2; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states2.push_back(s);
	}
	states2[0].set_transition(1, "a");
	states2[0].set_transition(1, "eps");
	states2[0].set_transition(0, "b");
	states2[1].set_transition(0, "a");
	states2[1].set_transition(1, "b");
	states2[0].is_terminal = true;
	FiniteAutomaton fa2(1, states2, {"a", "b"});

	assert(FiniteAutomaton::bisimilar(fa1, fa2));
}

void Example::test_merge_bisimilar() {
	FiniteAutomaton fa = Regex("(a|b)*b").to_glushkov();
	FiniteAutomaton fa1 = fa.merge_bisimilar();

	vector<State> states2;
	for (int i = 0; i < 3; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states2.push_back(s);
	}
	states2[0].set_transition(1, "a");
	states2[0].set_transition(1, "eps");
	states2[0].set_transition(2, "b");
	states2[1].set_transition(2, "a");
	states2[1].set_transition(1, "b");
	states2[2].set_transition(1, "a");
	states2[2].set_transition(1, "eps");
	states2[2].set_transition(0, "b");
	states2[0].is_terminal = true;
	states2[2].is_terminal = true;
	FiniteAutomaton fa2(1, states2, {"a", "b"});

	vector<State> states3;
	for (int i = 0; i < 2; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states3.push_back(s);
	}
	states3[0].set_transition(0, "b");
	states3[0].set_transition(1, "a");
	states3[1].set_transition(0, "eps");
	states3[1].set_transition(0, "a");
	states3[1].set_transition(1, "b");
	states3[1].is_terminal = true;
	FiniteAutomaton fa3(0, states3, {"a", "b"});

	assert(FiniteAutomaton::equal(Regex("(a|b)*b").to_ilieyu(), fa1));
	assert(FiniteAutomaton::equal(fa2.merge_bisimilar(), fa3));
}

void Example::test_regex_subset() {
	Regex r1("a*baa");
	Regex r2("abaa");

	assert(r1.subset(r2));
	assert(!r2.subset(r1));
}

void Example::test_regex_equal() {
	Regex r1("a(bbb*aaa*)*bb*|aaa*(bbb*aaa*)*");
	Regex r2("aaa*(bbb*aaa*)*|a(bbb*aaa*)*bb*");
	Regex r3("a(bbb*aaa*)*bb*|aaa*(bbb*aaa*)");

	assert(Regex::equal(r1, r2));
	assert(!Regex::equal(r1, r3));
}

void Example::test_ambiguity() {
	FiniteAutomaton fa1 = Regex("(a*)*").to_tompson();
	FiniteAutomaton fa2 = Regex("b|a|aa").to_tompson();
	FiniteAutomaton fa3 = Regex("abc").to_tompson();
	FiniteAutomaton fa4 = Regex("b|a").to_tompson();
	FiniteAutomaton fa5 = Regex("(aa|aa)*").to_glushkov();
	FiniteAutomaton fa6 = Regex("(aab|aab)*").to_glushkov();

	assert(fa1.ambiguity() == FiniteAutomaton::exponentially_ambiguous);
	assert(fa2.ambiguity() == FiniteAutomaton::polynomially_ambigious);
	assert(fa3.ambiguity() == FiniteAutomaton::unambigious);
	assert(fa4.ambiguity() == FiniteAutomaton::almost_unambigious);
	assert(fa5.ambiguity() == FiniteAutomaton::exponentially_ambiguous);
	assert(fa6.ambiguity() == FiniteAutomaton::exponentially_ambiguous);
}
void Example::test_arden() {
	auto test_equivalence = [](string rgx_str) {
		Regex reg(rgx_str);
		assert(Regex::equivalent(reg, reg.to_tompson().to_regex()));
		assert(Regex::equivalent(reg, reg.to_glushkov().to_regex()));
		assert(Regex::equivalent(reg, reg.to_ilieyu().to_regex()));
		assert(Regex::equivalent(reg, reg.to_antimirov().to_regex()));
	};

	test_equivalence("a");
	test_equivalence("a*");
	test_equivalence("(ab)*a");
	test_equivalence("a(a)*ab(bb)*baa");
	test_equivalence("(b)*(b)");
	test_equivalence("a*|");
	test_equivalence("|b((b((a)*)(a(|(a))))*)");
	test_equivalence("(((a*)))(((a(b|)|a)*||b))");
	test_equivalence("((b(((ba|b)|||(b))*)))");
	test_equivalence("(((((a*)((a*)|bb)(((|||((b)))))))))");
}
void Example::test_pump_length() {
	assert(Regex("abaa").pump_length() == 5);
}

void Example::fa_to_pgrammar() {
	FiniteAutomaton a1 =
		Regex("(c1(ab*a|b*)*d1)|(c2(ba*b|a*)*d2)")
			.to_glushkov()
			.merge_bisimilar(); // Regex("b*a(a|c)*b(b|c)*").to_ilieyu();
	// cout << a1.to_txt();

	vector<State> states1;
	for (int i = 0; i < 5; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states1.push_back(s);
	}
	// states1[0].set_transition(0, "b");
	states1[4].set_transition(1, "a");
	// states1[0].set_transition(1, "c");
	//  states1[1].set_transition(1, "a");
	//  states1[1].set_transition(1, "c");
	states1[1].set_transition(2, "b");
	states1[1].set_transition(4, "c");
	// states1[2].set_transition(2, "c");
	states1[2].set_transition(2, "b");
	states1[2].set_transition(2, "c");
	states1[2].is_terminal = true;
	states1[0].set_transition(4, "c");
	states1[3].set_transition(0, "a");
	states1[3].set_transition(0, "b");
	states1[4].is_terminal = true;
	FiniteAutomaton dfa1 = FiniteAutomaton(3, states1, {"a", "b", "c"});

	Grammar g;
	FiniteAutomaton test = a1.annote();
	cout << dfa1.to_txt();

	g.fa_to_prefix_grammar(dfa1);
	cout << "+++++++++++++++++++++++++++++" << endl;
	cout << g.pg_to_txt();
	cout << "+++++++++++++++++++++++++++++" << endl;
	cout << g.prefix_grammar_to_automaton().to_txt();
}
void Example::test_is_one_unambiguous() {
	Regex r1("(a|b)*a");
	Regex r2("(a|b)*(ac|bd)");
	Regex r3("(a|b)*a(a|b)");
	Regex r4("(c(a|b)*c)*");
	Regex r5("a(bbb*aaa*)*bb*|aaa*(bbb*aaa*)*|b(aaa*bbb*)*aa*|");

	// ok
	assert(r1.to_glushkov().is_one_unambiguous());
	// doesn't fulfills the orbit property
	assert(!r2.to_glushkov().is_one_unambiguous());
	// consists of a single orbit, but neither a nor b is consistent
	assert(!r3.to_glushkov().is_one_unambiguous());
	// ok
	assert(r4.to_glushkov().is_one_unambiguous());
	// doesn't fulfills the orbit property
	assert(!r5.to_glushkov().is_one_unambiguous());
};

void Example::test_interpreter() {
	Interpreter interpreter;
	interpreter.set_log_mode(Interpreter::LogMode::nothing);
	assert(!interpreter.run_line("A = Annote (Glushkova {a})"));
	assert(interpreter.run_line("N1 = ((Glushkov ({ab|a})))"));
	assert(interpreter.run_line("N2 =  (Annote N1)"));
	assert(!interpreter.run_line("N2 =  (Glushkov N1)"));
	assert(!interpreter.run_line("Equiv N1 N3"));
	assert(interpreter.run_line("Equiv ((N1)) ((Reverse.Reverse (N2)))"));
	assert(interpreter.run_line("Test (Glushkov {a*}) {a*} 1"));

	assert(interpreter.run_line("A = Annote.Glushkov.DeAnnote {a}"));
	assert(interpreter.run_line("B = Annote (Glushkov.DeAnnote {a})"));
	assert(interpreter.run_line("B = Annote (Glushkov(DeAnnote {a}))"));
	assert(interpreter.run_line("A = Annote.Glushkov.DeAnnote {a} !!"));
	assert(interpreter.run_line("B = Annote (Glushkov.DeAnnote {a}) !!"));
	assert(interpreter.run_line("B = Annote (Glushkov(DeAnnote {a})) !!"));
}
void Example::test_TransformationMonoid() {
	FiniteAutomaton fa1 = Regex("a*b*c*").to_tompson().minimize();
	TransformationMonoid tm1(fa1);
	assert(tm1.class_card() == 7);
	assert(tm1.class_length() == 2);
	assert(tm1.is_minimal());
	assert(tm1.get_classes_number_MyhillNerode() == 3);

	vector<State> states;
	for (int i = 0; i < 5; i++) {
		State s = {
			i, {i}, to_string(i), false, map<alphabet_symbol, set<int>>()};
		states.push_back(s);
	}
	states[0].set_transition(1, "a");
	states[1].set_transition(2, "c");
	states[2].set_transition(3, "a");
	states[3].set_transition(2, "c");
	states[3].set_transition(4, "b");
	states[4].set_transition(4, "b");
	states[4].set_transition(4, "c");
	states[4].is_terminal = true;
	FiniteAutomaton fa2(0, states, {"a", "b", "c"});
	TransformationMonoid tm2(fa2);
	assert(tm2.class_card() == 12);
	assert(tm2.class_length() == 4);
	assert(tm2.is_minimal() == 1);
	assert(tm2.get_classes_number_MyhillNerode() == 5);

	FiniteAutomaton fa3 = Regex("ab|b").to_glushkov().minimize();
	TransformationMonoid tm3(fa3);
	assert(tm3.is_minimal());

	FiniteAutomaton fa4 = Regex("a").to_glushkov().minimize();
	TransformationMonoid tm4(fa4);
	assert(tm4.is_minimal());

	FiniteAutomaton fa5 = Regex("b*a*").to_tompson().minimize();
	TransformationMonoid tm5(fa5);
	assert(tm5.is_minimal());
}

void Example::test_GlaisterShallit() {
	assert(Regex("abc").to_glushkov().get_classes_number_GlaisterShallit() ==
		   4);
	assert(Regex("a*b*c*").to_glushkov().get_classes_number_GlaisterShallit() ==
		   1);
	assert(
		Regex("aa*bb*cc*").to_glushkov().get_classes_number_GlaisterShallit() ==
		3);
}
