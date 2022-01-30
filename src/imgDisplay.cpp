// imgDisplay.cpp

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char const *argv[]) {
    std::cout << "OpenCV Hello the world..." << std::endl;

    Mat img = imread("../data/dog.jpg", IMREAD_COLOR);
    namedWindow("dog", WINDOW_AUTOSIZE);

    for (;;) {
        imshow("dog", img);

        int key = waitKey(0);

        if (key == 'q') {
            break;
        }
    }

    return 0;
}