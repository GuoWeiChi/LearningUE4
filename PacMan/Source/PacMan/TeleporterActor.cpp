// Fill out your copyright notice in the Description page of Project Settings.
#include "TeleporterActor.h"


#include "Engine/Public/TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/SceneComponent.h"

// Sets default values
ATeleporterActor::ATeleporterActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATeleporterActor::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &ATeleporterActor::OnOverlapBegin);
}

// Called every frame
void ATeleporterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleporterActor::TeleportToTarget(AActor* Actor)
{
	UE_LOG(LogTemp, Warning, TEXT("cOLLISION"));
	USceneComponent* TargetSpawn = Cast<USceneComponent>(Target->GetDefaultSubobjectByName("Spawn"));

	if (TargetSpawn != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn is not null"));
		UGameplayStatics::PlaySound2D(this, TeleportSound);

		Actor->SetActorLocation(TargetSpawn->GetComponentLocation());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn is null"));
	}
	
}

void ATeleporterActor::OnOverlapBegin(AActor* TeleporterActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Pacman"))
	{
		//下一帧调用
		GetWorldTimerManager().SetTimerForNextTick([OtherActor, this]() {TeleportToTarget(OtherActor); });
	}
}

