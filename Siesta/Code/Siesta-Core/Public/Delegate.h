#pragma once

#include "Types.h"

template <typename... Args>
class PDelegate
{
public:
	template <std::invocable<Args...> Func>
	void Bind(Func&& InFunc)
	{
		m_Callback = [F = std::move(InFunc)](Args... InArgs) {
			F(InArgs...);
		};
	}

	template <typename THandler>
	void Bind(THandler* Handler, void (THandler::*Callback)(Args...))
	{
		m_Callback = [Handler, Callback](Args&&... InArgs) {
			(Handler->*Callback)(InArgs...);
		};
	}

	void Invoke(Args&&... InArgs) 
	{
		if (m_Callback)
		{
			m_Callback(InArgs...);
		}
	}

private:
	PFunction<void(Args...)> m_Callback;
};

#define MAKE_DELEGATE_TYPE(Name, ...) using Name = PDelegate<__VA_ARGS__>

using TDelegateHandle = uint32;

template<typename ... Args>
class PMultiDelegate
{
	struct TCallback
	{
		void* Handler;
		PFunction<void(Args...)> Func;
	};

public:
	template <std::invocable<Args...> Func>
	TDelegateHandle Bind(Func&& InFunc)
	{
		TCallback OutCallback{};
		OutCallback.Func = [F = std::move(InFunc)](Args&&... InArgs) {
			F(std::forward<Args>(InArgs)...);
		};

		TDelegateHandle OutHandle = (TDelegateHandle)m_Callbacks.size();
		m_Callbacks.push_back(std::move(OutCallback));
		return OutHandle;
	}

	template <typename THandler>
	TDelegateHandle Bind(THandler* Handler, void (THandler::*Callback)(Args...))
	{
		TCallback OutCallback{};
		OutCallback.Func = [Handler, Callback](Args&&... InArgs) {
			(Handler->*Callback)(std::forward<Args>(InArgs)...);
		};

		OutCallback.Handler = Handler;
		TDelegateHandle OutHandle = (TDelegateHandle)m_Callbacks.size();
		m_Callbacks.push_back(std::move(OutCallback));
		return OutHandle;
	}
	
	void Invoke(Args... InArgs)
	{
		for (auto& Callbacks : m_Callbacks)
		{
			if (Callbacks.Func)
			{
				Callbacks.Func(InArgs...);
			}
		}
	}

	void Unbind(TDelegateHandle Handle)
	{
		if (m_Callbacks.size() > Handle)
		{
			m_Callbacks[Handle] = {};
		}
	}

	void Unbind(void* Handler)
	{
		auto Iter = std::find_if(m_Callbacks.begin(), m_Callbacks.end(), [Handler](const TCallback& C) { return C.Handler == Handler; });
		if (Iter != m_Callbacks.end())
		{
			*Iter = {};	
		}
	}

private:
	PDynArray<TCallback> m_Callbacks;
};

#define MAKE_MULTIDELEGATE_TYPE(Name, ...) using Name = PMultiDelegate<__VA_ARGS__>