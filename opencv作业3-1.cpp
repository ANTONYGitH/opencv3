//��ҵ1 ѧϰ�����opencv��ʹ�������н���
#include<opencv2/opencv.hpp>
using namespace cv;

constexpr auto WINDOW_NAME = "ϯ�����ҵ-������";

void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle(Mat& img, Rect box);//���ƾ�������


Rect g_rectangle;
bool g_bDrawingBox = false;//�������Ҽ��Ƿ���
RNG rng((unsigned)time(NULL));//���ڲ�����ɫ

int main(int argc, char** argv)
{
	g_rectangle = Rect(-1, -1, 0, 0);
	Mat XQAImage(540, 960, CV_8UC3), XQAImage2;//8λ�޷��Ŵ�Alphaͨ����RGB��ɫͼ��
	XQAImage.copyTo(XQAImage2);
	g_rectangle = Rect(-1, -1, 0, 0);
	XQAImage = Scalar::all(0);

	namedWindow(WINDOW_NAME);
	setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*)&XQAImage);

	while (1)
	{
		printf("\n������꡾�Ҽ������о��λ��ƣ�����ESC���˳�\n");//�����ʾ��Ϣ

		XQAImage.copyTo(XQAImage2);
		if (g_bDrawingBox) DrawRectangle(XQAImage2, g_rectangle);//�����л��Ƶı�ʶ��Ϊ�棬����л���
		imshow(WINDOW_NAME, XQAImage2);
		if (waitKey(10) == 27) break;//ESC��ASCCll����27������ESC���������˳�
	}
	destroyAllWindows();
	return 0;
}


void on_MouseHandle(int event, int x, int y, int flags, void* param)//�ص��������ο�opencv3����ֲ�
{

	Mat& image = *(Mat*)param;
	switch (event)
	{
	case EVENT_MOUSEMOVE:
	{
		if (g_bDrawingBox)//����Ƿ���л��Ƶı�ʶ��Ϊ�棬���¼�³��Ϳ�RECT�ͱ�����
		{
			g_rectangle.width = x - g_rectangle.x;
			g_rectangle.height = y - g_rectangle.y;
		}
	}
	break;

	//�Ҽ�����
	case EVENT_RBUTTONDOWN:
	{
		g_bDrawingBox = true;
		g_rectangle = Rect(x, y, 1, 1);//��¼��ʼ��
	}
	break;

	//�Ҽ�̧��
	case EVENT_RBUTTONUP:
	{
		g_bDrawingBox = false;//�ñ�ʶ��Ϊfalse
		//�Կ�͸�С��0�Ĵ���
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
		//���ú������л���
		DrawRectangle(image, g_rectangle);
	}
	break;

	}
}

void DrawRectangle(Mat& img, Rect box)//���ƾ��κ���
{
	rectangle(img, box.tl(), box.br(), Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)));//�����ɫ
}


//������ϯ���|ѧ�ţ�B21023716|���ʱ�䣺2022��9��15��20:46:02