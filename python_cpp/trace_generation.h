#ifndef TRACE_GENERATION
#define TRACE_GENERATION

//include
#include <opencv2/opencv.hpp>

#include <string>
#include <math.h>
#include <vector>
#include <fstream>
#include <iostream>


// define
#define SIZE_MAT 64
//#include "bitmap_image.hpp"
//#include "cpp-bmp-images.h"
//#define DEBUG 



//TODO  : classe génération trace
/*
- Paramètres de configuration
- Image spectrale
- Modulation( take pattern from file)
- Dispersion
*/
typedef std::vector<double> v1d;
typedef std::vector<v1d> v2d;
typedef std::vector<v2d> v3d;

class trace_generation
{
public:
	trace_generation();
	trace_generation(uint16_t M , uint8_t dispersion , uint8_t lambda ); 
	uint16_t getM() const; 
	uint8_t getDisp() const; // ou mettre en #define
	uint8_t getLambda() const; 

	void setM(uint16_t M); 
	void setDisp(uint8_t disp);
	void setLambda(uint8_t lambda); 
	
	// functions before modulation
	void source(uint16_t M); 

/*Paramètres de configuration
 Source : M*M
 Dispersion : 0
 spectre : from Vero file, carré
 Bande spectrale : 400-700 -> lambda

*/
private:
	uint16_t m_M;
	uint8_t m_disp; 
	uint8_t m_lambda;
	//std::ifstream m_fileSpectre("cat_scr_npy", std::ios::out);  // remplace by Vero_file
};


class HyperspectralGenerator {
public:
	// Constructeur
	HyperspectralGenerator(int width, int height, const std::vector<double> &wavelengths)
		: width(width), height(height), wavelengths(wavelengths)
	{
		std::srand(std::time(0));

		generateGreyscaleImage();
		createHyperspectralImage();

		// Generate Hadamard pattern
		hadamardPattern = generateHadamardPattern(greyscaleImage.rows, greyscaleImage.cols);

		modulateHyperspectralImage();

		// Display the Hadamard matrix
		//displayHadamardMatrixIn();
	}

	// Afficher l'image greyscale avec OpenCV
	void displayGreyscaleImage() const {
		cv::imshow("Image Greyscale", greyscaleImage);
		cv::waitKey(0);
	}

	// Afficher l'image hyperspectrale (une seule longueur d'onde) avec OpenCV
	void displayHyperspectralImage(int wavelengthIndex) const {
		cv::imshow("Image Hyperspectrale (1 Longueur d'onde)", hyperspectralImage[wavelengthIndex]);
		cv::waitKey(0);
	}

	// Afficher l'image hyperspectrale modulée avec OpenCV
	void displayModulatedHyperspectralImage(int wavelengthIndex) const
	{
		cv::imshow("Image Hyperspectrale Modulée", modulatedHyperspectralImage[wavelengthIndex]);
		cv::waitKey(0);
	}


private:
	int width;
	int height;
	std::vector<double> wavelengths;
	cv::Mat greyscaleImage;
	std::vector<cv::Mat> hyperspectralImage;
	std::vector<cv::Mat> modulatedHyperspectralImage;
	cv::Mat hadamardPattern;

	// Générer une image greyscale aléatoire
	void generateGreyscaleImage() {
		/*
		 image source
		 read an image and convert to greyscale
		*/
		cv::Mat image2d = cv::imread("source_512x512.png");
		if (image2d.empty())
		{
			std::cerr << "error to open file" << std::endl;
		}
		// convert to greyscale 
		cv::cvtColor(image2d, greyscaleImage, cv::COLOR_BGR2GRAY);

		cv::Size size_image = greyscaleImage.size();
		std::cout << "size of source greyscale : " << size_image << std::endl;
	}

	// Créer l'image hyperspectrale en 3D à partir de l'image greyscale
	void createHyperspectralImage()
	{
		hyperspectralImage.resize(wavelengths.size());


		// Remplir chaque canal de longueur d'onde avec la valeur greyscale
		for (int wavelengthIndex = 0; wavelengthIndex < wavelengths.size(); ++wavelengthIndex)
		{
			hyperspectralImage[wavelengthIndex] = greyscaleImage.clone();
			// Appliquer la longueur d'onde actuelle (échelle ou autre logique)
			// Ici, nous utilisons simplement une multiplication
			hyperspectralImage[wavelengthIndex] *= wavelengths[wavelengthIndex];
		}

		size_t size_image = hyperspectralImage.size();
		std::cout << "size of hyperspectrale mat after : " << size_image << std::endl;
	}

	// pattern
	cv::Mat generateHadamardPattern(int rows, int cols)
	{
		if ((rows & (rows - 1)) != 0 || (cols & (cols - 1)) != 0 || rows <= 0 || cols <= 0)
		{
			std::cerr << "Size must be a power of 2 and greater than 0." << std::endl;
			return cv::Mat();
		}

		cv::Mat hadamardPattern(rows, cols, CV_32F, cv::Scalar(1.0));

		for (int step = rows / 2; step >= 1; step /= 2)
		{
			for (int i = 0; i < rows; i += 2 * step)
			{
				for (int j = i; j < i + step; ++j)
				{
					hadamardPattern.at<float>(j + step, i) = -hadamardPattern.at<float>(j, i);
					hadamardPattern.at<float>(j, i + step) = hadamardPattern.at<float>(j, i);
				}
			}
		}

		hadamardPattern *= 1.0 / rows;

		return hadamardPattern;
	}

	// Moduler l'image hyperspectrale avec le motif d'Hadamard

	void modulateHyperspectralImage()
	{
		modulatedHyperspectralImage.resize(wavelengths.size());

		for (int wavelengthIndex = 0; wavelengthIndex < wavelengths.size(); ++wavelengthIndex)
		{
			// Ensure hyperspectralImage is not empty before cloning
			if (!hyperspectralImage[wavelengthIndex].empty())
			{
				// Make sure modulatedHyperspectralImage is allocated properly
				modulatedHyperspectralImage[wavelengthIndex] = cv::Mat::zeros(greyscaleImage.size(), CV_32F);

				// Ensure hadamardPattern has the same size as hyperspectralImage
				if (hadamardPattern.rows == modulatedHyperspectralImage[wavelengthIndex].rows &&
					hadamardPattern.cols == modulatedHyperspectralImage[wavelengthIndex].cols)
				{
					// Modulate each pixel with the corresponding Hadamard pattern value
					for (int i = 0; i < modulatedHyperspectralImage[wavelengthIndex].rows; ++i)
					{
						for (int j = 0; j < modulatedHyperspectralImage[wavelengthIndex].cols; ++j)
						{
							modulatedHyperspectralImage[wavelengthIndex].at<float>(i, j) =
								hyperspectralImage[wavelengthIndex].at<float>(i, j) * hadamardPattern.at<float>(i, j);
						}
					}
				}
				else
				{
					std::cerr << "Error: Hadamard pattern size does not match hyperspectral image size." << std::endl;
				}
			}
			else
			{
				std::cerr << "Error: Hyperspectral image at index " << wavelengthIndex << " is empty." << std::endl;
			}
		}
	}

	void displayHadamardMatrixIn() const
	{
		cv::imshow("Hadamard Matrix", hadamardPattern);
		cv::waitKey(0);
	}



};

// call out of the class 
void print_matrice(double *matrice_recons, int N);
void test17();



#endif // !TRACE_GENERATION


