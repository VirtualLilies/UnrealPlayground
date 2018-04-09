// Copyright C 2018 Tomasz Figas

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingActor.generated.h"

class UStaticMeshComponent;
class UParticleSystemComponent;

UCLASS()
class UNREALPLAYGROUND_API AFloatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* StaticMeshComp;

	float RunningTime;

	UPROPERTY(EditAnywhere, Category = "Parameters")
		float FloatingScale = -20.0f;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* ParticleComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Functionality")
	void RunFloating(float DeltaTime);



};

