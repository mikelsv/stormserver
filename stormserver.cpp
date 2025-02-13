#define PROJECTNAME "stormserver"
#define PROJECTVER PROJECTNAME ## _versions
#define USEMSV_MSVCORE

#define USEMSV_ITOS
#define USEMSV_ILIST
#define USEMSV_OLIST
#define USEMSV_MLIST
#define USEMSV_XDATACONT

#define USEMSV_STORMSERVER
#define USEMSV_WEBSOCKETS

#define USEMSV_CONFLINE
#define USEMSV_CONSOLE
#define USEMSV_HASH
#define USEMSV_HTTP
#define USEMSV_OPENSSL
#define USEMSV_PCRE
#define STORMSERVER_POLL_AUTO

#define USEMSV_MSL_FL

#define STORMSERVER_CORE_MODSTATE

#define USEMSV_LIGHTSERVER

// Debug
#define USEMSV_LIGHTSERVER_WEBSOCKET_PROCESS light_websocket_debug

#include "../msvcore2/msvcore.cpp"

Versions PROJECTVER[]={
	// new version to up
	"0.0.0.1", "25.05.2015 00:34"
};

//DWORD StormServerEmulate(LPVOID){
//	Sleep(300);
//
//	//for(int i=0; i<64*1024; i++)
//	//	MyStormCore.AddSocketEmulate(listen_http::static_storm_new(), i + 1);
//
//	while(1){
//		print(HLString() + "Sockets: " + MyStormCore.GetSocketsCount() + "\r\n");
//		Sleep(500);
//	}
//
//	return 0;
//}

DWORD StormServerThread(LPVOID);
DWORD LightServerThread(LPVOID);

//int modstate_debug = 0;

int main(int args, char* arg[], char* env[]){
	msvcoremain(args, arg, env);
	print(PROJECTNAME, " v.", PROJECTVER[0].ver, " (", PROJECTVER[0].date, ").\r\n");

	
	ConfLine cf(STORMSERVER_CONFIG);
	VString debug = cf.Get("ListenDebug");

	if(debug)
		MyStormCore.DebugEnable(1);

	// Read cmd
	//VString l;

	//while(l = msvcorestate.link.GetArg()){
	//	if(l == "--debug"){
	//		MyStormCore.DebugEnable(1);
	//		//modstate_debug = 1;
	//	}
	//}

	//StartThread(StormServerEmulate);
	StormServerThread(0);

	return 0;
}

DWORD StormServerThread(LPVOID){
	MyStormServer.UseConf(STORMSERVER_CONFIG);
//	MyStormServer.InsertProto("raw", listen_raw::static_storm_new());
	MyStormServer.InsertProto("http", listen_http::static_storm_new());

	// Modstate
	if(MyStormCore.IsDebug()){
		StartThread(LightServerThread);
	}

	MyStormServer.Run();

	print("Open port failed. Exit.\r\n");

	Sleep(1000);
	exit(0);
	return 0;
}

DWORD LightServerThread(LPVOID){
	LightServerWebDebug light;

	ConfLine cf(STORMSERVER_CONFIG);
	VString port = cf.Get("ListenDebug");

	if(!port){
		print("Error! ListenDebug is empty.\r\n");
		return 0;
	}

	light.SetPort(port);
	light.SetMaxCon(5);
	light.Listen();

	print("Error! Listen() closed.\r\n");

	return 0;
}