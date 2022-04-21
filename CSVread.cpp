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
#include "histogram.h"
#include <map>
#pragma warning(disable : 4996) 

using namespace std;
using namespace cv;







int main(int argc, char* argv[]) {

	ofstream myFile;
	ifstream rfile;
	ifstream cfile;
	string address;
	string baseline;
	string histo;
	string spatial1;
	string task4s;
	string task5s;

	vector<float>match;
	vector<float> spatialsort;
	vector<float> task4sort;
	vector<float> task5sort;
	vector<int> sorted;
	
	
	// open the csv file
	rfile.open("feature.csv");
	// initalize a getline in while.. so that the EOF is reached
	while (getline(rfile, address, ',')) {
		
		// get all column values and store them into strings
		getline(rfile, baseline, ',');
		getline(rfile, histo, ',');
		getline(rfile, spatial1, ',');
		getline(rfile, task4s, ',');
		getline(rfile, task5s, '\n');
		// convert all strings to ints or floats and store them into specific vectors
			stringstream temp(baseline);
			int x = 0;
			temp >> x;
			sorted.push_back(x);

			stringstream temp1(histo);
			float y = 0.0;
			temp1 >> y;
			match.push_back(y);

			stringstream temp2(spatial1);

			float z = 0.0;
			temp2 >> z;
			spatialsort.push_back(z);

			float w = 0.0;
			stringstream temp3(task4s);
			temp3 >> w;
			task4sort.push_back(w);

			float u = 0.0;
			stringstream temp4(task5s);
			temp4 >> u;
			task5sort.push_back(u);
	}
	// close the file
	rfile.close();
	// sort all values in vectors
	sort(sorted.begin(), sorted.end());
	sort(match.begin(), match.end());
	sort(spatialsort.begin(), spatialsort.end());
	sort(task4sort.begin(), task4sort.end());
	sort(task5sort.begin(), task5sort.end());
	
	// declare Mats to output image
	Mat baseoutput;
	Mat histoout;
	Mat spatialout;
	Mat task4out;
	Mat task5out;
	// open the csv file to read
	cfile.open("feature.csv");
	string check;

	
	// declare a key to take user input
	char key = waitKey(0);
	int N;
	int total = sorted.size();
	// take input for number of images the user needs
	cout << "enter the the value of images to be returned, the value must be less than:" << total << endl;
	cin >> N;
	// take input for the task the user wants the machine to perform
	cout << "enter a key" << endl;
	cin >> key;
	
	int count = 0;
	// initialize while loop to perform tasks according to user input
	while (count < N) {
		for (int i = 0; i < sorted.size(); i++)
		{
			// declare strings to read from csv file again

			string address;
			string base;
			string histo;
			string spatialgrab;
			string task4string;
			string task5string;

			// get all values and store them into the above strings

			getline(cfile, address, ',');
			getline(cfile, base, ',');
			getline(cfile, histo, ',');
			getline(cfile, spatialgrab, ',');
			getline(cfile, task4string, ',');
			getline(cfile, task5string);

			// convert to int or float

			stringstream temp(base);
			stringstream temp2(histo);
			stringstream temp3(spatialgrab);
			stringstream temp4(task4string);
			stringstream temp5(task5string);

			int x = 0;
			temp >> x;
			float y = 0.0;
			temp2 >> y;
			float z = 0.0;
			temp3 >> z;
			float w = 0.0;
			temp4 >> w;
			float u = 0.0;
			temp5 >> u;
			
			// comparing the CSV file with their correspoding sorted vectors for each task and outputing the result
			if (key == 'b') {
				
				if (x < sorted[N])
				{
					baseoutput = imread(address);
					imshow("output", baseoutput);
					waitKey(0);
					count++;
					cout << address << endl;
					
				}

			}
			else if (key == 'h') {
				
				if (y < match[N]) {
					histoout = imread(address);
					imshow("output", histoout);
					waitKey(0);
					cout << address << endl;
					count++;
				}
			}
			else if (key == 's') {
				
				if (z < spatialsort[N]) {
					spatialout = imread(address);
					imshow("output", spatialout);
					waitKey(0);
					cout << address << endl;
					count++;
				}
			}
			else if (key == 't') {
				
				if (w < task4sort[N]) {
					task4out = imread(address);
					imshow("output", task4out);
					waitKey(0);
					cout << address << endl;
					count++;
				}
			}
			else if (key == 'o') {
				
					if (u < task5sort[N]) {
						task5out = imread(address);
						
						imshow("output", task5out);
						waitKey(0);
						cout << address << endl;
						count++;
					}
			}
			
		}
		if (key != 'b' || 'o' || 't' || 's' || 'o') {
		cout << "no valid key detected" << endl;
		count = N;
			}
	}
	printf("Terminating\n");
	return(0);
}
