#include "pch.h"
#include "ByteBook.h"
typedef unsigned short StrLen;
ByteBook::ByteBook(std::vector<uint8_t>& buffer) : m_BufferRef(buffer)
{

}

ByteBook::ByteBook(std::vector<uint8_t>& buffer, OpenMode flag) : m_BufferRef(buffer)
{
	m_OpenMode = flag;
}

ByteBook::~ByteBook()
{

}

void ByteBook::serializeStr(const std::string& str)
{
	StrLen stringLength = str.size();
	serializeFixedTypes(stringLength);
	//m_BufferRef.resize(m_BufferRef.size() + sizeof(stringLength) + stringLength);
	//std::memcpy(m_BufferRef.data() + m_BufferRef.size() - sizeof(stringLength) - stringLength, &stringLength, sizeof(stringLength));

	m_BufferRef.resize(m_BufferRef.size() + stringLength);
	std::memcpy(m_BufferRef.data() + m_BufferRef.size() - stringLength, str.data(), stringLength);
}

void ByteBook::serializeMat(const cv::Mat& mat)
{

	const cv::Mat& srcMat = mat.isContinuous() ? mat : mat.clone();
	int rows = srcMat.rows;
	int cols = srcMat.cols;
	int type = srcMat.type();

	serializeFixedTypes(rows);
	serializeFixedTypes(cols);
	serializeFixedTypes(type);

	try
	{
		m_BufferRef.resize(m_BufferRef.size() + srcMat.total() * srcMat.elemSize());
	}
	catch (const std::exception& e)
	{
		const char* str = e.what();
		std::cerr << " Error message: " << str;
		if (strcmp(str, "bad allocation") == 0)
			std::cout << "ÄÚ´æ·ÖÅäÊ§°Ü" << std::endl;
	}
	std::memcpy(m_BufferRef.data() + m_BufferRef.size() - srcMat.total() * srcMat.elemSize(), srcMat.data, srcMat.total() * srcMat.elemSize());
}



void ByteBook::deserializeStr(std::string& str)
{
	StrLen stringLength;

	//std::memcpy(&stringLength, m_BufferRef.data() + m_Offset, sizeof(stringLength));
	//m_Offset += sizeof(stringLength);

	deserializeFixedTypes(stringLength);

	str.assign(reinterpret_cast<const char*>(m_BufferRef.data() + m_Offset), stringLength);
	m_Offset += stringLength;
}

void ByteBook::deserializeMat(cv::Mat& mat)
{
	int rows, cols, type;
	deserializeFixedTypes(rows);
	deserializeFixedTypes(cols);
	deserializeFixedTypes(type);
	mat.create(rows, cols, type);

	std::memcpy(mat.data, m_BufferRef.data() + m_Offset, mat.total() * mat.elemSize());
	m_Offset += mat.total() * mat.elemSize();
}



