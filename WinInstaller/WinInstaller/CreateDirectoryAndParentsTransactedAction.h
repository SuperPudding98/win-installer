#pragma once
#include "TransactedAction.h"
#include "Transaction.h"
#include <filesystem>
#include <Windows.h>


namespace mywininstaller
{
	namespace transactions
	{
		namespace filesystem
		{
			class CreateDirectoryAndParentsTransactedAction : public TransactedAction
			{
			public:
				CreateDirectoryAndParentsTransactedAction(const std::filesystem::path& dirPath);
				~CreateDirectoryAndParentsTransactedAction() override;

			private:
				const std::filesystem::path m_dirPath;
				Transaction m_innerTransaction;

				void execute() override;
				void rollback() override;
			};
		}
	}
}
