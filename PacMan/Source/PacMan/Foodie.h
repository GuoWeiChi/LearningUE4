// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

#include "Foodie.generated.h"

UENUM(BlueprintType)
enum class EFoodieType : uint8 {
	Regula,
	PowerUp
};


//创建委托，用于事件的触发，FoodieType是用于接收的名字
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFoodieEatenEvent, EFoodieType, FoodieType);

UCLASS()
class PACMAN_API AFoodie : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFoodie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void Consume();


	UPROPERTY(EditAnywhere)
		EFoodieType FoodieType = EFoodieType::Regula;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FFoodieEatenEvent FoodieEatenEvent;

private:
	UPROPERTY(EditAnywhere)
		USoundCue* ConsumptionSound;

};
