{
	"targets": [
		{
			"target_name": "addon",
			"sources": [
				"source/CAddOn.cc", "source/CFuncEmitter.cc", "source/CWorkerThread.cc",
				"include/CAddOn.h", "include/CWorkerThread.h", "include/CFuncEmitter.h" ],
			"defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ],
			"include_dirs": [ "<!@(node -p \"require( 'node-addon-api' ).include\")", "include" ],
		}
	]
}

