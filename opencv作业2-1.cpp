//��ҵ1 ��ʾһ�������廷ͼ�񣬲��������͡���ʴ��������ʾЧ����
#include<opencv2/opencv.hpp>
using namespace cv;

Mat XQAImage, Dil_or_Ero_XQAImage;//��һ��Ϊԭͼ���ڶ���ΪЧ��ͼ
int BarNum = 2;//0��ʾ��ʴ��1��ʾ����,2��ʾ���Ͳ���ʴ
int CoreSize = 0;//�ں˾���ĳߴ�

void Process();
void NewBar(int, void*);//�ص�����
void NewSize(int, void*);//�ص�����

int main()
{
	XQAImage = imread("�����廷.bmp");//ԭͼ	
	if (!XQAImage.data)
	{
		printf("\n����ʾ����ȡͼ�����,��������е�������ͼ���Ƿ�һ�¡�\n");
		system("pause");
		return 0;
	}
	namedWindow("��ԭͼ��", 0);
	resizeWindow("��ԭͼ��", 400, 270);
	imshow("��ԭͼ��", XQAImage);
	
	namedWindow("������/��ʴ���Ч��ͼ��", 0);
	resizeWindow("������/��ʴ���Ч��ͼ��", 400, 270);
	createTrackbar("��ֵ��С", "������/��ʴ���Ч��ͼ��", &CoreSize, 30, NewSize);
	createTrackbar("��λ�任��", "������/��ʴ���Ч��ͼ��", &BarNum, 2, NewBar);//��ʴ0/����1/��ʴ������2
	
	waitKey(0);
	destroyAllWindows();
	return 0;
}
void Process()
{
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * CoreSize + 1, 2 * CoreSize + 1), Point(CoreSize, CoreSize));
	//���и�ʴ�����Ͳ���|��ʴ0/����1/��ʴ������2
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
	putText(Dil_or_Ero_XQAImage, "B21023716XQA's Tips(Look Down)", Point(20, 480), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2, 8);//��ͼƬ��д����
	namedWindow("������/��ʴ���Ч��ͼ��", 0);
	resizeWindow("������/��ʴ���Ч��ͼ��", 400, 270);
	imshow("������/��ʴ���Ч��ͼ��", Dil_or_Ero_XQAImage);
}
void NewBar(int, void*)
{
	Process();
}
void NewSize(int, void*)
{
	Process();
}
//������ϯ���|ѧ�ţ�B21023716|���ʱ�䣺2022��9��9��11:40:00