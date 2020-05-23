#pragma once

/*
This file warrants some explanation. Essentially, there are some cases
where we want to run a single function without knowing all the end
listeners. For instance, multiple behaviors may want to listen to the
same collision event. So, to enable this we wrap all of those functions
around a delegate class like this. We then execute the delegate
and it calls back all of the stored listeners with the handle they gave us,
plus some parameters (templatized out here).

Usage to follow:
Collider.h: Delegate onCollide;

myBehavior.cpp: onCollide.subscribe(this, myBehavior::someFunc);
*/

#include <functional>
#include <vector>


using DelegateHandle = unsigned long long int;


template<class... CallbackParams>
class Delegate
{
private:
	using Callback = std::function<void(CallbackParams...)>;
	using CallbackContainer = std::vector<Callback>;

	//takes a member function and an instance to an object, and returns an std::function
	//that will call it on that specific instance. Usage example:
	//auto my_attached_fn = Attach(&myClass::myFunc, my_instance);
	template<typename Ret_type, typename Src_type, typename Inst, typename... Args>
	std::function<Ret_type(Args...)> Attach(Ret_type(Src_type::* func)(Args...), Inst instance)
	{
		return [instance, func](Args... args)->Ret_type {return (instance->*func)(args...); };
	}
public:
	//DelegateHandle subscribe(Callback const&) const;

	template<typename T>
	void subscribe(T* instance, void(T::* func)(CallbackParams...));

	void invoke(CallbackParams...);

private:
	CallbackContainer callbacks_;
};

//implementation below

template<class ...CallbackParams>
template<typename T>
inline void Delegate<CallbackParams...>::subscribe(T* instance, void(T::* func)(CallbackParams...))
{
	callbacks_.push_back(Attach(func, instance));
}

template<class ...CallbackParams>
inline void Delegate<CallbackParams...>::invoke(CallbackParams ... cbparams)
{
	for (Callback& cb : callbacks_)
	{
		std::invoke(cb, cbparams...);
	}
}
