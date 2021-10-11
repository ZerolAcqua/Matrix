#include "Matrix.h"
#include "math.h"

using namespace std;
int main()
{
	//����
	Matrix A = { 1,2,3 };
	cout << A << endl;
	//��������
	Matrix B = -+-+-+-A;
	B += 1;
	cout << B << endl;
	//������ֵ
	A = {{1,2,3},
		 {4,5,6},
		 {7,8,10}};
	cout << A << endl;

	//ת��+�ƶ�����
	Matrix C = A.transpose();
	cout << C<< endl;
	//����+�ƶ���ֵ
	B = A.inverse();
	cout << B << endl;
	
	//����
	cout << "/" << endl;
	Matrix D = A * A - 2 * -(+(-A)) * 2;
	cout << D.transpose()<< endl;
	cout << D.inverse() << endl;
	cout << A / D << endl;
	cout << 1 / D << endl;
	cout << D / 2 << endl;
	cout << D / 0 << endl;
	cout << D / D << endl;




	double det = 0;
	D.det(det);
	cout << det << endl;

	const Matrix E = D.transpose() + A;
	cout << E << endl;
	D[0][0] = 1;	// �����ð汾  ��ȷ
	//E[0][0] = 1;  //	 ���ð汾  ����

	//�վ���ļ���
	Matrix F;
	Matrix G = ++--F--++ * 2 - 1;
	cout << F << endl;
	cout << G << endl;

	const Matrix H = 2 * A;
	Matrix I = H * 2;


	cout << H << endl;
	cout << I << endl;
	cout << ++--I--++ << endl;

	cout << I << endl;


}