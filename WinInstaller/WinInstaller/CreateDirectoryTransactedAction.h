#pragma once
#include "TransactedAction.h"
#include <filesystem>
#include <Windows.h>


namespace mywininstaller
{
	namespace transactions
	{
		namespace filesystem
		{
			class CreateDirectoryTransactedAction : public TransactedAction
			{
			public:
				CreateDirectoryTransactedAction(const std::filesystem::path& dirPath, LPSECURITY_ATTRIBUTES securiryAttributes = nullptr);

			private:
				const std::filesystem::path m_dirPath;
				const LPSECURITY_ATTRIBUTES m_securiryAttributes;

				void execute() override;
				void rollback() override;
			};
		}
	}
}
