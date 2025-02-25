#pragma once

#include "pch.h"
class DLL_API ByteBook
{
public:
	enum class OpenMode
	{
		NotOpen = 0x0000,
		ReadOnly = 0x0001,
		WriteOnly = 0x0002,
	};
	ByteBook(std::vector<uint8_t>& buffer);
	ByteBook(std::vector<uint8_t>& buffer, OpenMode flag);
	~ByteBook();

public:
	template<typename T>
	inline void serializeFixedTypes(T val);	// int double float bool

	inline void serializeStr(const std::string& str);

	inline void serializeMat(const cv::Mat& mat);

public:
	template<typename T>
	inline void deserializeFixedTypes(T& val);

	inline void deserializeStr(std::string& str);

	inline void deserializeMat(cv::Mat& mat);

private:
	std::vector<uint8_t>& m_BufferRef;
	size_t m_Offset = 0;
	OpenMode m_OpenMode = OpenMode::NotOpen;
};

template<typename T>
inline void ByteBook::serializeFixedTypes(T val)
{
	m_BufferRef.resize(m_BufferRef.size() + sizeof(val));
	std::memcpy(m_BufferRef.data() + m_BufferRef.size() - sizeof(val), &val, sizeof(val));
}

template<typename T>
inline void ByteBook::deserializeFixedTypes(T& val)
{
	std::memcpy(&val, m_BufferRef.data() + m_Offset, sizeof(val));
	m_Offset += sizeof(val);
}


