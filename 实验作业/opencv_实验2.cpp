//ʵ��2 ���³�����Լ�ʵ���㷨��Ҳ���Ե���OpenCV�ĺ���
//1. ʹ��Canny�㷨���б�Ե��⡪��1)��˹�˲���2)Sobel����ͼ���񻯣�3)�Ǽ���ֵ���ƣ�4)˫��ֵ������
//2. ���ô�򷨽���ͼ��ָ
#include<opencv2/opencv.hpp>

using namespace cv;

Mat XQAImage;//ԭͼ

int main()
{
	XQAImage = imread("ϯ�����ҵ��ͼ-����.jpg");
	if (!XQAImage.data){printf("\n����ʾ����ȡͼ�����,��������е�������ͼ���Ƿ�һ�¡�\n");return false;}
	namedWindow("��ԭͼ��",0);
	resizeWindow("��ԭͼ��", 600, 405);
	imshow("��ԭͼ��", XQAImage);

	"---------------\t��ʵ������1��ʹ��Canny�㷨���б�Ե���\t---------------\n";
	Mat XQAImage_2;//�洢�Ҷ�ͼ
	cvtColor(XQAImage, XQAImage_2, COLOR_RGB2GRAY);//��ͼת�Ҷ�ͼ
	Mat XQAImage_3;//�洢��Canny���Ӵ���ı�Եͼ
	GaussianBlur(XQAImage_2, XQAImage_3, Size(3, 3),0.01);//����,��˹�����Խ��ͼ��Խģ����
										//Sigma(��)Խ��ƽ��Ч��Խ���ԣ�����ƽ��ϵ����0.01��
	Canny(XQAImage_3, XQAImage_3, 254,254, 3,false); //����ֵ����Ϊ255���ף�����Ϊ0���ڣ�
	//������ֵ1�������������������ص�ᱻ��Ϊ���Ǳ�Ե��������ֵ2�����ĸ������������ص�ᱻ��Ϊ�Ǳ�Ե
	Mat XQAImage_4;//�洢canny�㷨���
	XQAImage_4.create(XQAImage.size(), XQAImage.type());//������ԭͼͬ���ͺʹ�С��ͼ������˵����
	XQAImage_4 = Scalar::all(0); //��XQAImage_4�ڵ�����Ԫ������Ϊ0
	XQAImage.copyTo(XQAImage_4, XQAImage_3);//ʹ��Canny��������ı�Եͼ��Ϊ���룬����ԭͼ����Ч��ͼ��
	namedWindow("��Ч��ͼ��Canny�㷨��Ե���",0);
	resizeWindow("��Ч��ͼ��Canny�㷨��Ե���", 600, 405);
	imshow("��Ч��ͼ��Canny�㷨��Ե���", XQAImage_4);
	
	"---------------\t��ʵ������2�����ô�򷨽���ͼ��ָ�\t-------------------\n";
	cvtColor(XQAImage, XQAImage, COLOR_RGB2GRAY);//������Ҫ��ͼƬתΪ�Ҷ�ͼ
	Mat XQAImageOtsu;//�洢������
	threshold(XQAImage, XQAImageOtsu, 0, 255, THRESH_OTSU); //ͼƬ��xqa.jpg���ķ�����ֵΪ0

	namedWindow("��Ч��ͼ��Otsuͼ��ָ�",0);
	resizeWindow("��Ч��ͼ��Otsuͼ��ָ�", 600, 405);
	imshow("��Ч��ͼ��Otsuͼ��ָ�", XQAImageOtsu);

    waitKey(0);
	destroyAllWindows();
    return 0;
}
//������ϯ���|ѧ�ţ�B21023716|���ʱ�䣺2022��11��10��00:09:47