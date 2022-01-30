// vidDisplay.cpp

#include <iostream>
#include <opencv2/opencv.hpp>

#include "filters.hpp"

using namespace cv;
using namespace filters;

enum mode {
    ORIGINAL = 1,
    GREY = 2,
    CUSTOM_GREY = 3,
    GAUSSIAN = 4,
    SOBEL_X = 5,
    SOBEL_Y = 6,
} MODE;

int main(int argc, char *argv[]) {
    cv::VideoCapture *capdev;

    // open the video device
    capdev = new cv::VideoCapture(0);
    if (!capdev->isOpened()) {
        printf("Unable to open video device\n");
        return (-1);
    }

    // get some properties of the image
    cv::Size refS((int)capdev->get(cv::CAP_PROP_FRAME_WIDTH),
                  (int)capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
    printf("Expected size: %d %d\n", refS.width, refS.height);

    cv::namedWindow("Video", 1);  // identifies a window

    cv::Mat frame;
    // must pass capdev to frame, to get updated frame size for initiating other Mat as below
    *capdev >> frame;

    cv::Mat dst;
    cv::Mat sol16(frame.rows, frame.cols, CV_16SC3);

    for (;;) {
        *capdev >> frame;  // get a new frame from the camera, treat as a stream
        if (frame.empty()) {
            printf("frame is empty\n");
            break;
        }

        // see if there is a waiting keystroke
        char key = cv::waitKey(10);

        // break the loop
        if (key == 'q') {
            break;
        }

        // assign color mode
        switch (key) {
        case 'o':
            MODE = ORIGINAL;
            break;
        case 'g':
            MODE = GREY;
            break;
        case 'h':
            MODE = CUSTOM_GREY;
            break;
        case 'b':
            MODE = GAUSSIAN;
            break;
        case 'x':
            MODE = SOBEL_X;
            break;
        case 'y':
            MODE = SOBEL_Y;
            break;
        }

        // render image based on color mode
        switch (MODE) {
        case ORIGINAL:
            cv::imshow("Video", frame);
            break;
        case GREY:
            cv::cvtColor(frame, dst, COLOR_RGBA2GRAY, 0);
            cv::imshow("Video", dst);
            break;
        case CUSTOM_GREY:
            filters::greyscale(frame, dst);
            cv::imshow("Video", dst);
            break;
        case GAUSSIAN:
            filters::blur5x5(frame, dst);
            cv::imshow("Video", dst);
            break;
        case SOBEL_X:
            filters::sobelX3x3(frame, sol16);
            cv::convertScaleAbs(sol16, dst, 1, 0);  // convert from CV_16S3C to CV_8UC3 for Mat
            cv::imshow("Video", dst);
            break;
        case SOBEL_Y:
            filters::sobelY3x3(frame, sol16);
            cv::convertScaleAbs(sol16, dst, 1, 0);  // convert from CV_16S3C to CV_8UC3 for Mat
            cv::imshow("Video", dst);
            break;
        default:
            cv::imshow("Video", frame);
            break;
        }
    }

    delete capdev;
    return (0);
}