#include "Gene.h"
#include <SkImageEncoder.h>

namespace GeneticImages
{
	Gene::Gene(const unsigned int width, const unsigned int height)
	{
		this->bitmap.allocN32Pixels(width, height);
	}

	Gene::~Gene()
	{}

	void Gene::EvaluateFitness(const SkBitmap& targetBitmap)
	{
		this->fitness = 0;

		unsigned int numberOfPixels = this->bitmap.width() * this->bitmap.height();
		int bytesPerPixel = this->bitmap.bytesPerPixel();

		uint8_t* pixels = (uint8_t*)this->bitmap.getPixels();
		uint8_t* targetPixels = (uint8_t*)targetBitmap.getPixels();

		for (unsigned int i = 0; i < numberOfPixels; ++i)
		{
			// Calculate fitness values for this pixel
			this->fitness += 255 - abs(pixels[0] - targetPixels[0]); // Red
			this->fitness += 255 - abs(pixels[1] - targetPixels[1]); // Green
			this->fitness += 255 - abs(pixels[2] - targetPixels[2]); // Blue
			this->fitness += 255 - abs(pixels[3] - targetPixels[3]); // Alpha

			// Increment the pointers along the pixel arrays
			pixels += bytesPerPixel;
			targetPixels += bytesPerPixel;
		}

		// for (int i = 0; i < this->; ++i)
		// {
		// 	for (int j = 0; j < this->bitmap.cols; ++j)
		// 	{
		// 		this->fitness += 255 - abs(this->bitmap.at<cv::Vec4b>(i, j)[0] - targetBitmap.at<cv::Vec4b>(i, j)[0]);
		// 		this->fitness += 255 - abs(this->bitmap.at<cv::Vec4b>(i, j)[1] - targetBitmap.at<cv::Vec4b>(i, j)[1]);
		// 		this->fitness += 255 - abs(this->bitmap.at<cv::Vec4b>(i, j)[2] - targetBitmap.at<cv::Vec4b>(i, j)[2]);
		// 		this->fitness += 255 - abs(this->bitmap.at<cv::Vec4b>(i, j)[3] - targetBitmap.at<cv::Vec4b>(i, j)[3]);
		// 	}
		// }
	}

	void Gene::Save(const std::string name) const
	{
		// Create the output string
		std::string outputName = "engine-output/" + name;

		// Create the file stream
		SkFILEWStream file(outputName.c_str());

		// Save the bitmap to the file
		SkEncodeImage(&file, this->bitmap, SkEncodedImageFormat::kPNG, 100);
	}

	int Gene::GetFitness() const
	{
		return this->fitness;
	}

	bool Gene::operator < (const Gene& gene) const
	{
		return this->fitness < gene.GetFitness();
	}

	bool Gene::operator > (const Gene& gene) const
	{
		return this->fitness > gene.GetFitness();
	}
}