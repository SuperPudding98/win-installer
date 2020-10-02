#pragma once
#include <functional>
#include <stack>
#include <iostream>


namespace mywininstaller
{
	template <typename T>
	class Transaction
	{
	public:
		Transaction() = default;
		~Transaction();
		Transaction(const Transaction<T>& other) = delete;
		Transaction(Transaction<T>&& other) = delete;
		Transaction<T>& operator=(const Transaction<T>& other) = delete;
		Transaction<T>& operator=(Transaction<T>&& other) = delete;
		void rollback(bool throwOnError = true);
		void commit();
		void addAction(T object, std::function<void(T)> rollbackFunc, const std::string name = "");

	private:
		struct TransactedAction
		{
			T object;
			std::function<void(T)> rollbackFunc;
			const std::string name;

			TransactedAction(T object, std::function<void(T)> rollbackFunc, const std::string name) :
				object(object),
				rollbackFunc(rollbackFunc),
				name(name)
			{}
		};

		std::stack<TransactedAction> m_actions;

		inline void handleRollbackError(bool throwOnError, size_t index, TransactedAction action, const std::exception* exception)
		{
			using std::cerr;
			using std::endl;

			cerr << "Failed to rollback action " << index;
			if (!action.name.empty())
			{
				cerr << " [" << action.name << "]";
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


	template <typename T>
	Transaction<T>::~Transaction()
	{
		rollback(false);
	}

	template <typename T>
	void Transaction<T>::rollback(bool throwOnError)
	{
		size_t actionIndex = m_actions.size() - 1;

		while (!m_actions.empty())
		{
			TransactedAction action = m_actions.top();
			try
			{
				action.rollbackFunc(action.object);
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

	template <typename T>
	void Transaction<T>::commit()
	{
		while (!m_actions.empty())
		{
			m_actions.pop();
		}
	}

	template <typename T>
	void Transaction<T>::addAction(T object, std::function<void(T)> rollbackFunc, const std::string name)
	{
		m_actions.emplace(object, rollbackFunc, name);
	}
}
