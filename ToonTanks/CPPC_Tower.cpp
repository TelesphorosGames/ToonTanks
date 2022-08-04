// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPC_Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"





void ACPPC_Tower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(Tank)
    {

    float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
    
        if(Distance <= FireRange)
            {
                TankSpot = Tank->GetActorLocation();
                TankSpot.Z = TankSpot.Z - TankSpotOffset;
                RotateTurret(TankSpot);
            }

    }
}

void ACPPC_Tower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}


void ACPPC_Tower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ACPPC_Tower::CheckFireCondition, FireRate, true);

}

void ACPPC_Tower::CheckFireCondition()
{
    if(Tank && Tank != nullptr)
    {
        
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

        if(Distance <= FireRange && Tank->bIsAlive == true)
            {
               Fire();
            }

    }
    
}