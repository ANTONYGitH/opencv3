//ѧϰͼ������ֵ���Աȶȵ��������ο���132ҳ��
#include<opencv2/opencv.hpp>

using namespace cv;
Mat XQAImage, XQAImage2;//XQAImageΪԭͼ��XQAImage2ΪЧ��ͼ
int Initial_Contrast=7, Initial_Bright=16;//�Աȶȳ�ֵ�����ȳ�ֵ
void ContrastAndBright(int, void*);

int main()
{
	XQAImage = imread("�����ձ�.jpg");//ԭͼ
	XQAImage2 = Mat::zeros(XQAImage.size(), XQAImage.type());
	namedWindow("��ԭͼ������ͼ��-XQA", 0);
	resizeWindow("��ԭͼ������ͼ��-XQA", 600, 405);
	imshow("��ԭͼ������ͼ��-XQA", XQAImage);

	namedWindow("��Ч��ͼ������ͼ��-XQA", 0);
	resizeWindow("��Ч��ͼ������ͼ��-XQA", 600, 491);//���ڽ������Ŀ��Ϊ43*2�����Խ����ڼӿ�491
	createTrackbar("�Աȶ�","��Ч��ͼ������ͼ��-XQA", &Initial_Contrast, 30, ContrastAndBright);
	createTrackbar("����", "��Ч��ͼ������ͼ��-XQA", &Initial_Bright, 20, ContrastAndBright);
	
	ContrastAndBright(Initial_Contrast, 0);//�ص����������Աȶ�
	ContrastAndBright(Initial_Bright, 0);//�ص�������������
	waitKey(0);
	destroyAllWindows();
	return 0;
}

void ContrastAndBright(int, void*)//�ο���opencv3������š�Դ��
{
	for (int y = 0; y < XQAImage.rows; y++)
	{
		for (int x = 0; x < XQAImage.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				XQAImage2.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((Initial_Contrast * 0.1) * (XQAImage.at<Vec3b>(y, x)[c]) + Initial_Bright);//���ڵ������������ʳ�0.001��Ϊ��0.1
			}
		}
	}
	imshow("��Ч��ͼ������ͼ��-XQA", XQAImage2);
}
//������ϯ���|ѧ�ţ�B21023716|���ʱ�䣺2022��9��20��11:49:05