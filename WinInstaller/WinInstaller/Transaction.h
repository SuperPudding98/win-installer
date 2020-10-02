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
			catch (...)
			{
				// TODO: better message + maybe dedicated log function
				// Perhaps show stacktrace
				std::cerr << "Failed to rollback action " << actionIndex;
				if (!action.name.empty())
				{
					std::cerr << " [" << action.name << "]";
				}
				std::cerr << ". Will still try to rollback previous actions." << std::endl;

				if (throwOnError)
				{
					throw;
				}
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
