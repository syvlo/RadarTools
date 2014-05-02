#include "../ImwHelper.hh"
#include <iostream>
#include <string>
#include <cv.h>
#include <highgui.h>

void
printHelp()
{
	std::cout << "imw2png input output" << std::endl
			  << "Will save input.imw as output.png with values map from "
			  << std::endl
			  << "[0; mu + 3 * sigma] to [0; 255]" << std::endl;
}


int main (int argc, char* argv[])
{
	if (argc != 3)
	{
		printHelp();
		return 1;
	}

	cv::Mat SARImage = ReadImw(argv[1]);
	cv::Scalar mean;
	cv::Scalar stddev;

	cv::meanStdDev(SARImage, mean, stddev);

	double upperVal = mean.val[0] + 3 * stddev.val[0];

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

	std::string outputFileName(argv[2]);
	outputFileName += ".png";

	cv::imwrite(outputFileName.c_str(), Output);

	return 0;
}
