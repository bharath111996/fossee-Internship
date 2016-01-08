# fossee-Internship
	contact
	-------
	Name  : S.K.Bharath
	Institute : IITM
	email : bharath111996@gmail.com	
	ph no : 9840487311


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




	compilation
	-----------
	g++ `pkg-config --cflags opencv` stdfilt.cpp `pkg-config --libs opencv` -o stdfilt
	
	execution
	---------
	./stdfilt  <img_name>



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



	compilation
	-----------
	g++ `pkg-config --cflags opencv` imquantize.cpp `pkg-config --libs opencv` -o imquantize
	
	execution
	---------
	./imquantize  <img_name> q1 q2 q3 q4 q5 q6 q7 
	^where q1 q2 q3 etc are quantization levels. There is no limit on no of levels	 
