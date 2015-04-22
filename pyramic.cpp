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


// main
// preconditions: appropriate images exist in code directory
// postconditions: displays the score image resulting from template matching and an
//					overlay of the template on the search image at the best matching location

int main(int argc, char* argv[]) {
    cv::Mat ref = cv::imread(argv[1]);
    cv::Mat tpl = cv::imread(argv[2]);

    if (ref.empty() || tpl.empty())
        return -1;

    cv::Mat gref, gtpl;
    cv::cvtColor(ref, gref, CV_BGR2GRAY);
    cv::cvtColor(tpl, gtpl, CV_BGR2GRAY);

    cv::Mat res(ref.rows - tpl.rows + 1, ref.cols - tpl.cols + 1, CV_32FC1);
    cv::matchTemplate(gref, gtpl, res, CV_TM_CCOEFF_NORMED);
    cv::threshold(res, res, 0.1, 1., CV_THRESH_TOZERO);

    while (true) {
        double minval, maxval, threshold = atof(argv[3]);
        cv::Point minloc, maxloc;
        cv::minMaxLoc(res, &minval, &maxval, &minloc, &maxloc);

        if (maxval >= threshold) {
            cout << "\n Template Matches with input image\n";

            cv::rectangle(
                    ref,
                    maxloc,
                    cv::Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows),
                    CV_RGB(0, 255, 0), 2
                    );
            cv::floodFill(res, maxloc, cv::Scalar(0), 0, cv::Scalar(.1), cv::Scalar(1.));
            break;
        } else {
            cout << "\nTemplate does not match with input image\n";
            break;
        }
    }

    cv::imshow("reference", ref);
    cv::waitKey();
    ref.release();
    tpl.release();
    return 0;
}