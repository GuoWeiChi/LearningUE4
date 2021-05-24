// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BatteryMan_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class CUETEST_API ABatteryMan_GameMode : public AGameMode
{
	GENERATED_BODY()
	ABatteryMan_GameMode();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<APawn> PlayerRecharge;

	float SPawn_Z = 500.0f;

	UPROPERTY(EditAnywhere)
		float SPawn_X_Min;

	UPROPERTY(EditAnywhere)
		float SPawn_X_Max;

	UPROPERTY(EditAnywhere)
		float SPawn_Y_Min;

	UPROPERTY(EditAnywhere)
		float SPawn_Y_Max;

	void SpawnPlaerRecharge();
};
