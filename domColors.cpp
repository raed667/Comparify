/**
 * File : domColors.cpp
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
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {
	/**
	 * Indicates the power of the relation between the 2 pictures in param.
	 * It goes from 0 to 1.
	 */
	double relation = 0;

	if (argc != 3) {
		printf("argument error\n");
		return 0;
	}

	Mat img1, img2;
	Mat hsv_half_down;

	Mat image1 = cv::imread(argv[1], 1);
	Mat image2 = cv::imread(argv[2], 1);

	cvtColor(image1, img1, COLOR_BGR2HSV);
	cvtColor(image2, img2, COLOR_BGR2HSV);

/// Using 50 bins for hue and 60 for saturation
	int h_bins = 50;
	int s_bins = 60;
	int histSize[] = { h_bins, s_bins };

// hue varies from 0 to 179, saturation from 0 to 255
	float h_ranges[] = { 0, 180 };
	float s_ranges[] = { 0, 256 };

	const float* ranges[] = { h_ranges, s_ranges };

// Use the o-th and 1-st channels
	int channels[] = { 0, 1, 2 };

	MatND hist_base;
	MatND hist_img2;

/// Calculate the histograms for the HSV images
	calcHist(&img1, 1, channels, Mat(), hist_base, 2, histSize, ranges, true,
			false);
	normalize(hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&img2, 1, channels, Mat(), hist_img2, 2, histSize, ranges, true,
			false);
	normalize(hist_img2, hist_img2, 0, 1, NORM_MINMAX, -1, Mat());

	int compare_method = CV_COMP_CORREL;
	double base_base = compareHist(hist_base, hist_base, compare_method);
	double base_img2 = compareHist(hist_base, hist_img2, compare_method);
	relation = (base_img2 / base_base);
	/*printf("[CV_COMP_CORREL] Perfect [%f] | Img2 [%f] \n", base_base,
			base_img2);

	printf("Done \n");*/

	/**
	 * This print should be the last execution before exiting.
	 * Do not change the format unless to follow a change of version.
	 */
	printf("%1.2f",base_img2);
	return 0;
}

