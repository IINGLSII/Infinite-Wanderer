// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chunk.generated.h"

UCLASS()
class AChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChunk();

	static float size;

	// returns int corresponding to player position in 3x3, 0-8 grid.
	UFUNCTION()
	uint8 check_player_adjacency(FVector location) const;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* earth;

protected:
	// Called when the game starts or when spawned

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
