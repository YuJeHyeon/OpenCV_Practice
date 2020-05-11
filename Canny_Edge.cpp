const double Rad2Degree = 57.2957951;
for (int y = 1; y < img.rows - 1; y++)
{
    for (int x = 1; x < img.cols - 1; x++)
    {
        xg = xGradient(img_gray, x, y);
        pGx[y][x] = xg;
        yg = yGradient(img_gray, x, y);
        total_sum = sqrt(pow(xg, 2) + pow(yg, 2));
        //total_sum = abs(xg) + abs(yg);
            
        total_sum = total_sum > 255 ? 255 : total_sum;
        total_sum = total_sum < 0 ? 0 : total_sum;
        img_sobel.at<uchar>(y, x) = total_sum;
        img_sobel_direction.at<uchar>(y - 1, x - 1) = atan2(yg, xg) * Rad2Degree;
    }
}
int xGradient(Mat image, int x, int y)
{
    return image.at<uchar>(y-1, x-1) + 2*image.at<uchar>(y, x-1) + image.at<uchar>(y+1, x-1) - image.at<uchar>(y-1, x+1) - 2*image.at<uchar>(y, x+1) - image.at<uchar>(y+1, x+1);
}
int yGradient(Mat image, int x, int y)
{
    return image.at<uchar>(y-1, x-1) + 2*image.at<uchar>(y-1, x) + image.at<uchar>(y-1, x+1) - image.at<uchar>(y+1, x-1) - 2*image.at<uchar>(y+1, x) - image.at<uchar>(y+1, x+1);
}
for (int y = 1; y < img.rows - 1; y++)
{
    for (int x = 1; x < img.cols - 1; x++)
    {
        if (img_sobel.at<uchar>(y, x) > t_low)
        {
            if (pGx[y][x] != 0)
            {
                if ((direction[y][x] >= -22.5f && direction[y][x] < 22.5f) || (direction[y][x] > 157.5f || direction[y][x] < -157.5f))
                {
                    direction2[y][x] = 0;
                }
                else if ((direction[y][x] >= 22.5f && direction[y][x] < 67.5f) || (direction[y][x] >= -157.5f && direction[y][x] < -112.5f))
                {
                    direction2[y][x] = 1;
                }
                else if ((direction[y][x] >= 67.5f && direction[y][x] < 112.5f) || (direction[y][x] >= -112.5f && direction[y][x] < -67.5f))
                {
                    direction2[y][x] = 2;
                }
                else 
                {
                    direction2[y][x] = 3;
                }
            }
            else
            {
                direction2[y][x] = 2;
            }
        }
               local_max = false;
        switch (direction2[y][x])
        {
        case 0:
            if ((img_sobel.at<uchar>(y, x) > img_sobel.at<uchar>(y, x - 1)) && (img_sobel.at<uchar>(y, x) > img_sobel.at<uchar>(y, x + 1)))
            {
                local_max = true;
            }
            break;
        case 1:
            if ((img_sobel.at<uchar>(y, x) > img_sobel.at<uchar>(y - 1, x - 1)) && (img_sobel.at<uchar>(y, x) > img_sobel.at<uchar>(y + 1, x + 1)))
            {
                local_max = true;
            }
            break;
        case 2:
            if ((img_sobel.at<uchar>(y, x) > img_sobel.at<uchar>(y - 1, x)) && (img_sobel.at<uchar>(y, x) > img_sobel.at<uchar>(y + 1, x)))
            {
                local_max = true;
            }
            break;
        case 3:
            if ((img_sobel.at<uchar>(y, x) > img_sobel.at<uchar>(y - 1, x + 1)) && (img_sobel.at<uchar>(y, x) > img_sobel.at<uchar>(y + 1, x - 1)))
            {
                local_max = true;
            }
            break;
        }
        if (local_max)
for (int y = 1; y < img.rows - 1; y++)
{
    for (int x = 1; x < img.cols - 1; x++)
    {
        if ((img_sobel.at<uchar>(y, x) > t_high) && (img_visited.at<uchar>(y, x) == 0))
        {
            Follow_Edge(img_sobel, img_visited, img_edge, x, y);
        }
    }
}
void Follow_Edge(Mat image1, Mat image2, Mat image3, int x, int y)
{
    image2.at<uchar>(y, x) = 1;
    image3.at<uchar>(y, x) = 255;
    for (int j = y - 1; j < y + 2; j++)
    {
        for (int i = x - 1; i < x + 2; i++)
        {
            if ((image1.at<uchar>(j, i) > t_low) && (image2.at<uchar>(j, i) == 0))
            {
                Follow_Edge(image1, image2, image3, i, j);
            }
        }
    }
}

