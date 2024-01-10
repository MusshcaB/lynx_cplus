// python_cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// matrice biblio
//https://github.com/cdelv/Vector3D
/*https://www.learncpp.com/
https://stackoverflow.com/questions/53639591/implementing-a-3d-matrix-in-c-using-nested-stdvector
*/
#include "trace_generation.h" 
#include "plot.h"
#include <list>
#include "libxl.h"
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <string>


typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;


using namespace libxl;
using namespace std::chrono;
using namespace std;

v1d &lireSpectre(v1d &spectre_blanc);
int generateHadamard(v2d &matrice_re);

void displayHadamardMatrix(cv::Mat hadamardPattern)
{
	cv::imshow("Hadamard Matrix in Main", hadamardPattern);
	cv::waitKey(0);
}

int main() {
	std::vector<double> wavelengths;
	for (double wavelength = 400.0; wavelength <= 700.0; ++wavelength)
	{
		double i = 400.0 + (wavelength / 299.0) * 300.0; // Échelle linéaire entre 400 et 700 nm

		wavelengths.push_back(1.0); // Spectre blanc, chaque longueur d'onde a la même intensité
	}
	//std::vector<std::vector<double>> matrice_re(512, std::vector<double>(512, 0));
	//v2d matrice_re; 
	//int taille_mat;
	//taille_mat = generateHadamard(matrice_re);
	//cv::Mat hadamarPattern(taille_mat, taille_mat, CV_8U);

	//for (int i = 0; i < taille_mat; i++)
	//{
	//	for (int j = 0; j < taille_mat; j++)
	//	{
	//		//cout << matrice_re[i][j];
	//		hadamarPattern.at<uchar>(i, j) = matrice_re[i][j] * 255;
	//	}
	//}
	//displayHadamardMatrix(hadamarPattern);


	// Créer un générateur hyperspectral
	HyperspectralGenerator generator(512, 512, wavelengths);

	// Afficher l'image greyscale
	generator.displayGreyscaleImage();

	// Afficher l'image hyperspectrale (une seule longueur d'onde)
	generator.displayHyperspectralImage(20);
	// Afficher l'image hyperspectrale modulée (une seule longueur d'onde, par exemple, la première)
	//generator.displayModulatedHyperspectralImage(20);

	return 0;
}

//
//int main()
//{
//	// variable declaration
//	uint8_t num_ligne = 0;
//	std::string ligne;
//	std::vector<double> stores;
//	double matrice_scr = 0.0;
//	std::ifstream fichier("cat_scr_npy", std::ios::out);
//
//
//	/*
//	 // image source
//	*/
//	// read an image and convert to greyscale
//	cv::Mat image = cv::imread("source_512x512.png");
//	if (image.empty())
//	{
//		std::cerr << "error to open file" << std::endl;
//	}
//	// convert to greyscale 
//	cv::Mat image2d;
//	cv::cvtColor(image, image2d, cv::COLOR_BGR2GRAY);
//	/*cv::imshow("original image", image2d);
//	cv::waitKey(0);*/
//
//	// transform greyscale image in matrice format to process it
//	//std::vector<std::vector<double>> image2dMatrix; 
//	v2d image2dMatrix;
//
//	for (int colonne = 0; colonne < image2d.rows; ++colonne) {
//		std::vector<double> row; 
//		for (int ligne = 0; ligne < image2d.cols; ++ligne)
//		{
//			//implicit conversion with static_cast
//			// accessing the pixel (i,j) and specifying its data type to be unsigned char
//			row.push_back(static_cast<double>(image2d.at<uchar>(colonne, ligne)));
//		}
//		image2dMatrix.push_back(row); 
//	}
//	std::cout << "fin transformation source" << std::endl; 
//	std::cout << "source size : \t" << image2dMatrix.size() << std::endl;;
//
//	// Print the values of the imageArray
//	/*const int N = image2d.cols;  // Assuming N is the number of columns
//	std::cout << "Image Array:" << std::endl;
//	for (int i = 0; i < image2d.rows; ++i) {
//		for (int j = 0; j < image2d.cols; ++j) {
//			std::cout << image2dMatrix[i][j] << "\t"; // Adjust spacing as needed
//		}
//		std::cout << std::endl;
//	}
//	*/
//
//	// generation spectre TODO in function 
//	/*1 - direct generation
//	  2- generation by Vero excel file
//	*/
//	v1d spectre_b;
//	v1d *spectre_blanc = &lireSpectre(spectre_b);
//	spectre_b = *spectre_blanc; 
//	std::cout << "fin extraction spectre" << std::endl;
//	std::cout << "spectre blanc size : \t" << spectre_b.size();
//	std::cout << std::endl;
//
//	
//	
//	// hypercube
//	// in : image2dMatrix, spectre_blanc
//	// out : imSpectrale
//	v3d imSpectrale; 
//	v2d spectre = { {spectre_b},{0} };
//	imSpectrale.emplace_back(image2dMatrix);
//	imSpectrale.emplace_back(spectre_b);
//	std::cout << imSpectrale.size() << std::endl;
//
//
//	/*for (int colonne = 0; colonne < image2d.rows; ++colonne) {
//		std::vector<double> row;
//		for (int ligne = 0; ligne < image2d.cols; ++ligne)
//		{
//	for (int i = 0; i < image2d.rows; ++i) {
//		v2d tempoVec; a
//		for (int j = 0; j < image2d.cols; ++j) {
//
//			for (int q = 0; q < spectre_blanc.size(); ++q) {
//
//			}
//		}
//		imSpectrale.push_back(tempoVec);
//	}*/
//	
//
//
//#ifdef DEBUG
//	// class instance
//	trace_generation Trace128;
//	std::cout << Trace128.getM() << std::endl;
//	//test17(); 
//	BMP bmp(1024, 1024);
//	//bmp.fill_region(50, 20, 100, 200, 0, 0, 255, 255);
//	bmp.draw_rectangle(0, 0, 900, 1000, 0, 255, 255, 900, 1000);
//	bmp.write("img_test1.bmp");
//	// read the file 
//	if (!fichier.is_open()) {
//		printf("failed to open\n");
//		return EXIT_FAILURE;
//	}
//	while (fichier >> matrice_scr) {
//		stores.push_back(matrice_scr);
//	}
//	// taille matrice par rapport à la taille du vector
//	int N = int(sqrt(stores.size())); 
//	double *matrice_recons = new double[N * N * sizeof(double)]();
//	
//
//	for (int ligne_ = 0; ligne_ < N;ligne_++) {
//		for (int colonne_ = 0; colonne_ < N; colonne_++)
//		{
//			int index = ligne_ * N + colonne_;
//			std::vector<double>::iterator iter = stores.begin();
//			std::advance(iter, index);
//			matrice_recons[index] = *iter;
//			
//		}
//	}
///*	cv::Mat test(512, 512, CV_8UC3, cv::Scalar(255, 255, 255));
//	cv::circle(test, cv::Point(256, 256), 200, cv::Scalar(0, 0, 0), cv::FILLED);
//	cv::namedWindow("Generated Image", cv::WINDOW_NORMAL);
//	cv::imshow("Generated Image", test);
//	cv::waitKey(0);*/
//
//	cv::Mat matrice_plot(N, N, CV_32F, matrice_recons);
//	cv::namedWindow("Generated Image", cv::WINDOW_NORMAL);
//	cv::imshow("Generated Image", matrice_plot);
//	cv::waitKey(0);
//
//	//print_matrice(matrice_recons, N/2); 
//#endif // DEBUG
//
//	return EXIT_SUCCESS;
//}


v1d &lireSpectre(v1d &spectre_blanc)
{
	Book* book = xlCreateXMLBook();

	if (book->load(L"Densites_spectrales_Vero.xlsx"))
	{
		Sheet* sheet = book->getSheet(0);
		// take only the first column
		int col = sheet->firstCol() + 1;
		int offset_start = 21;
		for (int row = sheet->firstRow() + 22; row < sheet->lastRow() - 79;++row) {
			CellType cellType = sheet->cellType(row, col);
			//std::cout << "(" << row+378 << "," << col << ")=";
			//std::cout << cellType << std::endl;
			switch (cellType)
			{
			case CELLTYPE_EMPTY: //std::wcout << "[empty]";
				break;
			case CELLTYPE_NUMBER:
			{
				double cellule = sheet->readNum(row, col);
				//std::wcout << cellule;
				//std::cout << std::endl;
				spectre_blanc.push_back(cellule);
				break;
			}
			case CELLTYPE_BLANK: std::wcout << "[blank]";
				break;
			case CELLTYPE_ERROR: std::wcout << "[error]";
				break;
			default:
				break;
			}
			//std::cout << std::endl;
		}
	}
	else {
		std::cerr << "error opened file" << std::endl;
	}
	/*
	//------>	Plot le spectre
	*/

	cv::Mat specter_draw(spectre_blanc);
	//Ptr<plot::Plot2d> plot = plot::Plot2d::create(specter_draw);

	cv::Ptr<cv::plot::Plot2d> plot_ = cv::plot::Plot2d::create(specter_draw);
	cv::Mat plot_result;
	// Set plot size
	plot_->setPlotSize(800, 600);

	// Show the plot
	plot_->render(plot_result);
	cv::flip(plot_result, plot_result, 0);

	cv::imshow("Vector Plotting", plot_result);
	cv::waitKey(0);

	book->release();

	// print spectre 
	/*for (int i = 0; i < spectre_blanc.size();++i) {
		std::wcout << spectre_blanc[i] << " ";
	}
	std::cout << std::endl;*/

	return spectre_blanc;
}

int generateHadamard(v2d & matrice_re)
{
	uint8_t oct = 8;
	uint16_t pattern;
	bool pixel;
	list<uint32_t> bin_image;
	string line;
	uint16_t current_line = 0;
	pattern = 150;

	ifstream hadamard_file("save_hadamard_512", ios::in);

	if (hadamard_file.fail())
	{
		cout << "Erreur lors de l'ouverture du fichier." << endl;
		
	}
	// recupération du pattern et stockage dans line
	while (!hadamard_file.eof())
	{
		current_line++;
		getline(hadamard_file, line);
		if (current_line == pattern) break;
	}
	int taille_pattern = line.length(); 
	cout << taille_pattern << endl;

	// reconstruction  de la matrice du pattern correspondant
	for (char & c : line)
	{
		if (c != 0x0A)
		{	// decomposition octet par octet
			for (auto i = 0; i < oct; i++)
			{
				pixel = (c >> i) & 1;
				bin_image.push_back(pixel);
			}
		}
	}
	int tempo = taille_pattern / (oct * oct)*oct;
	/*for (auto i:bin_image)
	{
		cout << i ;
	}*/
	//put in matrix
	matrice_re.resize(512, std::vector<double>(512, 0));

	for (auto i = 0; i < 512; i++)
	{
		for (auto j = 0; j < 512; j++)
		{
			//auto index = tempo *i +j; 
			auto index = std::next(bin_image.begin(), (i *512 + j));
			if (*index < bin_image.size()) {
				matrice_re[i][j] = *index;
			}
			//auto it1 = std::next(bin_image.begin(), (i *tempo + j));
			//matrice_re[i][j] = *it1;
		}
	}

	return 512;

}