//学习图像亮度值、对比度调整。（参考书132页）
#include<opencv2/opencv.hpp>

using namespace cv;
Mat XQAImage, XQAImage2;//XQAImage为原图，XQAImage2为效果图
int Initial_Contrast=7, Initial_Bright=16;//对比度初值，亮度初值
void ContrastAndBright(int, void*);

int main()
{
	XQAImage = imread("洛阳日报.jpg");//原图
	XQAImage2 = Mat::zeros(XQAImage.size(), XQAImage.type());
	namedWindow("【原图】人物图像-XQA", 0);
	resizeWindow("【原图】人物图像-XQA", 600, 405);
	imshow("【原图】人物图像-XQA", XQAImage);

	namedWindow("【效果图】人物图像-XQA", 0);
	resizeWindow("【效果图】人物图像-XQA", 600, 491);//由于进度条的宽度为43*2，所以将窗口加宽到491
	createTrackbar("对比度","【效果图】人物图像-XQA", &Initial_Contrast, 30, ContrastAndBright);
	createTrackbar("亮度", "【效果图】人物图像-XQA", &Initial_Bright, 20, ContrastAndBright);
	
	ContrastAndBright(Initial_Contrast, 0);//回调函数调整对比度
	ContrastAndBright(Initial_Bright, 0);//回调函数调整亮度
	waitKey(0);
	destroyAllWindows();
	return 0;
}

void ContrastAndBright(int, void*)//参考《opencv3编程入门》源码
{
	for (int y = 0; y < XQAImage.rows; y++)
	{
		for (int x = 0; x < XQAImage.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				XQAImage2.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((Initial_Contrast * 0.1) * (XQAImage.at<Vec3b>(y, x)[c]) + Initial_Bright);//由于调整进度条，故乘0.001改为乘0.1
			}
		}
	}
	imshow("【效果图】人物图像-XQA", XQAImage2);
}
//姓名：席庆澳|学号：B21023716|完成时间：2022年9月20日11:49:05