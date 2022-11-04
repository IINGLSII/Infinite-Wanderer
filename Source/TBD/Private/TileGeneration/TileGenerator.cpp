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

ATile* ATileGenerator::get_tile(int row_offset, int col_offset) const
{
	return get_tile(row_offset, col_offset, grid_array);
}

ATile* ATileGenerator::get_tile (int8 row_offset, int8 col_offset, const TArray<ATile*>& arr) const
{
	// check if row/column offsets fall within dimension of array (dim)
	verify(ATileGenerator::validate_offset(row_offset, col_offset));
	
	// index and return contents of array at indexed position
	int8 pos = ATileGenerator::convert_offset_to_idx(row_offset, col_offset);
	return arr[pos];
}

void ATileGenerator::set_tile(int8 row_offset, int8 col_offset, ATile* chunk, TArray<ATile*>& arr)
{
	// check if row/column fall within dimension of array (dim)
	verify(ATileGenerator::validate_offset(row_offset, col_offset));

	// set contents of array at indexed position
	int8 pos = ATileGenerator::convert_offset_to_idx(row_offset, col_offset);
	arr[pos] = chunk;
}
// Spawns a chunk at a given r/c offset
void ATileGenerator::spawn_tile(int8 row, int8 col)
{
	// get reference to center
	ATile* center = ATileGenerator::get_tile(0, 0, grid_array);
	FVector offset = FVector(row * tile_size, col * tile_size, 0);
	FTransform spawn_transform;
	// determine if center exists
	if (center != nullptr)
		spawn_transform.SetLocation(center->GetActorLocation() + offset);
	else
		spawn_transform.SetLocation(this->GetActorLocation() + offset);

	// spawn actor, adjust size variable, begin calling beginplay, and then set chunk reference in grid array
	ATile* tile = GetWorld()->SpawnActorDeferred<ATile>(TileBP, spawn_transform);
	ATileGenerator::generate_tile(tile);
	tile->FinishSpawning(spawn_transform);
	ATileGenerator::set_tile(row, col, tile, grid_array);
}

// returns True if given offsets result in a valid converted array index, False if not
bool ATileGenerator::validate_offset(int8 row, int8 col) const
{
	return (row >= -dim / 2 && row <= dim / 2) && (col >= -dim / 2 && col <= dim / 2);
}

// converts row column offset from zero to array indices, where (0,0) offset is in the center of the 2D array
int ATileGenerator::convert_offset_to_idx(int8 row, int8 col) const
{
	return (row + dim/2)* dim + (col + dim/2);
}


void ATileGenerator::update_grid(FVector location) {

	ATile* center_tile = ATileGenerator::get_tile(0,0, grid_array);
	
	verify(center_tile != nullptr);

	int8 x_offset = center_tile->get_player_offset(location, 1);
	int8 y_offset = center_tile->get_player_offset(location, 0);

	// check if player has moved from center tile (0,0)
	if (abs(x_offset) + abs(y_offset) != 0) {

		// create empty grid array
		TArray<ATile*> temp_arr;
		temp_arr.Init(nullptr, dim*dim);

		// iterate through every tile to shift to new pos
		for (int8 row = -dim / 2; row <= dim / 2; row++) {
			for (int8 col = -dim / 2; col <= dim / 2; col++) {
				// new offset of tile after shifting array
				int8 new_row_offset = row - x_offset;
				int8 new_col_offset = col - y_offset;
				
				// if tiles shifted location is within dim bounds, set shifted pos of temp array to unshifted pos in grid_array
				if (ATileGenerator::validate_offset(new_row_offset, new_col_offset))
					ATileGenerator::set_tile(new_row_offset, new_col_offset, ATileGenerator::get_tile(row, col, grid_array), temp_arr);
				else
					get_tile(row, col , grid_array)->Destroy();
			}
		}
		// set contents of grid array to temp array
		grid_array = temp_arr;

		//spawn chunks for null positions of array (newly discovered chunks)
		ATileGenerator::populate_grid(false);
	}
}

void ATileGenerator::populate_grid(bool flush_array)
{
	for (int8 row = -dim / 2; row <= dim / 2; row++) {
		for (int8 col = -dim / 2; col <= dim / 2; col++) {
			ATile* tile = ATileGenerator::get_tile(row, col, grid_array);
			if (tile == nullptr)
				ATileGenerator::spawn_tile(row, col);
			else if (flush_array) {
				tile->Destroy();
				ATileGenerator::spawn_tile(row, col);
			}
		}
	}
}

int ATileGenerator::get_dim() { return dim; }

float ATileGenerator::get_tile_size() { return tile_size; }

void ATileGenerator::generate_tile(ATile* tile)
{
	FTileData tile_data = FTileData();
	tile_data.tile_size = tile_size;
	tile->load_tile_data(tile_data);
}