// Copyright Epic Games, Inc. All Rights Reserved.

#include "FS_WebSocket.h"

#define LOCTEXT_NAMESPACE "FFS_WebSocketModule"

void FFS_WebSocketModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FFS_WebSocketModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFS_WebSocketModule, FS_WebSocket)