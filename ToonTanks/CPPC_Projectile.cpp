// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPC_Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ACPPC_Projectile::ACPPC_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));

	ProjectileCloud = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System Component"));

	ProjectileCloud->SetupAttachment(RootComponent);

	
	

}

// Called when the game starts or when spawned
void ACPPC_Projectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &ACPPC_Projectile::OnHit);


if (LaunchSound)
{
	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
}
	
	
}

// Called every frame
void ACPPC_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ACPPC_Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const  FHitResult& Hit)
{
	
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr)
	{
		Destroy();
	 return;
	}
	
	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();

	UClass* DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(
			OtherActor,
			Damage,
			MyOwnerInstigator,
			this,
			DamageTypeClass
		);
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());

		if(HitCameraShakeClass)
		{

			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
			
		}
		
	}
	
	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	}
		Destroy();

	UE_LOG(LogTemp,Error,TEXT("%s was hit!"), *OtherActor->GetName());

	






}