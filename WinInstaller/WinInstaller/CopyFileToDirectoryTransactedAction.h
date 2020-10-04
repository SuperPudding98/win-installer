#pragma once
#include "TransactedAction.h"
#include <filesystem>


namespace mywininstaller
{
	namespace transactions
	{
		namespace filesystem
		{
			class CopyFileToDirectoryTransactedAction : public TransactedAction
			{
			public:
				CopyFileToDirectoryTransactedAction(const std::filesystem::path& fromFilePath, const std::filesystem::path& toDirPath, bool overwrite = false);

			private:
				const std::filesystem::path m_fromPath;
				const std::filesystem::path m_toPath;
				const bool m_overwrite;

				void execute() override;
				void rollback() override;
			};
		}
	}
}
