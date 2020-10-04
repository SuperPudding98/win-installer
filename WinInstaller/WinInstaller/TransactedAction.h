#pragma once
#include <string>


namespace mywininstaller
{
	namespace transactions
	{
		class Transaction;


		class TransactedAction
		{
		public:
			TransactedAction(const std::string& name = "") :
				m_name(name)
			{}
			virtual ~TransactedAction() = default;
			const std::string& name() const { return m_name; }

		private:
			const std::string m_name;

			virtual void execute() = 0;
			virtual void rollback() = 0;

			friend class Transaction;
		};
	}
}
