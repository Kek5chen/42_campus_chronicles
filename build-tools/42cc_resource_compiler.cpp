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

void append_to_outfile(std::ofstream &outfile,
					  long long fileSize,
					  const std::string &path,
					  const std::vector<char> &data)
{
	outfile.write((char*)&fileSize, 8);
	outfile.write("\0", 1);
	outfile << path;
	outfile.write("\0", 1);
	outfile.write(data.data(), fileSize);
	outfile.write("\0", 1);
}

int	main(int argc, char **argv)
{
	std::vector<char>	infileData;
	std::streamsize		fileSize;
	int 				i;

	if (argc < 3) {
		printf("Usage: %s <infile> <resfile>\n", argv[0]);
		return 1;
	}
	std::ofstream	outfile(argv[argc - 1], std::ios::binary | std::ios_base::trunc);
	if (!outfile.is_open()) {
		printf("Error: Could not open output file %s\n", argv[argc - 1]);
		return 1;
	}

	i = 1;
	while (i < argc - 1) {
		printf("Input: %s\nOutput: %s\n", argv[i], argv[argc - 1]);
		fileSize = read_infile(argv[i], infileData);
		if (fileSize < 0) {
			printf("Error: Could not open input file %s\n", argv[i]);
			return 1;
		}
		append_to_outfile(outfile, fileSize, argv[i], infileData);
		infileData.clear();
		i++;
	}
	outfile.close();
	return 0;
}