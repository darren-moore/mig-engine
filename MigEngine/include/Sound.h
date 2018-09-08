#pragma once
#include <string>

class Sound{
public:
	Sound(std::string filename) : filename_(filename) {};
	std::string getFilename() { return filename_; }
private:
	std::string filename_;
};