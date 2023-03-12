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
//	/*����RGB��Χ��Ƥ�����*/
//	Mat RGB_detect(Mat& img)
//	{
//		/*
//			R>95 AND G>40 B>20 AND MAX(R,G,B)-MIN(R,G,B)>15 AND ABS(R-G)>15 AND R>G AND R>B
//				OR
//			R>220 AND G>210 AND B>170 AND ABS(R-G)<=15 AND R>B AND G>B
//		*/
//		//�������ͼƬ�����¡��һ���µ�ͼƬ����
//		Mat detect = img.clone();
//		//��detect����Ϊ�վ��󣬷��������洢�µ�ʶ�������Ƥ��
//		detect.setTo(0);
//		//�ж��Ƿ��ǿ�ͼƬ���߲��ǲ�ɫͼƬ������ǾͲ��ٽ����ж�
//		//channels=3,��ɫͼƬ��RGB��ͨ��
//		if (img.empty() || img.channels() != 3)
//		{
//			return detect;
//		}
//		//�Ծ�������н��б���
//		for (int i = 0; i < img.rows; i++)
//		{
//			for (int j = 0; j < img.cols; j++)
//			{
//				//uchar���޷����ַ�����0-255
//				//p_detect��ָ��detect��i��j��Ԫ�ص�ָ��
//				uchar* p_detect = detect.ptr<uchar>(i, j);
//				//p_img��ָ��img(i,j)Ԫ�ص�ָ��
//				uchar* p_img = img.ptr<uchar>(i, j);
//				//�ж��Ƿ���Ƥ��
//				if ((p_img[2] > 95 && p_img[1] > 40 && p_img[0] > 20 &&
//					(MAX(p_img[0], MAX(p_img[1], p_img[2])) - MIN(p_img[0], MIN(p_img[1], p_img[2])) > 15) &&
//					abs(p_img[2] - p_img[1]) > 15 && p_img[2] > p_img[1] && p_img[1] > p_img[0]) ||
//					(p_img[2] > 200 && p_img[1] > 210 && p_img[0] > 170 && abs(p_img[2] - p_img[1]) <= 15 &&
//						p_img[2] > p_img[0] && p_img[1] > p_img[0]))
//				{
//					//����rgb�����ͽ����ش�ŵ�detect�У��������һ������������Ƥ��ʶ��ͼƬ
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
//	/*HSV��ɫ�ռ�H��Χɸѡ��*/
//	Mat HSV_detect(Mat& src)
//	{
//		Mat hsv_image;
//		int h = 0;
//		int s = 1;
//		int v = 2;
//		cvtColor(src, hsv_image, CV_BGR2HSV); //����ת���ɵ�YCrCb�ռ�
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
//	/*YCrCb��ɫ�ռ�Cr,Cb��Χɸѡ��*/
//	Mat YCrCb_detect(Mat& src)
//	{
//		Mat ycrcb_image;
//		int Cr = 1;
//		int Cb = 2;
//		cvtColor(src, ycrcb_image, CV_BGR2YCrCb); //����ת���ɵ�YCrCb�ռ�
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
//	/*YCrCb��ɫ�ռ�Cr����+Otsu��*/
//	Mat YCrCb_Otsu_detect(Mat& src)
//	{
//		Mat ycrcb_image;
//		cvtColor(src, ycrcb_image, CV_BGR2YCrCb); //����ת���ɵ�YCrCb�ռ�
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
//	/*������ԲƤ��ģ�͵�Ƥ�����*/
//	Mat ellipse_detect(Mat& src)
//	{
//		Mat img = src.clone();
//		Mat skinCrCbHist = Mat::zeros(Size(256, 256), CV_8UC1);
//		//����opencv�Դ�����Բ���ɺ���������һ����ɫ��Բģ��
//		ellipse(skinCrCbHist, Point(113, 155.6), Size(23.4, 15.2), 43.0, 0.0, 360.0, Scalar(255, 255, 255), -1);
//		Mat ycrcb_image;
//		Mat output_mask = Mat::zeros(img.size(), CV_8UC1);
//		cvtColor(img, ycrcb_image, CV_BGR2YCrCb); //����ת���ɵ�YCrCb�ռ�
//		for (int i = 0; i < img.cols; i++)   //������ԲƤ��ģ�ͽ���Ƥ�����
//			for (int j = 0; j < img.rows; j++)
//			{
//				Vec3b ycrcb = ycrcb_image.at<Vec3b>(j, i);
//				if (skinCrCbHist.at<uchar>(ycrcb[1], ycrcb[2]) > 0)   //���������Ƥ��ģ����Բ�����ڣ��õ����Ƥ�����ص�
//					output_mask.at<uchar>(j, i) = 255;
//			}
//
//		Mat detect;
//		img.copyTo(detect, output_mask);  //���ط�ɫͼ
//		return detect;
//	}
//
//	/*opencv�Դ���ɫ�����AdaptiveSkinDetector*/
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
//		printf("���ܼ���ͼ��\n");
//		return -1;
//	}
//	namedWindow("1--ԭͼ", WINDOW_AUTOSIZE);
//	imshow("1--ԭͼ", src);
//
//	Mat dst;
//	//ͼ����ֵ�˲�
//	medianBlur(src, dst, 5);
//	imshow("2--medianblur(ksize=5)", dst);
//
//	waitKey(0);
//	return 0;
//
//	
//}