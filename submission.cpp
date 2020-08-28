#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int
main()
{

    string filename = "./The_West_Wind.jpg";
    Mat image = imread(filename);
    int width = image.size().width;
    int height = image.size().height;
    vector<int> hueCount[180];

    for (int i=0; i < 180; i++)
    {
        hueCount[i].push_back(0);
    }

    cout << hueCount << endl;

    Mat hsv;
    cvtColor(image, hsv, COLOR_BGR2HSV);

    namedWindow("image", WINDOW_NORMAL);
    resizeWindow("image", width/8, height/8);

    imshow("image", hsv);
    waitKey(0);
    return 0;
}