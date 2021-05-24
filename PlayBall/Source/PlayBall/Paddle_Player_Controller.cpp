// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle_Player_Controller.h"

#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"



#include "Paddle.h"


APaddle_Player_Controller::APaddle_Player_Controller()
{
}

void APaddle_Player_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnableInput(this);

	InputComponent->BindAxis("MoveHorizontal", this, &APaddle_Player_Controller::MoveHorizontal);
	InputComponent->BindAction("Launch", IE_Pressed, this, &APaddle_Player_Controller::Launch);

}

void APaddle_Player_Controller::BeginPlay()
{
	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CameraActors);

	FViewTargetTransitionParams params; 
	SetViewTarget(CameraActors[0], params);


	SpawnNewBall();
}

void APaddle_Player_Controller::MoveHorizontal(float AxisValue)
{

	auto MyPawn = Cast<APaddle>(GetPawn());

	if (MyPawn) {

		MyPawn->MoveHorizontal(AxisValue);
	}

}
 
void APaddle_Player_Controller::Launch()
{
	if (MyBall)
	{
		MyBall->Launch();
	}
	
	
}

void APaddle_Player_Controller::SpawnNewBall()
{
	if (!MyBall) {
		MyBall = nullptr;
	}

	if (BallObj) {
		UE_LOG(LogTemp, Warning, TEXT("init MyBall"));
		MyBall = GetWorld()->SpawnActor<ABall>(BallObj, SpawnLocation, SpawnRotation, SpawnInfo);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BallObj init error"));
	}
}
