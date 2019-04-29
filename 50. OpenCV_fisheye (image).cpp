// 50. OpenCV_fisheye (image)

#include <opencv2/opencv.hpp>
#include <limits>
#include <vector>

using namespace cv;
using namespace std;

/////////////////////////
// Lens properties
int lsize = 90, lsize2 = lsize * lsize;
float mag = 2.0f;
float k = -0.00016f;

int offX, offY;
int border, borderViaLens;

int main() {

	cout << " Usage: display_image ImageToLoadAndDisplay" << endl;
	
	Mat_<Vec3b> imgOrg;

	//Image size는 400 by 400 이어야함. 
	//imgOrg = imread("Fisheye.jpg", CV_LOAD_IMAGE_COLOR);
//	imgOrg = imread("Board.jpg", CV_LOAD_IMAGE_COLOR);
	imgOrg = imread("photo.jpg", CV_LOAD_IMAGE_COLOR);


	if (!imgOrg.data)                              // Check for invalid input
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Display window", imgOrg);                   // Show our image inside it.
														//waitKey(0);                                          // Wait for a keystroke in the window

	
	Mat_<Vec3b> imgClone = imgOrg.clone();
	
	///radial distortion (방사왜곡): xc = x(1+k1r^2+k1r^4+k1r^6), yx = y(1+k1r^2+k1r^4+k1r^6)
	 //펼쳐지기만 함
	//int halfWidth = imgClone.rows / 2;
	//int halfHeight = imgClone.cols / 2;
	//float k1, k2, k3, theta;
	//k1 = 0.01;
	//k2 = 0;
	//k3 = 0;
	//int newX, newY, sourceX, sourceY;
	//double distance;
	//double R;

	//for (int i = 0; i < imgClone.rows; ++i) //400
	//{
	//	for (int j = 0; j < imgClone.cols; j++) //400
	//	{
	//		newX = i - halfWidth;
	//		newY = j - halfHeight;
	//		distance = sqrt(pow(newX, 2) + pow(newY, 2));
	//		R = distance/200;// focal length
	//		newX = newX*(1 + k1 * pow(R, 2) + k2 * pow(R, 4) + k3 * pow(R, 6));
	//		newY = newY*(1 + k1 * pow(R, 2) + k2 * pow(R, 4) + k3 * pow(R, 6));
	//		if (R == 0.0)
	//			theta = 1;
	//		else
	//			theta = atan(R) / R;

	//		sourceX = round(halfWidth + theta*newX);
	//		sourceY = round(halfHeight + theta*newY);

	//		imgClone(i, j)[0] = imgOrg(sourceX, sourceY)[0];
	//		imgClone(i, j)[1] = imgOrg(sourceX, sourceY)[1];
	//		imgClone(i, j)[2] = imgOrg(sourceX, sourceY)[2];

	//	}
	//}

	////////////////////////////////////////////////////////////////////////////////////////////

	// 2. radial distortion (방사왜곡): xc = x(1+k1r^2+k1r^4+k1r^6), yc = y(1+k1r^2+k1r^4+k1r^6)
	// 펼쳐지기만 함
	int halfWidth = imgClone.rows / 2;
	int halfHeight = imgClone.cols / 2;
	float k1, k2, k3, focalLength;
	k1 = -0.01;
	k2 = 0;
	k3 = 0;
	focalLength = 200.0;
	int newX, newY, sourceX, sourceY;
	double distance, theta;
	double R;

	for (int i = 0; i < imgClone.rows; ++i) //400
	{
		for (int j = 0; j < imgClone.cols; j++) //400
		{
			newX = i - halfWidth;
			newY = j - halfHeight;
			distance = sqrt(pow(newX, 2) + pow(newY, 2) + pow(focalLength, 2));//
			R = distance / 6;// focal length
			newX = newX*(1 + k1 * pow(R, 2) + k2 * pow(R, 4) + k3 * pow(R, 6));
			newY = newY*(1 + k1 * pow(R, 2) + k2 * pow(R, 4) + k3 * pow(R, 6));
			if (R == 0.0)
				theta = 1;
			else
				theta = atan(R) / R;

			sourceX = round(halfWidth + theta*newX);
			sourceY = round(halfHeight + theta*newY);

			imgClone(i, j)[0] = imgOrg(sourceX, sourceY)[0];
			imgClone(i, j)[1] = imgOrg(sourceX, sourceY)[1];
			imgClone(i, j)[2] = imgOrg(sourceX, sourceY)[2];

		}
	}

	/*Mat rot = imgClone.clone();
	Point2f pt(imgClone.cols / 2., imgClone.rows / 2.);
	imgClone = getRotationMatrix2D(pt, 180, 1.0);
*/
	cv::Mat src = imgClone.clone();
	cv::Mat dst;

	cv::Point2f pc(src.cols / 2., src.rows / 2.);
	cv::Mat r = cv::getRotationMatrix2D(pc, 180, 1.0);

	cv::warpAffine(src, dst, r, src.size()); // what size I should use?

	//cv::imwrite("rotated_im.png", dst);


	namedWindow("Display window 2", WINDOW_AUTOSIZE);
	imshow("Display window 2", dst);                   // Show our image inside it.
	waitKey(0);

	return 0;
}