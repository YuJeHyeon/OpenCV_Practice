double HoughT(Mat img1, Mat img2)
{
    int i, j;
    double RhoAng[rho][360] = {
        0,
    };

    for (int x = 0; x < ang; x++)
    {
        hough_sin[x] = sin(x * conv_deg);
        hough_cos[x] = cos(x * conv_deg);
    }
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (img1.at<uchar>(y, x) > 128)
            {
                for (int theta = 0; theta < ang; theta++)
                {
                    mh = x * hough_sin[theta] + y * hough_cos[theta];
                    if (mh >= 0 && mh < rho)
                    {
                        RhoAng[mh][theta]++;
                    }
                }
            }
        }
    }
    for (int mh = 0; mh < rho; mh++)
    {
        for (int theta = 0; theta < ang; theta++)
        {
            if (RhoAng[mh][theta] > 100)
            {
                for (int i = 0; i < width; i++)
                {
                    j = (int)((mh - i * hough_sin[theta]) / hough_cos[theta]);

                    if (j < height && j >= 0)
                    {
                        img2.at<uchar>(j, i) = 255;
                    }
                }
                for (int j = 0; j < height; j++)
                {
                    i = (int)((mh - j * hough_cos[theta]) / hough_sin[theta]);

                    if (i < width && i >= 0)
                    {

                        img2.at<uchar>(j, i) = 255;
                    }
                }
            }
        }
    }
}