#pragma once
#include <filesystem>


namespace mywininstaller
{
	namespace config
	{
		static const std::filesystem::path InstallDir = "E:\\Temp\\InstallDir";
		static const std::filesystem::path InstalledFiles[] = {
			"E:\\Temp\\InstalledFiles\\file0.txt",
			"E:\\Temp\\InstalledFiles\\file1.txt",
			"E:\\Temp\\InstalledFiles\\file2.txt",
			"E:\\Temp\\InstalledFiles\\file3.txt"
		};

		const bool OverwriteIfExists = false;
	}
}
