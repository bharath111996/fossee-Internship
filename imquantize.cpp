/*
	imquantize implementation	
	-------------------------
	#Read the image
	#Check if the image is properly read	
	#Populate the quantization 'levels' vector based on command line inputs
	#Make sure that  none of the levels are negative
	#Call the function imquantize(Mat src ,vector<int> levels)
	#Based on no of channels(gray scale or color), find the quantization-interval to which each pixel belongs 
	#As mentioned in the matlab website, once we find the quantization interval to which a pixel belongs,
	 we can either set its value to the upper bound of that interval or lower bound. So, we have two images dst_min and dst_max 	                        	
*/

/*
	compilation
	-----------
	g++ `pkg-config --cflags opencv` imquantize.cpp `pkg-config --libs opencv` -o imquantize
	
	execution
	---------
	./imquantize  <img_name> q1 q2 q3 q4 q5 q6 q7 
	^where q1 q2 q3 etc are quantization levels. There is no limit on no of levels	 
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




Mat src , dst_min , dst_max;

vector<int> levels;

bool sortFunction (int i,int j) { return (i<j); }

void imquantize(Mat src){
	//sorting the levels
	sort (levels.begin(), levels.end(), sortFunction);		
	dst_min.create( src.size(), CV_8U );
	dst_max.create( src.size(), CV_8U );
	if(src.channels() == 1){	
		//itterate through all the pixels		
		for(int i = 0 ; i <src.rows ; i++){
			for(int  j = 0 ; j<src.cols ; j++){
				//find the quantization interval to which the pixel belongs
				int pixVal = src.at<uchar>(i,j);
				for(int l = 0 ; l < levels.size() ;  l++ ){
					if(pixVal >= levels[l] && pixVal < levels[l+1] ){
 						dst_min.at<uchar>(i,j) = levels[l];
						dst_max.at<uchar>(i,j) = levels[l+1];		
					}
				}					
			}	
		}

	}	
	// for 3 channel images
	else if(src.channels() == 3){
		//itterate through all the pixels	
		for(int i = 0 ; i <src.rows ; i++){
			for(int  j = 0 ; j<src.cols ; j++){
				//find the quantization interval to which the pixel belongs
				Vec3b pixVal = src.at<Vec3b>(i,j);
				for(int l = 0 ; l < 3 ; l++){
					for(int k = 0 ; k<levels.size()-1 ; k++){
						//checking for each interval
						if(pixVal[l] >= levels[k] && pixVal[l] <levels[k+1] ){
							dst_min.at<Vec3b>(i,j)[l] = levels[k];
							dst_max.at<Vec3b>(i,j)[l] = levels[k+1];				
						}
								
					}
				}
														
			}	
		}
	}
	else{
		printf("img.channels != 1 or != 3\n");
		exit(3);	
	}	
}

int main(int argc, char** argv){	
	//reading the image		
	src = imread(argv[1] , CV_LOAD_IMAGE_GRAYSCALE);
	
	//checking if the image is properly loaded
	if(src.empty()){
		printf("image could not be loaded\n");
		exit(1);	
	}
	//populating levels	
	levels.push_back(0);        
	for(int  i = 2 ; i < argc ; i++){
		levels.push_back(atoi(argv[i]));
		if(atoi(argv[i]) < 0){
			printf("quantization levels cannot be negative\n");
			exit(2);		
		}	
	}
	levels.push_back(255);
	
	//quantize the image
	imquantize(src);
	
	//displaying the images
	imshow("input" , src);
		
	imshow("output_min" , dst_min);
	imshow("output_max" , dst_max);		
	while(1){
		char c =waitKey(10);
		if(c == 27) break;	
	}		
	return 0;
}

