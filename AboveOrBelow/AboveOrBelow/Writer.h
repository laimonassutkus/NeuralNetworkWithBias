#pragma once
#include <vector>
#include <tuple>

class Writer
{
	std::string path;
public:
	explicit Writer(std::string p);
	~Writer();
	void WriteValues(const std::vector<std::tuple<double, double, bool>> &data) const;
	void ResetFile() const;
};

