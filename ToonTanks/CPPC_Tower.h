// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPPC_BasePawn.h"
#include "CPPC_Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ACPPC_Tower : public ACPPC_BasePawn
{
	GENERATED_BODY()
	
public: 

		virtual void Tick(float DeltaTime) override;

		void HandleDestruction();


	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	private:

	class ATank* Tank;

	UPROPERTY(EditAnywhere, category="My C++")
	float FireRange=500.f;

	FTimerHandle FireRateTimerHandle;

	UPROPERTY(EditAnywhere, category= "My C++")
	float FireRate = 2.f;

	void CheckFireCondition();

	FVector TankSpot;

	UPROPERTY(EditAnywhere)
	float TankSpotOffset = 0.f;




};

	