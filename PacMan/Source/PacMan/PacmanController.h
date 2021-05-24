// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PacmanPawn.h"
#include "PacmanController.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API APacmanController : public APlayerController
{
	GENERATED_BODY()

protected:
	void SetupInputComponent() override;

	APacmanPawn* GetPacmanPawn() const;

public:
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void StopMove();


	//记录按下键的数量
	int pressedCount = 0;

	
};
