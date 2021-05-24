// Copyright Epic Games, Inc. All Rights Reserved.

#include "CUETestGameMode.h"
#include "CUETestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACUETestGameMode::ACUETestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
