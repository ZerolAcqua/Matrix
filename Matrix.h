/**
  * @file     	Matrix.h
  * @author   	Zerol Acqua\<zerolacqua@outlook.com\>
  * @version	V1.4.1
  * @date    	2022/01/21	
  * @brief   	����������
  *	@details	
  * 
  * ���ļ��洢������ĸ������������Ϣ
  *
  * Version|Auther|Date|Describe
  * --------|-----------|----------|-----------
  * V1.0.0  |Zerol Acqua|2021/03/22|Create Files
  * V1.1.0  |Zerol Acqua|2021/10/02|Add Functions
  * V1.2.0  |Zerol Acqua|2021/10/09|Add Functions
  * V1.3.0  |Zerol Acqua|2021/10/11|Add Functions
  * V1.3.1  |Zerol Acqua|2022/01/17|Small Patches
  * V1.4.0  |Zerol Acqua|2022/01/21|Add Functions
  * V1.4.1  |Zerol Acqua|2022/11/30|Small Patches
  *
  * ## V1.0.0
  *
  *	�������ڽ��о���Ļ�������
  *
  *	- ����ӷ����������ˣ�����˷�
  *	- ����㲥������ϲ��������е�
  *	- ��˹��Ԫ��������
  *	- ��������ʽ���������棬��������
  *
  * ## V1.1.0
  *
  *	- ����ע�ͣ��޸ı�������
  *	- �Ż��޸��˲��ֵĹ��캯���;�̬����
  *	    - `eye` ����
  *		- `ones` ����
  *		- `zeros` ����
  *	- �������ƶ����캯�����ƶ���ֵ����ʵ��
  *	- ������`<<`���������ʵ�������
  *	- �޲ι��캯���ʹ��󷵻صľ������Ϊ0*0�Ŀվ��󣬲��޸���
  *	   ���ֺ����ڼ�������״�Ĵ���(��Ҫ�ǿվ�����ж�)
  *	- �޸��˴󲿷ֳ�Ա��������Ϊ�ǳ�Ա��������Ϊ��Ԫ������
  *	   ��������Ϊ�������ã���ֵ����ֵ���ھ��ɰ󶨡�
  *		- ��Ա���� =rvalue  =lvalue
  *		- ��Ԫ���� Matrix+Matrix Matrix-Matrix
  *		- ��Ԫ���� Matrix*Matrix
  *		- ��Ԫ���� factor*Matrix Matrix*factor
  *   - TODO��
  *     - ����㲥��
  *	    - ���ϸ�ֵ `+=` �� `-=`
  *	    - ǰ�������� `++` ���Լ�`--`
  *	    - ��Ԫ����� `+/-`
  *	    - ������� `/`
  *
  * ## V1.2.0
  *
  *	- ����㲥��ֻ���������ֵģ�
  *	- ���ϸ�ֵ `+=` �� `-=`
  *	- ��Ԫ����� `+/-`
  *
  * ## V1.3.0
  *
  *	- ǰ��������"++"�Լ�"--"��
  *	- ������� "/"
  *	- �޸��˲��ָ������������� `const` �ؼ��֣�ʹ�䲻���޸ĳ�Ա����
  *	- TODO��
  *	    - ������ֵ�Ƿ�Ҫת��Ϊ���������
  *	    - ������������غ󣬹���һЩ�����������ع�����
  *	    - �ֿ����
  *	    - ���Ⱥʹ�ӡ��صĲ���
  *
  * ### V1.3.1
  *
  *	- ��������˲��ָ���������ע�ͣ������к�С�ĸĶ�
  *	- TODO:
  *	    - ������������ֵ��QR �㷨��
  *	    - ������ݣ��������ʽ����
  *	    - �ֿ����
  *	    - ���Ⱥʹ�ӡ��صĲ���
  *	    - `reshape` ������ش���
  *
  * ## V1.4.0
  *
  *	- �޸��˸������еȵ��߼�
  *	- ����˾�����״������ظ�������
  *	- ��� `diag` ����
  *	- ����� `eigen` �������Լ���ص� `hessenberg` ������`qrDecom4Hessenberg` ����
  *		Ŀǰ����������ֵֻ�ܼ���ʵ����ֵ��������ڸ�����ֵ����û�취������
  *	- ����� `randMatrix` �������������� 0~1 α���Ԫ����ɵľ���
  *	- TODO��
  *	    - ��дһ���쳣�׳���صĶ�������Ȼ�Ժ� debug ̫���ˣ���������һ����С�Ĺ���
  *
  * ### V1.4.1
  *
  *   - �޸� `noexcept` ���ڳ�Ա������ʵ���в����� `noexcept`
  *   - �Ż��� `rowExchange` ������ʵ���߼�
  * 
  * @attention
  *  ���ļ����ڿ�����
  */

#ifndef _Matrix_H
#define _Matrix_H

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <initializer_list>

typedef std::initializer_list<double> MatIniLst;	//��ʼ���б�

/**
* @class Matrix
* @brief �������ڽ��о���Ļ�������
* @author Zerol Acqua\<zerolacqua@outlook.com\>
* @note
* detailed description
*/
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
	*	@details ��ȡһ��0*0��δ�����ڴ�Ŀվ���,
	*			 ���Ϸ��ļ���һ�㷵�ر�����
	*/
	explicit Matrix();

	/**
	*	@brief ���캯��
	*   @details ��double����ת��Ϊ1*1����
	*
	*	@param[in] num ����
	*/
	Matrix(double num);

	/**
	*	@brief ���캯��
	*	@details ʹ�ó�ʼ���б������
	*
	*	@param[in] lst ��ʼ���б�
	*/
	Matrix(const MatIniLst& lst);


	/**
	*	@brief ���캯��
	*	@details ʹ�ó�ʼ���б����������Ϊ����һ�е�Ԫ�ظ�����������0���������е�Ԫ�ء�
	*
	*	@param[in] lst ��ʼ���б����㣩
	*/
	Matrix(const std::initializer_list<MatIniLst>& lst);

	/**
	*	@brief ���캯��
	*	@details ʹ�ó�ʼ���б�����󣬸����趨��������������0�����ʼ���б���û�е�Ԫ�ء�
	*
	*	@param[in] lst ��ʼ���б����㣩
	*	@param[in] col ��������
	*/
	explicit Matrix(const std::initializer_list<MatIniLst>& lst, int col);

	/**
	*	@brief ���캯��
	*	@details ʹ��ָ����ָ�����ݹ������,�����鳤��С����Ҫ�ĳ���row*col����ᱨ��
	*
	*	@param[in] p double��ָ�룬��Ҫ���������
	*	@param[in] row ��������
	*	@param[in] col ��������
	*   @param[in] count ���鳤��
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
	Matrix(Matrix&& tmp)noexcept;

	/**
	*	@brief ��������
	*/
	~Matrix();

	// ---- ��̬��Ա���� ----

	/**
	*	@brief ��̬����
	*	@details ����һ�������������ɵ�λ����
	*
	*	@param[in] row ����Ľ���
	*	@return ���ص�λ����
	*/
	static Matrix eye(int row);

	/**
	*	@brief ��̬����
	*	@details ����һ�������������ɵ�λ����
	*
	*	@param[in] row ���������
	*	@param[in] col ���������
	*	@return ���ص�λ����
	*/
	static Matrix eye(int row, int col);

	/**
	*	@brief ��̬����
	*	@details ����һ��������������Ԫ��ȫΪ1�ķ���
	*
	*	@param[in] row ����Ľ���
	*	@return ����Ԫ��ȫΪ1�ķ���
	*/
	static Matrix ones(int row);

	/**
	*	@brief ��̬����
	*	@details ����һ��������������Ԫ��ȫΪ1�ľ���
	*
	*	@param[in] row ���������
	*	@param[in] col ���������
	*	@return ����Ԫ��ȫΪ1�ľ���
	*/
	static Matrix ones(int row, int col);

	/**
	*	@brief ��̬����
	*	@details ����һ��������������Ԫ��ȫΪ0�ķ���
	*
	*	@param[in] row ����Ľ���
	*	@return ����Ԫ��ȫΪ0�ķ���
	*/
	static Matrix zeros(int row);

	/**
	*	@brief ��̬����
	*	@details ����һ��������������Ԫ��ȫΪ0�ľ���
	*
	*	@param[in] row ���������
	*	@param[in] col ���������
	*	@return ����Ԫ��ȫΪ0�ľ���
	*/
	static Matrix zeros(int row, int col);

	/**
	*	@brief ��̬����
	*	@details ���С����������ɶԽǾ��󣬻��ߴ�һ�������ȡ�Խ���Ԫ�ء�
	*
	*	@param[in] mat
	*	@return ���ضԽǾ��󣬻��ɾ��󷵻ضԽ�Ԫ��������
	*/
	static Matrix diag(Matrix mat);

	/**
	*	@brief ��̬����
	*	@details ����Ԫ������ķ���
	*
	*	@param[in] n �������
	*	@return		�����������
	*/
	static Matrix randMatrix(int n);

	/**
	*	@brief ��̬����
	*	@details ����Ԫ������ķ���
	*
	*	@param[in] row	��������
	* 	@param[in] col	��������
	*	@return		�����������
	*/
	static Matrix randMatrix(int row, int col);



	/**
	*	@brief ��̬����
	*	@details ���þ�����ʾ�ľ��ȡ�
	*
	*	@param[in] precise ����
	*/
	static void setPrecise(int precise);


	// ---- ��������� ----

	/**
	*	@brief ��������أ�������ֵ����
	*	@details ������ֵ��
	*
	*	@param[in] tmp ��Ϊֵ�ľ���
	*	@return ���ظ�ֵ֮��ľ��������
	*/
	Matrix& operator=(const Matrix& tmp);

	/**
	*	@brief ��������أ��ƶ���ֵ����
	*	@details ������ֵ��
	*
	*	@param[in] tmp ��Ϊֵ�ľ���
	*	@return ���ظ�ֵ֮��ĸþ��������
	*/
	Matrix& operator=(Matrix&& tmp)noexcept;

	/**
	*	@brief ��������أ���Ԫ����
	*	@details �����������������������͡�
	*
	*	@param[in] lMat ��Ӿ���
	*	@param[in] rMat �ҼӾ���
	*	@return �������֮��ĸþ��������
	*/
	friend Matrix operator+(const Matrix& lMat, const Matrix& rMat);

	/**
	*	@brief ��������أ���Ԫ����
	*	@details �����������������������
	*
	*	@param[in] lMat �󱻼�����
	*	@param[in] rMat �Ҽ�����
	*	@return �������֮��ľ���
	*/
	friend Matrix operator-(const Matrix& lMat, const Matrix& rMat);

	/**
	*	@brief ��������أ���Ԫ����
	*	@details ��������������������������˻���
	*
	*	@param[in] lMat ��˾���
	*	@param[in] rMat �ҳ˾���
	*	@return ���������˻�֮����¾���
	*/
	friend Matrix operator*(const Matrix& lMat, const Matrix& rMat);

	/**
	*	@brief ��������أ���Ԫ����
	*	@details double*matrix������һ������
	*
	*	@param[in] lFactor ��˵�ϵ��
	*	@param[in] rMat ����
	*	@return ���ؾ������˺�Ľ��
	*/
	friend Matrix operator*(const double& lFactor, const Matrix& rMat);

	/**
	*	@brief ���������,��Ԫ����
	*   @details matrix*double������һ������
	* 
	*	@param[in] lMat ����
	*	@param[in] rFactor �ҳ˵�ϵ��
	*	@return ���ؾ������˺�Ľ��
	*/
	friend Matrix operator*(const Matrix& lMat, const double& rFactor);

	/**
	*	@brief ���������,��Ԫ����
	*	@details ��������������������������˻���
	*
	*	@param[in] lMat ��������
	*	@param[in] rMat �ҳ�����
	*	@return ������������֮��ľ���
	*/
	friend Matrix operator/(const Matrix& lMat, const Matrix& rMat);

	/**
	*	@brief ���������,��Ԫ����
	*	@details double/matrix������һ������
	*
	*	@param[in] lFactor ������ϵ��
	*	@param[in] rMat �ҳ�����
	*	@return ���ؾ��������Ľ��
	*/
	friend Matrix operator/(const double& lFactor, const Matrix& rMat);

	/**
	*	@brief ���������,��Ԫ����
	*   @details matrix/double������һ������
	*
	*	@param[in] lMat �����ľ���
	*	@param[in] rFactor �ҳ�ϵ��
	*	@return ���ؾ��������Ľ��
	*/
	friend Matrix operator/(const Matrix& lMat, const double& rFactor);

	/**
	*	@brief ���������,��Ԫ����
	*	@details matrix+double������һ������
	*
	*	@param[in] lMat ��ӵľ���
	*	@param[in] rMat �Ҽӵ�����
	*	@return ���ؾ���㲥��Ľ��
	*/
	friend Matrix operator+(const Matrix& lMat, const double& rNum);
	
	/**
	*	@brief ���������,��Ԫ����
	*	@details double+matrix������һ������
	*
	*	@param[in] lNum ��ӵ�����
	*	@param[in] rMat �Ҽӵľ���
	*	@return ���ؾ���㲥��Ľ��
	*/
	friend Matrix operator+(const double& lNum, const Matrix& rMat);
	
	/**
	*	@brief ���������,��Ԫ����
	*	@details matrix-double������һ������
	*
	*	@param[in] lMat �����ľ���
	*	@param[in] rMat ��������
	*	@return ���ؾ���㲥��Ľ��
	*/
	friend Matrix operator-(const Matrix& lMat, const double& rNum);
	
	/**	
	*	@brief ���������,��Ԫ����
	*	@details double-matrix������һ������
	*
	*	@param[in] lNum ����������
	*	@param[in] rMat ���ľ���
	*	@return ���ؾ���㲥��Ľ��
	*/
	friend Matrix operator-(const double& lNum, const Matrix& rMat);

	/**
	*	@brief ���������
	*   @details ���ϸ�ֵ+=��
	*
	*	@param[in] tmp Ҫ���ϵľ���
	*	@return ���ؽ�����������
	*/
	Matrix& operator+=(const Matrix& tmp);

	/**
	*	@brief ���������
	*   @details ���ϸ�ֵ+= ��
	*
	*	@param[in] tmp Ҫ���ϵľ���
	*	@return ���ؽ���þ��������
	*/
	Matrix& operator+=(const double& num);

	/**
	*	@brief ���������
	*   @details ���ϸ�ֵ-=��
	*
	*	@param[in] tmp Ҫ��ȥ�ľ���
	*	@return ���ؽ�����������
	*/
	Matrix& operator-=(const Matrix& tmp);

	/**
	*	@brief ���������
	*   @details ���ϸ�ֵ+=��
	*
	*	@param[in] tmp Ҫ��ȥ������
	*	@return ���ؽ�����������
	*/
	Matrix& operator-=(const double& num);
	
	/**
	*	@brief ��������أ���Ԫ����
	*   @details �еȡ�
	*
	*	@param[in] lMat �����
	*	@param[in] rMat �Ҿ���
	*	@return �����еȽ��
	*/
	friend bool operator==(const Matrix& lMat, const Matrix& rMat);
	/**
	*	@brief ��������أ���Ԫ����
	*   @details �в��ȡ�
	*
	*	@param[in] lMat �����
	*	@param[in] rMat �Ҿ���
	*	@return �����в��Ƚ��
	*/
	friend bool operator!=(const Matrix& lMat, const Matrix& rMat);

	/**
	*	@brief ��������أ���Ԫ����
	*   @details ȡ�෴��
	*
	*	@param[in] Mat ����
	*	@return ����ȡ�����
	*/
	friend Matrix operator-(const Matrix& Mat);
	/**
	*	@brief ���������,��Ԫ����
	*   @details ����š�
	*
	*	@param[in] Mat ����
	*	@return ���ز���ŵĽ��
	*/
	friend Matrix operator+(const Matrix& Mat);


	/**
	*	@brief ���������
	*   @details ǰ�õ�����
	*
	*	@return ������ľ�������
	*/
	Matrix& operator++();
	
	/**
	*	@brief ���������
	*   @details ���õ�����
	*	
	*	@param[in] useless ����ǰ���õĲ�������ʵ������
	*	@return ����ǰ�ľ���
	*/
	Matrix operator++(int);
	
	/**
	*	@brief ���������
	*   @details ǰ�õݼ���
	*
	*	@return �ݼ���ľ�������
	*/
	Matrix& operator--();
	
	/**
	*	@brief ���������
	*   @details ���õݼ���
	*
	*	@param[in] useless ����ǰ���õĲ�������ʵ������
	*	@return �ݼ�ǰ�ľ���
	*/
	Matrix operator--(int);


	/**
	*	@brief ���������
	*   @details ȡ�±ꡣ
	*			 �����±��Ӧ�ľ����ĳһ�У�
	*			 һ������ʹ������[]�Ի�ȡĳ��ָ�롣
	*			 ��Ҫ����ķ�����ʹ��ȡ�±��������
	*			 �������汾����Ϊ�ǳ����汾��
	*
	*	@param[in] num �±�
	*	@return �����±��Ӧ�ľ����ĳһ�еĵ�һ��Ԫ�ص�ָ��
	*/
	double* operator[](int num);
	/**
	*	@brief ���������
	*   @details ȡ�±ꡣ
	*			 �����±��Ӧ�ľ����ĳһ�У�
	*			 һ������ʹ������[]�Ի�ȡĳ��ָ�롣
	*			 ��Ҫ����ķ�����ʹ��ȡ�±��������
	*			 �������汾����Ϊ�����汾��
	*
	*	@param[in] num �±�
	*	@return �����±��Ӧ�ľ����ĳһ�еĵ�һ��Ԫ�ص�ָ��
	*/
	const double* operator[](int num)const;

	/**
	*	@brief ���������,��Ԫ����
	*   @details ����ʵ��cout<< xxx << xxx��
	*			 ����ostream�����á�
	*
	*   @param[in,out] os	ostream
	*   @param[in] tmp	����
	*   @return ����os�����ü�ostream&
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
	*	@details ��������뱾����ĺͣ��롰+���ȼۡ�
	*	
	*	@param[in] tmp ���ϵľ���
	*	@return ������ͺ�Ľ��
	*/
	Matrix add(const Matrix& tmp)const;

	/**
	*	@brief ���к���
	*	@details ���㱾���������Ĳ�롰-���ȼۡ�
	*
	*	@param[in] tmp ��ȥ�ľ���
	*	@return ��������Ľ��
	*/
	Matrix sub(const Matrix& tmp)const;

	/**
	*	@brief ���к���
	*	@details ����ĳ�����ҳ˱������롰*���ȼۡ�
	*
	*	@param[in] tmp �ҳ˵ľ���
	*	@return �����ҳ˺�Ľ��
	*/
	Matrix rMultiple(const Matrix& tmp)const;

	/**
	*	@brief ���к���
	*	@details ����������ˣ��롰*���ȼۡ�
	*
	*	@param[in] tmp ���˵���
	*	@return �����ҳ˺�Ľ��
	*/
	Matrix sMultiple(const double& factor)const;

	/**
	*	@brief ���к���
	*	@details ����ת�á�
	*
	*	@return ����ת�õĽ��
	*/
	Matrix transpose()const;

	/**
	*	@brief ���к���
	*	@details ������������ʽ��
	*
	*	@param[in] result ��������ʽ��ֵ
	*	@return ��������ʽ����true�����򷵻�false
	*/
	bool det(double& result)const;

	/**
	*	@brief ���к���
	*	@details �Ծ�����и�˹��Ԫ��
	*
	*	@return ���ظ�˹��Ԫ�Ľ��
	*/
	Matrix gauss()const;

	/**
	*	@brief ���к���
	*	@details �������档
	*
	*	@return ��������Ľ��
	*/
	Matrix inverse()const;

	/**
	*	@brief ���к���
	*	@details ���������ȡ�
	*
	*	@return ���ؾ������
	*/
	int rank()const;

	/**
	*	@brief ���к���
	*	@details ��������״����Ч�ԡ�
	*
	*	@return ���������״��Ч������true,
	*			���򷵻�false������������Ϊ�վ���
	*/
	bool isSizeValidity();

	/**
	*	@brief	���к���
	*	@details �������Ƿ�Ϊ����
	* 
	*	@return	������Ϊ���󣬷���true��
	*			���򷵻�false
	*/
	bool isSquareMatrix()const;

	/**
	*	@brief	���к���
	*	@details �������Ƿ�Ϊ�վ���
	*
	*	@return	������Ϊ�վ��󣬷���true��
	*			���򷵻�false
	*/
	bool isEmptyMatrix()const;


	/**
	*	@brief ���к���
	*	@details ��������ӡ�
	*
	*	@param[in] des		Ҫ�ӵ���Ŀ����
	*	@param[in] src		��Ϊ���ӵ���
	*	@param[in] factor	�����ϵ���������
	*/
	void rowAdd(int des, int src, double factor);

	/**
	*	@brief ���к���
	*	@details �н�����
	*
	*   @param[in] des		Ҫ��������
	*	@param[in] src		Ҫ��������
	*	@return	��������ʽ���ԣ�����ŷ���true��
	*			���򷵻�false������������ͬ��
	*/
	bool rowExchange(int des, int src);

	/**
	*	@brief ���к���
	*	@details �����ˡ�
	*
	*	@param[in] des		Ҫ���˵�Ŀ����
	*	@param[in] factor	�����ϵ���������
	*/
	void rowMultiply(int des, double factor);

	/**
	*	@brief ��̬����
	*	@details ��������ƴ�ӡ�
	* 
	*	@param[in] left		ƴ������ߵľ���
	*	@param[in] right	ƴ�����ұߵľ���
	*	@return ����ƴ�Ӻ�ľ���
	*/
	static Matrix lrMerge(Matrix& left, Matrix& right);

	/**
	*	@brief ��̬����
	*	@details ��������ƴ�ӡ�
	* 
	*	@param[in] up		ƴ�����ϱߵľ���
	*	@param[in] down		ƴ�����±ߵľ���
	*	@return	����ƴ�Ӻ�ľ���
	*/
	static Matrix udMerge(Matrix& up, Matrix& down);

	/**
	*	@brief ���к���
	*	@details �Ӿ���õ�һ�����
	*
	*	@param[in] startRowId	�ֳ��ľ������Ͻ�Ԫ����ԭ�����е��кţ���0���㣩
	*	@param[in] startColId	�ֳ��ľ������Ͻ�Ԫ����ԭ�����е��кţ���0���㣩
	*	@param[in] blockRow		�ֳ��ľ��������
	*	@param[in] blockCol		�ֳ��ľ��������
	*	@return				���طֳ��ľ���
	*						�����ֳܷ����󣬷��ؿվ���
	*/
	Matrix getBlock(int startRowId, int startColId, int blockRow, int blockCol)const;
	
	/**
	*	@brief ���к���
	*	@details �������ĳһ������Ϊ�����ľ���
	*
	*	@param[in] startRowId	�����ľ������Ͻ�Ԫ����ԭ�����е��кţ���0���㣩
	*	@param[in] startColId	�����ľ������Ͻ�Ԫ����ԭ�����е��кţ���0���㣩
	*	@param[in] block		�����ľ���
	*	@return				���ر���������
	*						���������ã������޸ģ���Ȼ���ر���������
	*/
	Matrix& setBlock(int startRowId, int startColId, const Matrix& block);

	/**
	*	@brief ���к���
	*	@details ���þ���Ϊ��Hessenberg���󣨷��󣩡�
	* 
	*	@param[out] Q		�ɱ��������Ʊ任����Hessenberg����ĶԳ�������
	*						H=Q^T*A*Q
	*	@return			��þ������Ƶ���Hessenberg����
	*/
	Matrix hessenberg(Matrix& Q)const;

	/**
	*	@brief ���к���
	*	@details �Ըþ������QR�ֽ⡣
	*
	*	@param[in] Q	��������
	*	@param[in] R	���������Ǿ���
	*/
	void qrDecom(Matrix& Q, Matrix& R)const;
	
	/**
	*	@brief ���к���
	*	@details ����������ֵ���Ӵ�С���У���
	*
	*	@return		��������ֵ��ɵ����������Ӵ�С���С�
	*				�������ޣ����ڸ�����ֵ��ԭ�����޷���⣬�򷵻ؿվ���
	*/
	Matrix eigen()const;


private:
	/**
	*	@brief ˽�о�̬����
	*	@details ����ķ��ź�����������Hessenberg����
	*
	*	@param[in]	num		Ҫ�������
	*	@return			����Ǹ�������1�����븺������-1
	*/
	static signed char sgn(double num);
	
	/**
	*	@brief ˽�к���
	*	@details ����ƴ�ӣ����ڸ�˹��Ԫ�����棩��
	*
	*	@param[in] right	Ҫƴ���ڱ������ұߵľ���
	*	@return			ƴ�Ӻ�ľ���
	*/
	Matrix merge(Matrix& right)const;

	/**
	*	@brief ˽�к���
	*	@details �����֣����ڸ�˹��Ԫ�����棩��
	*
	*	@param[in] col		��ֺ���߾������һ�ж�Ӧ��ԭ�����е��±�
	*	@return			��ֺ���Ҿ���
	*/
	Matrix lrDivide(int col)const;

	/**
	*	@brief ˽�к���
	*	@details �Ը�Hessenberg���󣨷��󣩽�����ȫQR�ֽ⡣
	*			 ���þ���ΪHessenberg����������Ľ����
	*			 ��QR�ֽⷨ������ֵʹ�á�
	*
	*	@param[out] Q	��������
	*	@param[out] R	�����Ǿ���
	*	@return		������Խ�����ȫQR�ֽ⣬����true,
	*				���򷵻�false,��Q��RΪ�վ���
	*/
	bool qrDecom4Hessenberg(Matrix& Q, Matrix& R)const;
};



#endif // !_Matrix
