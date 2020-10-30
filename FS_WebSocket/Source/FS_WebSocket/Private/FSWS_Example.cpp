// Fill out your copyright notice in the Description page of Project Settings.


#include "FSWS_Example.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AFSWS_Example::AFSWS_Example()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFSWS_Example::BeginPlay()
{
	Super::BeginPlay();
	if (FSWebSocketInstance != nullptr) {
		FSWebSocketInstance->FSOnConnectComplete.AddDynamic(this, &AFSWS_Example::OnConnected);
		FSWebSocketInstance->FSOnClosed.AddDynamic(this, &AFSWS_Example::OnConnectionClosed);
		FSWebSocketInstance->FSOnConnectError.AddDynamic(this, &AFSWS_Example::OnConnectionError);
		FSWebSocketInstance->FSOnReceiveData.AddDynamic(this, &AFSWS_Example::OnReceivedData);
	}
}

// Called every frame
void AFSWS_Example::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFSWS_Example::OnConnected()
{
	UE_LOG(LogTemp, Warning, TEXT("Example - Connected"));
}

void AFSWS_Example::OnReceivedData(const FString & data)
{
	UE_LOG(LogTemp, Warning, TEXT("Example - Message received : %s"), *data);
}

void AFSWS_Example::OnConnectionClosed()
{
	UE_LOG(LogTemp, Warning, TEXT("Example - Connection closed"));
}

void AFSWS_Example::OnConnectionError(const FString& error)
{
	UE_LOG(LogTemp, Warning, TEXT("Example - Connection error : %s"), *error);
}

void AFSWS_Example::SendData(const FString data)
{
	if (FSWebSocketInstance != nullptr) {
		FSWebSocketInstance->SendSDKMessage(data);
	}
}

