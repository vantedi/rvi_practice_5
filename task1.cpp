#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main() {
	setlocale(LC_ALL, "Russian");

	Mat image = imread("C:/Users/James-Bond/Downloads/cards.jpg");

	vector<Mat> cardsImages;
	vector<string> cardsNames;
	vector<Mat> cardsDescriptors;

	cardsImages.push_back(imread("C:/Users/James-Bond/Downloads/карты/10_piki.jpg"));
	cardsNames.push_back("10_piki");

	cardsImages.push_back(imread("C:/Users/James-Bond/Downloads/карты/3_bubi.jpg"));
	cardsNames.push_back("3_bubi");

	cardsImages.push_back(imread("C:/Users/James-Bond/Downloads/карты/q_chervi.jpg"));
	cardsNames.push_back("dama_chervi");

	cardsImages.push_back(imread("C:/Users/James-Bond/Downloads/карты/j_kresti.jpg"));
	cardsNames.push_back("valet_kresti");

	Ptr<ORB> detector = ORB::create();

	Mat gray;
	cvtColor(image, gray, COLOR_BGR2GRAY);

	GaussianBlur(gray, gray, Size(5, 5), 0);

	Mat descriptors;
	vector<KeyPoint> keypoints;
	detector->detectAndCompute(gray, noArray(), keypoints, descriptors);

	Mat edges;
	Canny(gray, edges, 30, 90);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(edges, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	drawContours(image, contours, -1, Scalar(0, 255, 0), 1);

	for (int i = 0; i < cardsNames.size(); i++) {
		putText(image, cardsNames[i], keypoints[i].pt, 1, 2, Scalar(255, 0, 0), 2);
	}

	imshow("результат", image);
	waitKey(0);

	return 0;
}
