// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryMan_GameMode.h"
#include "GameFramework/Actor.h"

ABatteryMan_GameMode::ABatteryMan_GameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABatteryMan_GameMode::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle UnsedHandle;
	GetWorldTimerManager().SetTimer(UnsedHandle, this, &ABatteryMan_GameMode::SpawnPlaerRecharge, FMath::RandRange(1,3), true);

}

void ABatteryMan_GameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABatteryMan_GameMode::SpawnPlaerRecharge()
{
	float RandX = FMath::RandRange(SPawn_X_Min, SPawn_X_Max);
	float RandY = FMath::RandRange(SPawn_Y_Min, SPawn_Y_Max);

	FVector SpawnPosition = FVector(RandX, RandY, SPawn_Z);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

	GetWorld()->SpawnActor(PlayerRecharge,&SpawnPosition,&SpawnRotation);
}
