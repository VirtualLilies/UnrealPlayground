// Copyright C 2018 Tomasz Figas

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseFPSCharacter.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;

UCLASS()
class UNREALPLAYGROUND_API ABaseFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handles input for moving forward and backward.
	UFUNCTION()
		void MoveForward(float Value);

	// Handles input for moving right and left.
	UFUNCTION()
		void MoveRight(float Value);

	// Sets jump flag when key is pressed.
	UFUNCTION()
		void StartJump();

	// Clears jump flag when key is released.
	UFUNCTION()
		void StopJump();

	// Function that handles firing projectiles.
	UFUNCTION()
		void Fire();

	// FPS camera.
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UCameraComponent* FPSCamera;
	
	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		USkeletalMeshComponent* FPSMesh;

	/*The EditAnywhere specifier allow you to change the value of the muzzle offset within the Defaults mode of the Blueprint Editor or within the Details tab for any instance of the character. The BlueprintReadWrite specifier allows you to get and set the value of the muzzle offset within a Blueprint.*/
	// Gun muzzle's offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		FVector MuzzleOffset;

	/*The EditDefaultsOnly specifier means that you will only be able to set the projectile class as a default on the Blueprint, not on each instance of the Blueprint.*/
	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		TSubclassOf<class ABaseFPSProjectile> ProjectileClass;

	
};
