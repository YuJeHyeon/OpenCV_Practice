#include "opencv2/opencv.hpp"
#include "math.h"
#include "time.h"
#include "stdlib.h"
#include <vector>
#include <algorithm>

using namespace std;
using namespace cv;

/******* VARIABLES *******/
int width = 1000, height = 1000, thresh = 10;
int xxx1, yyy1, xxx2, yyy2;
/******* VECTOR *******/
vector<double> Errorrr;
vector<Point2f> Random;
vector<Point3f> Liner_mat;
vector<double> Count_Inlier;
vector<double> Count_Error;

/******** MAT ********/
Mat RanSac(width, height, CV_32FC3);
Mat Comp(width, height, CV_32FC3);
Mat LMS, inX, inY, Liner_Error, empty;

/******** FUNCTION ********/
void Compare(int x1, int y1, int x2, int y2, int num_dot);
void Ransac_Line();
void Loop();
void Result();
/******** MAIN ********/
int main()
{

    // RanSac = Scalar(0); // 초기화
    srand(time(NULL));
    Compare(0, 0, 1000, 1000, 400);
    Loop();
    Result();
    imshow("Image", RanSac);
    imshow("Result", Comp);
    waitKey(0);

    return 0;
}
void Loop()
{
    int sum = 0;
    while (sum < 25)
    {
        int x;
        cin >> x;
        empty.copyTo(inX);
        empty.copyTo(inY);
        Ransac_Line();
        imshow("Image", RanSac);
        imshow("Result", Comp);
        waitKey(1);
        sum += x;
    }
}
void Compare(int x1, int y1, int x2, int y2, int num_dot)
{
    // y = ax + b : 직선의 방정식
    int a, b, x, y, weight;

    a = (y2 - y1) / (x2 - x1); // 기울기
    b = -a * x1 + y1;          // y절편
    for (int i = 0; i < num_dot; i++)
    {
        x = rand() % width;
        weight = pow(-1, i) * (rand() % 40);
        y = abs(a * x + b + weight * (sqrt(a * a + 1)));
        RanSac.at<Vec3f>(x, y)[0] = 0; // 임의의 점 찍기
        RanSac.at<Vec3f>(x, y)[1] = 0;
        RanSac.at<Vec3f>(x, y)[2] = 255;
        Random.push_back(Point(x, y)); // 임의의 점 2D 벡터에 저장
    }
    line(RanSac, Point(x1, y1), Point(x2, y2), Scalar(255, 0, 0), 1); // 결과 비교 용 직선 그리기
    line(Comp, Point(x1, y1), Point(x2, y2), Scalar(255, 0, 0), 1);
}
void Ransac_Line()
{
    int num1, num2, x1, x2, y1, y2, xx1, xx2, yy1, yy2;
    float a, b, d, dd, LMS_a, LMS_b;
    float count = 0, err = 0;
    float data[2] = {
        0,
    };
    num1 = rand() % Random.size();
    x1 = Random[num1].x;
    y1 = Random[num1].y;
    xxx1 = x1;
    yyy1 = y1;
    do
    {
        num2 = rand() % Random.size();
        x2 = Random[num2].x;
        y2 = Random[num2].y;
        xxx2 = x2;
        yyy2 = y2;
    } while (num1 == num2);
    line(RanSac, Point(xxx1, yyy1), Point(xxx2, yyy2), Scalar(0, 255, 0), 1);

    a = (y2 - y1) / (x2 - x1); // 기울기
    b = -a * x1 + y1;          // y절편

    for (int i = 0; i < Random.size(); i++)
    {
        d = abs(a * Random[i].x - Random[i].y + b) / sqrt(a * a + 1);
        if (d < thresh)
        {
            data[0] = Random[i].x;
            data[1] = 1;
            Mat mX(1, 2, CV_32FC1, data);
            Mat mY(1, 1, CV_32FC1, Random[i].y);
            inX.push_back(mX);
            inY.push_back(mY);
            count++;
        }
    }
    if (count > 50)
    {

        LMS = ((inX.t() * inX).inv()) * inX.t() * inY; // 최소자승법 X(a,b) = (((A^T) *A)^(-1)) * (A^T)*B

        LMS_a = LMS.at<float>(0, 0);
        LMS_b = LMS.at<float>(1, 0);
        xx1 = width;
        yy1 = LMS_a * xx1 + LMS_b;

        xx2 = 0;
        yy2 = LMS_a * xx2 + LMS_b;
        line(RanSac, Point(xx1, yy1), Point(xx2, yy2), cv::Scalar(255, 255, 0), 1);
        line(Comp, Point(xx1, yy1), Point(xx2, yy2), cv::Scalar(255, 255, 0), 1);
        for (int i = 0; i < Random.size(); i++)
        {
            dd = (float)(abs(LMS_a * Random[i].x - Random[i].y + LMS_b)) / sqrt(LMS_a * LMS_a + 1);
            err += dd;
        }
        // Liner_mat.push_back(Point(LMS_a,LMS_b));
        Liner_mat.push_back(Point3f(LMS_a, LMS_b, count));
        Count_Error.push_back(err);
    }
}

void Result()
{
    int Best = 0, min = Count_Error[0]; //0;//, min = Errorrr[0], si = Errorrr.size();
    float a, b;
    float x1, x2, y1, y2;
    for (int i = 0; i < Count_Error.size(); i++)
    {
        if (min > Count_Error[i])
        {
            min = Count_Error[i];
            Best = i;
        }
    }

    a = Liner_mat[Best].x;
    b = Liner_mat[Best].y;

    x1 = width;
    y1 = a * x1 + b;

    x2 = 0;
    y2 = a * x2 + b;

    line(RanSac, Point(x1, y1), Point(x2, y2), cv::Scalar(255, 255, 255), 1);
    line(Comp, Point(x1, y1), Point(x2, y2), cv::Scalar(255, 255, 255), 1);
}

struct Rectangle
{
    int length;
    int width;
};