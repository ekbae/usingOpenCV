// 1-1. Open Camera

#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"

using namespace cv;

#define RECORD


int main()
{
	VideoCapture cap(0);

	if (!cap.isOpened()) return -1; // 연결실패
	//cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	//cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

#ifdef RECORD
	double fps = 15;
	int fourcc = CV_FOURCC('X', 'V', 'I', 'D'); // codec
	bool isColor = true;

	VideoWriter writer;
	writer.open("Result.avi", fourcc, fps, Size(cap.get(CAP_PROP_FRAME_WIDTH), cap.get(CAP_PROP_FRAME_HEIGHT)), isColor);
	if (!writer.isOpened())
	{
		return 1; //정상종료
	}
#endif // RECORD

	Mat img;
	while (1) {
		cap >> img;
		if (img.empty()) break;

#ifdef RECORD
		writer.write(img);
#endif // RECORD

		imshow("cam", img);  
		if (waitKey(10) == 27) break; //ESC
	}

	destroyAllWindows();

	return 0;
}