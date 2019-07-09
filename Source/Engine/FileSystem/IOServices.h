#pragma once
#include "../Common/InnoType.h"
#include "../Common/InnoContainer.h"

INNO_PRIVATE_SCOPE InnoFileSystemNS
{
	bool setupWorkingDirectory();

	std::string loadTextFile(const std::string & fileName);
	std::vector<char> loadBinaryFile(const std::string & fileName);

	bool isFileExist(const std::string & filePath);
	std::string getFileExtension(const std::string & filePath);
	std::string getFileName(const std::string & filePath);
	std::string getWorkingDirectory();

	inline bool serialize(std::ostream& os, void* ptr, size_t size)
	{
		os.write((char*)ptr, size);
		return true;
	}

	template<typename T>
	inline bool serializeVector(std::ostream& os, const InnoArray<T>& vector)
	{
		serialize(os, (void*)&vector[0], vector.size() * sizeof(T));
		return true;
	}

	inline bool deserialize(std::istream& is, void* ptr)
	{
		// get pointer to associated buffer object
		auto pbuf = is.rdbuf();
		// get file size using buffer's members
		std::size_t l_size = pbuf->pubseekoff(0, is.end, is.in);
		pbuf->pubseekpos(0, is.in);
		pbuf->sgetn((char*)ptr, l_size);
		return true;
	}

	template<typename T>
	inline bool deserializeVector(std::istream& is, std::streamoff startPos, std::size_t size, InnoArray<T>& vector)
	{
		// get pointer to associated buffer object
		auto pbuf = is.rdbuf();
		pbuf->pubseekpos(startPos, is.in);
		pbuf->sgetn((char*)&vector[0], size);
		return true;
	}

	template<typename T>
	inline bool deserializeVector(std::istream& is, InnoArray<T>& vector)
	{
		// get pointer to associated buffer object
		auto pbuf = is.rdbuf();
		// get file size using buffer's members
		std::size_t l_size = pbuf->pubseekoff(0, is.end, is.in);
		pbuf->pubseekpos(0, is.in);
		pbuf->sgetn((char*)&vector[0], l_size);
		return true;
	}
}