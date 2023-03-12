//#include <iostream>
//#include <cstdio>
//#include <cstring>
//#include <ctime>
//#include<stdio.h>
//#include <opencv2/highgui.hpp>
//#include<opencv2/core.hpp>
//#include<opencv2/opencv.hpp>
//#include<opencv2/imgproc/types_c.h>
//#include<opencv2/imgproc/imgproc_c.h>
//
//using namespace std;
//using namespace cv;



//class skin_detector
//{
//public:
//	/*基于RGB范围的皮肤检测*/
//	Mat RGB_detect(Mat& img)
//	{
//		/*
//			R>95 AND G>40 B>20 AND MAX(R,G,B)-MIN(R,G,B)>15 AND ABS(R-G)>15 AND R>G AND R>B
//				OR
//			R>220 AND G>210 AND B>170 AND ABS(R-G)<=15 AND R>B AND G>B
//		*/
//		//将传入的图片矩阵克隆成一个新的图片矩阵
//		Mat detect = img.clone();
//		//将detect设置为空矩阵，方便用来存储新的识别出来的皮肤
//		detect.setTo(0);
//		//判断是否是空图片或者不是彩色图片，如果是就不再进行判断
//		//channels=3,彩色图片有RGB三通道
//		if (img.empty() || img.channels() != 3)
//		{
//			return detect;
//		}
//		//对矩阵的行列进行遍历
//		for (int i = 0; i < img.rows; i++)
//		{
//			for (int j = 0; j < img.cols; j++)
//			{
//				//uchar是无符号字符代表0-255
//				//p_detect是指向detect（i，j）元素的指针
//				uchar* p_detect = detect.ptr<uchar>(i, j);
//				//p_img是指向img(i,j)元素的指针
//				uchar* p_img = img.ptr<uchar>(i, j);
//				//判断是否是皮肤
//				if ((p_img[2] > 95 && p_img[1] > 40 && p_img[0] > 20 &&
//					(MAX(p_img[0], MAX(p_img[1], p_img[2])) - MIN(p_img[0], MIN(p_img[1], p_img[2])) > 15) &&
//					abs(p_img[2] - p_img[1]) > 15 && p_img[2] > p_img[1] && p_img[1] > p_img[0]) ||
//					(p_img[2] > 200 && p_img[1] > 210 && p_img[0] > 170 && abs(p_img[2] - p_img[1]) <= 15 &&
//						p_img[2] > p_img[0] && p_img[1] > p_img[0]))
//				{
//					//满足rgb条件就将像素存放到detect中，最终输出一个满足条件的皮肤识别图片
//					p_detect[0] = p_img[0];
//					p_detect[1] = p_img[1];
//					p_detect[2] = p_img[2];
//				}
//
//			}
//
//		}
//		return detect;
//	}
//
//	/*HSV颜色空间H范围筛选法*/
//	Mat HSV_detect(Mat& src)
//	{
//		Mat hsv_image;
//		int h = 0;
//		int s = 1;
//		int v = 2;
//		cvtColor(src, hsv_image, CV_BGR2HSV); //首先转换成到YCrCb空间
//		Mat output_mask = Mat::zeros(src.size(), CV_8UC1);
//		for (int i = 0; i < src.rows; i++)
//		{
//			for (int j = 0; j < src.cols; j++)
//			{
//				uchar* p_mask = output_mask.ptr<uchar>(i, j);
//				uchar* p_src = hsv_image.ptr<uchar>(i, j);
//				if (p_src[h] >= 10 && p_src[h] <= 20 && p_src[s] >= 55 && p_src[v] >= 60)
//				{
//					p_mask[0] = 255;
//				}
//			}
//		}
//		Mat detect;
//		src.copyTo(detect, output_mask);;
//		return detect;
//	}
//
//	/*YCrCb颜色空间Cr,Cb范围筛选法*/
//	Mat YCrCb_detect(Mat& src)
//	{
//		Mat ycrcb_image;
//		int Cr = 1;
//		int Cb = 2;
//		cvtColor(src, ycrcb_image, CV_BGR2YCrCb); //首先转换成到YCrCb空间
//		Mat output_mask = Mat::zeros(src.size(), CV_8UC1);
//		for (int i = 0; i < src.rows; i++)
//		{
//			for (int j = 0; j < src.cols; j++)
//			{
//				uchar* p_mask = output_mask.ptr<uchar>(i, j);
//				uchar* p_src = ycrcb_image.ptr<uchar>(i, j);
//				if (p_src[Cr] >= 130 && p_src[Cr] <= 180 && p_src[Cb] >= 70 && p_src[Cb] <= 120)
//				{
//					p_mask[0] = 255;
//				}
//			}
//		}
//		Mat detect;
//		src.copyTo(detect, output_mask);;
//		return detect;
//
//	}
//
//	/*YCrCb颜色空间Cr分量+Otsu法*/
//	Mat YCrCb_Otsu_detect(Mat& src)
//	{
//		Mat ycrcb_image;
//		cvtColor(src, ycrcb_image, CV_BGR2YCrCb); //首先转换成到YCrCb空间
//		Mat detect;
//		vector<Mat> channels;
//		split(ycrcb_image, channels);
//		Mat output_mask = channels[1];
//		threshold(output_mask, output_mask, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
//		src.copyTo(detect, output_mask);
//		return detect;
//
//	}
//
//	/*基于椭圆皮肤模型的皮肤检测*/
//	Mat ellipse_detect(Mat& src)
//	{
//		Mat img = src.clone();
//		Mat skinCrCbHist = Mat::zeros(Size(256, 256), CV_8UC1);
//		//利用opencv自带的椭圆生成函数先生成一个肤色椭圆模型
//		ellipse(skinCrCbHist, Point(113, 155.6), Size(23.4, 15.2), 43.0, 0.0, 360.0, Scalar(255, 255, 255), -1);
//		Mat ycrcb_image;
//		Mat output_mask = Mat::zeros(img.size(), CV_8UC1);
//		cvtColor(img, ycrcb_image, CV_BGR2YCrCb); //首先转换成到YCrCb空间
//		for (int i = 0; i < img.cols; i++)   //利用椭圆皮肤模型进行皮肤检测
//			for (int j = 0; j < img.rows; j++)
//			{
//				Vec3b ycrcb = ycrcb_image.at<Vec3b>(j, i);
//				if (skinCrCbHist.at<uchar>(ycrcb[1], ycrcb[2]) > 0)   //如果该落在皮肤模型椭圆区域内，该点就是皮肤像素点
//					output_mask.at<uchar>(j, i) = 255;
//			}
//
//		Mat detect;
//		img.copyTo(detect, output_mask);  //返回肤色图
//		return detect;
//	}
//
//	/*opencv自带肤色检测类AdaptiveSkinDetector*/
////	Mat AdaptiveSkinDetector_detect(Mat& src)
////	{
////		IplImage* frame;
////		frame = &IplImage(src);  //Mat -> IplImage
////		CvAdaptiveSkinDetector filter(1, CvAdaptiveSkinDetector::MORPHING_METHOD_ERODE_DILATE);
////
////		IplImage* maskImg = cvCreateImage(cvSize(src.cols, src.rows), IPL_DEPTH_8U, 1);
////		IplImage* skinImg = cvCreateImage(cvSize(src.cols, src.rows), IPL_DEPTH_8U, 3);
////		cvZero(skinImg);
////		filter.process(frame, maskImg);    // process the frame
////		cvCopy(frame, skinImg, maskImg);
////		Mat tmp(skinImg);  //IplImage -> Mat
////		Mat detect = tmp.clone();
////		cvReleaseImage(&skinImg);
////		cvReleaseImage(&maskImg);
////		return detect;
////	}
//};







//int main()
//{
//	/*const int num=10;
//	char filename[50];
//	char windowname[50];
//	char windowname1[50];
//	Mat frame;*/
//	
//	//for (int i = 1; i <= 10; i++)
//	{
//		//skin_detector detector;	
//		//sprintf(filename, "I:\\personal\\Desktop\\opencv\\%d.jpg", i);
//		//sprintf(windowname, "I:\\personal\\Desktop\\opencv\\test\\%d_.jpg", i);
//		//sprintf(windowname1, "I:\\personal\\Desktop\\opencv\\test\\%d__.jpg", i);
//		//frame = imread(filename);
//		//
//		////Mat img = detector.YCrCb_detect(frame);
//		////Mat img = detector.RGB_detect(frame);
//		////Mat img = detector.HSV_detect(frame);
//		//Mat img = detector.YCrCb_Otsu_detect(frame);
//
//		//
//		////Mat img = detector.ellipse_detect(frame);
//		//Mat dst;
//		//cvtColor(img, dst, CV_RGB2GRAY);
//		//Mat bin;
//		//threshold(dst, bin, 127, 255, THRESH_BINARY);
//		////namedWindow("windowname");
//		//imwrite(windowname, dst);
//		//imwrite(windowname1, bin);
//
//
//	}
//		
//	Mat src = imread("I:\\personal\\Desktop\\pic\\20200409173935484.jpg");
//	if (src.empty()) {
//		printf("不能加载图像！\n");
//		return -1;
//	}
//	namedWindow("1--原图", WINDOW_AUTOSIZE);
//	imshow("1--原图", src);
//
//	Mat dst;
//	//图像中值滤波
//	medianBlur(src, dst, 5);
//	imshow("2--medianblur(ksize=5)", dst);
//
//	waitKey(0);
//	return 0;
//
//	
//}