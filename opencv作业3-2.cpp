//作业2 找一幅图像，对原图进行中值滤波，显示效果；Soble算子提取边缘，显示效果。
#include "opencv2/core/core.hpp" 
#include "opencv2/highgui/highgui.hpp" 
#include "opencv2/imgproc/imgproc.hpp" 
 
using namespace cv;

int main()
{
	Mat XQAImage = imread("洛阳日报.jpg");//原图
	Mat medianBlurImage;//中值滤波后的图
	Mat out_xImage, out_yImage;//Sobel
	Mat abs_x, abs_y;
	Mat SobelImage;//Sobel提取后的图
	int medianBlurValue = 1;
	//中值滤波
	medianBlur(XQAImage, medianBlurImage, medianBlurValue*2+1);//注意此处第三个参数不能随意修改，必须符合medianBlurValue*2+1
	//用sobel算子提取边缘
	Sobel(XQAImage, out_xImage, CV_64F, 1, 0, 1, 1, 1, BORDER_DEFAULT);//求x方向梯度,第6个参数为soble内核，很重要
	convertScaleAbs(out_xImage, abs_x);
	Sobel(XQAImage, out_yImage, CV_64F, 0, 1, 1, 1, 1, BORDER_DEFAULT);//求y方向梯度
	convertScaleAbs(out_yImage, abs_y);
	addWeighted(abs_x, 0.5, abs_y, 0.5, 0, SobelImage);
	//显示图像
	namedWindow("【原图】人物图像-XQA", 0);
	resizeWindow("【原图】人物图像-XQA", 400, 270);
	imshow("【原图】人物图像-XQA", XQAImage);
	namedWindow("【效果图】中值滤波后-XQA", 0);
	resizeWindow("【效果图】中值滤波后-XQA", 400, 270);
	imshow("【效果图】中值滤波后-XQA", medianBlurImage);
	namedWindow("【效果图】Sobel提取后-XQA", 0);
	resizeWindow("【效果图】Sobel提取后-XQA", 400, 270);
	imshow("【效果图】Sobel提取后-XQA", SobelImage);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
//姓名：席庆澳|学号：B21023716|完成时间：2022年9月15日18:13:50