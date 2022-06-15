#include "Matrix.h"
#include "math.h"

#define _MATRIX_DEBUG


using namespace std;
int main()
{
	Matrix::setPrecise(1);

#ifndef _MATRIX_DEBUG
	//����
	Matrix A = { 1,2,3 };
	cout << A << endl;
	//��������
	Matrix B = -+-+-+-A;
	B += 1;
	cout << B << endl;
	//������ֵ
	A = { {1,2,3},
		 {4,5,6},
		 {7,8,10} };
	cout << A << endl;

	//ת��+�ƶ�����
	Matrix C = A.transpose();
	cout << C << endl;
	//����+�ƶ���ֵ
	B = A.inverse();
	cout << B << endl;

	//����
	cout << "/" << endl;
	Matrix D = A * A - 2 * -(+(-A)) * 2;
	cout << D.transpose() << endl;
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

	//����ֿ飨����Ӧ�ýзָ
	cout << "�ֿ�" << endl;
	cout << I.getBlock(0, 0, 3, 3) << endl;
	cout << I.getBlock(-1, -1, 3, 3) << endl;
	cout << I.getBlock(0, 0, 4, 4) << endl;
	cout << I.getBlock(1, 1, -1, -1) << endl;
	cout << I.getBlock(1, 1, 2, 2) << endl;

	//���÷ֿ�
	cout << "���÷ֿ�" << endl;
	cout << I.setBlock(0, 0, Matrix::eye(4, 4)) << endl;
	cout << I.setBlock(1, 1, Matrix::eye(2, 2)) << endl;
	cout << I.setBlock(0, 1, Matrix::eye(2, 2)) << endl;
	cout << I.setBlock(0, 0, Matrix({ 3,4,5 })) << endl;

	// �е����
	cout << "�е�" << endl;
	I == I;
	cout << D / 1e-16 << endl;
	A = { {1,2,3.5},
			{2,4,7} ,
			{3,6,9} };
	cout << A.inverse();

	// Hessenberg
	Matrix J = { {1,2,1,2},
				{2,2,-1,1},
				{1,-1,1,1},
				{2,1,1,1} };
	Matrix Qh = Matrix::eye(4);
	cout << "Hessenberg" << endl;

	//cout << J.Hessenberg(Qh) << Qh <<Qh.transpose()<< endl;	// �����棿����

	Matrix H = J.Hessenberg(Qh);
	cout << H << Qh << Qh.transpose() * J * Qh << endl;
	Matrix Q, R;
	H.QRDecom4Hessenberg(Q, R);
	cout << "QR" << endl;
	cout << Q << Q.transpose() * Q << R << H << Q * R << R * Q << endl;


	Matrix diag = { 1,2,3,4 };
	cout << diag << Matrix::diag(diag) << Matrix::diag(diag.transpose()) << endl;
	Matrix A = { {1,2,3,4},{5,6,7,8},{9,10,11,12} };
	Matrix B = { {43,32,1},{5,3,8},{9,10,11},{3,0,0} };
	cout << A << Matrix::diag(A) << B << Matrix::diag(B) << endl;

#endif



	Matrix B = { {1,2,1,2},
				{2,5,-1,1},
				{1,-1,1,1},
				{2,1,1,1} };
	Matrix Q, R;
	B.qrDecom(Q, R);
	cout << B << Q << R << Q * R << Q * Q.transpose() << endl;

}