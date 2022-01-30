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
    cv::Mat dst;

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
        default:
            cv::imshow("Video", frame);
            break;
        }
    }

    delete capdev;
    return (0);
}