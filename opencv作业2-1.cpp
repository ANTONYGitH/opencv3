//作业1 显示一幅奥运五环图像，并进行膨胀、腐蚀操作，显示效果。
#include<opencv2/opencv.hpp>
using namespace cv;

Mat XQAImage, Dil_or_Ero_XQAImage;//第一个为原图，第二个为效果图
int BarNum = 2;//0表示腐蚀，1表示膨胀,2表示膨胀并腐蚀
int CoreSize = 0;//内核矩阵的尺寸

void Process();
void NewBar(int, void*);//回调函数
void NewSize(int, void*);//回调函数

int main()
{
	XQAImage = imread("奥运五环.bmp");//原图	
	if (!XQAImage.data)
	{
		printf("\n【提示】读取图像错误,请检查代码中的命名和图像是否一致。\n");
		system("pause");
		return 0;
	}
	namedWindow("【原图】", 0);
	resizeWindow("【原图】", 400, 270);
	imshow("【原图】", XQAImage);
	
	namedWindow("【膨胀/腐蚀后的效果图】", 0);
	resizeWindow("【膨胀/腐蚀后的效果图】", 400, 270);
	createTrackbar("阈值大小", "【膨胀/腐蚀后的效果图】", &CoreSize, 30, NewSize);
	createTrackbar("档位变换↓", "【膨胀/腐蚀后的效果图】", &BarNum, 2, NewBar);//腐蚀0/膨胀1/腐蚀并膨胀2
	
	waitKey(0);
	destroyAllWindows();
	return 0;
}
void Process()
{
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * CoreSize + 1, 2 * CoreSize + 1), Point(CoreSize, CoreSize));
	//进行腐蚀或膨胀操作|腐蚀0/膨胀1/腐蚀并膨胀2
	if (BarNum == 0) {
		erode(XQAImage, Dil_or_Ero_XQAImage, element);
	}
	else if(BarNum == 1) {
		dilate(XQAImage, Dil_or_Ero_XQAImage, element);
	}
	else {
		dilate(XQAImage, Dil_or_Ero_XQAImage, element);
		erode(Dil_or_Ero_XQAImage, Dil_or_Ero_XQAImage, element);
	}
	putText(Dil_or_Ero_XQAImage, "B21023716XQA's Tips(Look Down)", Point(20, 480), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2, 8);//在图片上写文字
	namedWindow("【膨胀/腐蚀后的效果图】", 0);
	resizeWindow("【膨胀/腐蚀后的效果图】", 400, 270);
	imshow("【膨胀/腐蚀后的效果图】", Dil_or_Ero_XQAImage);
}
void NewBar(int, void*)
{
	Process();
}
void NewSize(int, void*)
{
	Process();
}
//姓名：席庆澳|学号：B21023716|完成时间：2022年9月9日11:40:00