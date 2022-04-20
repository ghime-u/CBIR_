# CBIR_
Implemented image thresholding, feature detection and extraction from scratch, implemented multi-histogram matching and normalization, texture matching with different distance metrics from scratch to classify different images from a dataset of 2000 images. 
//Operating System and IDE

Windows 10

Visual Studio 2022

// Instructions:

1) There are 2 cpp files, CSVwrite and CSVread, please run the CSVwrite file first, it will create a CSV file in the directory path.

2) Enter the directory path in command line argument of the project, and keep the image you want to compare at the start of the directory. e.g rename pic0024 to apic0024

3) The CSV file with all 5 task for all 1200 images takes around 30 minutes to write, either input a directory with 100 images or less, or change the program according to specific task. if the program is being checked for first task, make sure all other pushback values are zero and other histogram functions are commented out.

e.g. for baseline matching of all 1200 images, comment out all other histogram fucntions, and make sure the vectos hm, spatial,task4, task5 are getting atleast 1 float value.

I have been trying to reduce the time to write the file with all 5 tasks, I apologize for the inconvinience.

4) Run CSVread.cpp once the feature.csv is written, make sure they are in the same path and entire CSVwrite is commented as to avoid having 2 main fucntion in one project.

5) the command line will ask you to enter the number of images to be returned and a key to apply the specific task.



keys :

b - baseline matching

h - task 2

s - task 3

t - task 4

0 - task 5

any other key will terminate the program.



6) for task 5 create a dataset of some images containing the book in image 0404 and random images.

