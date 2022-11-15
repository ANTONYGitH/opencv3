//实验1 以下程序可自己实现算法，也可以调用OpenCV的函数
//1.对一副灰度图像img1所有像素的灰度值 + 50，输出图像img2；
//2.对img2进行直方图均衡化，输出图像img3；
//3.对img3进行膨胀、腐蚀，并输出img4。
//4.通过C++语言对已数字化的图像img4进行中值滤波以及利用Sobel算子进行图像锐化
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;

int main()
{
	Mat XQAImage;//原图
	XQAImage = imread("洛阳日报.jpg");
	if (!XQAImage.data)
	{
		printf("\n【提示】读取图像错误,请检查代码中的命名和图像是否一致。\n");
		std::cin.get();
		std::cin.get();
		return 0;
	}
    namedWindow("【原图】", 0);
    resizeWindow("【原图】", 400, 270);
	imshow("【原图】", XQAImage);

	//分割线--------------------------------------------//实验任务开始//---------------------------------------------

	"\t【实验任务1】对一副灰度图像img1所有像素的灰度值 + 50，输出图像img2\n";

	int height = XQAImage.rows;//求出原图的高
	int width = XQAImage.cols;//求出原图的宽
	Mat XQAImage_2 = Mat::zeros(XQAImage.size(), XQAImage.type());  //创建一个与原图一样大小的空白图片，下同      

	float brightValue = 50;//调整亮度加50
	//循环操作，遍历每一列，每一行的元素
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if (XQAImage.channels() == 3)//判断是否为3通道图片
			{
				//将遍历得到的原图像素值，返回给变量b,g,r
				float b = XQAImage.at<Vec3b>(row, col)[0];//blue
				float g = XQAImage.at<Vec3b>(row, col)[1];//green
				float r = XQAImage.at<Vec3b>(row, col)[2];//red
				//开始操作像素，对变量b,g,r做改变后再返回到新的图片。
				XQAImage_2.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b + brightValue);
				XQAImage_2.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g + brightValue);
				XQAImage_2.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r + brightValue);
			}
			else if (XQAImage_2.channels() == 1)//判断是否为单通道的图片
			{
				float i = XQAImage_2.at<uchar>(row, col);
				XQAImage_2.at<uchar>(row, col) = saturate_cast<uchar>(i + brightValue);
			}
		}
	}
	namedWindow("【效果图1】灰度值+50", 0);
	resizeWindow("【效果图1】灰度值+50", 400, 270);
	imshow("【效果图1】灰度值+50", XQAImage_2);

	"\t【实验任务2】对img2进行直方图均衡化，输出图像img3\n";

	Mat XQAImage_3 = Mat::zeros(XQAImage.size(), XQAImage.type());
	
	std::vector<Mat> rc;
	split(XQAImage_2, rc);//将一个多通道数组分离成几个单通道数组
	equalizeHist(rc[0], rc[0]);//0、1、2是三通道
	equalizeHist(rc[1], rc[1]);
	equalizeHist(rc[2], rc[2]);
	merge(rc, XQAImage_3);//是split()函数的逆向操作，将多个数组组合合并成一个多通道的数组

	namedWindow("【效果图2】彩图的直方图均衡化", 0);
	resizeWindow("【效果图2】彩图的直方图均衡化", 400, 270);
	imshow("【效果图2】彩图的直方图均衡化", XQAImage_3);

	"\t【实验任务3】对img3进行膨胀、腐蚀，并输出img4\n";

	Mat XQAImage_4 = Mat::zeros(XQAImage.size(), XQAImage.type());
	int CoreSize = 4;//内核矩阵的尺寸
	//膨胀操作
	dilate(XQAImage_3, XQAImage_4, getStructuringElement
	(MORPH_RECT, Size(2 * CoreSize + 1, 2 * CoreSize + 1), Point(CoreSize, CoreSize)));
	//腐蚀操作
	erode(XQAImage_4, XQAImage_4, getStructuringElement
	(MORPH_RECT, Size(2 * CoreSize + 1, 2 * CoreSize + 1), Point(CoreSize, CoreSize)));
	namedWindow("【效果图3】膨胀、腐蚀后", 0);
	resizeWindow("【效果图3】膨胀、腐蚀后", 400, 270);
	imshow("【效果图3】膨胀、腐蚀后", XQAImage_4);

	"\t【实验任务4】通过C++语言对已数字化的图像img4进行中值滤波以及利用Sobel算子进行图像锐化\n";

	Mat XQAImage_5 = Mat::zeros(XQAImage.size(), XQAImage.type());//中值滤波后的图
	Mat out_xImage, out_yImage;//Sobel算子输出的对x，y两个方向的梯度处理的图片
	Mat abs_x, abs_y;//Sobel算子的内参
	Mat XQAImage_6 = Mat::zeros(XQAImage.size(), XQAImage.type());//Sobel提取后的图

	//中值滤波
	int medianBlurValue = 10;
	//中值滤波
	medianBlur(XQAImage_4, XQAImage_5, medianBlurValue * 2 + 1);//注意此处第三个参数不能随意修改，必须符合medianBlurValue*2+1
	//用sobel算子提取图像轮廓
	Sobel(XQAImage_5, out_xImage, CV_64F, 1, 0, 1, 1, 1, BORDER_DEFAULT);//求x方向梯度,第6个参数为soble内核，很重要
	convertScaleAbs(out_xImage, abs_x);
	Sobel(XQAImage_5, out_yImage, CV_64F, 0, 1, 1, 1, 1, BORDER_DEFAULT);//求y方向梯度
	convertScaleAbs(out_yImage, abs_y);
	addWeighted(abs_x, 0.5, abs_y, 0.5, 0, XQAImage_6);//合并梯度
	namedWindow("【效果图4】中值滤波&Sobel算子图像锐化", 0);
	resizeWindow("【效果图4】中值滤波&Sobel算子图像锐化", 400, 270);
	imshow("【效果图4】中值滤波&Sobel算子图像锐化", XQAImage_6);

    waitKey(0);
    destroyAllWindows();
    return 0;
}
//姓名：席庆澳|学号：B21023716|完成时间：2022年9月27日11:00:41