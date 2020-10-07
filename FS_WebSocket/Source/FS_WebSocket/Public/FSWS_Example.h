// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FS_WebSocketBase.h"
#include "FSWS_Example.generated.h"

UCLASS()
class FS_WEBSOCKET_API AFSWS_Example : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFSWS_Example();

	UPROPERTY(EditAnywhere)
	AFS_WebSocketBase* FSWebSocketInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void OnConnected();

	UFUNCTION()
	void OnReceivedData(const FString &data);

	UFUNCTION()
	void OnConnectionClosed();

	UFUNCTION()
	void OnConnectionError(const FString& error);

	UFUNCTION()
	void SendData(const FString data);

};
