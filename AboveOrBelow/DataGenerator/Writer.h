#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <fstream>
#include <iostream>

class Writer
{
	std::string path;
public:
	Writer(std::string p);
	~Writer();
	void WriteValues(const std::vector<std::tuple<double, double, bool>> &data,
		const std::vector<unsigned int> &topology) const;
	void ResetFile() const;
};

