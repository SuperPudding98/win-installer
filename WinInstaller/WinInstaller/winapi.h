#pragma once
#include <Windows.h>


namespace mywininstaller
{

	namespace winapi
	{
		bool createDirectoryThrows(LPCWSTR path, LPSECURITY_ATTRIBUTES securiryAttributes = nullptr, bool existOK = false);
		void removeDirectoryThrows(LPCWSTR path);
		void copyFileThrows(LPCWSTR from, LPCWSTR to, bool overwrite = false);
		void deleteFileThrows(LPCWSTR path);
	}
}
