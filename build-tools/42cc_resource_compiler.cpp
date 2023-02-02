#include <cstdio>
#include <vector>
#include <fstream>

/*
 * .42CC Resource Format will be defined like the following:
 * [DataSize:8] 0x00 [PathName:-] 0x00 [Data:-] 0x00 ....
 */

std::streamsize read_infile(const std::string& filename, std::vector<char> &data)
{
	std::ifstream	infile(filename, std::ios::binary);
	std::streamsize	size;

	if(!infile.is_open())
		return -1;
	infile.seekg(0, std::ios::end);
	size = infile.tellg();
	infile.seekg(0, std::ios::beg);
	data.resize(size);
	infile.read(data.data(), size);
	infile.close();
	return size;
}

int append_to_outfile(const std::string& filename,
					  long long fileSize,
					  const std::string &path,
					  const std::vector<char> &data)
{
	std::ofstream	outfile(filename, std::ios::app);

	if(!outfile.is_open())
		return -1;
	outfile.write((char*)&fileSize, 8);
	outfile.write("\0", 1);
	outfile << path;
	outfile.write("\0", 1);
	outfile.write(data.data(), fileSize);
	outfile.write("\0", 1);
	outfile.close();
	return 0;
}

int	main(int argc, char **argv)
{
	std::vector<char>	infileData;
	std::streamsize		fileSize;

	if (argc != 3) {
		printf("Usage: %s <infile> <resfile>\n", argv[0]);
		return 1;
	}
	printf("Input: %s\nOutput: %s\n", argv[1], argv[2]);
	fileSize = read_infile(argv[1], infileData);
	if (fileSize < 0) {
		printf("Error: Could not open input file %s\n", argv[1]);
		return 1;
	}
	fileSize = append_to_outfile(argv[2], fileSize, argv[1], infileData);
	if (fileSize < 0) {
		printf("Error: Could not open output file %s\n", argv[2]);
		return 1;
	}
	return 0;
}