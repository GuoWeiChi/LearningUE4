// Fill out your copyright notice in the Description page of Project Settings.


#include "Brick.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Ball.h"
#include "math.h"
// Sets default values
ABrick::ABrick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_Brick = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Brick"));

	SM_Brick->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	Box_Collision->SetBoxExtent(FVector(25.0f, 10.0f, 10.0f));

	RootComponent = SM_Brick;
	Box_Collision->SetupAttachment(SM_Brick, "Brick");
}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Brick Begin Play"));
	Super::BeginPlay();

	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &ABrick::OnOverlapBegin);
	
}



// Called every frame
void ABrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABrick::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Ball"))
	{
		ABall* MyBall = Cast<ABall>(OtherActor);

		FVector BallVelocity = MyBall->GetVelocity();
		//BallVelocity *= (SpeedModifierOnBounce - 1.0f);

		UE_LOG(LogTemp, Warning, TEXT("BallVelocity:%f,%f,%f,%f"), BallVelocity[0], BallVelocity[1], BallVelocity[2], sqrt(pow(BallVelocity[0],2)+ pow(BallVelocity[1], 2)+ pow(BallVelocity[2], 2)));

		//MyBall->GetBall()->SetPhysicsLinearVelocity(BallVelocity, true);

		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &ABrick::DestroyBrick, 0.1f, false);
	}
}

void ABrick::DestroyBrick()
{
	this->Destroy();
}

