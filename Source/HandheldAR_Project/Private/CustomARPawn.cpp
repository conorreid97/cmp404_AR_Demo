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

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ACustomARPawn::OnScreenTouch);

}

void ACustomARPawn::OnScreenTouch(const ETouchIndex::Type fingerIndex, const FVector screenPos)
{
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, TEXT("Screen Touched"));

	// Perform a hitTest, get the return values as hitTestResult
	if (!WorldHitTest(FVector2D(screenPos), hitTestResult)) {
		// HitTest returned false, get out
		UKismetSystemLibrary::PrintString(this, "Nothing pressed", true, true, FLinearColor(0, 0.66, 1, 1), 2);
		return;

		// Get object of actor hit
		UClass* hitActorClass = UGameplayStatics::GetObjectClass(hitTestResult.GetActor());

		// If we've hit a target
		if (UKismetMathLibrary::ClassIsChildOf(hitActorClass, ACustomActor::StaticClass())) {
			UKismetSystemLibrary::PrintString(this, "Cube Clicked!", true, true, FLinearColor(0, 0.66, 1, 1), 2);
		}

	}

	
}

bool ACustomARPawn::WorldHitTest(FVector2D screenPos, FHitResult hitResult)
{
	// Get player controller
	APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
	// Perform deprojection taking 2d clicked area and generating reference in 3d world-space.
	FVector worldPosition;
	FVector worldDirection; // Unit Vector
	bool deprojectionSuccess = UGameplayStatics::DeprojectScreenToWorld(playerController, screenPos, /*out*/worldPosition, /*out*/ worldDirection);
	
	// Construct trace vector (from point clicked to 1000.0 units beyond in the same direction)
	FVector traceEndVector = worldDirection * 1000.0;
	traceEndVector = worldPosition + traceEndVector;

	// Perform line trace (Raycast)
	bool traceSuccess = GetWorld()->LineTraceSingleByChannel(hitResult, worldPosition, traceEndVector, ECollisionChannel::ECC_WorldDynamic);
	
	
	
	return traceSuccess;
}

