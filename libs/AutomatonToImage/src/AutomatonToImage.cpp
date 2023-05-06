#include "AutomatonToImage/AutomatonToImage.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

AutomatonToImage::AutomatonToImage() {}

AutomatonToImage::~AutomatonToImage() {}

/*
void AutomatonToImage::to_image(string automat, int name) {
	char cmd[1024];
	sprintf(cmd,
			"dot -Tpng ./resources/input.dot > "
			"./resources/output%d.png && rm ./resources/input.dot",
			name);
	system(cmd);
*/

string AutomatonToImage::to_image(string automat, string metadata) {

	// для Linux:
	//system("cd refal && rm -f Meta_input.data && rm -f Aux_input.data");
	// для Windows
	system("cd refal && DEL Aux_input.data");

	FILE* fo;
	fo = fopen("./refal/input.dot", "wt");
	fprintf(fo, "%s", automat.c_str());
	if (0)
		{cout << "Metadata is found" << endl;
		string str_m = "/*\n" + (metadata + "*/\n");
		fprintf(fo, "%s", str_m.c_str());
		}     
	fclose(fo);           
	system(
		"cd refal && refgo Preprocess+MathMode+FrameFormatter input.dot > error_refal0.txt");
	system("cd refal && dot2tex -ftikz -tmath \"Mod_input.dot\" > input.tex");
	system("cd refal && refgo Postprocess+MathMode+FrameFormatter input.tex > error_refal.txt "
		   "2>&1");

	// для Linux:
	//system("cd refal && rm -f Meta_input.data && rm -f Aux_input.data");
	// для Windows
	system("cd refal && DEL Aux_input.data");

	// автомат
	ifstream infile_for_R("./refal/R_input.tex");
	stringstream graph;
	string s;
	if (!infile_for_R) return "";

	while (!infile_for_R.eof()) {
		getline(infile_for_R, s);
		graph << s << endl;
	}
	infile_for_R.close();

	// TODO: разные команды для Linux и Windows
	system("cd refal && DEL input.dot && DEL input.tex && DEL Mod_input.dot DEL R_input.tex");
	return graph.str();
}

string AutomatonToImage::colorize(string automaton, string metadata) {

	// для Linux:
	//system("cd refal && rm -f Meta_input.data && rm -f Aux_input.data");
	// для Windows
	//system("cd refal && DEL Meta_input.data");

	FILE* fo;
	FILE* md;
	ifstream infile_for_Final;
	fo = fopen("./refal/Col_input.tex", "wt");
	fprintf(fo, "%s", automaton.c_str());
	fclose(fo);           
	if (metadata != "")
	 {md = fopen("./refal/Meta_input.data", "wt");
	 fprintf(md, "%s", metadata.c_str());
      	 fclose(md);
	 system(
		"cd refal && refgo Colorize+MathMode Col_input.tex > error_colorize.txt");
	 infile_for_Final.open("./refal/Final_input.tex");
	 system("cd refal && DEL Meta_input.data");
	 }
	else 
         infile_for_Final.open("./refal/Col_input.tex");           
		// для Linux:
	//system("cd refal && rm -f Meta_input.data && rm -f Aux_input.data");
	// для Windows

	// автомат
	stringstream graph;
	string s;
	if (!infile_for_Final) return "";

	while (!infile_for_Final.eof()) {
		getline(infile_for_Final, s);
		graph << s << endl;
	}
	infile_for_Final.close();

	// TODO: разные команды для Linux и Windows
	system("cd refal && DEL Final_input.tex && DEL Col_input.tex");
	// таблица
	ifstream infile_for_L("./refal/L_input.tex");

	if (!infile_for_L) return graph.str();

	// the table is adjusted for frames in the general renderer module
	while (!infile_for_L.eof()) {
		getline(infile_for_L, s);
		graph << s << endl;
	}
	infile_for_L.close();

	system("cd refal && DEL L_input.tex");


	return graph.str();
}