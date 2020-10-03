#pragma once
#include <string>


namespace mywininstaller
{
	namespace fsutils
	{
		void createDirectoryThrows(const std::wstring& path, bool existOK = false);
		void removeDirectoryThrows(const std::wstring& path);
		void copyFileThrows(const std::wstring& from, const std::wstring& to, bool overwrite = false);
		void deleteFileThrows(const std::wstring& path);
	}
}
