#include "Matrix.h"





/*-----------------------���캯��----------------------*/
//Ĭ�Ϲ��캯��
Matrix::Matrix()
{
	this->miRow = 0, this->miCol = 0;
	this->mpBuf = nullptr;
}
//double��ת����
Matrix::Matrix(double num)
{
	this->miRow = 1, this->miCol = 1;
	this->mpBuf = new double[1];
	mpBuf[0] = num;
}
//ʹ�ó�ʼ���б�(������)
Matrix::Matrix(const MatIniLst& lst)
{
	int i = 0;
	this->miRow = 1, this->miCol = lst.size();
	if (!sizeValidityCheck())
		return;
	this->mpBuf = new double[this->miRow * this->miCol];
	for (auto itm : lst)
	{
		mpBuf[i++] = itm;
	}
}
//ʹ�ó�ʼ���б�(һ��ľ���,���Զ���0)
Matrix::Matrix(const std::initializer_list<MatIniLst>& lst)
{
	int i = 0;
	this->miRow = lst.size();
	for (auto itm : lst)
	{
		//�ҳ�����
		if (this->miCol < itm.size())
			this->miCol = itm.size();
	}
	if (!sizeValidityCheck())
		return;
	this->mpBuf = new double[this->miRow * this->miCol];
	for (auto itm : lst)
	{
		for (auto ele : itm)
		{
			this->mpBuf[i++] = ele;
		}
		//��0
		for (int j = itm.size(); j < this->miCol; j++)
		{
			this->mpBuf[i++] = 0;
		}
	}
}

//ʹ�ó�ʼ���б�(һ��ľ���,���Զ���0)
Matrix::Matrix(const std::initializer_list<MatIniLst>& lst, int col)
{
	int i = 0;
	this->miRow = lst.size();
	this->miCol = col;
	for (auto itm : lst)
	{
		//�ҳ�����
		if (this->miCol < itm.size())
			this->miCol = itm.size();
	}
	if (!sizeValidityCheck())
		return;
	this->mpBuf = new double[this->miRow * this->miCol];
	for (auto itm : lst)
	{
		for (auto ele : itm)
		{
			this->mpBuf[i++] = ele;
		}
		//��0
		for (int j = itm.size(); j < this->miCol; j++)
		{
			this->mpBuf[i++] = 0;
		}
	}
}
//ʹ��һά�����ʼ����
//����������׵�ַ�������������������������鳤��
Matrix::Matrix(double* p, int row, int col, int count):miRow(row),miCol(col)
{
	if (!sizeValidityCheck())
		return;
	if (count < row * col)
	{
		this->miRow = 0;
		this->miCol = 0;
		this->mpBuf = nullptr;
		return;
	}
	this->mpBuf = new double[this->miRow * this->miCol];
	for (int i = 0; i < this->miRow * this->miCol; i++)
	{
		this->mpBuf[i] = p[i];
	}
}

/*-----------------------�������캯��----------------------*/
Matrix::Matrix(const Matrix& tmp) :miRow(tmp.miRow), miCol(tmp.miCol)
{
	if (this->mpBuf != nullptr)
		delete[]this->mpBuf;
	//û��Ҫ
	if (!sizeValidityCheck())
		return;
	this->mpBuf = new double[this->miRow * this->miCol];
	memcpy(this->mpBuf, tmp.mpBuf, this->miRow * this->miCol * sizeof(double));
}
/*-----------------------�ƶ����캯��----------------------*/
Matrix::Matrix(Matrix&& tmp) :miRow(tmp.miRow), miCol(tmp.miCol), mpBuf(tmp.mpBuf)
{
	tmp.mpBuf = nullptr;
	//û��Ҫ
	if (!sizeValidityCheck())
		return;
}
/*-----------------------��������----------------------*/
Matrix::~Matrix()
{
	if (this->mpBuf == nullptr)
		return;
	delete[]mpBuf;
	mpBuf = nullptr;
	this->miRow = this->miCol = 0;
}




/*-----------------------��̬����-----------------------*/
// ��������һЩ�������
Matrix Matrix::eye(int row)
{
	if (row <= 0)
	{
		return Matrix();
	}
	int col = row;
	double* buf = new double[row * col];
	memset(buf, 0, row * col * sizeof(double));
	for (int i = 0, j = 0; i < row && j < col; i++, j++)
	{
		buf[i * col + j] = 1;
	}
	Matrix temp = Matrix(buf, row, col, row * col);
	delete[] buf;
	return temp;
}
Matrix Matrix::eye(int row, int col)
{
	if (row <= 0 || col <= 0)
	{
		return Matrix();
	}
	double* buf = new double[row * col];
	memset(buf, 0, row * col * sizeof(double));
	for (int i = 0,j = 0; i < row && j < col; i++, j++)
	{
		buf[i * col + j] = 1;
	}
	Matrix temp = Matrix(buf, row, col, row * col);
	delete[] buf;
	return temp;
}
Matrix Matrix::ones(int row)
{
	if (row <= 0)
	{
		return Matrix();
	}
	int col = row;
	double* buf = new double[row * col];
	memset(buf, 0, row * col * sizeof(double));
	for (int i = 0; i < row * col; i++)
	{
		buf[i] = 1;
	}
	Matrix temp = Matrix(buf, row, col, row * col);
	delete[] buf;
	return temp;
}
Matrix Matrix::ones(int row, int col)
{
	if (row <= 0 || col <= 0)
	{
		return Matrix();
	}
	double* buf = new double[row * col];
	memset(buf, 0, row * col * sizeof(double));
	for (int i = 0; i < row*col; i++)
	{
			buf[i] = 1;
	}
	Matrix temp = Matrix(buf, row, col, row * col);
	delete[] buf;
	return temp;
}
Matrix Matrix::zeros(int row)
{
	if (row <= 0)
	{
		return Matrix();
	}
	int col = row;
	double* buf = new double[row * col];
	memset(buf, 0, row * col * sizeof(double));
	Matrix temp = Matrix(buf, row, col, row * col);
	delete[] buf;
	return temp;
}
Matrix Matrix::zeros(int row, int col)
{
	if (row <= 0 || col <= 0)
	{
		return Matrix();
	}
	double* buf = new double[row * col];
	memset(buf, 0, row * col * sizeof(double));
	Matrix temp = Matrix(buf, row, col, row * col);
	delete[] buf;
	return temp;
}


/*----------------------���������---------------------*/
// = ������ֵ
Matrix& Matrix::operator=(const Matrix& tmp)
{
	if (this == &tmp)
		return *this;

	if (this->mpBuf != nullptr)
		delete[]this->mpBuf;
	this->miRow = tmp.miRow;
	this->miCol = tmp.miCol;
	if (!sizeValidityCheck())
		return *this;
	this->mpBuf = new double[this->miRow * this->miCol];
	memcpy(this->mpBuf, tmp.mpBuf, this->miRow * this->miCol * sizeof(double));
	return *this;
}
// = �ƶ���ֵ
Matrix& Matrix::operator=(Matrix&& tmp)
{
	if (this == &tmp)
		return *this;

	if (this->mpBuf != nullptr)
		delete[]this->mpBuf;
	this->miRow = tmp.miRow;
	this->miCol = tmp.miCol;
	this->mpBuf = tmp.mpBuf;
	tmp.mpBuf = nullptr;
	sizeValidityCheck();
	return *this;
}

// + �ӷ��������ܼ��㣬���ؿվ���
Matrix operator+(const Matrix& lMat, const Matrix& rMat)
{
	return lMat.add(rMat);
}
// - �����������ܼ��㣬���ؿվ���
Matrix operator-(const Matrix& lMat, const Matrix& rMat)
{
	return lMat.sub(rMat);
}
// * �˷��������ܼ��㣬���ؿվ���
Matrix operator*(const Matrix& lMat, const Matrix& rMat)
{
	return lMat.rMultiple(rMat);
}
// * ����
Matrix operator*(const double& lFactor, const Matrix& rMat)
{
	return rMat.sMultiple(lFactor);
}
Matrix operator*(const Matrix& lMat, const double& rFactor)
{
	return lMat.sMultiple(rFactor);
}

//  �����������ܼ��㣬���ؿվ�����˷����ƣ�
Matrix operator/(const Matrix& lMat, const Matrix& rMat)
{
	return lMat * rMat.inverse();
}
Matrix operator/(const double& lFactor, const Matrix& rMat)
{
	return lFactor * rMat.inverse();
}
Matrix operator/(const Matrix& lMat, const double& rFactor)
{
	if (rFactor == 0)
		return Matrix();
	return double(1) / rFactor * lMat;
}


// �㲥
Matrix operator+(const Matrix& lMat, const double& rNum)
{
	return lMat + rNum * Matrix::ones(lMat.miRow, lMat.miCol);
}
Matrix operator+(const double& lNum, const Matrix& rMat)
{
	return rMat + lNum * Matrix::ones(rMat.miRow, rMat.miCol);
}
Matrix operator-(const Matrix& lMat, const double& rNum)
{
	return lMat - rNum * Matrix::ones(lMat.miRow, lMat.miCol);
}
Matrix operator-(const double& lNum, const Matrix& rMat)
{
	return rMat - lNum * Matrix::ones(rMat.miRow, rMat.miCol);
}



// += �����������ܼ��㣬���ؿվ���
Matrix& Matrix::operator+=(const Matrix& tmp)
{
	*this = *this + tmp;
	return *this;
}
Matrix& Matrix::operator+=(const double& num)
{
	*this = *this + num;
	return *this;
}
// -= �Լ��������ܼ��㣬���ؿվ���
Matrix& Matrix::operator-=(const Matrix& tmp)
{
	*this = *this - tmp;
	return *this;
}
Matrix& Matrix::operator-=(const double& num)
{
	*this = *this - num;
	return *this;
}

// ==��!= �е�(ֻ������������ͬʱ������true)
bool operator==(const Matrix& lMat, const Matrix& rMat)
{
	int count = lMat.miRow * lMat.miCol;
	if (count != rMat.miRow * rMat.miCol)
		return false;
	for (int i = 0; i < count; i++)
	{
		if (lMat.mpBuf[i] != rMat.mpBuf[i])
			return false;
	}
	return true;
}
bool operator!=(const Matrix& lMat, const Matrix& rMat)
{
	return !(lMat == rMat);
}
// - ȡ�෴
Matrix operator-(const Matrix& Mat)
{
	return Mat.sMultiple(-1);
}
// + ����
Matrix operator+(const Matrix& Mat)
{
	return Mat;
}



// ++
Matrix& Matrix::operator++()
{
	*this += 1;
	return *this;
}
Matrix Matrix::operator++(int)
{
	Matrix tmp = *this;
	*this += 1;
	return tmp;
}
// --
Matrix& Matrix::operator--()
{
	*this -= 1;
	return *this;
}
Matrix Matrix::operator--(int)
{
	Matrix tmp = *this;
	*this -= 1;
	return tmp;
}


// []ȡ�±�(Ҫ������[]�Է���Ԫ��)
// ---------------------------------
// ��Ҫ����ķ�����ʹ��ȡ�±������������
// ��Ҫ����ķ�����ʹ��ȡ�±������������
// ��Ҫ����ķ�����ʹ��ȡ�±������������
// ��ֱ��ʹ��mpBuf[]��ȡԪ�� ������
// ---------------------------------
double*  Matrix::operator[](int num)
{
	return this->mpBuf + num * this->miCol;
}
const double*  Matrix::operator[](int num)const
{
	return this->mpBuf + num * this->miCol;
}


// <<�����
std::ostream& operator<<(std::ostream& os,  const Matrix& tmp)
{
	os << '[' << std::endl;
	for (int i = 0; i < tmp.miRow; i++)
	{
		os << "   ";
		for (int j = 0; j < tmp.miCol; j++)
		{
			os << std::setw(10) << std::left << std::setprecision(5) << tmp.mpBuf[i * tmp.miRow + j];
		}
		os << std::endl;
	}
	os << ']' << std::endl;
	return os;
}




/*-----------------------���ʺ���----------------------*/
//���ؾ��������
int Matrix::getRow()
{
	return this->miRow;
}
//���ؾ��������
int Matrix::getCol()
{
	return this->miCol;
}

//����ӷ�
const Matrix Matrix::add(const Matrix& tmp)const
{
	//ͬ�ͼ��
	if (this->miRow != tmp.miRow || this->miCol != tmp.miCol)
	{
		return Matrix();
	}
	//����ӷ�
	Matrix result = *this;

	for (int i = 0; i < miRow * miCol; i++)
	{
		result.mpBuf[i] += tmp.mpBuf[i];
	}
	return result;
}

//�������
const Matrix Matrix::sub(const Matrix& tmp)const
{
	//ͬ�ͼ��
	if (this->miRow != tmp.miRow || this->miCol != tmp.miCol)
	{
		return Matrix();
	}
	//�������
	Matrix result = *this;

	for (int i = 0; i < miRow * miCol; i++)
	{
		result.mpBuf[i] -= tmp.mpBuf[i];
	}
	return result;
}
//��������
const Matrix Matrix::sMultiple(const double& factor)const
{
	Matrix result = *this;
	//����ӷ�
	for (int i = 0; i < miRow * miCol; i++)
	{
		result.mpBuf[i] *= factor;
	}
	return result;
}
//�����ҳˣ�tmp���Ҿ���
const Matrix Matrix::rMultiple(const Matrix& tmp)const
{
	if (this->miCol != tmp.miRow)
	{
		return Matrix();
	}
	if (this->miRow <= 0 || this->miCol <= 0
		|| tmp.miRow <= 0 || tmp.miCol <= 0)
	{
		return Matrix();
	}

	Matrix result= Matrix::zeros(this->miRow, tmp.miCol);
	int count = 0;
	for (int i = 0; i < this->miRow; i++)
	{
		for (int j = 0; j < tmp.miCol; j++)
		{
			for (int k = 0; k < tmp.miRow; k++)
			{
				result.mpBuf[count] += this->mpBuf[i * this->miCol + k] * tmp.mpBuf[k * tmp.miCol + j];
			}
			count++;
		}
	}
	return result;
}
//����ת��
const Matrix Matrix::transpose()const
{
	Matrix result = Matrix::zeros(this->miCol, this->miRow);
	for (int i = 0; i < this->miRow; i++)
	{
		for (int j = 0; j < this->miCol; j++)
		{
			result.mpBuf[j * this->miRow + i] = this->mpBuf[i * this->miCol + j];
		}
	}
	return result;
}
//����������ʽ��
//������Ϊ���󣬺�������false,resultΪ0
bool Matrix::det(double& result)const
{
	//�Ƿ�Ϊ����
	if (this->miRow != this->miCol)
	{
		result = 0;
		return false;
	}
	//������ʽ��ֵ
	Matrix tmp = *this;

	int count = 0;	//��Ŵ���
	for (int i = 0; i < tmp.miRow; i++)
	{
		int j = 0;
		for (j = i; j < tmp.miRow; j++)
		{
			if (tmp.mpBuf[j * tmp.miCol + i] != 0)
			{
				count += tmp.rExchange(i, j);
				break;
			}
		}
		if (j == tmp.miRow)
		{
			result = 0;
			return true;
		}
		for (j = i + 1; j < tmp.miRow; j++)
		{
			double factor = tmp.mpBuf[tmp.miCol * j + i] / tmp.mpBuf[tmp.miCol * i + i];
			tmp.rAdd(j, i, -factor);
		}
	}
	result = 1;
	for (int i = 0; i < tmp.miCol; i++)
	{
		result *= tmp.mpBuf[i * tmp.miCol + i];
	}
	//���
	if (count % 2)
		result = -result;


	return true;
}
//��˹��Ԫ��
Matrix Matrix::gauss()
{
	//����һ��
	Matrix tmp = *this;
	//��Ԫ����
	int j = 0, count = 0;
	int size = tmp.miRow > tmp.miCol ? tmp.miCol : tmp.miRow;
	//���ݻ�
	for (int i = 0; i < tmp.miCol; i++)
	{
		for (j = i - count; j < tmp.miRow; j++)
		{
			if (tmp.mpBuf[j * tmp.miCol + i] != 0)
			{
				tmp.rExchange(i - count, j);
				break;
			}
		}
		if (j == tmp.miRow)
		{
			count++;
			continue;
		}
		for (j = i - count + 1; j < tmp.miRow; j++)
		{
			double factor = tmp.mpBuf[tmp.miCol * j + i] / tmp.mpBuf[tmp.miCol * (i - count) + i];
			tmp.rAdd(j, i - count, -factor);
		}
	}
	//�����
	for (int i = 0; i < tmp.miRow; i++)
	{
		for (j = i; j < tmp.miCol; j++)
		{
			if (tmp.mpBuf[i * tmp.miCol + j] != 0)
				break;
		}
		if (j == tmp.miCol)
			continue;
		tmp.rTime(i, 1 / tmp.mpBuf[i * tmp.miCol + j]);
		for (int k = i - 1; k >= 0; k--)
		{
			tmp.rAdd(k, i, -tmp.mpBuf[k * tmp.miCol + j]);
		}
	}
	return tmp;
}
//����
int Matrix::rank()
{
	Matrix tmp = this->gauss();
	int j, i;
	for (i = 0; i < tmp.miRow; i++)
	{
		for (j = i; j < tmp.miCol; j++)
		{
			if (tmp.mpBuf[i * tmp.miCol + j] != 0)
				break;
		}
		if (j == tmp.miCol)
			return i;
	}
	return i;
}
//����
const Matrix Matrix::inverse()const
{
	double det;
	this->det(det);
	if (det == 0)
		return Matrix();
	Matrix diag = Matrix::eye(this->miRow);
	Matrix tmp = this->merge(diag);
	tmp = tmp.gauss();
	return tmp.divide(this->miRow);
}


/*-----------------------��������----------------------*/
//������״�ĺϷ��Լ��
bool Matrix::sizeValidityCheck()
{
	if (this->miRow <= 0 || this->miCol <= 0)
	{
		this->miRow = 0, this->miCol = 0;
		if (this->mpBuf != nullptr)
		{
			delete[] this->mpBuf;
			this->mpBuf = nullptr;
		}
		return false;
	}
	else
		return true;
}

//����ʽ����
//��������ӣ���src�б���factor��ӵ�des��
void Matrix::rAdd(int des, int src, double factor)
{
	for (int i = 0; i < this->miCol; i++)
	{
		this->mpBuf[des * this->miCol + i] += factor * this->mpBuf[src * this->miCol + i];
	}
	return;
}
//�н���,ע���ŵ�����
bool Matrix::rExchange(int des, int src)
{
	double tmp;
	for (int i = 0; i < this->miCol; i++)
	{
		tmp = this->mpBuf[src * this->miCol + i];
		this->mpBuf[src * this->miCol + i] = this->mpBuf[des * this->miCol + i];
		this->mpBuf[des * this->miCol + i] = tmp;
	}
	//�Ƿ���
	return des == src ? 0 : 1;
}
//��ָ���г���factor
void Matrix::rTime(int des, double factor)
{
	for (int i = 0; i < this->miCol; i++)
	{
		this->mpBuf[des * this->miCol + i] *= factor;
	}
	return;
}
//�ϲ�����֣����Ա任�������
Matrix Matrix::merge(Matrix& right)const
{
	if (this->miRow != right.miRow)
		return Matrix();
	Matrix result = Matrix::zeros(this->miRow, this->miCol + right.miCol);
	for (int i = 0; i < this->miRow; i++)
	{
		for (int j = 0; j < this->miCol; j++)
		{
			result.mpBuf[i * result.miCol + j] = this->mpBuf[i * this->miCol + j];
		}
		for (int j = 0; j < right.miCol; j++)
		{
			result.mpBuf[i * result.miCol + this->miCol + j] = right.mpBuf[i * right.miCol + j];
		}
	}
	return result;
}
//�������Ϊ�����������������col��,�����Ҿ���
Matrix Matrix::divide(int col)
{
	if (this->miCol <= col)
		return Matrix();
	Matrix result = Matrix::zeros(this->miRow, this->miCol - col);
	for (int i = 0; i < this->miRow; i++)
	{
		for (int j = 0; j < this->miCol - col; j++)
		{
			result.mpBuf[i * result.miCol + j] = this->mpBuf[i * this->miCol + col + j];
		}
	}
	return result;
}
//���Һϲ�
Matrix Matrix::LRMerge(Matrix& left,Matrix& right)
{
	if (left.miRow != right.miRow)
		return Matrix();
	Matrix result = Matrix::zeros(left.miRow, left.miCol + right.miCol);
	for (int i = 0; i < left.miRow; i++)
	{
		for (int j = 0; j < left.miCol; j++)
		{
			result.mpBuf[i * result.miCol + j] = left.mpBuf[i * left.miCol + j];
		}
		for (int j = 0; j < right.miCol; j++)
		{
			result.mpBuf[i * result.miCol + left.miCol + j] = right.mpBuf[i * right.miCol + j];
		}
	}
	return result;
}
//���ºϲ�
Matrix Matrix::UDMerge(Matrix& up, Matrix& down)
{
	if (up.miCol != down.miCol)
		return Matrix();
	Matrix result = Matrix::zeros(up.miRow + down.miRow, up.miCol);
	memcpy(result.mpBuf, up.mpBuf, up.miCol * up.miRow * sizeof(double));
	memcpy(result.mpBuf + up.miCol * up.miRow, down.mpBuf, down.miCol * down.miRow * sizeof(double));
	return result;
}