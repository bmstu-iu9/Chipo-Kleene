#pragma once
#include <string>
using namespace std;

class AutomatonToImage {
  public:
	AutomatonToImage();
	~AutomatonToImage();
	static string to_image(string automat, string metadata = "");
	static string colorize(string automat, string metadata);
};