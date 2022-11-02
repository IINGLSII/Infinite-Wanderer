// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkGeneration/Chunk.h"

// Sets default values
AChunk::AChunk()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	floor = CreateDefaultSubobject<UStaticMeshComponent>("floor");
	AChunk::SetRootComponent(floor);
	
}


// Called when the game starts or when spawned
void AChunk::BeginPlay()
{
	Super::BeginPlay();
	floor->SetRelativeScale3D(FVector(chunk_data.chunk_size / 400));
}

// Called every frame
void AChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// returns the chunk offset of a given location, bool indicates axis (1 = X, 0 = Y)
int8 AChunk::get_player_offset(FVector loc, bool dir) const
{
	float offs;
	if (dir)
		offs = loc.X - chunk_data.chunk_size / 2 - Super::GetActorLocation().X;
	else
		offs = loc.Y - chunk_data.chunk_size / 2 - Super::GetActorLocation().Y;

	if (abs(offs) > chunk_data.chunk_size / 2) {
		if (offs > 0)
			return 1;
		else
			return -1;
	}
	return 0;
}

void AChunk::load_chunk_data(FChunkData new_chunk_data)
{
	chunk_data = new_chunk_data;
}
