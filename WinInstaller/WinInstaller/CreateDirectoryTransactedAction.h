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
				CreateDirectoryTransactedAction(const std::filesystem::path& dirPath, LPSECURITY_ATTRIBUTES securiryAttributes = nullptr, bool existOK = false);

			private:
				const std::filesystem::path m_dirPath;
				const LPSECURITY_ATTRIBUTES m_securiryAttributes;
				const bool m_existOK;
				bool m_created;

				void execute() override;
				void rollback() override;
			};
		}
	}
}
