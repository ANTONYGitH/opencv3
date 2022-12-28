//实验2 以下程序可自己实现算法，也可以调用OpenCV的函数
//1. 使用Canny算法进行边缘检测——1)高斯滤波；2)Sobel算子图像锐化；3)非极大值抑制；4)双阈值法处理。
//2. 运用大津法进行图像分割。
#include<opencv2/opencv.hpp>

using namespace cv;

Mat XQAImage;//原图

int main()
{
	XQAImage = imread("席庆澳作业用图-月亮.jpg");
	if (!XQAImage.data){printf("\n【提示】读取图像错误,请检查代码中的命名和图像是否一致。\n");return false;}
	namedWindow("【原图】",0);
	resizeWindow("【原图】", 600, 405);
	imshow("【原图】", XQAImage);

	"---------------\t【实验任务1】使用Canny算法进行边缘检测\t---------------\n";
	Mat XQAImage_2;//存储灰度图
	cvtColor(XQAImage, XQAImage_2, COLOR_RGB2GRAY);//彩图转灰度图
	Mat XQAImage_3;//存储用Canny算子处理的边缘图
	GaussianBlur(XQAImage_2, XQAImage_3, Size(3, 3),0.01);//降噪,高斯卷积核越大，图像越模糊；
										//Sigma(σ)越大，平滑效果越明显，这里平滑系数用0.01。
	Canny(XQAImage_3, XQAImage_3, 254,254, 3,false); //像素值设置为255（白），设为0（黑）
	//低于阈值1（第三个参数）的像素点会被认为不是边缘；高于阈值2（第四个参数）的像素点会被认为是边缘
	Mat XQAImage_4;//存储canny算法输出
	XQAImage_4.create(XQAImage.size(), XQAImage.type());//创建与原图同类型和大小的图（或者说矩阵）
	XQAImage_4 = Scalar::all(0); //将XQAImage_4内的所有元素设置为0
	XQAImage.copyTo(XQAImage_4, XQAImage_3);//使用Canny算子输出的边缘图作为掩码，来将原图拷到效果图中
	namedWindow("【效果图】Canny算法边缘检测",0);
	resizeWindow("【效果图】Canny算法边缘检测", 600, 405);
	imshow("【效果图】Canny算法边缘检测", XQAImage_4);
	
	"---------------\t【实验任务2】运用大津法进行图像分割\t-------------------\n";
	cvtColor(XQAImage, XQAImage, COLOR_RGB2GRAY);//这里需要将图片转为灰度图
	Mat XQAImageOtsu;//存储大津法输出
	threshold(XQAImage, XQAImageOtsu, 0, 255, THRESH_OTSU); //图片“xqa.jpg”的方差阈值为0

	namedWindow("【效果图】Otsu图像分割",0);
	resizeWindow("【效果图】Otsu图像分割", 600, 405);
	imshow("【效果图】Otsu图像分割", XQAImageOtsu);

    waitKey(0);
	destroyAllWindows();
    return 0;
}
//姓名：席庆澳|学号：B21023716|完成时间：2022年11月10日00:09:47