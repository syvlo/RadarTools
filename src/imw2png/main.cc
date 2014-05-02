#include "../ImwHelper.hh"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cv.h>
#include <highgui.h>

void
printHelp()
{
	std::cout << "imw2png input[.imw] n [output]" << std::endl << std::endl
			  << "Will save input.imw as output.png (or input.png if output"
			  << std::endl << "is not set) with values map from " << std::endl
			  << "[0; mu + n * sigma] to [0; 255] with n a float" << std::endl;
}


int main (int argc, char* argv[])
{
	if (argc != 3 && argc != 4)
	{
		printHelp();
		return 1;
	}

	std::string inputFileName(argv[1]);

	if (inputFileName.length() > 4 && inputFileName.substr(inputFileName.length() - 4).compare(".imw") == 0)
		inputFileName.erase(inputFileName.length() - 4);

	cv::Mat SARImage = ReadImw(inputFileName.c_str());
	cv::Scalar mean;
	cv::Scalar stddev;

	cv::meanStdDev(SARImage, mean, stddev);

	double n = atof(argv[2]);

	double upperVal = mean.val[0] + n * stddev.val[0];

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

	std::string outputFileName;
	if (argc == 4)
		outputFileName = argv[3];
	else
		outputFileName = inputFileName;

	outputFileName += ".png";

	cv::imwrite(outputFileName.c_str(), Output);

	return 0;
}
