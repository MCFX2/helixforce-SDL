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

using CallbackID = unsigned long long int;

template<class... CallbackParams>
class Delegate
{
private:
	template<typename... T>
	friend struct DelegateHandle;

	using Callback = std::function<void(CallbackParams...)>;

	struct callback_data {
		Callback cb;
		CallbackID handle;
	};

	using CallbackContainer = std::vector<callback_data>;
	static const CallbackID id_invalid = -1;
	//takes a member function and an instance to an object, and returns an std::function
	//that will call it on that specific instance. Usage example:
	//auto my_attached_fn = Attach(&myClass::myFunc, my_instance);
	template<typename Ret_type, typename Src_type, typename Inst, typename... Args>
	static std::function<Ret_type(Args...)> Attach(Ret_type(Src_type::* func)(Args...), Inst instance){
		return [instance, func](Args... args)->Ret_type {return (instance->*func)(args...); };
	}
public:
	//DelegateHandle subscribe(Callback const&) const;

	//subscribes an instance + member delegate func, returns a handle.
	//you MUST keep track of this handle to unsubscribe
	//considering using an intermediate object to manage this for you
	template<typename T>
	DelegateHandle<CallbackParams...> subscribe(T* instance, void(T::* func)(CallbackParams...));

	//invoke the underlying functionset with the given args
	void invoke(CallbackParams...);
	void operator()(CallbackParams... cbp) { invoke(cbp...); };

	void unsubscribe(DelegateHandle<CallbackParams...>&& handle);
	//Delegate& operator+=()

private:
	CallbackContainer callbacks_;
};

//implementation below

template<class ...CallbackParams>
template<typename T>
inline DelegateHandle<CallbackParams...> Delegate<CallbackParams...>::subscribe(T* instance, void(T::* func)(CallbackParams...))
{
	std::function<void(CallbackParams...)> fn = Attach(func, instance);
	DelegateHandle<CallbackParams...> dh(this);
	callbacks_.push_back({ fn, dh.id });

	return dh;
}

template<class ...CallbackParams>
inline void Delegate<CallbackParams...>::invoke(CallbackParams ... cbparams)
{
	for (callback_data& cbd : callbacks_)
	{
		std::invoke(cbd.cb, cbparams...);
	}
}

template<class ...CallbackParams>
inline void Delegate<CallbackParams...>::unsubscribe(DelegateHandle<CallbackParams...>&& handle)
{
	if (handle.id == id_invalid)
	{ // handle is invalid, save some time and don't look
		return;
	}
	for (auto it = callbacks_.begin(); it < callbacks_.end(); ++it)
	{
		if (it->handle == handle.id)
		{
			callbacks_.erase(it);
			break;
		}
	}
}

template<typename ... T>
struct DelegateHandle
{
	static CallbackID cur_id;
	DelegateHandle(Delegate<T...>* t) : id(cur_id++), unsub_target(t){}
	DelegateHandle() : id(Delegate<T...>::id_invalid), unsub_target(nullptr){}
	DelegateHandle(const DelegateHandle&) = delete;
	DelegateHandle(DelegateHandle&& dh)
	{
		id = dh.id; unsub_target = dh.unsub_target;
		dh.unsub_target = nullptr;
	}
	~DelegateHandle() {
		if(unsub_target) unsub_target->unsubscribe(std::move(*this));
	}

	DelegateHandle& operator=(DelegateHandle&& rhs) {
		this->~DelegateHandle();
		id = rhs.id; unsub_target = rhs.unsub_target;
		rhs.unsub_target = nullptr;
		return *this;
	}

	CallbackID id;
	Delegate<T...>* unsub_target;
};
template<typename ...T>
CallbackID DelegateHandle<T...>::cur_id = 0;