// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chunk.generated.h"

UENUM()
enum class EWeather : uint8 {
	CLEAR = 0 UMETA(DisplayName = "CLEAR"),
	FOG = 1   UMETA(DisplayName = "FOG"),
	SNOW = 2  UMETA(DisplayName = "SNOW"),
	STORM = 3 UMETA(DisplayName = "STORM"),
};

UENUM()
enum class EStructure : uint8 {
	NONE = 0 UMETA(DisplayName = "NONE"),
	RUINS = 1   UMETA(DisplayName = "RUINS"),
	ALTAR = 2  UMETA(DisplayName = "ALTAR"),
	ROAD = 3 UMETA(DisplayName = "ROAD"),
};

UENUM()
enum class EEncounter : uint8 {
	NONE = 0 UMETA(DisplayName = "NONE"),
	WOLVES = 1 UMETA(DisplayName = "WOLVES"),
	SKELETONS = 2   UMETA(DisplayName = "SKELETONS"),
	WANDERER = 3  UMETA(DisplayName = "WANDERER"),
};


USTRUCT()
struct FChunkData
{
	GENERATED_BODY()

	FChunkData() {
		weather = EWeather::CLEAR;
		structure = EStructure::NONE;
		encounter = EEncounter::NONE;
		folliage_density = 0.5;
		chunk_size = 400;
	}

	UPROPERTY()
		EWeather weather;

	UPROPERTY()
		EStructure structure;

	UPROPERTY()
		EEncounter encounter;

	UPROPERTY()
		float folliage_density;

	UPROPERTY()
		float chunk_size;
};


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
		void load_chunk_data(FChunkData new_chunk_data);

private:

	UPROPERTY()
		FChunkData chunk_data = FChunkData();

protected:
	// Called when the game starts or when spawned

	virtual void BeginPlay() override;

public:	
	// Called every frame

	virtual void Tick(float DeltaTime) override;
};
