// Fill out your copyright notice in the Description page of Project Settings.


#include "TileGeneration/TileGenerator.h"


ATileGenerator::ATileGenerator()
{
	
}

void ATileGenerator::BeginPlay() {
	grid_array.Init(nullptr, dim * dim);
	// dimension must be odd (has a center tile)
	verify(dim % 2 != 0);
}


bool ATileGenerator::validate_offset(FOffset offset) const
{
	return (offset.row >= -dim / 2 && offset.row <= dim / 2) && (offset.col >= -dim / 2 && offset.col <= dim / 2);
}


int ATileGenerator::convert_offset_to_idx(FOffset offset) const
{
	return ((-offset.row + dim/2) * dim) + (offset.col + dim/2);
}

FOffset ATileGenerator::convert_idx_to_offset(int idx) const 
{
	return FOffset(-(idx / dim) + dim / 2, (idx % dim) - dim / 2);
}

int ATileGenerator::get_dim() const 
{ 
	return dim; 
}

float ATileGenerator::get_tile_size() const
{ 
	return tile_size; 
}

ATile* ATileGenerator::get_tile(FOffset offset) const
{
	return get_tile(offset, grid_array);
}

ATile* ATileGenerator::get_tile_by_index(int32 idx) const
{
	return get_tile(convert_idx_to_offset(idx), grid_array);
}

ATile* ATileGenerator::get_tile (FOffset offset, const TArray<ATile*>& arr) const
{
	// check if row/column offsets fall within dimension of array (dim)
	verify(ATileGenerator::validate_offset(offset));
	
	// index and return contents of array at indexed position
	int pos = ATileGenerator::convert_offset_to_idx(offset);
	return arr[pos];
}

void ATileGenerator::set_tile(FOffset offset, ATile* tile, TArray<ATile*>& arr)
{
	// check if row/column fall within dimension of array (dim)
	verify(ATileGenerator::validate_offset(offset));

	// set contents of array at indexed position
	int pos = ATileGenerator::convert_offset_to_idx(offset);
	arr[pos] = tile;
}


void ATileGenerator::spawn_tile(FOffset tile_offset)
{
	// get reference to center
	ATile* center = ATileGenerator::get_tile(FOffset(0,0), grid_array);
	FVector location_offset = FVector(tile_offset.row * tile_size, tile_offset.col * tile_size, 0);
	FTransform spawn_transform;
	// determine if center exists
	if (center != nullptr)
		spawn_transform.SetLocation(center->GetActorLocation() + location_offset);
	else
		spawn_transform.SetLocation(this->GetActorLocation() + location_offset);

	// spawn actor, adjust size variable, begin calling beginplay, and then set tile reference in grid array
	ATile* tile = GetWorld()->SpawnActorDeferred<ATile>(TileBP, spawn_transform);
	ATileGenerator::generate_tile(tile);
	tile->FinishSpawning(spawn_transform);
	ATileGenerator::set_tile( tile_offset, tile, grid_array);
}

void ATileGenerator::update_grid(FVector location) 
{

	ATile* center_tile = ATileGenerator::get_tile(FOffset(0, 0), grid_array);
	
	verify(center_tile != nullptr);

	FOffset tile_offset = center_tile->get_player_offset(location);

	// check if player has moved from center tile (0,0)
	if (abs(tile_offset.row) + abs(tile_offset.col) != 0) {

		// create empty grid array
		TArray<ATile*> temp_arr;
		temp_arr.Init(nullptr, dim*dim);

		// iterate through every tile to shift to new pos
		for (int32 Index = 0; Index != grid_array.Num(); ++Index)
		{
			// new offset of tile after shifting array
			FOffset offset = ATileGenerator::convert_idx_to_offset(Index);
			FOffset forward_offset = FOffset(offset.row - tile_offset.row, offset.col - tile_offset.col);
			FOffset backward_offset = FOffset(offset.row + tile_offset.row, offset.col + tile_offset.col);
				
			// if tiles shifted location is within dim bounds, set shifted pos of temp array to unshifted pos in grid_array
			if (ATileGenerator::validate_offset(forward_offset))
				ATileGenerator::set_tile(forward_offset, ATileGenerator::get_tile(offset, grid_array), temp_arr);
			else
				get_tile(offset, grid_array)->Destroy();
		}
		// set contents of grid array to temp array
		grid_array = temp_arr;

		//spawn tiles for null positions of array (newly discovered tiles)
		ATileGenerator::populate_grid(false);
	}
}

void ATileGenerator::populate_grid(bool flush_array)
{
	// iterate through all tiles
	for (int32 Index = 0; Index != grid_array.Num(); ++Index)
	{
		// if tile is null, always spawn tile at location
		FOffset offset = ATileGenerator::convert_idx_to_offset(Index);
		ATile* tile = ATileGenerator::get_tile(offset);
		if (tile == nullptr)
			ATileGenerator::spawn_tile(offset);

		// otherwise only spawn and replace tiles if 'flush' parameter is true
		else if (flush_array) {
			tile->Destroy();
			ATileGenerator::spawn_tile(offset);
		}
	}
}

void ATileGenerator::generate_tile(ATile* tile)
{
	FTileData tile_data = FTileData();
	tile_data.tile_size = tile_size;
	tile->load_tile_data(tile_data);
}