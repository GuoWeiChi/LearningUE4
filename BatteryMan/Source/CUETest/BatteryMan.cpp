// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryMan.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABatteryMan::ABatteryMan()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	//bUseControllerRotationPitch = false;
	//bUseControllerRotationYaw = false;
	//bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;  //如果为真，则使用相机方向旋转角色，使用RotationRate作为角色旋转变化的速率。
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 900.0f;
	GetCharacterMovement()->AirControl = 0.0f;//在空中控制角色的灵敏度

	//创建USpringArmComponent组件
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	CameraBoom->TargetArmLength = 300.0f;//300 cm
	CameraBoom->bUsePawnControlRotation = true;//运动时控制视角

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	//附加到CameraBoom上
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	bDead = false;

	Power = 100;

	Power_Threshold = 1;
}





// Called when the game starts or when spawned
void ABatteryMan::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABatteryMan::OnBeginOverlap);

	if (Player_Power_Widget_Class != nullptr) {
		Player_Power_Widget = CreateWidget(GetWorld(), Player_Power_Widget_Class);
		Player_Power_Widget->AddToViewport();
	}
	
}

void ABatteryMan::RestartGame()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()),false);
}

// Called every frame
void ABatteryMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Power -= DeltaTime * Power_Threshold;

	if (Power <= 0) {
		bDead = true;

		//游戏结束
		GetMesh()->SetSimulatePhysics(true);

		FTimerHandle UnsedHandle;
		GetWorldTimerManager().SetTimer(UnsedHandle, this, &ABatteryMan::RestartGame, 3.0f, false);

	}

}

// Called to bind functionality to input
void ABatteryMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Accelerate", IE_Pressed, this, &ABatteryMan::Accelerate);
	PlayerInputComponent->BindAction("Accelerate", IE_Released, this, &ABatteryMan::DeAccelerate);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABatteryMan::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABatteryMan::MoveRight);
}

void ABatteryMan::OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Collided with"));
	if (OtherActor->ActorHasTag("Recharge"))
	{
		

		Power += 10.0f;

		if (Power > 100.0f)
			Power = 100.0f;

		
		OtherActor->Destroy();
	}
}

void ABatteryMan::MoveForward(float Axis)
{
	if (!bDead)
	{
		const FRotator rotation = Controller->GetControlRotation();

		const FVector Direction = FRotationMatrix(rotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Axis);
	}
}

void ABatteryMan::MoveRight(float Axis)
{
	//UE_LOG(LogTemp, Warning, TEXT("MoveRight %f"),Axis);
	if (!bDead)
	{
		const FRotator rotation = Controller->GetControlRotation();

		const FVector Direction = FRotationMatrix(rotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Axis);
	}
}

void ABatteryMan::Accelerate()
{

	GetCharacterMovement()->MinAnalogWalkSpeed = 6000;
	

}

void ABatteryMan::DeAccelerate()
{
	GetCharacterMovement()->MinAnalogWalkSpeed = 0;
}

