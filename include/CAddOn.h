#ifndef __CADDON_H
#define	__CADDON_H

#include <string>
#include <napi.h>

class CAddOn : public Napi::ObjectWrap<CAddOn>
{
private:
	Napi::Value _test( const Napi::CallbackInfo& info ) ;
	static Napi::FunctionReference s_constructor;

public:
	CAddOn(const Napi::CallbackInfo& info) ;
	virtual ~CAddOn() {}
	static Napi::Object _init( const Napi::Env env, Napi::Object exports ) ;
} ;

#endif

