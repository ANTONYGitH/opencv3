//作业2 找一幅人物图像，显示它的直方图；对原图进行直方图均匀，显示效果。
#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;

Mat Histogram(Mat XQA_in);//由于要绘制两次直方图，所以我直接把绘制的代码写成子程序，以便调用

int main()
{
    Mat XQAImage = imread("洛阳日报.jpg");
	if (!XQAImage.data)
	{
		printf("\n【提示】读取图像错误,请检查代码中的命名和图像是否一致。\n");
		system("pause");
		return 0;
	}

	namedWindow("【原图】人物图像-XQA", 0);
	resizeWindow("【原图】人物图像-XQA", 400, 270);
	imshow("【原图】人物图像-XQA", XQAImage);
	
	//直方图均衡（彩图均衡、灰度化后均衡）
	Mat Equ_XQAImage, Equ_XQAImageGRAY;
	//彩图均衡
	std::vector<Mat> mv;
	split(XQAImage, mv);
	equalizeHist(mv[0], mv[0]);//0、1、2是三通道
	equalizeHist(mv[1], mv[1]);
	equalizeHist(mv[2], mv[2]);
	merge(mv, Equ_XQAImage);
	namedWindow("【直方图均衡化后的图】人物图像-XQA", 0);
	resizeWindow("【直方图均衡化后的图】人物图像-XQA", 400, 270);
	imshow("【直方图均衡化后的图】人物图像-XQA", Equ_XQAImage);
	//灰度化后均衡
	cvtColor(XQAImage, XQAImage,COLOR_BGR2GRAY);//COLOR_BGR2GRAY灰度化
	equalizeHist(XQAImage, Equ_XQAImageGRAY);
	namedWindow("【直方图均衡化后的图(灰)】人物图像-XQA", 0);
	resizeWindow("【直方图均衡化后的图(灰)】人物图像-XQA", 400, 270);
	imshow("【直方图均衡化后的图(灰)】人物图像-XQA",Equ_XQAImageGRAY);
	//显示直方图
	Mat Histogram1 = Histogram(XQAImage);
	imshow("【原图的直方图】", Histogram1);
	Mat Histogram2 = Histogram(Equ_XQAImage);
	imshow("【均衡化后的直方图】", Histogram2);
	Mat Histogram3 = Histogram(Equ_XQAImageGRAY);
	imshow("【(灰)均衡化后的直方图】", Histogram3);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
Mat Histogram(Mat XQA_in) {
	Mat image, dstHist;//dstHist是定义存储直方图变量

	XQA_in.copyTo(image);
	int dims = 1;//直方图维数
	float hranges[] = { 0, 255 };
	const float* ranges[] = { hranges };//阈值
	int size = 256;
	int channels = 0;
	calcHist(&image, 1, &channels, Mat(), dstHist, dims, &size, ranges);//计算图像的直方图
	//以上计算得到的结果都存入dstHist中
	int scale = 1;
	Mat dstImage(size * scale, size, CV_8U, Scalar(0));//直方图
	double minValue = 0, maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);//找寻最大值和最小值

	//绘制直方图
	int hpt = saturate_cast<int>(0.9 * size);
	for (int i = 0; i < 256; i++)
	{
		float binValue = dstHist.at<float>(i);
		int realValue = saturate_cast<int>(binValue * hpt / maxValue);
		rectangle(dstImage, Point(i * scale, size - 1), Point((i + 1) * scale - 1, size - realValue), Scalar(255));
	}
	return dstImage;
}
//姓名：席庆澳|学号：B21023716|完成时间：2022年9月15日18:13:50
