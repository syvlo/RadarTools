#include <ImwHelper.hh>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cv.h>
#include <highgui.h>

void
printHelp()
{
	std::cout << "imw2png input[.imw] [-o output] [-NSigma n] [-upper up]"
			  << std::endl << std::endl
			  << "Will save input.imw as output.png (or input.png if output"
			  << std::endl << "is not set) with values map from:" << std::endl
			  << " - [0; up] to [0; 255] if up is set;" << std::endl
			  << " - [0; mu + n * sigma] to [0; 255] if n is set" << std::endl
			  << " - [0; mu + 3 * sigma] to [0; 255] otherwise." << std::endl;
}


int main (int argc, char* argv[])
{
	if (argc < 2)
	{
		printHelp();
		return 1;
	}

	double n = -1;
	std::string outputFileName = "";
	double upperVal = -1;

	std::string inputFileName;
	for (int i = 1; i < argc; ++i)
	{
		if (!strcmp("-NSigma", argv[i]))
		{
			n = atof(argv[++i]);
		}
		else if (!strcmp("-o", argv[i]))
		{
			outputFileName = argv[++i];
		}
		else if (!strcmp("-upper", argv[i]))
		{
			upperVal = atof(argv[++i]);
		}
		else if (!strcmp("-h", argv[i]) || !strcmp("--help", argv[i]))
		{
			printHelp();
			return 0;
		}
		else
			inputFileName = argv[i];
	}

	if (inputFileName.length() > 4 && inputFileName.substr(inputFileName.length() - 4).compare(".imw") == 0)
		inputFileName.erase(inputFileName.length() - 4);

	cv::Mat SARImage = ReadImw(inputFileName.c_str());

	if (upperVal == -1)
	{
		cv::Scalar mean;
		cv::Scalar stddev;

		cv::meanStdDev(SARImage, mean, stddev);

		if (n == -1)
			n = 3;

		upperVal = mean.val[0] + n * stddev.val[0];
	}

	std::clog << "Mapping [0; " << upperVal << "] to [0; 255]" << std::endl;

	cv::Mat Output(SARImage.size(), CV_8U);

	for (int i = 0; i < Output.size().height; ++i)
	{
		for (int j = 0; j < Output.size().width; ++j)
		{
			double inputVal = (double)SARImage.at<unsigned short>(i, j);
			double val = (inputVal * 255) / upperVal;

			unsigned char outputVal = (val > 255 ? 255 : val);
			Output.at<unsigned char>(i, j) = outputVal;
		}
	}


	if (outputFileName.compare("") == 0)
	{
		outputFileName = inputFileName;
		outputFileName += ".png";
	}


	std::clog << "Writing to " << outputFileName.c_str() << std::endl;
	cv::imwrite(outputFileName.c_str(), Output);

	return 0;
}
