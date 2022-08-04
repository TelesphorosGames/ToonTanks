// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPPC_Projectile.generated.h"

UCLASS()
class TOONTANKS_API ACPPC_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPPC_Projectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess="true"), Category = "My C++")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComp;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const  FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;


	UPROPERTY(EditAnywhere)
	class UParticleSystem* HitParticles;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* ProjectileCloud;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* LaunchSound;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf <class UCameraShakeBase> HitCameraShakeClass;



};
