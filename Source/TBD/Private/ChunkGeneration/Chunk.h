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

	// returns int corresponding to player position in 3x3, 0-8 grid.
	UFUNCTION()
	int8 get_player_offset(FVector loc, bool dir = 0) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* floor;

	UFUNCTION()
	void set_size(float x);

private:

	UPROPERTY()
	float size;

protected:
	// Called when the game starts or when spawned

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
