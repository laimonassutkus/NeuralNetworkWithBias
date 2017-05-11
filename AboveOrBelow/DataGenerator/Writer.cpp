#include "Writer.h"

Writer::Writer(std::string p)
{
	path = p;
}

Writer::~Writer()
{
}

void Writer::WriteValues(const std::vector<std::tuple<double, double, bool>> &data,
	const std::vector<unsigned int> &topology) const
{
	std::ofstream writer;
	writer.open(path, std::ios_base::app);

	if (!writer.is_open())
	{
		std::cout << "Failed to open file" << std::endl;
		exit(1);
	}

	for each (auto point in data)
	{
		std::string position = std::get<bool>(point) ? "1" : "0";
		writer << std::get<0>(point) << " " << std::get<1>(point) 
			<< std::endl << position << std::endl;
	}

	writer.close();
}

void Writer::ResetFile() const
{
	std::fstream ofs;
	ofs.open(path, std::ofstream::out | std::ofstream::trunc);

	if (!ofs.is_open())
	{
		std::cout << "Failed to open file" << std::endl;
		exit(1);
	}
	ofs.close();
}
