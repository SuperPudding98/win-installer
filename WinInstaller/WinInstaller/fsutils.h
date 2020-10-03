#pragma once
#include <string>
#include <filesystem>
#include "Transaction.h"


namespace mywininstaller
{
	namespace fsutils
	{
		void createDirectoryAndParentsTransacted(Transaction<std::filesystem::path>& transaction, const std::filesystem::path& dirPath);
		void copyFileToDirTransacted(
			Transaction<std::filesystem::path>& transaction,
			const std::filesystem::path& fromFilePath,
			const std::filesystem::path& toDirPath,
			bool overwrite = false
		);
	}
}
