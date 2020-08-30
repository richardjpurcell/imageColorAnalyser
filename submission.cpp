#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void
CountImage(vector<Mat> I, Vec3f* hc)
{
    CV_Assert(I[0].depth() == CV_8U);
    int nRows = I[0].rows;
    int nCols = I[0].cols;

    if (I[0].isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    int i, j;
    uchar* h; 
    uchar* s;
    uchar* v;
    float satAvg = 0;
    float valAvg = 0;
    int N = 1;

    for(i =0; i < nRows; ++i)
    {
        h = I[0].ptr<uchar>(i);
        s = I[1].ptr<uchar>(i);
        v = I[2].ptr<uchar>(i);
        for (j = 0; j < nCols; ++j)
        {
            //count hue
            hc[h[j]][0] += 1;
            //find satAvg for this hue
            satAvg = hc[h[j]][1];
            satAvg -= satAvg/N;
            hc[h[j]][1] = satAvg + (((float)s[j])- satAvg)/(N+1);
            //find valAvg for this hue
            valAvg = hc[h[j]][2];
            valAvg -= valAvg/N;
            hc[h[j]][2] = valAvg + (((float)v[j])- satAvg)/(N+1);
            N++;
        }
    }
}

int
main()
{

    string filename = "./The_West_Wind.jpg";
    Mat image = imread(filename);

    resize(image, image, Size(image.size().width/4, image.size().height/4));

    int width = image.size().width;
    int height = image.size().height;

    cout << width << " " << height << endl;

    Vec3f hueCount[180];

    for (int i=0; i < 180; i++)
    {
        hueCount[i][0] = 0;
        hueCount[i][1] = 0;
        hueCount[i][2] = 0;
    }



    Mat hsvImage;
    cvtColor(image, hsvImage, COLOR_BGR2HSV);

    vector<Mat> hsvChannels(3);
    split(hsvImage, hsvChannels);

    CountImage(hsvChannels, hueCount);

    for (int i=0; i<180; i++)
    {
        cout << hueCount[i] << endl;
        //cout << hsvChannels[1] << endl;
    }

    namedWindow("image", WINDOW_NORMAL);
    //resizeWindow("image", width/8, height/8);

    imshow("image", hsvImage);
    waitKey(0);
    return 0;
}