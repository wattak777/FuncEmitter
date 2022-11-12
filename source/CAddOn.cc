#include <iostream>
#include <napi.h>
#include "CAddOn.h"
#include "CWorkerThread.h"

Napi::FunctionReference CAddOn::s_constructor;

CAddOn::CAddOn(const Napi::CallbackInfo& info) : Napi::ObjectWrap<CAddOn>(info)
{
	std::cout << "CAddOn::constructor" << std::endl ;

	CWorkerThread* pWorkerThread = new CWorkerThread(info) ;
	pWorkerThread->startTask() ;
}

Napi::Object CAddOn::_init(const Napi::Env env, Napi::Object exports)
{
	Napi::HandleScope scope(env) ;
	Napi::Function func = DefineClass(env, "CAddOn", {
		InstanceMethod("test", &CAddOn::_test),
	}) ;

	std::cout << "_init" << std::endl ;

	s_constructor = Napi::Persistent(func) ;
	s_constructor.SuppressDestruct();
	exports.Set("CAddOn", func) ;

	return exports ;
}

Napi::Value CAddOn::_test(const Napi::CallbackInfo& info)
{
	std::string _arg = info[0].As<Napi::String>().Utf8Value() ;

	std::cout << __FUNCTION__ << _arg << std::endl ;

	return info.Env().Undefined() ;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
	std::cout << "Init." << std::endl ;
	return CAddOn::_init(env, exports) ;
}
NODE_API_MODULE(addon, Init)

