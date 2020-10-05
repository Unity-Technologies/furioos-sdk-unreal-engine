// Fill out your copyright notice in the Description page of Project Settings.

#include "FS_WebSocketBase.h"
#include "Modules/ModuleManager.h"
#include "WebSockets/Public/IWebSocket.h"
#include "WebSockets/Public/WebSocketsModule.h"
#include "JsonObjectConverter.h"


#define MAX_ECHO_PAYLOAD 64*1024

// Sets default values
AFS_WebSocketBase::AFS_WebSocketBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFS_WebSocketBase::BeginPlay()
{
	Super::BeginPlay();

	FName ModuleName = TEXT("WebSockets");
	FModuleManager& Manager = FModuleManager::Get();
	FWebSocketsModule& Module = Manager.LoadModuleChecked<FWebSocketsModule>("WebSockets");

}

// Called every frame
void AFS_WebSocketBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AFS_WebSocketBase::Connect(const FString& uri) {

	const FString ServerURL = (TEXT("%s"), uri);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *ServerURL);
	const FString ServerProtocol = TEXT("");

	Socket = FWebSocketsModule::Get().CreateWebSocket(ServerURL, ServerProtocol);

	Socket->OnConnected().AddUObject(this, &AFS_WebSocketBase::SendSignIn);

	Socket->OnConnectionError().AddUObject(this, &AFS_WebSocketBase::OnConnectionError);

	if (Debug) {
		Socket->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool bWasClean) -> void {
			UE_LOG(LogTemp, Error, TEXT("Connection Closed"));
		});
		Socket->OnMessage().AddLambda([](const FString& Message) -> void {
			UE_LOG(LogTemp, Warning, TEXT("Message Received : %s"), *Message);
		});
		Socket->OnConnectionError().AddLambda([](const FString& ErrorMessage) -> void {
			UE_LOG(LogTemp, Error, TEXT("Connection Error : %s"), *ErrorMessage);
		});
		Socket->OnConnected().AddLambda([]() -> void {
			UE_LOG(LogTemp, Warning, TEXT("Connection Success"));
		});
		Socket->OnMessageSent().AddLambda([](const FString& MessageString) -> void {
			UE_LOG(LogTemp, Warning, TEXT("Message sent : %s"), *MessageString);
		});
	}

	Socket->OnMessage().AddUObject(this, &AFS_WebSocketBase::OnReceivedData);

	Socket->OnMessage().AddUObject(this, &AFS_WebSocketBase::OnReceivedDataDebug);

	Socket->OnRawMessage().AddLambda([](const void* Data, SIZE_T Size, SIZE_T BytesRemaining) -> void {
		//Here you can implement a Raw Message function
	});

	Socket->Connect();

}

void AFS_WebSocketBase::Close()
{
	if (Socket != nullptr)
		Socket->Close();
	Socket = nullptr;
}


void AFS_WebSocketBase::SendText(const FString& data) {
	if (data.Len() > MAX_ECHO_PAYLOAD)
	{
		UE_LOG(LogTemp, Error, TEXT("Too large package to send > MAX_ECHO_PAYLOAD:%d > %d"), data.Len(), MAX_ECHO_PAYLOAD);
		return;
	}

	if (Socket != nullptr)
	{
		if (!Socket->IsConnected()) return;
		Socket->Send(data);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("The socket is closed, SendText fail"));
	}
}

void AFS_WebSocketBase::SendSignIn()
{
	SendText("{\"type\" :\"signIn\",\"peerName\" :\"SDK_APP\"}");
}


void AFS_WebSocketBase::OnConnectionSuccess() {
//	SendSignIn();
}

void AFS_WebSocketBase::OnConnectionError(const FString& error)
{
	FSOnConnectError.Broadcast(error);
}

void AFS_WebSocketBase::OnConnectionClosed()
{
	FSOnClosed.Broadcast();
}

void AFS_WebSocketBase::OnReceivedData(const FString& data)
{
	FSDKMessage JsonData;
	bool JsonParsed = FJsonObjectConverter::JsonObjectStringToUStruct<FSDKMessage>(
			*data,
			&JsonData,
			0, 0);
	if (!JsonParsed) {
		UE_LOG(LogTemp, Error, TEXT("Failed to parse message"));
		return;
	}
	if (!JsonData.type.IsEmpty()) {
		if (JsonData.type == "signIn") {
			if (!JsonData.status.IsEmpty()) {
				if (JsonData.status == "SUCCESS") {
					if (!JsonData.sessionId.IsEmpty() && !JsonData.peerId.IsEmpty()) {
						SessionId = JsonData.sessionId;
						PeerId = JsonData.peerId;
						if (Debug) {
							UE_LOG(LogTemp, Warning, TEXT("Signed In."));
						}
						FSOnConnectComplete.Broadcast();
					}
				}
				else {
					UE_LOG(LogTemp, Error, TEXT("Sign-in error : %s"), *JsonData.status);
				}
			}
		}
		else if (JsonData.type == "reconnect") {
			if (JsonData.status == "SUCCESS") {
				if (Debug)
					UE_LOG(LogTemp, Warning, TEXT("Slot reconnected"));
			}
			else {
				UE_LOG(LogTemp, Error, TEXT("Reconnect Error : %s"), *JsonData.message);
			}
		}
		else if (JsonData.type == "furioos" && JsonData.task == "sdk") {
			FSOnReceiveData.Broadcast(JsonData.data);
		}
	}
	
}

void AFS_WebSocketBase::OnReceivedDataDebug(const FString & data)
{
	FSOnReceiveDataDebug.Broadcast(data);
}
