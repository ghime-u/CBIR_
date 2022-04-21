//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//#include <cstdio>
//#include <dirent.h>
//#include <cstring>
//#include <cstdlib>
//#include <vector>
//#include <iostream>
//#include <fstream>
//#include "histogram.h"
//#pragma warning(disable : 4996) 
//using namespace std;
//using namespace cv;
//
//
//int main(int argc, char* argv[]) {
//	
//		char dirname[256];
//		char buffer[256];
//
//		ofstream myFile;
//		ifstream rfile;
//		ifstream sfile;
//		ifstream cfile;
//		ifstream tfile;
//		DIR* dirp;
//		struct dirent* dp;
//		vector<string> filename;
//		vector<int> sorted;
//		vector<int> bm;
//		vector<float> hm;
//		vector<float> spatial;
//		vector<float> task4;
//		vector<float> task5;
//		Mat Template;
//		if (argc < 2)
//		{
//			printf("usage: %s<directory path>\n", argv[0]);
//			exit(-1);
//		}
//		
//		strcpy(dirname, argv[1]);
//
//
//		printf("Processing directory %s\n", dirname);
//
//		dirp = opendir(dirname);
//		if (dirp == NULL) {
//			printf("Cannot open directory %s\n", dirname);
//			exit(-1);
//		}
//		// loop over all the files in the image file listing
//		while ((dp = readdir(dirp)) != NULL) {
//			// check if the file is an image
//			if (strstr(dp->d_name, ".jpg") ||
//				strstr(dp->d_name, ".png") ||
//				strstr(dp->d_name, ".ppm") ||
//				strstr(dp->d_name, ".tif")) {
//				printf("processing image file: %s\n", dp->d_name);
//				// build the overall filename
//				strcpy(buffer, dirname);
//				strcat(buffer, "\\");
//				strcat(buffer, dp->d_name);
//				printf("full path name: %s\n", buffer);
//				filename.push_back(buffer);
//			}
//		}
//		float Sum1;
//		float Sum2;
//		Mat trial;
//
//
//
//		// writing csv
//
//		myFile.open("feature.csv");
//		for (int i = 0; i < filename.size(); i++) {
//			Mat src = imread(filename[0]);
//			Mat img = imread(filename[i]);
//
//			//baseline matching
//
//			template_detect(src, Template, 9, 9);
//			//storing into designated vector
//			bm.push_back(baseline_matching(Template, img, 9, 9));
//
//
//			//histogram
//			float sum = Histogram(src, img);
//			//storing into designated vector
//			hm.push_back(sum);
//
//			// multihistogram
//			// cropping the source image
//			template_detect(src, trial, 400, 400);
//			// BGR and HSV histogram
//			Sum1 = Histogram(trial, img);
//			Sum2 = Histogram2(trial, img);
//			/*cout << Sum2 << endl;*/
//			//weighted average as both are 3-D histogram with equal number of bins.
//			float avgsum = (Sum1 + Sum2) / 2;
//			/*cout << avgsum << endl;*/
//			//storing into designated vector
//			spatial.push_back(avgsum);
//
//			// texture Matching
//			// RGB and Texture histogram Matching
//			float rgb = Histogram(src, img);
//			float texture = HistogramTexture(src, img);
//			//weighted average as both are 3-D histogram with equal number of bins.
//			float sum4 = (rgb + texture) / 2;
//			//storing into designated vector
//			task4.push_back(sum4);
//			
//			// Object detection
//
//			float low5 = trainer(src, img);
//			// storing into designated vector
//			task5.push_back(low5);
//			
//			// storing into CSV file.
//			myFile << filename[i] << "," << bm[i] << "," << hm[i] << "," << spatial[i] << "," << task4[i] << "," << task5[i] << endl;
//		}
//		myFile.close();
//	
//	
//}