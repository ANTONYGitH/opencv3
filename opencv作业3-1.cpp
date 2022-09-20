//作业1 学习如何在opencv中使用鼠标进行交互
#include<opencv2/opencv.hpp>
using namespace cv;

constexpr auto WINDOW_NAME = "席庆澳作业-鼠标操作";

void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle(Mat& img, Rect box);//绘制矩形声明


Rect g_rectangle;
bool g_bDrawingBox = false;//检查鼠标右键是否按下
RNG rng((unsigned)time(NULL));//用于产生颜色

int main(int argc, char** argv)
{
	g_rectangle = Rect(-1, -1, 0, 0);
	Mat XQAImage(540, 960, CV_8UC3), XQAImage2;//8位无符号带Alpha通道的RGB彩色图像
	XQAImage.copyTo(XQAImage2);
	g_rectangle = Rect(-1, -1, 0, 0);
	XQAImage = Scalar::all(0);

	namedWindow(WINDOW_NAME);
	setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*)&XQAImage);

	while (1)
	{
		printf("\n按下鼠标【右键】进行矩形绘制，按下ESC键退出\n");//输出提示信息

		XQAImage.copyTo(XQAImage2);
		if (g_bDrawingBox) DrawRectangle(XQAImage2, g_rectangle);//当进行绘制的标识符为真，则进行绘制
		imshow(WINDOW_NAME, XQAImage2);
		if (waitKey(10) == 27) break;//ESC的ASCCll码是27，按下ESC键，程序退出
	}
	destroyAllWindows();
	return 0;
}


void on_MouseHandle(int event, int x, int y, int flags, void* param)//回调函数，参考opencv3编程手册
{

	Mat& image = *(Mat*)param;
	switch (event)
	{
	case EVENT_MOUSEMOVE:
	{
		if (g_bDrawingBox)//如果是否进行绘制的标识符为真，则记录下长和宽到RECT型变量中
		{
			g_rectangle.width = x - g_rectangle.x;
			g_rectangle.height = y - g_rectangle.y;
		}
	}
	break;

	//右键按下
	case EVENT_RBUTTONDOWN:
	{
		g_bDrawingBox = true;
		g_rectangle = Rect(x, y, 1, 1);//记录起始点
	}
	break;

	//右键抬起
	case EVENT_RBUTTONUP:
	{
		g_bDrawingBox = false;//置标识符为false
		//对宽和高小于0的处理
		if (g_rectangle.width < 0)
		{
			g_rectangle.x += g_rectangle.width;
			g_rectangle.width *= -1;
		}

		if (g_rectangle.height < 0)
		{
			g_rectangle.y += g_rectangle.height;
			g_rectangle.height *= -1;
		}
		//调用函数进行绘制
		DrawRectangle(image, g_rectangle);
	}
	break;

	}
}

void DrawRectangle(Mat& img, Rect box)//绘制矩形函数
{
	rectangle(img, box.tl(), box.br(), Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)));//随机颜色
}


//姓名：席庆澳|学号：B21023716|完成时间：2022年9月15日20:46:02