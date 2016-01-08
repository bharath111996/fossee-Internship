/*
	stdfilt implementation	
	-----------------------
	#reads the img
	#verifies if the img is gray scale. If not converts it to grayscale
	#prompts user for kernel size
	#pads input image with extra pixels using BORDER_REFLECTION_101 as mentioned on matlab website
	#itterates through all the pixels and populates dst img with local standard deviation values
	
	computing std-deviation
	-----------------------	
	# variance = (mean of suares) - (square of mean);
	#ex: data={1,2} mean of squares = 5/2 = 2.5 and square of mean = 1.5^2 = 2.25 and hence variance = 2.5 - 2.25 = 0.25
	#std-deviation = sqrt(variance)		 
*/

/*
	compilation
	-----------
	g++ `pkg-config --cflags opencv` stdfilt.cpp `pkg-config --libs opencv` -o stdfilt
	
	execution
	---------
	./stdfilt  <img_name>
*/

/*
	contact
	-------
	Name  : S.K.Bharath
	Institute : IITM
	email : bharath111996@gmail.com	
	ph no : 9840487311
*/

#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using namespace cv;
using namespace std;

Mat  dst;

void stdfilt(Mat src, int SIZE=3){
		Mat _src;
		dst.create( src.size(), CV_32F );
    
		//extra pixels to be added
		int pad = (SIZE - 1) /2;
		//pad input image with extra pixels	
		copyMakeBorder(src , _src , pad, pad , pad , pad ,BORDER_REFLECT_101);
		//itterate through all the pixels 		
		for(int i = pad ; i < _src.rows-pad ; i++){
			for(int j =pad ; j < _src.cols-pad ; j++){	
				float sum = 0, square_sum = 0;
				//itterate through neighbouring pixels 
				for(int k = i - pad ; k < i + pad ; k++){
					float* _srcdata = (float*)(_src.data + k*_src.step);
					for(int l = j - pad ; l < j + pad ; l++){
						sum += _srcdata[l];						
						square_sum+=_srcdata[l] * _srcdata[l];
					}				
				}
				//computing std-deviation
				float area = SIZE*SIZE;
				dst.at<float>(i-pad,j-pad) = sqrt((square_sum/area)-(sum/area)*(sum/area));				
			}		
		}
	
}

int getSize(){
	int SIZE;	
	//SIZE OF KERNEL should be even	
	do{
		printf("enter the kernel size for std deviation filter.Should be an odd number\n");
		scanf("%d" , &SIZE);
	}while(SIZE  % 2 != 1);
	
	return SIZE;	
}

int main(int argc, char** argv){
	//read the image and convert it to grayscale if it is a 3-chanel image	
	Mat src = imread(argv[1] , CV_LOAD_IMAGE_GRAYSCALE);
	
	//if source is not loaded properly
	if(src.empty()){
		printf("img could not be loaded\n");
		exit(1);	
	}
	
	//get kernel size from command line
	int SIZE = getSize();	
	
	//apply std deviation filter
	stdfilt(src , SIZE);
	
	//displaying input and output images
	imshow("input" , src);
	imshow("output" , dst);
	
	printf("press esc to exit\n");
	while(1){
		char c = waitKey(10);
		if(c == 27) break;	
	}	

	return 0;
}
