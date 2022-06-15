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
//-----------------------------------------------------------------------------------
// 
//		1.	����ע�ͣ��޸ı�������
//      2.	�Ż��޸��˲��ֵĹ��캯���;�̬����
//			1)eye
//			2)ones
//			3)zeros
//		3.	�������ƶ����캯�����ƶ���ֵ����ʵ��
//																			2021/10/02
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
//																			2021/10/05
// 
// 
//		1.	����㲥��ֻ���������ֵģ�
//		2.	���ϸ�ֵ"+=""-="
//		3.	��Ԫ�����"+/-"
//																			2021/10/09	
//	
//		1. ǰ��������"++"�Լ�"--"��
//		2. ������� "/"  
//		3. �޸��˲��ָ�������������const�ؼ��֣�ʹ�䲻���޸ĳ�Ա����
//		TODO:	
//		1.	������ֵ�Ƿ�Ҫת��Ϊ���������
//			1���漰���������չ���⣬�����Ǻ�����  
//			2���漰�������ļ����⣬�����������ֿ���������Լ��ٺ������ص�������
//			   �����е������Ϊֻ������������㣬���ҿ��Խ����������ֵļӼ���ͳ
//				һ���㲥����
//			3) ����Ҳ�����⣬��������˹���Ĺ㲥���磨6*4��+��3*2�������ľ������㣬
//			   ��ô��Ӧ���Ǵ��������ͻ�����ͨ��
//		2.	������������غ󣬹���һЩ�����������ع�����
//		3.	�ֿ����
//		4.	���Ⱥʹ�ӡ��صĲ���
//		5.	reshape��ش���
//																			2021/10/11	
//-----------------------------------------------------------------------------------
// 
//		1.	��������˲��ָ���������ע�ͣ������к�С�ĸĶ�
//		TODO:
//		1.	������������ֵ��QR�㷨������
//		2.	������ݣ��������ʽ���㲻���Σ�
//		3.	�ֿ����
//		4.	���Ⱥʹ�ӡ��صĲ���
//		5.	reshape��ش���
//																			2022/01/17																	
// 
//		1.	�޸��˸������еȵ��߼�
//		2.	����˾�����״������ظ�������
//		3.	���diag����
//		4.	�����eigen�������Լ���ص�hessenberg������qrDecom4Hessenberg����
//			Ŀǰ����������ֵֻ�ܼ���ʵ����ֵ��������ڸ�����ֵ����û�취������
//		5.	�����randMatrix()��������������0~1α���Ԫ����ɵľ���
//		TODO:
//		1.	��дһ���쳣�׳���صĶ�������Ȼ�Ժ�debug̫���ˣ���������һ����С�Ĺ���
//																			2022/01/21	
// 
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
	// ---- ��̬��Ա���� ----
	static int iPrecise;	// �������������ʾ����

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

	/**
	*	@brief ��̬����
	*	���С����������ɶԽǾ��󣬻��ߴ�һ�������ȡ�Խ���Ԫ��
	*
	*	@param mat 
	*	@return ���ضԽǾ��󣬻��ɾ��󷵻ضԽ�Ԫ��������
	*/
	static Matrix diag(Matrix mat);

	/**
	*	@brief ��̬����
	*	����Ԫ������ķ���
	*
	*	@param n	�������
	*	@return		�����������
	*/
	static Matrix randMatrix(int n);

	/**
	*	@brief ��̬����
	*	����Ԫ������ķ���
	*
	*	@param row	��������
	* 	@param col	��������
	*	@return		�����������
	*/
	static Matrix randMatrix(int row, int col);



	/**
	*	@brief ��̬����
	*	���þ�����ʾ�ľ���
	*
	*	@param precise ����
	*/
	static void setPrecise(int precise);


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
	*  @param os	ostream
	*  @param tmp	����
	*  @return ����os�����ü�ostream&
	*/
	friend std::ostream& operator<<(std::ostream& os,  const Matrix& tmp);
	

public:

	/**
	*	@brief ���к���
	*	
	*	@return ���ظþ��������
	*/
	int getRow()const;

	/**
	*	@brief ���к���
	*
	*	@return ���ظþ��������
	*/
	int getCol()const;

	/**
	*	@brief ���к���
	*	��������뱾����ĺͣ��롰+���ȼ�
	*	
	*	@param tmp ���ϵľ���
	*	@return ������ͺ�Ľ��
	*/
	Matrix add(const Matrix& tmp)const;

	/**
	*	@brief ���к���
	*	���㱾���������Ĳ�롰-���ȼ�
	*
	*	@param tmp ��ȥ�ľ���
	*	@return ��������Ľ��
	*/
	Matrix sub(const Matrix& tmp)const;

	/**
	*	@brief ���к���
	*	����ĳ�����ҳ˱������롰*���ȼ�
	*
	*	@param tmp �ҳ˵ľ���
	*	@return �����ҳ˺�Ľ��
	*/
	Matrix rMultiple(const Matrix& tmp)const;

	/**
	*	@brief ���к���
	*	����������ˣ��롰*���ȼ�
	*
	*	@param tmp ���˵���
	*	@return �����ҳ˺�Ľ��
	*/
	Matrix sMultiple(const double& factor)const;

	/**
	*	@brief ���к���
	*	����ת��
	*
	*	@return ����ת�õĽ��
	*/
	Matrix transpose()const;

	/**
	*	@brief ���к���
	*	������������ʽ���������������е�����ʽ����
	*
	*	@param result ��������ʽ��ֵ
	*	@return ��������ʽ����true�����򷵻�false
	*/
	bool det(double& result)const;

	/**
	*	@brief ���к���
	*	�Ծ�����и�˹��Ԫ
	*
	*	@return ���ظ�˹��Ԫ�Ľ��
	*/
	Matrix gauss()const;

	/**
	*	@brief ���к���
	*	��������
	*
	*	@return ��������Ľ��
	*/
	Matrix inverse()const;

	/**
	*	@brief ���к���
	*	����������
	*
	*	@return ���ؾ������
	*/
	int rank()const;

	/**
	*	@brief ���к���
	*	��������״����Ч��
	*
	*	@return ���������״��Ч������true,
	*			���򷵻�false������������Ϊ�վ���
	*/
	bool isSizeValidity();

	/*
	*	@brief	���к���
	*	�������Ƿ�Ϊ����
	* 
	*	@return	������Ϊ���󣬷���true��
	*			���򷵻�false
	*/
	bool isSquareMatrix()const;

	/*
	*	@brief	���к���
	*	�������Ƿ�Ϊ�վ���
	*
	*	@return	������Ϊ�վ��󣬷���true��
	*			���򷵻�false
	*/
	bool isEmptyMatrix()const;


	/**
	*	@brief ���к���
	*	���������
	*
	*	@param des		Ҫ�ӵ���Ŀ����
	*	@param src		��Ϊ���ӵ���
	*	@param factor	�����ϵ���������
	*/
	void rowAdd(int des, int src, double factor);

	/**
	*	@brief ���к���
	*	�н���
	*
	*	@return	�������ж��ԣ�����ŷ���true��
	*			���򷵻�false
	*/
	bool rowExchange(int des, int src);

	/**
	*	@brief ���к���
	*	������
	*
	*	@param des		Ҫ���˵�Ŀ����
	*	@param factor	�����ϵ���������
	*/
	void rowMultiply(int des, double factor);

	/**
	*	@brief ��̬����
	*	��������ƴ��
	* 
	*	@param left		ƴ������ߵľ���
	*	@param right	ƴ�����ұߵľ���
	*	@return			����ƴ�Ӻ�ľ���
	*/
	static Matrix lrMerge(Matrix& left, Matrix& right);

	/**
	*	@brief ��̬����
	*	��������ƴ��
	* 
	*	@param up		ƴ�����ϱߵľ���
	*	@param down		ƴ�����±ߵľ���
	*	@return			����ƴ�Ӻ�ľ���
	*/
	static Matrix udMerge(Matrix& up, Matrix& down);

	/**
	*	@brief ���к���
	*	�Ӿ���õ�һ�����
	*
	*	@param startRowId	�ֳ��ľ������Ͻ�Ԫ����ԭ�����е��кţ���0���㣩
	*	@param startColId	�ֳ��ľ������Ͻ�Ԫ����ԭ�����е��кţ���0���㣩
	*	@param blockRow		�ֳ��ľ��������
	*	@param blockCol		�ֳ��ľ��������
	*	@return				���طֳ��ľ���
	*						�����ֳܷ����󣬷��ؿվ���
	*/
	Matrix getBlock(int startRowId, int startColId, int blockRow, int blockCol)const;
	
	/**
	*	@brief ���к���
	*	�������ĳһ������Ϊ�����ľ���
	*
	*	@param startRowId	�����ľ������Ͻ�Ԫ����ԭ�����е��кţ���0���㣩
	*	@param startColId	�����ľ������Ͻ�Ԫ����ԭ�����е��кţ���0���㣩
	*	@param block		�����ľ���
	*	@return				���ر���������
	*						���������ã������޸ģ���Ȼ���ر���������
	*/
	Matrix& setBlock(int startRowId, int startColId, const Matrix& block);

	/**
	*	@brief ���к���
	*	���þ���Ϊ��Hessenberg���󣨷���
	* 
	*	@param Q		�ɱ��������Ʊ任����Hessenberg����ĶԳ�������
	*					H=Q^T*A*Q
	*	@return			��þ������Ƶ���Hessenberg����
	*/
	Matrix hessenberg(Matrix& Q)const;

	/**
	*	@brief ���к���
	*	�Ըþ������QR�ֽ�
	*
	*	@param Q	��������
	*	@param R	���������Ǿ���
	*/
	void qrDecom(Matrix& Q, Matrix& R)const;
	
	/*
	*	@brief ���к���
	*	����������ֵ���Ӵ�С���У�
	*
	*	@return		��������ֵ��ɵ����������Ӵ�С����
	*				��������,���ڸ�����ֵ��ԭ�����޷���⣬�򷵻ؿվ���
	*/
	Matrix eigen()const;


private:
	/**
	*	@brief ˽�о�̬����
	*	����ķ��ź�����������Hessenberg����
	*
	*	@param	num		Ҫ�������
	*	@return			����Ǹ�������1�����븺������-1
	*/
	static signed char sgn(double num);
	
	/**
	*	@brief ˽�к���
	*	����ƴ�ӣ����ڸ�˹��Ԫ�����棩
	*
	*	@param right	Ҫƴ���ڱ������ұߵľ���
	*	@return			ƴ�Ӻ�ľ���
	*/
	Matrix merge(Matrix& right)const;

	/**
	*	@brief ˽�к���
	*	�����֣����ڸ�˹��Ԫ�����棩
	*
	*	@param col		��ֺ���߾������һ�ж�Ӧ��ԭ�����е��±�
	*	@return			��ֺ���Ҿ���
	*/
	Matrix lrDivide(int col)const;

	/**
	*	@brief ˽�к���
	*	�Ը�Hessenberg���󣨷��󣩽�����ȫQR�ֽ�
	*	���þ���ΪHessenberg����������Ľ��
	*	��QR�ֽⷨ������ֵʹ��
	*
	*	@param Q	��������
	*	@param R	�����Ǿ���
	*	@return		������Խ�����ȫQR�ֽ⣬����true
	*				���򷵻�false,��Q��RΪ�վ���
	*/
	bool qrDecom4Hessenberg(Matrix& Q, Matrix& R)const;
};



#endif // !_Matrix
