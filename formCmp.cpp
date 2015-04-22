/**
 * File : formCmp.cpp
 * Author : Raed Chammem
 * Year : 2015
 * API Version : 1.0
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Raed Chammem
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "opencv2/core/core_c.h"
#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/contrib/contrib.hpp"



using namespace cv;
using namespace std;

double getSimilarity(const Mat A, const Mat B) {
    if (A.rows > 0 && A.rows == B.rows && A.cols > 0 && A.cols == B.cols) {
        // Calculate the L2 relative error between images.
        double errorL2 = norm(A, B, CV_L2);
        // Convert to a reasonable scale, since L2 error is summed across all pixels of the image.
        double similarity = errorL2 / (double) (A.rows * A.cols);
        return similarity;
    } else {
        return 1.0; // Return a bad value
    }
}

double getPSNR(const Mat& I1, const Mat& I2) {
    Mat s1;
    absdiff(I1, I2, s1); // |I1 - I2|
    s1.convertTo(s1, CV_32F); // cannot make a square on 8 bits
    s1 = s1.mul(s1); // |I1 - I2|^2

    Scalar s = sum(s1); // sum elements per channel

    double sse = s.val[0] + s.val[1] + s.val[2]; // sum channels

    if (sse <= 1e-10) // for small values return zero
        return 0;
    else {
        double mse = sse / (double) (I1.channels() * I1.total());
        double psnr = 10.0 * log10((255 * 255) / mse);
        return psnr;
    }
}

Scalar getMSSIM(const Mat& i1, const Mat& i2) {
    const double C1 = 6.5025, C2 = 58.5225;
    /***************************** INITS **********************************/
    int d = CV_32F;

    Mat I1, I2;
    i1.convertTo(I1, d); // cannot calculate on one byte large values
    i2.convertTo(I2, d);

    Mat I2_2 = I2.mul(I2); // I2^2
    Mat I1_2 = I1.mul(I1); // I1^2
    Mat I1_I2 = I1.mul(I2); // I1 * I2

    /***********************PRELIMINARY COMPUTING ******************************/

    Mat mu1, mu2; //
    GaussianBlur(I1, mu1, Size(11, 11), 1.5);
    GaussianBlur(I2, mu2, Size(11, 11), 1.5);

    Mat mu1_2 = mu1.mul(mu1);
    Mat mu2_2 = mu2.mul(mu2);
    Mat mu1_mu2 = mu1.mul(mu2);

    Mat sigma1_2, sigma2_2, sigma12;

    GaussianBlur(I1_2, sigma1_2, Size(11, 11), 1.5);
    sigma1_2 -= mu1_2;

    GaussianBlur(I2_2, sigma2_2, Size(11, 11), 1.5);
    sigma2_2 -= mu2_2;

    GaussianBlur(I1_I2, sigma12, Size(11, 11), 1.5);
    sigma12 -= mu1_mu2;

    ///////////////////////////////// FORMULA ////////////////////////////////
    Mat t1, t2, t3;

    t1 = 2 * mu1_mu2 + C1;
    t2 = 2 * sigma12 + C2;
    t3 = t1.mul(t2); // t3 = ((2*mu1_mu2 + C1).*(2*sigma12 + C2))

    t1 = mu1_2 + mu2_2 + C1;
    t2 = sigma1_2 + sigma2_2 + C2;
    t1 = t1.mul(t2); // t1 =((mu1_2 + mu2_2 + C1).*(sigma1_2 + sigma2_2 + C2))

    Mat ssim_map;
    divide(t3, t1, ssim_map); // ssim_map =  t3./t1;

    Scalar mssim = mean(ssim_map); // mssim = average of ssim map
    return mssim;
}

int main(int argc, char *argv[]) {

    const Mat image1 = cv::imread(argv[1], 1);
    const Mat image2 = cv::imread(argv[2], 1);

    printf("Sim %2.2f", 1 - getSimilarity(image1, image2));
    printf("\nPSNR %2.2f\n", getPSNR(image1, image2));
    Scalar mssimV = getMSSIM(image1, image2);

    double moy = ((mssimV.val[2] + mssimV.val[1] + mssimV.val[0]) / 3)*100;
    cout << "MSSIM" << moy << "%" << endl;


    return 0;
}

