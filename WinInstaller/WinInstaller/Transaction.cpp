#include "Transaction.h"
#include "TransactedAction.h"
#include <stack>
#include <iostream>
#include <string>


namespace mywininstaller
{
	namespace transactions
	{
		Transaction::~Transaction()
		{
			rollback(false);
		}

		void Transaction::rollback(bool throwOnError)
		{
			size_t actionIndex = m_actions.size() - 1;

			while (!m_actions.empty())
			{
				// This dereference should be fine since we never allow null to be pushed to the stack
				TransactedAction& action = *m_actions.top();
				try
				{
					action.rollback();
				}
				catch (const std::exception& e)
				{
					handleRollbackError(throwOnError, actionIndex, action, &e);
				}
				catch (...)
				{
					handleRollbackError(throwOnError, actionIndex, action, nullptr);
				}

				m_actions.pop();
				actionIndex--;
			}
		}

		void Transaction::commit()
		{
			while (!m_actions.empty())
			{
				m_actions.pop();
			}
		}

		void Transaction::addAction(std::unique_ptr<TransactedAction> action)
		{
			if (!action)
			{
				throw std::invalid_argument("action pointer must not be null.");
			}

			// We first push to prevent a situation where execute succeeds but push fails, and rollback is never called.
			// This way if push throws we will not execute the action.
			m_actions.push(std::move(action));
			try
			{
				m_actions.top()->execute();
			}
			catch (...)
			{
				// If execute failed we do not want to rollback this action.
				m_actions.pop();
				throw;
			}
		}
	}
}
