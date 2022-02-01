// vidDisplay.cpp

#include <iostream>
#include <opencv2/opencv.hpp>

#include "filters.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace filters;
using namespace std;
enum mode {
    ORIGINAL = 1,
    GREY = 2,
    CUSTOM_GREY = 3,
    GAUSSIAN = 4,
    SOBEL_X = 5,
    SOBEL_Y = 6,
    MAGNITUDE = 7,
    QUANTIZE = 8,
    CARTOON = 9,
    PENCIL = 10,
    CONTOUR = 11,
    EDGE = 12,
    GABOR = 13,
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

    filters::printOptions();

    cv::namedWindow("Video", 1);  // identifies a window

    cv::Mat frame;
    // must pass capdev to frame, to get updated frame size for initiating other Mat as below
    *capdev >> frame;

    cv::Mat dst(frame.rows, frame.cols, CV_8UC3);  // CV_8UC3: 3 unsigned chars for properly displaying a Mat
    cv::Mat temp1(frame.rows, frame.cols, CV_8UC3);
    cv::Mat temp2(frame.rows, frame.cols, CV_8UC3);
    cv::Mat sol16_x(frame.rows, frame.cols, CV_16SC3);  // CV_16SC3: signed short, for [-255, 255]
    cv::Mat sol16_y(frame.rows, frame.cols, CV_16SC3);

    int quantizeLevel = 15;
    int magThreshold = 18;

    dst = frame.clone();

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
        case 'm':
            MODE = MAGNITUDE;
            break;
        case 'l':
            MODE = QUANTIZE;
            quantizeLevel = 15;
            break;
        case 'c':
            MODE = CARTOON;
            quantizeLevel = 15;
            magThreshold = 18;
            break;
        case '=':
            quantizeLevel++;
            break;
        case '-':
            quantizeLevel--;
            break;
        case ']':
            magThreshold++;
            break;
        case '[':
            magThreshold--;
            break;
        case '1':
            MODE = PENCIL;
            break;
        case '2':
            MODE = CONTOUR;
            break;
        case '3':
            MODE = EDGE;
            break;
        case '4':
            MODE = GABOR;
            break;
        case 's':
            cv::imwrite("/Users/jiapei/Desktop/image.jpg", dst);
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
            filters::sobelX3x3(frame, sol16_x);
            cv::convertScaleAbs(sol16_x, dst, 1, 0);  // convert from CV_16S3C to CV_8UC3 for Mat
            cv::imshow("Video", dst);
            break;
        case SOBEL_Y:
            filters::sobelY3x3(frame, sol16_y);
            cv::convertScaleAbs(sol16_y, dst, 1, 0);  // convert from CV_16S3C to CV_8UC3 for Mat
            cv::imshow("Video", dst);
            break;
        case MAGNITUDE:
            filters::sobelX3x3(frame, sol16_x);
            filters::sobelY3x3(frame, sol16_y);
            filters::magnitude(sol16_x, sol16_y, dst);  // convert from signed short Vec3s to unsigned char Vec3b within the function
            cv::imshow("Video", dst);
            break;
        case QUANTIZE:
            filters::blurQuantize(frame, dst, quantizeLevel);
            cv::imshow("Video", dst);
            break;
        case CARTOON:
            filters::cartoon(frame, dst, quantizeLevel, magThreshold);
            cv::imshow("Video", dst);
            break;
        case PENCIL:
            cv::pencilSketch(frame, temp1, temp2, 10, 0.07f, 0.03f);
            cv::detailEnhance(temp2, dst);
            cv::imshow("Video", dst);
            break;
        case CONTOUR:
            filters::contour(frame, dst);
            cv::imshow("Video", dst);
            break;
        case EDGE:
            filters::cannyEdgeVid(frame, dst);
            cv::imshow("Video", dst);
            break;
        case GABOR:
            filters::gabor(frame, dst);
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