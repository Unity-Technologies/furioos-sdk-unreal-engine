// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Modules/ModuleManager.h"
#include "WebSockets/Public/IWebSocket.h"
#include "WebSockets/Public/WebSocketsModule.h"
#include "FS_WebSocketBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWebSocketConnectError, const FString&, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWebSocketClosed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWebSocketConnected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWebSocketRecieve, const FString&, data);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWebSocketRecieveDebug, const FString&, data);

//DEFINE_LOG_CATEGORY_STATIC(FSWebSocket, Log, All);

USTRUCT()
struct FSDKMessage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		FString type = "furioos";
	UPROPERTY()
		FString task = "sdk";
	UPROPERTY()
		FString data;
	UPROPERTY()
		FString status;
	UPROPERTY()
		FString message;
	UPROPERTY()
		FString sessionId;
	UPROPERTY()
		FString connectionId;
	UPROPERTY()
		FString peerId;
};


UCLASS()
class FS_WEBSOCKET_API AFS_WebSocketBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	FString SessionId;
	FString PeerId;
	AFS_WebSocketBase();
	TSharedPtr<IWebSocket> Socket = nullptr;

	UPROPERTY(EditAnywhere)
	bool Debug = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = FSWebSocket)
	void Connect(const FString& uri);

	UFUNCTION(BlueprintCallable, Category = FSWebSocket)
	void Close();

	UFUNCTION(BlueprintCallable, Category = FSWebSocket)
	void SendText(const FString& data);

	UFUNCTION(BlueprintCallable, Category = FSWebSocket)
	void SendSignIn();

	UFUNCTION()
	void OnConnectionSuccess();

	UFUNCTION()
	void OnConnectionError(const FString& error);

	UFUNCTION()
	void OnConnectionClosed();

	UFUNCTION()
	void OnReceivedData(const FString& data);

	UFUNCTION()
		void OnReceivedDataDebug(const FString& data);

	UPROPERTY(BlueprintAssignable, Category = WebSocket)
	FWebSocketConnectError FSOnConnectError;

	UPROPERTY(BlueprintAssignable, Category = WebSocket)
	FWebSocketClosed FSOnClosed;

	UPROPERTY(BlueprintAssignable, Category = WebSocket)
	FWebSocketConnected FSOnConnectComplete;

	UPROPERTY(BlueprintAssignable, Category = WebSocket)
		FWebSocketRecieve FSOnReceiveData;

	UPROPERTY(BlueprintAssignable, Category = WebSocket)
		FWebSocketRecieveDebug FSOnReceiveDataDebug;
};
