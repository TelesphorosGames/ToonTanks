// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPC_BasePawn.h"
#include "Components/CapsuleComponent.h"
// #include "DrawDebugHelpers.h" //for debug spheres in code
#include "CPPC_Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"



// Sets default values
ACPPC_BasePawn::ACPPC_BasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp=CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider:"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh:"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh:"));

	TurretMesh->SetupAttachment(BaseMesh); 

	ProjectileSpawnPoint=CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

void ACPPC_BasePawn::HandleDestruction()
{
	if(DestructionEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DestructionEffect, GetActorLocation(), GetActorRotation());
		if(DestructionSound)
		{
		UGameplayStatics::PlaySoundAtLocation(this, DestructionSound, GetActorLocation());
		}
	}
}

void ACPPC_BasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(ToTarget.Rotation());
	TurretMesh->SetWorldRotation(LookAtRotation);
}

void ACPPC_BasePawn::Fire()
{
	auto Projectile = GetWorld()->SpawnActor<ACPPC_Projectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
	Projectile->SetOwner(this);
}



// void ACPPC_BasePawn::Tick(float DeltaTime)
// {
// 	   Super::Tick(DeltaTime);
// } truly easy to write back in anyways 

	//  DrawDebugSphere(
    //         GetWorld(),
    //         ProjectileSpawnPoint->GetComponentLocation(),
    //         35.f,
    //         6,
    //         FColor::Blue,
    //         false,
    //         3.f
    //     );