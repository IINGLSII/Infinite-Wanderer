// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkGeneration/Chunk.h"

const float        AChunk::size = float(250);

// Sets default values
AChunk::AChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AChunk::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

uint8 AChunk::check_player_adjacency(FVector location) const
{
	FVector offs = Super::GetActorLocation() - location;
	uint8 player_3x3_loc = 4;

	if( offs.X > size ) {
		player_3x3_loc += 1;
	}
	else if ( offs.X < size ) {
		player_3x3_loc -= 1;
	}

	if (offs.Y > size) {
		player_3x3_loc += 3;
	}
	else if (offs.Y < size) {
		player_3x3_loc -= 3;
	}

	return player_3x3_loc;
}