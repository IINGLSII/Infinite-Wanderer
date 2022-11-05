// Fill out your copyright notice in the Description page of Project Settings.


#include "TileGeneration/Tile.h"

// Sets default values
ATile::ATile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	floor = CreateDefaultSubobject<UStaticMeshComponent>("floor");
	ATile::SetRootComponent(floor);
	
}


// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	floor->SetRelativeScale3D(FVector(tile_data.tile_size / 400));
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// returns the chunk offset of a given location, bool indicates axis (1 = X, 0 = Y)
FOffset ATile::get_player_offset(FVector loc) const
{
	FVector position_offset;
	FOffset tile_offset = FOffset(0,0);
	position_offset = loc - (tile_data.tile_size / 2) - Super::GetActorLocation();

	if (abs(position_offset.X) > tile_data.tile_size / 2) {
		if (position_offset.X > 0)
			tile_offset.row = 1;
		else
			tile_offset.row = -1;
	}

	if (abs(position_offset.Y) > tile_data.tile_size / 2) {
		if (position_offset.Y > 0)
			tile_offset.col = 1;
		else
			tile_offset.col = -1;
	}
	return tile_offset;
}

void ATile::load_tile_data(FTileData new_tile_data)
{
	tile_data = new_tile_data;
}
