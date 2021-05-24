// Fill out your copyright notice in the Description page of Project Settings.


#include "PacmanController.h"

void APacmanController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("MoveUP", IE_Pressed, this, &APacmanController::MoveUp);
	InputComponent->BindAction("MoveDown", IE_Pressed, this, &APacmanController::MoveDown);
	InputComponent->BindAction("MoveLeft", IE_Pressed, this, &APacmanController::MoveLeft);
	InputComponent->BindAction("MoveRight", IE_Pressed, this, &APacmanController::MoveRight);

	//InputComponent->BindAction("MoveUP", IE_Released, this, &APacmanController::StopMove);
	//InputComponent->BindAction("MoveDown", IE_Released, this, &APacmanController::StopMove);
	//InputComponent->BindAction("MoveLeft", IE_Released, this, &APacmanController::StopMove);
	//InputComponent->BindAction("MoveRight", IE_Released, this, &APacmanController::StopMove);
}

APacmanPawn* APacmanController::GetPacmanPawn() const
{
	return Cast<APacmanPawn>(GetPawn());
}



void APacmanController::MoveUp()
{
	if (GetPacmanPawn() != nullptr) {
		GetPacmanPawn()->SetFrozen(false);
		GetPacmanPawn()->SetDirection(FVector::UpVector);
	}
}

void APacmanController::MoveDown()
{
	if (GetPacmanPawn() != nullptr) {
		GetPacmanPawn()->SetFrozen(false);
		GetPacmanPawn()->SetDirection(FVector::DownVector);
	}
}

void APacmanController::MoveLeft()
{
	if (GetPacmanPawn() != nullptr) {
		GetPacmanPawn()->SetFrozen(false);
		GetPacmanPawn()->SetDirection(FVector::LeftVector);
	}
}

void APacmanController::MoveRight()
{
	if (GetPacmanPawn() != nullptr) {
		GetPacmanPawn()->SetFrozen(false);
		GetPacmanPawn()->SetDirection(FVector::RightVector);
	}
}

void APacmanController::StopMove()
{

	if (GetPacmanPawn() != nullptr) {
			GetPacmanPawn()->SetFrozen(true);
	}
}
