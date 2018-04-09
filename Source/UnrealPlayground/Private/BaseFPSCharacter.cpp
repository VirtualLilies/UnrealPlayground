// Copyright C 2018 Tomasz Figas

#include "BaseFPSCharacter.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
ABaseFPSCharacter::ABaseFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Take control of the default Player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create a first person camera component.
	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));

	// Attach the camera component to our capsule component.
	FPSCamera->SetupAttachment(GetCapsuleComponent());

	// Position the camera slightly above the eyes.
	FPSCamera->SetRelativeLocation(FVector(0.0f, 0.0f, BaseEyeHeight));

	// Allow the pawn to control camera rotation.
	FPSCamera->bUsePawnControlRotation = true;

	// Create a first person mesh component for the owning player.
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));

	// Only the owning player sees this mesh.
	FPSMesh->SetOnlyOwnerSee(true);

	// Attach the FPS mesh to the FPS camera.
	FPSMesh->SetupAttachment(FPSCamera);

	// Setup relative location and rotation of the component.
	FPSMesh->SetRelativeLocation(FVector(-10.0f, -5.5f, -145.0f));
	FPSMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	// Disable some environmental shadowing to preserve the illusion of having a single mesh.
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	// The owning player doesn't see the regular (third-person) body mesh.
	GetMesh()->SetOwnerNoSee(true);

}

// Called when the game starts or when spawned
void ABaseFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Debug message to verify that BaseFPSCharacter class is being used.
	if (GEngine)
	{
		// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Using BaseFPSCharacter class."));
	}

	UE_LOG(LogTemp, Warning, TEXT("BaseFPSCharacter loaded."));
	
}

// Called every frame
void ABaseFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Setup "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseFPSCharacter::MoveRight);

	// Set up "look" bindings.
	PlayerInputComponent->BindAxis("MouseX", this, &ABaseFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MouseY", this, &ABaseFPSCharacter::AddControllerPitchInput);

	// Set up "action" bindings.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABaseFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABaseFPSCharacter::StopJump);

}

void ABaseFPSCharacter::MoveForward(float Value)
{
	// Find out which way is "forward" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
	UE_LOG(LogTemp, Warning, TEXT("Calling MoveForward input."));
}

void ABaseFPSCharacter::MoveRight(float Value)
{
	// Find out which way is "right" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
	UE_LOG(LogTemp, Warning, TEXT("Calling MoveRight input."));
}

void ABaseFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void ABaseFPSCharacter::StopJump()
{
	bPressedJump = false;
}
