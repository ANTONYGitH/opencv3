//��ҵ2 ��һ��ͼ�񣬶�ԭͼ������ֵ�˲�����ʾЧ����Soble������ȡ��Ե����ʾЧ����
#include "opencv2/core/core.hpp" 
#include "opencv2/highgui/highgui.hpp" 
#include "opencv2/imgproc/imgproc.hpp" 
 
using namespace cv;

int main()
{
	Mat XQAImage = imread("�����ձ�.jpg");//ԭͼ
	Mat medianBlurImage;//��ֵ�˲����ͼ
	Mat out_xImage, out_yImage;//Sobel
	Mat abs_x, abs_y;
	Mat SobelImage;//Sobel��ȡ���ͼ
	int medianBlurValue = 1;
	//��ֵ�˲�
	medianBlur(XQAImage, medianBlurImage, medianBlurValue*2+1);//ע��˴��������������������޸ģ��������medianBlurValue*2+1
	//��sobel������ȡ��Ե
	Sobel(XQAImage, out_xImage, CV_64F, 1, 0, 1, 1, 1, BORDER_DEFAULT);//��x�����ݶ�,��6������Ϊsoble�ںˣ�����Ҫ
	convertScaleAbs(out_xImage, abs_x);
	Sobel(XQAImage, out_yImage, CV_64F, 0, 1, 1, 1, 1, BORDER_DEFAULT);//��y�����ݶ�
	convertScaleAbs(out_yImage, abs_y);
	addWeighted(abs_x, 0.5, abs_y, 0.5, 0, SobelImage);
	//��ʾͼ��
	namedWindow("��ԭͼ������ͼ��-XQA", 0);
	resizeWindow("��ԭͼ������ͼ��-XQA", 400, 270);
	imshow("��ԭͼ������ͼ��-XQA", XQAImage);
	namedWindow("��Ч��ͼ����ֵ�˲���-XQA", 0);
	resizeWindow("��Ч��ͼ����ֵ�˲���-XQA", 400, 270);
	imshow("��Ч��ͼ����ֵ�˲���-XQA", medianBlurImage);
	namedWindow("��Ч��ͼ��Sobel��ȡ��-XQA", 0);
	resizeWindow("��Ч��ͼ��Sobel��ȡ��-XQA", 400, 270);
	imshow("��Ч��ͼ��Sobel��ȡ��-XQA", SobelImage);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
//������ϯ���|ѧ�ţ�B21023716|���ʱ�䣺2022��9��15��18:13:50