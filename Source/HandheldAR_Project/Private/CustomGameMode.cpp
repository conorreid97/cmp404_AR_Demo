// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameMode.h"

ACustomGameMode::ACustomGameMode()
{
	DefaultPawnClass = ACustomARPawn::StaticClass();
	GameStateClass = ACustomGameState::StaticClass();
	
	// Activates the tick function
	PrimaryActorTick.bCanEverTick = true;


}

void ACustomGameMode::StartPlay()
{
	// This is called before any BeginPlay
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Current Score: %d"), GetScore()));
	
	// This function will transcend to call BeginPlay on all the actors
	Super::StartPlay();

	

	// spawn cube every 4 seconds
	//GetWorldTimerManager().SetTimer(Ticker, this, &ACustomGameMode::SpawnCube, 4.0f, true, 0.0f);

	SpawnCube();
	
	
	
}

void ACustomGameMode::Tick(float DeltaSeconds)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("SPAWNED")));
	GetWorldTimerManager().SetTimer(Ticker, this, &ACustomGameMode::SpawnCube, 4.0f, true, 0.0f);

	
	//SpawnCube();

}

int32 ACustomGameMode::GetScore()
{
	return GetGameState<ACustomGameState>()->Score;
	//return int32();
}

void ACustomGameMode::SetScore(int32 NewScore)
{
	GetGameState<ACustomGameState>()->Score += NewScore;
}

void ACustomGameMode::SpawnCube()
{
	APlayerCameraManager* camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector camLocation = camManager->GetCameraLocation();
	FVector camForward = camManager->GetCameraRotation().Vector();

	FActorSpawnParameters SpawnInfo;
	FRotator myRot(0, 0, 0);
	FVector myLoc(camLocation.X + 200, camLocation.Y + 200, camLocation.Z + 200);
	ACustomActor* customActor = GetWorld()->SpawnActor<ACustomActor>(myLoc, myRot, SpawnInfo);


	//GetWorldTimerManager().SetTimer(Ticker, this, &ACustomGameMode::SpawnCube, 4.0f, true, 0.0f);

}

