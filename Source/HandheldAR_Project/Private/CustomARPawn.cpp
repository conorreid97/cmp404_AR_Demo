// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomARPawn.h"

// Sets default values
ACustomARPawn::ACustomARPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACustomARPawn::BeginPlay()
{
	Super::BeginPlay();

	// setup config and AR session
	UARSessionConfig* Config = NewObject<UARSessionConfig>();
	UARBlueprintLibrary::StartARSession(Config);

	// Printing messages to the screen
	UKismetSystemLibrary::PrintString(this, FString(TEXT("Hello world")),
		true, true, FLinearColor::Red, 5);

	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, TEXT("Hello World"));

	// attach components
	/*SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComp*///onent>(TEXT("CameraComponent"));
	//CameraComponent->SetupAttachment(SceneComponent);

}

// Called every frame
void ACustomARPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACustomARPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

