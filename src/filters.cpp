// filters.cpp

#include "filters.hpp"

#include <math.h>

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace filters;

int processBoundary(int total, int x) {
    if (x < 0) {
        return -x - 1;
    }
    if (x >= total) {
        return 2 * total - x - 1;
    }
    return x;
}

// Customized greyscale function that accesses G, B, R channels
// and applys the value of channel G to B and R
int filters::greyscale(cv::Mat &src, cv::Mat &dst) {
    dst = src.clone();

    for (int y = 0; y < dst.rows; y++) {
        for (int x = 0; x < dst.cols; x++) {
            cv::Vec3b t = dst.at<cv::Vec3b>(y, x);
            t.val[1] = t.val[0];
            t.val[2] = t.val[0];
            dst.at<cv::Vec3b>(y, x) = t;
        }
    }

    return 0;
}

// Apply a 5x5 Gaussian filter
int filters::blur5x5(cv::Mat &src, cv::Mat &dst) {
    Mat temp;
    float r, c;

    float co[] = {1, 2, 4, 2, 1};

    temp = src.clone();
    dst = src.clone();

    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            float sum[] = {0.0, 0.0, 0.0};

            for (int i = -2; i <= 2; i++) {
                r = processBoundary(src.rows, y - i);

                cv::Vec3b p = src.at<cv::Vec3b>(r, x);

                sum[0] += p[0] * co[i + 2];
                sum[1] += p[1] * co[i + 2];
                sum[2] += p[2] * co[i + 2];
            }

            for (int i = 0; i < 3; i++) {
                sum[i] /= 10;
            }

            cv::Vec3b t = temp.at<cv::Vec3b>(y, x);
            t.val[0] = sum[0];
            t.val[1] = sum[1];
            t.val[2] = sum[2];
            temp.at<cv::Vec3b>(y, x) = t;
        }
    }

    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            float sum[] = {0.0, 0.0, 0.0};

            for (int i = -2; i <= 2; i++) {
                c = processBoundary(src.cols, x - i);

                cv::Vec3b p = temp.at<cv::Vec3b>(y, c);

                sum[0] += p[0] * co[i + 2];
                sum[1] += p[1] * co[i + 2];
                sum[2] += p[2] * co[i + 2];
            }

            for (int i = 0; i < 3; i++) {
                sum[i] /= 10;
            }

            cv::Vec3b p = dst.at<cv::Vec3b>(y, x);
            p.val[0] = sum[0];
            p.val[1] = sum[1];
            p.val[2] = sum[2];
            dst.at<cv::Vec3b>(y, x) = p;
        }
    }

    return 0;
}

int apply_sobel(cv::Mat &src, cv::Mat &dst, double co_r[], double co_c[]) {
    cv::Mat temp(src.rows, src.cols, CV_16SC3);
    int r, c;

    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            float sum[] = {0.0, 0.0, 0.0};

            for (int i = -1; i <= 1; i++) {
                r = processBoundary(src.rows, y - i);

                cv::Vec3b p = src.at<cv::Vec3b>(r, x);

                sum[0] += p.val[0] * co_r[i + 1];
                sum[1] += p.val[1] * co_r[i + 1];
                sum[2] += p.val[2] * co_r[i + 1];
            }

            for (int i = 0; i < 3; i++) {
                sum[i] /= 1;
            }

            // NOTE: here is cv::Vec3s as type CV_16S3C, for range of -255 to 255
            // it is not CV_8UC3, unsigned char
            cv::Vec3s t = temp.at<cv::Vec3s>(y, x);
            t.val[0] = sum[0];
            t.val[1] = sum[1];
            t.val[2] = sum[2];
            temp.at<cv::Vec3s>(y, x) = t;
        }
    }

    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            float sum[] = {0.0, 0.0, 0.0};

            for (int i = -1; i <= 1; i++) {
                c = processBoundary(src.cols, x - i);

                cv::Vec3s p = temp.at<cv::Vec3s>(y, c);  // CV_16S3C

                sum[0] += p.val[0] * co_c[i + 1];
                sum[1] += p.val[1] * co_c[i + 1];
                sum[2] += p.val[2] * co_c[i + 1];
            }

            for (int i = 0; i < 3; i++) {
                sum[i] /= 4;
            }

            cv::Vec3s t = dst.at<cv::Vec3s>(y, x);
            t.val[0] = sum[0];
            t.val[1] = sum[1];
            t.val[2] = sum[2];
            dst.at<cv::Vec3s>(y, x) = t;
        }
    }

    return 0;
}

int filters::sobelX3x3(cv::Mat &src, cv::Mat &dst) {
    double co_r[] = {-1.0, 0.0, 1.0};
    double co_c[] = {1.0, 2.0, 1.0};

    apply_sobel(src, dst, co_r, co_c);
    return 0;
}

int filters::sobelY3x3(cv::Mat &src, cv::Mat &dst) {
    double co_r[] = {1.0, 2.0, 1.0};
    double co_c[] = {-1.0, 0.0, 1.0};

    apply_sobel(src, dst, co_r, co_c);
    return 0;
}

int filters::magnitude(cv::Mat &sx, cv::Mat &sy, cv::Mat &dst) {
    for (int y = 0; y < sx.rows; y++) {
        for (int x = 0; x < sy.rows; x++) {
            cv::Vec3s h = sx.at<cv::Vec3s>(y, x);
            cv::Vec3s v = sy.at<cv::Vec3s>(y, x);
            cv::Vec3b t = dst.at<cv::Vec3b>(y, x);

            for (int i = 0; i < 3; i++) {
                t.val[i] = (unsigned char)sqrt(h[i] * h[i] + v[i] * v[i]);
            }

            dst.at<cv::Vec3b>(y, x) = t;
        }
    }

    return 0;
}
