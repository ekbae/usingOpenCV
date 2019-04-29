// 2. Open Video 

#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"

using namespace cv;

int main()
{
	VideoCapture Cap("Sample.avi");
	if (!Cap.isOpened()) return -1; // 불러오기 실패

	Mat img;
	while (1) {
		Cap >> img;
		if (img.empty()) break;
		imshow("video", img);
		if (waitKey(10) == 27) break; //ESC
	}
	destroyAllWindows();

	return 0;
}