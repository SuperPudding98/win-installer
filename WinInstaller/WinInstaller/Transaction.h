#pragma once
#include "TransactedAction.h"
#include <stack>
#include <iostream>
#include <string>


namespace mywininstaller
{
	namespace transactions
	{
		class Transaction
		{
		public:
			Transaction() = default;
			~Transaction();
			Transaction(const Transaction& other) = delete;
			Transaction(Transaction&& other) = delete;
			Transaction& operator=(const Transaction& other) = delete;
			Transaction& operator=(Transaction&& other) = delete;
			void rollback(bool throwOnError = true);
			void commit();
			void addAction(std::unique_ptr<TransactedAction> action);

		private:
			std::stack<std::unique_ptr<TransactedAction>> m_actions;

			inline void handleRollbackError(bool throwOnError, size_t index, const TransactedAction& action, const std::exception* exception)
			{
				using std::cerr;
				using std::endl;

				cerr << "Failed to rollback action " << index;
				if (!action.name().empty())
				{
					cerr << " [" << action.name() << "]";
				}
				cerr << "." << endl;
				if (exception)
				{
					cerr << "  * Error: " << exception->what() << endl;
				}

				if (throwOnError)
				{
					throw;
				}
				else
				{
					cerr << "  * Will still try to rollback previous actions." << endl;
				}
			}
		};
	}
}
