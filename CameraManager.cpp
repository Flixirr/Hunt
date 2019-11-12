// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraManager.h"
#include "Classes/Components/InputComponent.h"
#include "Classes/GameFramework/FloatingPawnMovement.h"
#include "Classes/GameFramework/SpringArmComponent.h"
#include "Classes/Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraManager::ACameraManager()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloatingCameraMovement = CreateDefaultSubobject<UFloatingPawnMovement>("CameraMovement");

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");

	CameraArm = CreateDefaultSubobject<USpringArmComponent>("CameraSpringArm");
	CameraArm->SetupAttachment(StaticMesh);
	CameraArm->TargetArmLength = 500.f;

	CameraOne = CreateDefaultSubobject<UCameraComponent>("CameraComponentOne");
	CameraOne->SetRelativeLocation(FVector(-500.f, 0.f, 100.f));
	CameraOne->AddLocalRotation(FRotator(-25.f,0.f,0.f));

	SetRootComponent(StaticMesh);
}

// Called when the game starts or when spawned
void ACameraManager::BeginPlay()
{
	Super::BeginPlay();
	
}
void ACameraManager::MoveCameraForward(float Amount)
{
	FloatingCameraMovement->AddInputVector(GetActorForwardVector() * Amount * BlockFactor *MoveFactor*2);
}

void ACameraManager::MoveCameraRight(float Amount)
{
	FloatingCameraMovement->AddInputVector(GetActorRightVector() * Amount * BlockFactor*MoveFactor*2);

}

void ACameraManager::BlockCamera()
{
	if (bBlockCameraMovement == true)
	{
		bBlockCameraMovement = false;
	}
	else
	{
		bBlockCameraMovement = true;
	}
}

void ACameraManager::BlockMovement()
{
	MoveFactor = 0;
}

void ACameraManager::NBlockMovement()
{
	MoveFactor = 1;
}

// Called every frame
void ACameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	{
		if (bBlockCameraMovement) 
		{
			BlockFactor = 0;
			CameraOne->SetRelativeLocation(FVector(-200.f, 0.f, 0.f));
			CameraOne->SetupAttachment(CameraArm);

		}
		else
		{
			BlockFactor = 1;
			CameraOne->SetRelativeLocation(FVector(-500.f, 0.f, 0.f));
			CameraOne->SetupAttachment(NULL);
			
		}
	}

}

// Called to bind functionality to input
void ACameraManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveCameraForward", this, &ACameraManager::MoveCameraForward);
	PlayerInputComponent->BindAxis("MoveCameraRight", this, &ACameraManager::MoveCameraRight);
	PlayerInputComponent->BindAction("BlockCameraMovement", IE_Pressed, this, &ACameraManager::BlockCamera);
	PlayerInputComponent->BindAction("EnableCameraMovement", IE_Released, this, &ACameraManager::BlockMovement);
	PlayerInputComponent->BindAction("EnableCameraMovement", IE_Pressed, this, &ACameraManager::NBlockMovement);

}

