// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPC_BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ACPPC_BasePawn
{
	GENERATED_BODY()

	public:

	ATank();


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetPlayerControllerRef() const { return PlayerControllerRef; }

	bool bIsAlive = true;
	

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringyArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* CammyCam;

	void MoveForward(float Value);
	void TurnRight(float Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess="true"), Category = "My C++")
	float Speed = 0.f;           

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess="true"), Category = "My C++")
	float TurnRate = 0.f;

	APlayerController* PlayerControllerRef;

	
};
