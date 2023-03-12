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
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;
using namespace cv;

vector<int> p1;
vector<string> p2;
int arr[109][3];
pair<float, int> p;

//����ɫ��ɫ�� BGR
int InputData()
{
	ifstream infile("I:\\personal\\Desktop\\sehao.txt");
	int number;
	while (!infile.eof())
	{
		infile >> number;
		p1.push_back(number);
	}
	p1.pop_back();

	int j = 0, k = 0;
	int a;
	for (int i = 0; i < 327; i++)
	{
		a = p1[i];
		arr[j][k]=a;
		++k;
		if (k == 3)
		{
			k = 0;
			++j;
		}
	}
	return 0;
}

//����ɫ������
int InputTitle()
{
	ifstream infile("I:\\personal\\Desktop\\biaoti.txt");
	string title;
	while (!infile.eof())
	{
		infile >> title;
		p2.push_back(title);
	}
	p2.pop_back();
	return 0;
}

//����
int FangCha(float B,float G,float R,int arr[109][3])
{
	//����
	float s = (R - arr[0][0]) * (R - arr[0][0]) + (G - arr[0][1]) * (G - arr[0][1]) + (B - arr[0][2]) * (B - arr[0][2]);
	float mins = s;
	p.first = mins;
	p.second = 0;
	for (int i = 1; i < 109; i++)
	{
		s = (R - arr[i][0]) * (R - arr[i][0]) + (G - arr[i][1]) * (G - arr[i][1]) + (B - arr[i][2]) * (B - arr[i][2]);
		if (s < mins)
		{
			mins = s;
			p.first = mins;
			p.second = i;
		}
	}
	return 0;
}



//ͶƱ��
int mat()
{
	ifstream infile;
	infile.open("I:\\personal\\Desktop\\pantong.txt");
	if (!infile.is_open())
	{
		cout << "fail to open text" << endl;
		exit(-1);
	}
	char name[109][8];
	int dataRgb[109][3];
	for (int i = 0; i < 109; i++)
	{
		if (!infile.eof())
		{
			infile >> name[i] >> dataRgb[i][2] >> dataRgb[i][1] >> dataRgb[i][0];
		}
	}
	vector<int> tmp;
	int nameid = 0;
	int pot[109] = { 0 };
	int losses[109] = { 0 };
	Mat img = imread("I:\\personal\\Documents\\Tencent Files\\1432042067\\FileRecv\\skin\\87.jpg");
	int w = img.rows;
	int h = img.cols;
	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
		{
			int B = img.at<Vec3b>(j, i)[0];
			int G = img.at<Vec3b>(j, i)[1];
			int R = img.at<Vec3b>(j, i)[2];
			if (R > 95 && G > 40 && B > 20 && R > B&& R > G&& abs(R - G) > 15)//��һ�µ�����
			//if (R > 81 && R < 203 && G>66 && G < 173 && B>56 && B < 153)//��ͨɫ���ķ�Χ����������
			{
				for (int index = 0; index < 109; index++)
				{
					int value = (B - dataRgb[index][0]) * (B - dataRgb[index][0]) +
						(G - dataRgb[index][1]) * (G - dataRgb[index][1]) +
						(R - dataRgb[index][2]) * (R - dataRgb[index][2]);
					losses[index] += value;//�õ�109����ɫ������ʧ
				}
				int loss = 2147483647;
				for (int i = 0; i < 109; i++)
				{
					int tmp = losses[i];
					if (tmp < loss)
					{
						nameid = i;
						loss = tmp;
					}
				}//ΪͶƱ��׼����
				//img.at<Vec3b>(j, i)[0] = 0;

				pot[nameid]++;//�����沿��������ͨɫ���϶�Ӧ��ɫ������
			}
		}
	int tmps = 0;
	for (int i = 0; i < 109; i++)
	{
		cout << pot[i] << endl;
		if (pot[i] > tmps)
		{
			tmps = pot[i];
			nameid = i;
		}
	}
	cout << name[nameid] << endl;
	cout << nameid << endl;
}


//RGB��ɫ��Ȩ
int lab(Mat &img)
{
	ifstream infile;
	infile.open("I:\\personal\\Desktop\\pantong.txt");
	if (!infile.is_open())
	{
		cout << "fail to open text" << endl;
		exit(-1);
	}
	char name[109][8];
	int dataRgb[109][3];
	for (int i = 0; i < 109; i++)
	{
		if (!infile.eof())
		{
			infile >> name[i] >> dataRgb[i][2] >> dataRgb[i][1] >> dataRgb[i][0];
		}
	}
	vector<int> tmp;
	int nameid = 0;
	int pot[109] = { 0 };
	int losses[109] = { 0 };
	int w = img.rows;
	int h = img.cols;
	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
		{
			int B = img.at<Vec3b>(j, i)[0];
			int G = img.at<Vec3b>(j, i)[1];
			int R = img.at<Vec3b>(j, i)[2];
			if (R > 95 && G > 40 && B > 20 && R > B&& R > G&& abs(R - G) > 15)//��һ�µ�����
			//if (R > 81 && R < 203 && G>66 && G < 173 && B>56 && B < 153)//��ͨɫ���ķ�Χ����������
			{
				for (int index = 0; index < 109; index++)
				{
					int rmean = R + dataRgb[index][2];
					int b = B - dataRgb[index][0];
					int g = G - dataRgb[index][1];
					int r = R - dataRgb[index][2];
					int value = (2 + rmean / 256) * (r * r) + 4 * (g * g) + (2 + (255 - rmean) / 256) * (b * b);
					int v = sqrt(value);
					losses[index] +=v;//�õ�109����ɫ������ʧ
				}
				int loss = 2147483647;
				for (int i = 0; i < 109; i++)
				{
					int tmp = losses[i];
					if (tmp < loss)
					{
						nameid = i;
						loss = tmp;
					}
				}//ΪͶƱ��׼����
				//img.at<Vec3b>(j, i)[0] = 0;

				pot[nameid]++;//�����沿��������ͨɫ���϶�Ӧ��ɫ������
			}
		}
	int tmps = 0;
	for (int i = 0; i < 109; i++)
	{
		cout << pot[i] << endl;
		if (pot[i] > tmps)
		{
			tmps = pot[i];
			nameid = i;
		}
	}
	cout << name[nameid] << endl;
	cout << nameid << endl;
}






int main()
{

	//int a = mat();

	

	//int a = InputData();
	//int b = InputTitle();


	//�ȶ���ͼƬ
	Mat src_img = imread("I:\\personal\\Documents\\Tencent Files\\1432042067\\FileRecv\\skin\\0.jpg");
	imshow("ԭͼ", src_img);
	//����
	Mat back_up = src_img.clone();
	//���ͣ�ȥ����Ե�Ĳ��õĲ���
	Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, Size(29, 29));
	Mat dst_dila;
	dilate(src_img, dst_dila, kernel);
	imshow("���ͺ�",dst_dila);
	//��ֵ��
	Mat bin_img;
	cvtColor(dst_dila, dst_dila, CV_RGB2GRAY);
	threshold(dst_dila, bin_img , 230, 255, 1);
	imshow("��ֵ��", bin_img);
	//��ȡ����ͼƬ
	Mat final;
	back_up.copyTo(final, bin_img);
	imshow("����ͼ",final);

	//int a = lab(final);

	//�ֱ����ͼƬ��RGB��ֵ
	//Scalar cs;
	//cs=mean(back_up,bin_img);
	//float B = cs.val[0];
	//float G = cs.val[1];
	//float R = cs.val[2];
	//cout << R << " " << G << " " << B << endl;
	////�Ƚ�BGR�����С�ļ�Ϊ��������
	//int c = FangCha(B, G, R,arr);
	//cout << p.first << endl;
	//cout << p.second << endl;


	//����ɫ��ͼƬ
	/*int i = 0;
	string s = p2[i];
	cout << s << endl;
	int R1 = arr[i][0];
	int G1 = arr[i][1];
	int B1 = arr[i][2];
	Mat m = Mat(400, 400, CV_8UC3, Scalar(B1, G1, R1));
	imshow("ɫ��", m);*/

	Mat final_lab;
	cvtColor(final, final_lab, CV_BGR2Lab);
	imshow("final_lab", final_lab);


	waitKey(0);

	return 0;
}