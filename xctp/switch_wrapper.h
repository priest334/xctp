#pragma once


#include <map>

template <typename _Type, typename _Handler>
class SwitchWrapper {
	typedef _Handler SwitchHandler;
	typedef std::map<const _Type, SwitchHandler> SwitchHandlerSet;
public:
	SwitchWrapper(const _Type& expression) : expression_(expression), default_handler_(nullptr) {
	}

	SwitchWrapper& Case(const _Type& expression, const SwitchHandler& handler) {
		handlers_[expression] = handler;
		return (*this);
	}

	SwitchWrapper& Default(const SwitchHandler& handler) {
		default_handler_ = handler;
		return (*this);
	}

	template <typename ...Args>
	void Call(Args... args) {
		auto iter = handlers_.find(expression_);
		if (iter != handlers_.end()) {
			iter->second(args...);
			return;
		}
		if (default_handler_) {
			default_handler_(args...);
		}
	}

private:
	_Type expression_;
	SwitchHandlerSet handlers_;
	SwitchHandler default_handler_;
};



