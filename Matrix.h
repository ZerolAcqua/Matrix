#ifndef _Matrix_H
#define _Matrix_H
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <initializer_list>

//************************************************************************************
// 										Matrix��
//
//		�������ڽ��о���Ļ�������
//		1.	����ӷ����������ˣ�����˷�
//		2.	����㲥������ϲ��������е�
//		3.	��˹��Ԫ��������
//		4.	��������ʽ���������棬��������
//																			2021/3/22
//																				Acqua
//---------------------------------version: 0.1.0-------------------------------------
// 
//		1.	����ע�ͣ��޸ı�������
//      2.	�Ż��޸��˲��ֵĹ��캯���;�̬����
//			1)eye
//			2)ones
//			3)zeros
//		3.	�������ƶ����캯�����ƶ���ֵ����ʵ��
//																			2021/10/2
//		4.	������<<���������ʵ�������
//		5.	�޲ι��캯���ʹ��󷵻صľ������Ϊ0*0�Ŀվ��󣬲��޸���
//			���ֺ����ڼ�������״�Ĵ���(��Ҫ�ǿվ�����ж�)
//		6.	�޸��˴󲿷ֳ�Ա��������Ϊ�ǳ�Ա��������Ϊ��Ԫ������
//			��������Ϊ�������ã���ֵ����ֵ���ھ��ɰ󶨡�����
//			1) ��Ա���� =rvalue  =lvalue
//			2) ��Ԫ���� Matrix+Matrix Matrix-Matrix
//			3) ��Ԫ���� Matrix*Matrix
//			4) ��Ԫ���� factor*Matrix Matrix*factor
//		TODO:	
//		1. ����㲥��
//		2. ���ϸ�ֵ"+=""-="��
//		3. ǰ��������"++"�Լ�"--"��
//		4. ��Ԫ�����"+/-",
//		5. ������� "/"  
//																			2021/10/5
// 
// 
//		1.	����㲥��ֻ���������ֵģ�
//		2.	���ϸ�ֵ"+=""-="
//		3.	��Ԫ�����"+/-"
//																			2021/10/9	
//	
//		1. ǰ��������"++"�Լ�"--"��
//		2. ������� "/"  
//		3. �޸��˲��ָ�������������const�ؼ��֣�ʹ�䲻���޸ĳ�Ա����
// 
//																			2021/10/11	
//---------------------------------version: 0.1.2-------------------------------------
// 
// 
// 
//		TODO:	
//		1.	ǰ��������"++"�Լ�"--"��
//		2.	������� "/"
//		3.	������ֵ�Ƿ�Ҫת��Ϊ���������
//			1���漰���������չ���⣬�����Ǻ�����  
//			2���漰�������ļ����⣬�����������ֿ���������Լ��ٺ������ص�������
//			   �����е������Ϊֻ������������㣬���ҿ��Խ����������ֵļӼ���ͳ
//				һ���㲥����
//			3) ����Ҳ�����⣬��������˹���Ĺ㲥���磨6*4��+��3*2�������ľ������㣬
//			   ��ô��Ӧ���Ǵ��������ͻ�����ͨ��
//		4.	������������غ󣬹���һЩ�����������ع�����
//																		
//		
// 
// 
//************************************************************************************


typedef std::initializer_list<double> MatIniLst;	//��ʼ���б�

class Matrix
{
	// ---- ��Ա���� ----
private:
	int miRow = 0;		//����
	int miCol = 0;		//����
	double* mpBuf = nullptr;	//�洢����

public:
	// ---- ������������ ----

	/**
	*	@brief �޲������캯��
	* 
	*	��ȡһ��0*0��δ�����ڴ�Ŀվ���
	*	���Ϸ��ļ���һ�㷵�ر�����
	*/
	explicit Matrix();

	/**
	*	@brief ���캯��
	*   ��double����ת��Ϊ1*1����
	*
	*	@param num ����
	*/
	Matrix(double num);

	/**
	*	@brief ���캯��
	*	ʹ�ó�ʼ���б������
	*
	*	@param lst ��ʼ���б�
	*/
	Matrix(const MatIniLst& lst);


	/**
	*	@brief ���캯��
	*	ʹ�ó�ʼ���б����������Ϊ����һ�е�Ԫ�ظ�����������0���������е�Ԫ��
	*
	*	@param lst ��ʼ���б����㣩
	*/
	Matrix(const std::initializer_list<MatIniLst>& lst);

	/**
	*	@brief ���캯��
	*	ʹ�ó�ʼ���б�����󣬸����趨��������������0�����ʼ���б���û�е�Ԫ��
	*
	*	@param lst ��ʼ���б����㣩
	*	@param col ��������
	*/
	explicit Matrix(const std::initializer_list<MatIniLst>& lst, int col);

	/**
	*	@brief ���캯��
	*	ʹ��ָ����ָ�����ݹ������,�����鳤��С����Ҫ�ĳ���row*col����ᱨ��
	*
	*	@param p double��ָ�룬��Ҫ���������
	*	@param row ��������
	*	@param col ��������
	*   @param count ���鳤��
	*/
	explicit Matrix(double* p, int row, int col, int count);

	/**
	*	@brief �������캯��
	*
	*/
	Matrix(const Matrix& tmp);

	/**
	*	@brief �ƶ����캯��
	*
	*/
	Matrix(Matrix&& tmp);

	/**
	*	@brief ��������
	*/
	~Matrix();

	// ---- ��̬��Ա���� ----

	/**
	*	@brief ��̬����
	*	����һ�������������ɵ�λ����
	*
	*	@param row ����Ľ���
	*	@return ���ص�λ����
	*/
	static Matrix eye(int row);

	/**
	*	@brief ��̬����
	*	����һ�������������ɵ�λ����
	*
	*	@param row ���������
	*	@param col ���������
	*	@return ���ص�λ����
	*/
	static Matrix eye(int row, int col);

	/**
	*	@brief ��̬����
	*	����һ��������������Ԫ��ȫΪ1�ķ���
	*
	*	@param row ����Ľ���
	*	@return ����Ԫ��ȫΪ1�ķ���
	*/
	static Matrix ones(int row);

	/**
	*	@brief ��̬����
	*	����һ��������������Ԫ��ȫΪ1�ľ���
	*
	*	@param row ���������
	*	@param col ���������
	*	@return ����Ԫ��ȫΪ1�ľ���
	*/
	static Matrix ones(int row, int col);

	/**
	*	@brief ��̬����
	*	����һ��������������Ԫ��ȫΪ0�ķ���
	*
	*	@param row ����Ľ���
	*	@return ����Ԫ��ȫΪ0�ķ���
	*/
	static Matrix zeros(int row);


	/**
	*	@brief ��̬����
	*	����һ��������������Ԫ��ȫΪ0�ľ���
	*
	*	@param row ���������
	*	@param col ���������
	*	@return ����Ԫ��ȫΪ0�ľ���
	*/
	static Matrix zeros(int row, int col);

	// ---- ��������� ----

	/**
	*	@brief ��������أ�������ֵ����
	*	������ֵ
	*
	*	@param tmp ����ֵ�ľ���
	*	@return ���ظ�ֵ֮��ĸþ��������
	*/
	Matrix& operator=(const Matrix& tmp);

	/**
	*	@brief ��������أ��ƶ���ֵ����
	*	������ֵ
	*
	*	@param tmp ����ֵ�ľ���
	*	@return ���ظ�ֵ֮��ĸþ��������
	*/
	Matrix& operator=(Matrix&& tmp);

	/**
	*	@brief ���������,��Ԫ����
	*	������������������������
	*
	*	@param lMat ��Ӿ���
	*	@param rMat �ҼӾ���
	*	@return �������֮��ĸþ��������
	*/
	friend Matrix operator+(const Matrix& lMat, const Matrix& rMat);

	/**
	*	@brief ���������,��Ԫ����
	*	������������������������
	*
	*	@param lMat �󱻼�����
	*	@param rMat �Ҽ�����
	*	@return �������֮��ľ���
	*/
	friend Matrix operator-(const Matrix& lMat, const Matrix& rMat);

	/**
	*	@brief ���������,��Ԫ����
	*	��������������������������˻�
	*
	*	@param lMat ��˾���
	*	@param rMat �ҳ˾���
	*	@return ���������˻�֮����¾���
	*/
	friend Matrix operator*(const Matrix& lMat, const Matrix& rMat);

	/**
	*	@brief ���������,��Ԫ����
	*	double*matrix
	*	����һ������
	*
	*	@param lFactor ��˵�ϵ��
	*	@param rMat ����
	*	@return ���ؾ������˺�Ľ��
	*/
	friend Matrix operator*(const double& lFactor, const Matrix& rMat);

	/**
	*	@brief ���������,��Ԫ����
	*   matrix*double
	*	����һ������
	* 
	*	@param lMat ����
	*	@param rFactor �ҳ˵�ϵ��
	*	@return ���ؾ������˺�Ľ��
	*/
	friend Matrix operator*(const Matrix& lMat, const double& rFactor);

	/**
	*	@brief ���������,��Ԫ����
	*	��������������������������˻�
	*
	*	@param lMat ��������
	*	@param rMat �ҳ�����
	*	@return ������������֮��ľ���
	*/
	friend Matrix operator/(const Matrix& lMat, const Matrix& rMat);

	/**
	*	@brief ���������,��Ԫ����
	*	double/matrix
	*	����һ������
	*
	*	@param lFactor ������ϵ��
	*	@param rMat �ҳ�����
	*	@return ���ؾ��������Ľ��
	*/
	friend Matrix operator/(const double& lFactor, const Matrix& rMat);

	/**
	*	@brief ���������,��Ԫ����
	*   matrix/double
	*	����һ������
	*
	*	@param lMat �����ľ���
	*	@param rFactor �ҳ�ϵ��
	*	@return ���ؾ��������Ľ��
	*/
	friend Matrix operator/(const Matrix& lMat, const double& rFactor);

	/**
	*	@brief ���������,��Ԫ����
	*	matrix+double
	*	����һ������
	*
	*	@param lMat ��ӵľ���
	*	@param rMat �Ҽӵ�����
	*	@return ���ؾ���㲥��Ľ��
	*/
	friend Matrix operator+(const Matrix& lMat, const double& rNum);
	
	/**
	*	@brief ���������,��Ԫ����
	*	double+matrix
	*	����һ������
	*
	*	@param lNum ��ӵ�����
	*	@param rMat �Ҽӵľ���
	*	@return ���ؾ���㲥��Ľ��
	*/
	friend Matrix operator+(const double& lNum, const Matrix& rMat);
	
	/**
	*	@brief ���������,��Ԫ����
	*	matrix-double
	*	����һ������
	*
	*	@param lMat �����ľ���
	*	@param rMat ��������
	*	@return ���ؾ���㲥��Ľ��
	*/
	friend Matrix operator-(const Matrix& lMat, const double& rNum);
	
	/**	
	*	@brief ���������,��Ԫ����
	*	double-matrix
	*	����һ������
	*
	*	@param lNum ����������
	*	@param rMat ���ľ���
	*	@return ���ؾ���㲥��Ľ��
	*/
	friend Matrix operator-(const double& lNum, const Matrix& rMat);

	/**
	*	@brief ���������
	*   ���ϸ�ֵ+=
	*
	*	@param tmp Ҫ���ϵľ���
	*	@return ���ؽ�����������
	*/
	Matrix& operator+=(const Matrix& tmp);

	/**
	*	@brief ���������
	*   ���ϸ�ֵ+= 
	*
	*	@param tmp Ҫ���ϵľ���
	*	@return ���ؽ���þ��������
	*/
	Matrix& operator+=(const double& num);

	/**
	*	@brief ���������
	*   ���ϸ�ֵ-=
	*
	*	@param tmp Ҫ��ȥ�ľ���
	*	@return ���ؽ�����������
	*/
	Matrix& operator-=(const Matrix& tmp);

	/**
	*	@brief ���������
	*   ���ϸ�ֵ+=
	*
	*	@param tmp Ҫ��ȥ������
	*	@return ���ؽ�����������
	*/
	Matrix& operator-=(const double& num);
	
	/**
	*	@brief ���������,��Ԫ����
	*   �е�
	*
	*	@param lMat �����
	*	@param rMat �Ҿ���
	*	@return �����еȽ��
	*/
	friend bool operator==(const Matrix& lMat, const Matrix& rMat);
	/**
	*	@brief ���������,��Ԫ����
	*   �в���
	*
	*	@param lMat �����
	*	@param rMat �Ҿ���
	*	@return �����в��Ƚ��
	*/
	friend bool operator!=(const Matrix& lMat, const Matrix& rMat);

	/**
	*	@brief ���������,��Ԫ����
	*   ȡ�෴
	*
	*	@param Mat ����
	*	@return ����ȡ�����
	*/
	friend Matrix operator-(const Matrix& Mat);
	/**
	*	@brief ���������,��Ԫ����
	*   ����
	*
	*	@param Mat ����
	*	@return ���ز���Ľ��
	*/
	friend Matrix operator+(const Matrix& Mat);


	/**
	*	@brief ���������
	*   ǰ�õ���
	*
	*	@return ������ľ�������
	*/
	Matrix& operator++();
	
	/**
	*	@brief ���������
	*   ���õ���
	*	
	*	@param ����ǰ���õĲ���
	*	@return ����ǰ�ľ���
	*/
	Matrix operator++(int);
	
	/**
	*	@brief ���������
	*   ǰ�õݼ�
	*
	*	@return �ݼ���ľ�������
	*/
	Matrix& operator--();
	
	/**
	*	@brief ���������
	*   ���õݼ�
	*
	*	@param ����ǰ���õĲ���
	*	@return �ݼ�ǰ�ľ���
	*/
	Matrix operator--(int);


	/**
	*	@brief ���������
	*   ȡ�±�
	*	�����±��Ӧ�ľ����ĳһ��
	*   һ������ʹ������[]�Ի�ȡĳ��ָ��
	*   ��Ҫ����ķ�����ʹ��ȡ�±������������
	*	�������汾����Ϊ�ǳ����汾
	*
	*	@param num �±�
	*	@return �����±��Ӧ�ľ����ĳһ�еĵ�һ��Ԫ�ص�ָ��
	*/
	double* operator[](int num);
	/**
	*	@brief ���������
	*   ȡ�±�
	*	�����±��Ӧ�ľ����ĳһ��
	*   һ������ʹ������[]�Ի�ȡĳ��ָ��
	*   ��Ҫ����ķ�����ʹ��ȡ�±������������
	*	�������汾����Ϊ�����汾
	*
	*	@param num �±�
	*	@return �����±��Ӧ�ľ����ĳһ�еĵ�һ��Ԫ�ص�ָ��
	*/
	const double* operator[](int num)const;

	/**
	*	@brief ���������,��Ԫ����
	*   ����ʵ��cout<< xxx << xxx
	*	����ostream������
	*
	*  @param os ostream
	*  @param tmp ����
	*  @return ����os�����ü�ostream&
	*/
	friend std::ostream& operator<<(std::ostream& os,  const Matrix& tmp);
	



	// ����������������������������������������������
	// ʩ���У�����ʩ���У�����ʩ���У�����ʩ���У�����
	// ʩ���У�����ʩ���У�����ʩ���У�����ʩ���У�����
	// ʩ���У�����ʩ���У�����ʩ���У�����ʩ���У�����
	// ʩ���У�����ʩ���У�����ʩ���У�����ʩ���У�����
	// ����������������������������������������������


public:
	int getRow();
	int getCol();

	const Matrix add(const Matrix& tmp)const;
	const Matrix sub(const Matrix& tmp)const;
	const Matrix rMultiple(const Matrix& tmp)const;
	const Matrix sMultiple(const double& factor)const;

	const Matrix transpose()const;
	bool det(double& result)const;
	Matrix gauss();
	const Matrix inverse()const;
	int rank();

	bool sizeValidityCheck();
	void rAdd(int des, int src, double factor);
	bool rExchange(int des, int src);
	void rTime(int des, double factor);
	Matrix merge(Matrix& right)const;
	Matrix divide(int col);
	static Matrix LRMerge(Matrix& left, Matrix& right);
	static Matrix UDMerge(Matrix& up, Matrix& down);



};




#endif // !_Matrix
