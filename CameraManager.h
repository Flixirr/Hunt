// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraManager.generated.h"

UCLASS()
class WEEKONECAMERA4_API ACameraManager : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveCameraForward(float Amount);
	void MoveCameraRight(float Amount);

	class UFloatingPawnMovement* FloatingCameraMovement;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USpringArmComponent* CameraArm;


	UPROPERTY(EditAnywhere, Category = "Components")
	class UCameraComponent* CameraOne;


	bool bBlockCameraMovement;

	void BlockCamera();
	void BlockMovement();
	void NBlockMovement();
	float BlockFactor;
	float MoveFactor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
