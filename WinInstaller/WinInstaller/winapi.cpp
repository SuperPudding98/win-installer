#include "winapi.h"
#include "Win32Error.h"
#include <Windows.h>


namespace mywininstaller
{
	namespace winapi
	{
		void createDirectoryThrows(LPCWSTR path, LPSECURITY_ATTRIBUTES securiryAttributes)
		{
			if (!CreateDirectoryW(path, securiryAttributes))
			{
				throw Win32Error::fromLastError();
			}
		}

		void removeDirectoryThrows(LPCWSTR path)
		{
			if (!RemoveDirectoryW(path))
			{
				throw Win32Error::fromLastError();
			}
		}

		void copyFileThrows(LPCWSTR from, LPCWSTR to, bool overwrite)
		{
			if (!CopyFileW(from, to, !overwrite))
			{
				throw Win32Error::fromLastError();
			}
		}

		void deleteFileThrows(LPCWSTR path)
		{
			if (!DeleteFileW(path))
			{
				throw Win32Error::fromLastError();
			}
		}
	}
}
