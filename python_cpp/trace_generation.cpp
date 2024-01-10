#include "trace_generation.h"

trace_generation::trace_generation():
	m_M(128), m_disp(uint8_t(0)), m_lambda(uint8_t(400))
{
}
// constructeur pour parametrer les valeurs
trace_generation::trace_generation(uint16_t M, uint8_t dispersion, uint8_t lambda) :
	m_M(M), m_disp(dispersion), m_lambda(lambda)
{
}

//return and set value of attributes
uint16_t trace_generation::getM() const{ return m_M;}
uint8_t trace_generation::getDisp() const { return m_disp;}
uint8_t trace_generation::getLambda() const { return m_lambda;}
void trace_generation::setM(uint16_t M) { m_M = M; }
void trace_generation::setDisp(uint8_t disp) { m_disp = disp; }
void trace_generation::setLambda(uint8_t lambda) { m_lambda = lambda; }





// functions out of the class
void print_matrice(double *matrice_recons, int N) {

	for (int ligne_ = 0; ligne_ < N;ligne_++) {
		for (int colonne_ = 0; colonne_ < N; colonne_++)
		{
			int index = ligne_ * N + colonne_;
			std::cout << matrice_recons[index] << "";
		}
		std::cout << std::endl;
	}
}



// draw an image using a specific library
/*
void test17()
{
	bitmap_image image(1024, 1024);

	// set background to orange
	image.set_all_channels(0, 0, 0);

	image_drawer draw(image);

	draw.pen_width(256);
	draw.pen_color(255, 255, 255);
	draw.circle(image.width() / 2, image.height() / 2, 256);
	image.save_image("output1.bmp");

}*/