for (int y = 0; y < img.rows; y++)    
{        
    for (int x = 0; x < img.cols; x++)        
    {            
        if (img_gray.at<uchar>(y, x) == 0)            
        {                
            v_count++;            
        }        
    }    
}    
sumARA[0] = v_count / (float)image_size;    
sumAVG[0] = 0;
for (int t = 0; t < 256; t++)    
{        
    total_avg += t * (histogram[t] / (float)image_size);    
}
for (int t = 1; t < 256; t++)    
{        
    sumARA[t] = sumARA[t - 1] + (histogram[t] / (float)image_size);        
    sumAVG[t] = ((sumARA[t - 1] * sumAVG[t - 1]) + ((t * histogram[t]) / (float)image_size)) / sumARA[t];    
}    
for (int t = 0; t < 256; t++)    
{   
    sumAVG2[t] = (total_avg - (sumAVG[t] * sumARA[t])) / (1 - sumARA[t]);
    v_between[t] = (sumARA[t] * (1 - sumARA[t])) * ((sumAVG[t] - sumAVG2[t]) * (sumAVG[t] - sumAVG2[t]));   
}

    
float v_max = 0;    int otsu_thres = 0;    
for (int t = 0; t < 256; t++)    
{        
    if (v_max < v_between[t])        
    {            
        v_max = v_between[t];
        otsu_thres = t;       
    }    
}
int otsu_value = 0;
for (int y = 0; y < img.rows; y++)    
{        
    for (int x = 0; x < img.cols; x++)        
    {            
        otsu_value = img_gray.at<uchar>(y, x);            
        if (otsu_value <= otsu_thres)            
        {                
            img_otsu.at<uchar>(y, x) = 0;            
        }            
        if (otsu_value > otsu_thres)            
        {                
            img_otsu.at<uchar>(y, x) = 255;            
        }        
    }    
}