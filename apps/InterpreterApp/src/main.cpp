#include "Interpreter/Interpreter.h"
#include "Objects/Regex.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	// Приветствие
	cout << "Chipollino :-)\n";

	// Инициализируем интерпретатор
	Interpreter interpreter;
	interpreter.set_log_mode(Interpreter::LogMode::all);

	// Загружаем в интерпретатор файл с коммандами
	string load_file = "test.txt", log_gen;
	bool log_gen_flag = true;
	//string load_file = "./resources/all_functions.txt";
	if (argc > 1) load_file = argv[1];
	if (argc > 2) log_gen = argv[2];
	if (log_gen == "-n") log_gen_flag = false;
	if (interpreter.run_file(load_file)) {
		if (log_gen_flag) {interpreter.generate_log("./resources/report.tex");} else {cout << "The result is not logged.\n"; }
	}

	// Гененрируем выходной документ, завершаем работу логгера
	// Logger::finish();
	// Logger::deactivate();
}