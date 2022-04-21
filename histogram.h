#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <cstdio>
#include <dirent.h>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#pragma warning(disable : 4996) 
using namespace std;
using namespace cv;

// Gradient Magnitude

int SobelX3x3(Mat& src, Mat& dst)
{
	/* Declaring a 3 channel signed Variable*/
	Mat temp;
	/* Storing image data from source to destination*/
	src.copyTo(temp);
	/*Declaring Variables for channels, rows and columns*/
	int c, i, j;
	/*looping to acces each channel in each pixel*/
	for (c = 0; c < 3; c++)
	{
		for (i = 0; i < src.rows - 1; i++)
		{
			for (j = 1; j < src.cols - 1; j++)
			{
				/* Appying [1 2 1] Filter to each column*/
				temp.at<Vec3b>(i, j)[c] = src.at<Vec3b>(i, j - 1)[c] * 1 + src.at<Vec3b>(i, j)[c] * 2 + src.at<Vec3b>(i, j + 1)[c] * 1;
				/*Dividing output by summation of all constants in filter to bring result back to 256bits*/
				temp.at<Vec3b>(i, j)[c] /= 4;
			}
		}
	}
	for (c = 0; c < 3; c++)
	{
		for (i = 1; i < src.rows - 1; i++)
		{
			for (j = 0; j < src.cols - 1; j++)
			{
				/* Appying [-1 0 1] Filter to each row and storing the final result in destination variable*/
				dst.at<Vec3b>(i, j)[c] = temp.at<Vec3b>(i - 1, j)[c] * -1 + (temp.at<Vec3b>(i, j)[c] * 0) + temp.at<Vec3b>(i + 1, j)[c];
			}
		}
	}
	return 0;
}

/*Ysobel*/
/* Same as X-sobel but applying [1 2 1] to rows instead of column and [-1 0 1] to columns*/
int SobelY3x3(Mat& src, Mat& dst)
{
	Mat temp;
	src.copyTo(temp);
	int c, i, j;
	for (c = 0; c < 3; c++)
	{
		for (i = 0; i < src.rows - 1; i++)
		{
			for (j = 1; j < src.cols - 1; j++)
			{

				temp.at<Vec3b>(i, j)[c] = src.at<Vec3b>(i, j - 1)[c] * -1 + (src.at<Vec3b>(i, j)[c] * 0) + src.at<Vec3b>(i, j + 1)[c] * 1;

			}
		}
	}
	for (c = 0; c < 3; c++)
	{
		for (i = 1; i < src.rows - 1; i++)
		{
			for (j = 0; j < src.cols - 1; j++)
			{
				dst.at<Vec3b>(i, j)[c] = temp.at<Vec3b>(i - 1, j)[c] * 1 + (temp.at<Vec3b>(i, j)[c] * 2) + temp.at<Vec3b>(i + 1, j)[c];
				temp.at<Vec3b>(i, j)[c] /= 4;
			}
		}
	}
	return 0;
}


/*Gradient Magnitude*/
int Gradient_magnitude(Mat sobelx, Mat sobely, Mat& dst) {
	/*Declaring variables for rows, columsn and channel*/
	int c, i, j;
	/*Looping to acces each channel of each pixel*/
	for (i = 0; i < dst.rows; i++) {
		for (j = 0; j < dst.cols; j++) {
			for (c = 0; c < 3; c++) {
				/*assigning each channel in destiantion new values by using the formula sqrt(xs^2+xy^2)*/
				dst.at<Vec3b>(i, j)[c] = sqrt((sobelx.at<Vec3b>(i, j)[c] * sobelx.at<Vec3b>(i, j)[c]) + (sobely.at<Vec3b>(i, j)[c] * sobely.at<Vec3b>(i, j)[c]));
			}
		}
	}
	return 0;
}


// Task 4 function


float HistogramTexture(Mat& src, Mat& dst) {
	const int Hsize = 32;  //
	int dim[3] = { Hsize, Hsize, Hsize };

	int* hist_3d = new int[Hsize * Hsize * Hsize];
	int* hist_3d_2 = new int[Hsize * Hsize * Hsize];
	// temporary 3s images to store sobelx and sobel y
	Mat tempx;
	src.copyTo(tempx);
	SobelX3x3(src, tempx);
	Mat tempy;
	src.copyTo(tempy);
	SobelY3x3(src, tempy);
	// temporary image for gradient
	Mat Gradient;
	src.copyTo(Gradient);
	Gradient_magnitude(tempx, tempy, Gradient);
	// for destination image as well
	Mat dtempx;
	dst.copyTo(dtempx);
	SobelX3x3(dst, dtempx);
	Mat dtempy;
	dst.copyTo(dtempy);
	SobelY3x3(dst, dtempy);
	// temporary image for gradient
	Mat dGradient;
	dst.copyTo(dGradient);
	Gradient_magnitude(dtempx, dtempy, dGradient);


	// histogram initialize as zero
	for (int i = 0; i < Hsize; i++) {
		for (int j = 0; j < Hsize; j++) {
			for (int k = 0; k < Hsize; k++) {
				hist_3d[i * Hsize * Hsize + j * Hsize + k] = 0;
			}
		}
	}
	for (int i = 0; i < Hsize; i++) {
		for (int j = 0; j < Hsize; j++) {
			for (int k = 0; k < Hsize; k++) {
				hist_3d_2[i * Hsize * Hsize + j * Hsize + k] = 0;
			}
		}
	}
	int divisor = 256 / Hsize;
	// histogram append  according to gradient channel
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {

			int B, G, R;
			int b, g, r;
			B = Gradient.at<Vec3b>(i, j)[0];
			G = Gradient.at<Vec3b>(i, j)[1];
			R = Gradient.at<Vec3b>(i, j)[2];


			b = B / divisor;
			g = G / divisor;
			r = R / divisor;
			hist_3d[r * Hsize * Hsize + g * Hsize + b]++;
		}
	}

	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++) {
			int B, G, R;
			int b, g, r;
			B = dGradient.at<Vec3b>(i, j)[0];
			G = dGradient.at<Vec3b>(i, j)[1];
			R = dGradient.at<Vec3b>(i, j)[2];


			b = B / divisor;
			g = G / divisor;
			r = R / divisor;
			hist_3d_2[r * Hsize * Hsize + g * Hsize + b]++;
		}

	}



	// Matching
	float S = 0;
	float Sm1 = 0;
	int Sm2 = 0;
	for (int i = 0; i < Hsize * Hsize * Hsize; i++) {
		/*int D = sqrt((int(pow(hist_3d[i] - hist_3d_2[i], 2)))/(Hsize*Hsize*Hsize));
		S += D;*/
		Sm1 += hist_3d[i];
		Sm2 += hist_3d_2[i];

		float D = 1 - min(hist_3d[i], hist_3d_2[i]);

		S += D;
	}
	float Div = max(Sm1, Sm2);
	S = (S / Div);

	delete []hist_3d;
	delete []hist_3d_2;
	return S;
}




// 3-D HSV Histogram


float Histogram2(Mat& src, Mat& dst) {
	Mat src1;
	Mat dst1;
	cvtColor(src, src1, COLOR_BGR2HSV);
	cvtColor(dst, dst1, COLOR_BGR2HSV);
	const int Hsize = 32;  //
	int dim[3] = { Hsize, Hsize };

	int* hist_2d = new int[Hsize * Hsize];
	int* hist_2d_2 = new int[Hsize * Hsize];


	for (int i = 0; i < Hsize; i++) {
		for (int j = 0; j < Hsize; j++) {
			hist_2d[i * Hsize + j] = 0;
		}
	}
	for (int i = 0; i < Hsize; i++)
	{
		for (int j = 0; j < Hsize; j++) {
			hist_2d_2[i * Hsize + j] = 0;
		}
	}
	int divisor = 256 / Hsize;
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {

			int S, V;
			int s, v;

			S = src1.at<Vec3b>(i, j)[1];
			V = src1.at<Vec3b>(i, j)[2];


			s = S / divisor;
			v = V / divisor;
			hist_2d[s * Hsize + v]++;
		}
	}

	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++) {
			int S, V;
			int s, v;

			S = dst1.at<Vec3b>(i, j)[1];
			V = dst1.at<Vec3b>(i, j)[2];


			s = S / divisor;
			v = V / divisor;

			hist_2d_2[s * Hsize + v]++;
		}

	}
	float S = 0.0;
	float Sm1 = 0.0;
	float Sm2 = 0.0;
	for (int i = 0; i < Hsize * Hsize; i++) {
		/*int D = sqrt((int(pow(hist_3d[i] - hist_3d_2[i], 2)))/(Hsize*Hsize*Hsize));
		S += D;*/
		Sm1 += hist_2d[i];
		Sm2 += hist_2d_2[i];

		float D = 1 - min(hist_2d[i], hist_2d_2[i]);

		S += D;
	}
	float Div = max(Sm1, Sm2);

	S = S / Div;
	delete []hist_2d;
	delete []hist_2d_2;
	return S;
}






// 3-D BGR histogram





float Histogram(Mat& src, Mat& dst) {
	const int Hsize = 32;  //
	int dim[3] = { Hsize, Hsize, Hsize };

	int* hist_3d = new int[Hsize * Hsize * Hsize];
	int* hist_3d_2 = new int[Hsize * Hsize * Hsize];


	for (int i = 0; i < Hsize; i++) {
		for (int j = 0; j < Hsize; j++) {
			for (int k = 0; k < Hsize; k++) {
				hist_3d[i * Hsize * Hsize + j * Hsize + k] = 0;
			}
		}
	}
	for (int i = 0; i < Hsize; i++) {
		for (int j = 0; j < Hsize; j++) {
			for (int k = 0; k < Hsize; k++) {
				hist_3d_2[i * Hsize * Hsize + j * Hsize + k] = 0;
			}
		}
	}
	int divisor = 256 / Hsize;
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {

			int B, G, R;
			int b, g, r;
			B = src.at<Vec3b>(i, j)[0];
			G = src.at<Vec3b>(i, j)[1];
			R = src.at<Vec3b>(i, j)[2];


			b = B / divisor;
			g = G / divisor;
			r = R / divisor;
			hist_3d[r * Hsize * Hsize + g * Hsize + b]++;
		}
	}

	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++) {
			int B, G, R;
			int b, g, r;
			B = dst.at<Vec3b>(i, j)[0];
			G = dst.at<Vec3b>(i, j)[1];
			R = dst.at<Vec3b>(i, j)[2];


			b = B / divisor;
			g = G / divisor;
			r = R / divisor;
			hist_3d_2[r * Hsize * Hsize + g * Hsize + b]++;
		}

	}

	float S = 0;
	int Sm1 = 0;
	int Sm2 = 0;
	for (int i = 0; i < Hsize * Hsize * Hsize; i++) {
		
		Sm1 += hist_3d[i];
		Sm2 += hist_3d_2[i];

		int D = hist_3d[i] - min(hist_3d[i], hist_3d_2[i]);
		S += D;
	}
	int Div = max(Sm1, Sm2);
	S = S / Div;

	delete []hist_3d;
	delete []hist_3d_2;

	return S;
}


//Task 1 function

int baseline_matching(Mat& src, Mat& dst, int w, int h)
{
	int sb = 0;
	int sg = 0;
	int sr = 0;
	int i, j;
	Vec3i Result = { 0,0,0 };
	int val = 0;
	int c = 0;
	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++)
		{
			int a = w / 2;
			int d = h / 2;
			int x = dst.cols / 2;
			int y = dst.rows / 2;
			// the pixel value of destination image is calculated according to the w, h provided

			Result[0] = src.at<Vec3b>(Point(i, j))[0] - dst.at<Vec3b>(Point(x - a + i, y - d + j))[0];
			Result[0] = int(pow(Result[0], 2));
			Result[1] = src.at<Vec3b>(Point(i, j))[1] - dst.at<Vec3b>(Point(x - a + i, y - d + j))[1];
			Result[1] = int(pow(Result[1], 2));

			Result[2] = src.at<Vec3b>(Point(i, j))[2] - dst.at<Vec3b>(Point(x - a + i, y - d + j))[2];
			Result[2] = int(pow(Result[2], 2));

			sb = sb + Result[0];
			sg = sg + Result[1];
			sr = sr + Result[2];
			val = (sb + sg + sr) / (3 * w * h);
		}
	}
	return(val);
}


// Function to crop a image from its center to half of w and h provided on both sides of the center
int template_detect(Mat& src, Mat& dst, int w, int h) {
	dst = Mat::zeros(w, h, CV_8UC3);
	int a = w / 2;
	int d = h / 2;
	int x = src.cols / 2;
	int y = src.rows / 2;

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			for (int c = 0; c < 3; c++) {

				dst.at<Vec3b>(Point(i, j))[c] = src.at<Vec3b>(Point(x - a + i, y - d + j))[c];
			}
		}
	}

	return 0;
}


// object detection, trainer function for task 5


float trainer(Mat& src, Mat& dst) {
	const int Hsize = 32;  //
	int dim[3] = { Hsize, Hsize, Hsize };
	Mat srcHSV;
	Mat dstHSV;
	cvtColor(src, srcHSV, COLOR_BGR2HSV);
	cvtColor(dst, dstHSV, COLOR_BGR2HSV);


	int* hist_3d = new int[Hsize * Hsize * Hsize];
	int* hist_3d_2 = new int[Hsize * Hsize * Hsize];

	// initialize histograms to zero
	for (int i = 0; i < Hsize; i++) {
		for (int j = 0; j < Hsize; j++) {
			for (int k = 0; k < Hsize; k++) {
				hist_3d[i * Hsize * Hsize + j * Hsize + k] = 0;
			}
		}
	}
	for (int i = 0; i < Hsize; i++) {
		for (int j = 0; j < Hsize; j++) {
			for (int k = 0; k < Hsize; k++) {
				hist_3d_2[i * Hsize * Hsize + j * Hsize + k] = 0;
			}
		}
	}
	int divisor = 256 / Hsize;
	//initialize two integers to zero for storing value of area of yellow colour in each image

	int area1 = 0;
	int area2 = 0;
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{

			int H, S, V;

			int icount = 0;
			int jcount = 0;

			H = srcHSV.at<Vec3b>(i, j)[0];
			S = srcHSV.at<Vec3b>(i, j)[1];
			V = srcHSV.at<Vec3b>(i, j)[2];
			// HSV min and max space for the color yellow
			if ((H > 20 && H < 30) && (S > 100 && S < 255) && (V > 100 && V < 255)) {
				H = H / divisor;
				S = S / divisor;
				V = V / divisor;
				hist_3d_2[H * Hsize * Hsize + S * Hsize + V]++;
				// area will be appended by 1, as for each count i,j will be 1 and i*j = 1
				area1++;
			}
		}
	}

	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{

			int H, S, V;


			H = dstHSV.at<Vec3b>(i, j)[0];
			S = dstHSV.at<Vec3b>(i, j)[1];
			V = dstHSV.at<Vec3b>(i, j)[2];
			// HSV min and max space for the color yellow
			if ((H > 20 && H < 30) && (S > 100 && S < 255) && (V > 100 && V < 255)) {
				H = H / divisor;
				S = S / divisor;
				V = V / divisor;
				hist_3d[H * Hsize * Hsize + S * Hsize + V]++;
				// area will be appended by 1, as for each count i,j will be 1 and i*j = 1
				area2++;
			}
		}
	}


	float S = 0;
	int Sm1 = 0;
	int Sm2 = 0;

	for (int i = 0; i < Hsize * Hsize * Hsize; i++)
	{
		// sum all the values in histogram
		Sm1 += hist_3d[i];
		Sm2 += hist_3d_2[i];
		// absolute difference as distance metric
		

	}
	S = abs(Sm2 - Sm1);
	// calculate difference between both areas
	int A = abs(area2 - area1);
	
	// delete hists
	delete[]hist_3d;
	delete[]hist_3d_2;
	// if the difference between both areas is less than some threshold, return the sum of absolute difference
	if (A < 2500) {
		return S;
	}
	// otherwise just append the sum of absolute difference and return
	else 
	{
		for (int i = 0; i < 10000; i += 15) 
		{
			return S + i;
		}
	}
}

