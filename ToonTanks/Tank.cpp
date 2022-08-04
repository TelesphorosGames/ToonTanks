// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


ATank::ATank()
{
    SpringyArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringyArm->SetupAttachment(RootComponent);
    CammyCam = CreateDefaultSubobject<UCameraComponent>(TEXT("Cammy Cam The Camera Man"));
    CammyCam->SetupAttachment(SpringyArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("TurnRight"), this, &ATank::TurnRight);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(PlayerControllerRef)
    {
        FHitResult HitResult;
        PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
       DrawDebugSphere(
            GetWorld(),
            HitResult.ImpactPoint,
            45.f,
            3,
            FColor::Red,
            false,
            -1.f
        );
        if(HitResult.Component!=BaseMesh && HitResult.Component != TurretMesh)
        {
        RotateTurret(HitResult.ImpactPoint);
        }
    }
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bIsAlive = false;
}

void ATank::BeginPlay()
{
    Super::BeginPlay();
    PlayerControllerRef = Cast<APlayerController>(GetController());
   
}


void ATank::MoveForward(float Value)
{
    // UE_LOG(LogTemp, Warning, TEXT("%f"), Value);
    FVector DeltaLocation(0.f);
    // X Coordinate movement = Value * DeltaTime * Speed
	DeltaLocation.X=Value * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed;
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::TurnRight(float Value)
{
    // UE_LOG(LogTemp,Warning, TEXT("%f Turn Value"), Value);
    FRotator DeltaRotation = FRotator {0,0,0};
    DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation);
}