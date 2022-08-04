// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CPPC_BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ACPPC_BasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPPC_BasePawn();

	void HandleDestruction();

	
	

	// public:	
	// // Called every frame
	// virtual void Tick(float DeltaTime) override;
	//  I DONT NEED THIS RIGHT?! AGH 

protected:

	void RotateTurret(FVector LookAtTarget);

	void Fire();

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess="true"), Category = "My C++")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess="true"), Category = "My C++")
	UStaticMeshComponent* TurretMesh;


private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess="true"), Category = "My C++")
	class UCapsuleComponent* CapsuleComp;






	UPROPERTY(EditDefaultsOnly, Category = "My C++")
	TSubclassOf<class ACPPC_Projectile> ProjectileClass;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess="true"), Category = "My C++")
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* DestructionEffect;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* DestructionSound;

 


};
