// Fill out your copyright notice in the Description page of Project Settings.


#include "BallBoound.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Paddle_Player_Controller.h"

// Sets default values
ABallBoound::ABallBoound()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = Box_Collision;

}

// Called when the game starts or when spawned
void ABallBoound::BeginPlay()
{
	Super::BeginPlay();

	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &ABallBoound::OnOverlapBegin);

	PlayerController_REF = Cast<APaddle_Player_Controller>(
		UGameplayStatics::GetPlayerController(GetWorld(), 0)
		);
	
}

// Called every frame
void ABallBoound::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABallBoound::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Ball"))
	{
		OtherActor->Destroy();

		PlayerController_REF->SpawnNewBall();
	}
}


