#include <glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"
#include <time.h>
#include <stdbool.h>


const int width = 1024;
const int height = 768;
double xpos, ypos;

float* pixels = new float[width*height * 3];

double getRandomNumber(const double min, const double max)
{
	// temp >= 0.0 && temp <= 1.0
	double temp = (double)rand() / (double)RAND_MAX;

	// temp >= min && temp <= max
	temp = min + (max - min)*temp;

	return temp;
}

bool isInsideCircle( double x, double y, int a, int b)
{
	int r = 90;
	const double f = (x - a)*(x - a) + (y - b)*(y - b) - r*r;

	if (f > 0.0) return false;
	else	return true;

}


void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}

void drawLine2(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	/*double k = getRandomNumber(0.0, 100.0);*/
	
	if(i0==i1)
	{
		for (int i = j0; i <= j1; i++)
		{
		drawPixel(i0, i, red, green, blue);
		}
	}
	if(j0==j1)
		for (int i = i0; i <= i1; i++)
		{
			drawPixel(i, j0, red, green, blue);
		}
}


void basicCircles(int a , int b, float q, float w, float e)
{

	//Drawing Circles (1,1)
	int r = 90;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if ((j - b)*(j - b) + (i - a)*(i - a) <= r*r)
			{
				drawPixel(i, j, q, w, e);
			}
			if ((j - b)*(j - b) + (i - a)*(i - a) < r*r - 600)
			{
				drawPixel(i, j, 1.0f, 1.0f, 1.0f);
			}
		}
	}
	
	
}

void drawOnPixelBuffer()
{


	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background
	
	for (int a = 102; a < 919; a += 204)
	{
		basicCircles(a, 192, 1.0f, 0.0f, 0.0f);
		basicCircles(a, 576, 1.0f, 0.0f, 0.0f);
		if (isInsideCircle(xpos, ypos, a, 192) == true)
		{
			basicCircles(a, 576, 0.0f, 0.0f, 1.0f);
		}
		if (isInsideCircle(xpos, ypos, a, 576) == true)
		{
			basicCircles(a, 192, 0.0f, 0.0f, 1.0f);
		}
		
	}

	//inside circle(1,1), Crossline
	const int i0_T1 = 62, i1_T1 = 142;
	const int j0_T1 = 536, j1_T1 = 616;

	const int i0_T2 = i0_T1-1, i1_T2 = i1_T1+1;
	const int j0_T2 = j0_T1, j1_T2 = j1_T1+1;

	const int i0_T3 = i0_T1, i1_T3 = i1_T1+1;
	const int j0_T3 = j0_T1-1, j1_T3 = j1_T1;

	drawLine(i0_T1, j0_T1, i1_T1, j1_T1, 1.0f, 0.0f, 0.0f);
	drawLine(i0_T2, j0_T2, i1_T2, j1_T2, 1.0f, 0.0f, 0.0f);
	drawLine(i0_T3, j0_T3, i1_T3, j1_T3, 1.0f, 0.0f, 0.0f);

	//inside circle(1,2), Thick Small Circle
	
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if ((j - 576)*(j - 576) + (i - 306)*(i - 306) <= 30*30)
			{
				drawPixel(i, j, 1.0f, 0.0f, 0.0f);
			}
			if ((j - 576)*(j - 576) + (i - 306)*(i - 306) < 500)
			{
				drawPixel(i, j, 1.0f, 1.0f, 1.0f);
			}
		}
	}

	//inside circle(1,3), Square
	drawLine2(470, 616, 550, 616, 1.0f, 0.0f, 0.0f);
	drawLine2(550, 536, 550, 616, 1.0f, 0.0f, 0.0f);
	drawLine2(470, 536, 550, 536, 1.0f, 0.0f, 0.0f);
	drawLine2(470, 536, 470, 616, 1.0f, 0.0f, 0.0f);
	//inside circle(1,4), X word
	drawLine(664, 526, 764, 626, 1.0f, 0.0f, 0.0f);
	drawLine(664, 626, 764, 526, 1.0f, 0.0f, 0.0f);

	//inside circle(1,5), below arrow
	drawLine2(916, 536, 916, 616, 1.0f, 0.0f, 0.0f);
	drawLine(916, 536, 946, 556, 1.0f, 0.0f, 0.0f);
	drawLine(886, 556, 916, 536, 1.0f, 0.0f, 0.0f);

	//inside circle(2,1), right arrow
	drawLine2(52, 192, 152, 192, 1.0f, 0.0f, 0.0f);
	drawLine(122, 222, 152, 192, 1.0f, 0.0f, 0.0f);
	drawLine(122, 162, 152, 192, 1.0f, 0.0f, 0.0f);

	//inside circle(2,2), A word
	drawLine2(286, 192, 326, 192, 1.0f, 0.0f, 0.0f);
	drawLine(266, 152, 306, 232, 1.0f, 0.0f, 0.0f);
	drawLine(266, 153, 305, 233, 1.0f, 0.0f, 0.0f);
	drawLine(306, 232, 346, 152, 1.0f, 0.0f, 0.0f);
	drawLine(306, 233, 346, 153, 1.0f, 0.0f, 0.0f);

	//inside circle(2,3), L small word
	drawLine2(510, 152, 510, 222, 1.0f, 0.0f, 0.0f);

	//inside circle(2,4), left arrow
	drawLine2(664, 192, 764, 192, 1.0f, 0.0f, 0.0f);
	drawLine(664, 192, 694, 222, 1.0f, 0.0f, 0.0f);
	drawLine(664, 192, 694, 162, 1.0f, 0.0f, 0.0f);

	//inside circle(2,5), upward arrow
	drawLine2(916, 152, 916, 232, 1.0f, 0.0f, 0.0f);
	drawLine(916, 232, 946, 202, 1.0f, 0.0f, 0.0f);
	drawLine(886, 202, 916, 232, 1.0f, 0.0f, 0.0f);
}



int main(void)
{
	GLFWwindow* window;

	

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop unt il the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);
		glfwGetCursorPos(window, &xpos, &ypos);

		drawOnPixelBuffer();

		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	delete[] pixels;

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}