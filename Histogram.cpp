Mat img1 = cv::imread("/home/cona/test_ws/civa2.jpg", IMREAD_GRAYSCALE);
// 입력 그레이스케일 영상의 히스토그램 계산 
int histogram[256] = {0, };   
for(int y = 0; y < img1.rows; y++)   
{        for(int x = 0; x < img1.cols; x++)        
         {            
	   int value = img_gray.at<uchar>(y,x); 	   histogram[value] += 1;        
          }    
}

//입력 그레이스케일 영상의 누적 히스토그램 계산        
int cumulative_histogram[256] = {0, };    
int sum = 0;        
for(int i = 1; i < 256; i++)    
{        sum += histogram [i];        
         cumulative_histogram[i] = sum;    
} //누적 계산 반복문

float normalized_cumulative_histogram[256] = {0.0, }; 
int image_size = img1.rows * img1.cols;    
for(int i = 0; i < 256; i++)    
{        
         normalized_cumulative_histogram[i] =            
         cumulative_histogram[i] / (float) image_size; 
}    
img_result = Mat(img1.rows, img1.cols, CV_8UC1);
int histogram2[256] = { 0, };    
for(int y = 0; y < img1.rows; y++)    
{        for(int x = 0; x < img1.cols; x++)             
         {            img_result.at<uchar>(y,x) = normalized_cumulative_histogram[img_gray.at<uchar>(y,x)] * 255;
 // 히스토그램 과정을 거친 후 이미지의 결과를 재배치 과정                   
         histogram2[img_result.at<uchar>(y,x)] += 1;
         }    
}
