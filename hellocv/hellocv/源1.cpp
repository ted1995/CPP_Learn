#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include<stdio.h>
#include <opencv2/highgui.hpp>
#include<opencv2/core.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/types_c.h>
#include<opencv2/imgproc/imgproc_c.h>

using namespace std;
using namespace cv;

 Mat lapulasi(Mat &src )
{
	Mat src_gray, dst, abs_dst, dst1;
	//imshow("原始图像", src);
	//高斯滤波
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	//转化为灰度图，输入只能为单通道
	//cvtColor(src, src, CV_BGR2GRAY);
	Laplacian(src, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);
	//imshow("效果图Laplace变换", abs_dst);
	return abs_dst;
	waitKey();
}


void canny(Mat& srcImage)
{
	Mat srcImage1 = srcImage.clone();

	Mat dstImage, edge, grayImage;

	// 【1】创建与src同类型和大小的矩阵(dst)
	dstImage.create(srcImage1.size(), srcImage1.type());

	// 【2】将原图像转换为灰度图像
	cvtColor(srcImage1, grayImage, COLOR_BGR2GRAY);

	// 【3】先用使用 3x3内核来降噪
	blur(grayImage, edge, Size(3, 3));

	// 【4】运行Canny算子
	Canny(edge, edge, 3, 9, 3);

	//【5】将g_dstImage内的所有元素设置为0 
	//dstImage = Scalar::all(0);

	//【6】使用Canny算子输出的边缘图g_cannyDetectedEdges作为掩码，来将原图g_srcImage拷到目标图g_dstImage中
	//srcImage1.copyTo(dstImage, edge);

	//【7】显示效果图 
	imshow("【效果图】Canny边缘检测2", edge);


	waitKey(0);

}

Mat reverse(Mat src)
{
	Mat dst = src < 100;
	return dst;
}


//去除噪声
Mat removePepperNoise(Mat& mask)
{
	for (int y = 2; y < mask.rows - 2; ++y)
	{
		uchar* pThis = mask.ptr(y);
		uchar* pUp1 = mask.ptr(y - 1);
		uchar* pUp2 = mask.ptr(y - 2);
		uchar* pDown1 = mask.ptr(y + 1);
		uchar* pDown2 = mask.ptr(y + 2);

		pThis += 2; pUp1 += 2; pUp2 += 2; pDown1 += 2; pDown2 += 2;

		int x = 2;
		while (x < mask.cols - 2)
		{
			uchar v = *pThis;
			// 当前点为黑色
			if (v == 0)
			{
				// 5 * 5 邻域的外层
				/*bool allAbove = *(pUp2 - 2) && *(pUp2 - 1) && *(pUp2) && *(pUp2 + 1) && *(pUp2 + 2);
				bool allBelow = *(pDown2 - 2) && *(pDown2 - 1) && *(pDown2) && *(pDown2 + 1) && *(pDown2 + 2);
				bool allLeft = *(pUp1 - 2) && *(pThis - 2) && *(pDown1 - 2);
				bool allRight = *(pUp1 + 2) && *(pThis + 2) && *(pDown1 + 2);*/
				
				bool allAbove=*(pUp1 - 1) && *(pUp1) && *(pUp1 + 1) ;
				bool allLeft = *(pThis - 1);
				bool allRight=*(pThis + 1);
				bool allBelow =*(pDown1 - 1) && *pDown1 && *(pDown1 + 1);
				bool surroundings = allAbove && allBelow && allLeft && allRight;

				if (surroundings)
				{
					// 5*5 邻域的内层（3*3的小邻域）
					/**(pUp1 - 1) = *(pUp1) = *(pUp1 + 1) = 255;
					*(pThis - 1) = *pThis = *(pThis + 1) = 255;
					*(pDown1 - 1) = *pDown1 = *(pDown1 + 1) = 255;*/
					(*pThis) = ~(*pThis);
											// 0 ⇒ 255
				}
				pUp2 += 2; pUp1 += 2; pThis += 2; pDown1 += 2; pDown2 += 2;
				x += 2;
			}
			++pThis; ++pUp2; ++pUp1; ++pDown1; ++pDown2; ++x;
		}
	}
	return mask;
}



int main1()
{
	
	Mat img = imread("I:\\personal\\Documents\\Tencent Files\\1432042067\\FileRecv\\ceshi\\1028-145410421_B.bmp");//只读取灰度图

	//imshow("原始图", img);
	Mat DstPic, edge, grayImage;
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst, dst2;
	Mat src, src_gray, abs_dst, abs_dst1;
	Mat result, result_fin, dst_dila, edges, kernel;
	Mat src1, src_gray1, dst3;

	//canny算子找出待减去的边界
	cv::Canny(img, edges,2, 500);
	//imshow("【效果图1】", edges);
	kernel = cv::getStructuringElement(cv::MORPH_RECT, Size(17, 17));
	cv::dilate(edges, dst_dila, kernel);
	//imshow("【效果图】", dst_dila);

	//突出灰色的瑕疵
	GaussianBlur(img, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	cvtColor(src, src_gray, CV_RGB2GRAY);
	Laplacian(src_gray, dst2, CV_16S, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(dst2, abs_dst);
	Mat addst;
	absdiff(abs_dst, src_gray, addst);
	imshow("jiashen", addst);

	Mat a1;
	Mat a3 = lapulasi(addst);
	//二值化
	cv::threshold(a3, a1, 40, 255, 0);
	//imshow("【效果图】二值化", a1);

	//去边界
	subtract(a1, dst_dila, result);
	//imshow("result", result);
	Mat a2 = reverse(result);
	//imshow("【效果图】二值化", a2);
	Mat a6=reverse(a2);
	//imshow("效果", a6);
	

	//提取感兴趣的区域
	Rect rect(0, 50, 1150 ,400); 
	Mat roi = cv::Mat(a6, rect);
	imwrite("I:\\personal\\Documents\\Tencent Files\\1432042067\\FileRecv\\ceshi\\1028-145410421_B-1.bmp", roi);
	Mat logo = imread("I:\\personal\\Documents\\Tencent Files\\1432042067\\FileRecv\\ceshi\\1028-145410421_B-1.bmp");
	Mat mask = imread("I:\\personal\\Documents\\Tencent Files\\1432042067\\FileRecv\\ceshi\\1028-145410421_B-1.bmp", 0);
	imshow("mask", mask);
	cv::Mat imageROI, s = img.clone();
	Mat image = s.setTo(0);
	imageROI = image(cv::Rect(0, 50, logo.cols, logo.rows));
	logo.copyTo(imageROI, mask);
	cv::namedWindow("result");
	cv::imshow("result", image);
	Mat roi1 = reverse(image);
	imshow("roi1", roi1);


	//保存图片
	imwrite("I:\\personal\\Documents\\Tencent Files\\1432042067\\FileRecv\\ceshi\\1028-145410421_B-2.bmp", roi1);
	
	

	
	

	waitKey(0);

	return 0;
}
//String cascadeFilePath = "E:\\haarcascade_frontalface_alt.xml";   //反斜杠’\‘表示转义字符，所以绝对路径需要如是表示
	//CascadeClassifier face_cascade;
	//if (!face_cascade.load(cascadeFilePath))         // 用load函数加载XML分类器文件
	//{
		//cout<<"could not load the haar data..."<<endl;
		//return -1;
	//}
	//Mat src_img, gray_img;
	//src_img = imread("I:\\personal\\Desktop\\1.jpg");
	//cvtColor(src_img, gray_img, COLOR_BGR2GRAY);
	//equalizeHist(gray_img, gray_img);        //直方图均衡化
	//imshow("原图", src_img);


	//检测人脸
	//vector<Rect> faces;                  // faces是一个容器，用来接收检测到的人脸,是一个矩形框向量组
	//Mat image_rect;
	//face_cascade.detectMultiScale(gray_img, faces, 1.1, 2, 0, Size(30, 30));  
	//for (auto t = 0; t < faces.size(); ++t)
	//{
	//	rectangle(src_img, faces[t], Scalar(0, 0, 255), 2, 8, 0);            // 用红色矩形框出人脸
	//	Rect rect(faces[t].tl().x, faces[t].tl().y, faces[t].width, faces[t].height);
	//	cout << faces[t].tl().x<< endl;
	//	image_rect = src_img(rect);
	//	imshow("检测结果", image_rect);
	//}

	//Mat edges;
	//cv::Canny(image_rect, edges, 50, 100);
	//Mat kernel, dst_dila;
	//kernel = cv::getStructuringElement(cv::MORPH_RECT, Size(3, 3));
	//cv::erode(edges, dst_dila, kernel);
	//imshow("edge", edges);



	//检测眼睛
	//String cascadeFilePath1 = "E:\\haarcascade_eye.xml";
	//CascadeClassifier eye_cascade;
	//if (!eye_cascade.load(cascadeFilePath1))         // 用load函数加载XML分类器文件
	//{
	//	cout << "could not load the haar data..." << endl;
	//	return -1;
	//}
	//vector<Rect> eyes;                  // faces是一个容器，用来接收检测到的人脸,是一个矩形框向量组
	//Mat image_rect1;
	//Mat gray_img1;
	//cvtColor(image_rect, gray_img1, COLOR_BGR2GRAY);
	//eye_cascade.detectMultiScale(gray_img1, eyes, 1.1, 3, 2, Size(10, 10));
	//for (auto t = 0; t < eyes.size(); ++t)
	//{
	//	rectangle(image_rect, eyes[t], Scalar(0, 0, 255), 2, 8, 0);            // 用红色矩形框出人脸
	//	//Rect rect(faces[t].tl().x, faces[t].tl().y, faces[t].width, faces[t].height);
	//	//cout << faces[t].tl().x<< endl;
	//	//image_rect = src_img(rect);
	//	imshow("检测结果", image_rect);
	//}