// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPC_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "CPPC_Tower.h"
#include "TanksPlayerController.h"

void ACPPC_GameMode::ActorDied(AActor* DeadActor)
{
    if(DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if(ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);
               
    }
    else if (ACPPC_Tower* DestroyedTower = Cast<ACPPC_Tower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
        TargetTowers--;
        if(TargetTowers==0)
        {
            GameOver(true);
        }
    }
}

void ACPPC_GameMode::BeginPlay()
{
    Super::BeginPlay();

   HandleGameStart();

}

void ACPPC_GameMode::HandleGameStart()
{
    TargetTowers = GetTargetTowerCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));

    ToonTanksPlayerController = Cast<ATanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if(ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;

        FTimerDelegate StartTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &ATanksPlayerController::SetPlayerEnabledState, true);

        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, StartTimerDelegate, StartDelay, false);


    }


}

int32 ACPPC_GameMode::GetTargetTowerCount()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this,ACPPC_Tower::StaticClass(), Towers);
    return Towers.Num();
}
