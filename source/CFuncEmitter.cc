#include <string>
#include <vector>
#include <napi.h>
#include <iostream>
#include "CFuncEmitter.h"

CFuncEmitter::CFuncEmitter(const Napi::CallbackInfo& info, std::string _emit)
	: Napi::AsyncWorker(info.Env())
{
	Napi::Object _this = info.This().As<Napi::Object>() ;
	// イベント発生関数（emit）の実体を取得
	Napi::Function _func = _this.Get("emit").As<Napi::Function>() ;

	// this オブジェクトと関数オブジェクトの永続性を担保する
	m_this = Napi::Persistent(_this) ;
	m_this.SuppressDestruct() ;
	m_func = Napi::Persistent(_func) ;
	m_func.SuppressDestruct() ;

	// JavaScript の関数名をセット
	m_strEmitFunc = _emit ;
}

void CFuncEmitter::Execute()
{
	// ここで_func.Callすると落ちる
}

void CFuncEmitter::OnOK()
{
	Napi::Function _func = m_func.Value() ;
	Napi::Object _this = m_this.Value() ;
	Napi::Env _env = Env() ;

	Napi::HandleScope scope(_env) ;

	// 引数の設定
	// ※このサンプルは文字列の配列
	std::vector<napi_value> _arg = {
		Napi::String::New(_env, m_strEmitFunc),
	} ;
	for (uint32_t idx = 0 ; idx < m_vArg.size() ; idx++) {
		_arg.push_back(Napi::String::New(_env, m_vArg.at(idx))) ;
	}
	// 実行
	_func.Call(_this, _arg) ;
}

void CFuncEmitter::emitQueue(std::vector<std::string> _arg)
{
	// 呼び元から指定された引数をセット
	m_vArg = _arg ;
	// 実行するためのワーカスレッドを起動
	Queue() ;
}

