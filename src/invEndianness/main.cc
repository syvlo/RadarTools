#include <ImwHelper.hh>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cv.h>
#include <byteswap.h>

void printHelp()
{
	std::cout << "./invEndianness input[.imw] output" << std::endl
			  << "Switch the endianness of input.imw and save it in a file"
			  << std::endl
			  << "named output.imw." << std::endl;
}

int main (int argc, char* argv[])
{
    //Check args.
	if (argc != 3)
	{
		printHelp();
		if (argc == 2 && !strcmp(argv[1], "-h")) //Help have been asked.
		{
			return 0;
		}
		return 1;
	}

	//Construct input name (remove ".imw" if it is present).
	std::string inputFileName (argv[1]);
	if (inputFileName.length() > 4 && inputFileName.substr(inputFileName.length() - 4).compare(".imw") == 0)
		inputFileName.erase(inputFileName.length() - 4);

	//Get output filename.
	std::string outputFileName (argv[2]);

	std::clog << "Converting " << inputFileName << " to "
			  << outputFileName << std::endl;

	cv::Mat SARImage = ReadImw(inputFileName.c_str());

	cv::Mat Output(SARImage.size(), CV_16U);

	for (int i = 0; i < Output.size().height; ++i)
	{
		for (int j = 0; j < Output.size().width; ++j)
		{
			unsigned short in = SARImage.at<unsigned short> (i, j);
			unsigned short out = __bswap_16(in); //Swap endianness.
			Output.at<unsigned short> (i, j) = out;
		}
	}

	WriteImw (Output, outputFileName.c_str());
}
