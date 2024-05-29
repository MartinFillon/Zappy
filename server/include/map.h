/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** map
*/

#pragma once

#include "types/map.h"
#include "types/object.h"

/**
 * @brief Create a map object
 *
 * @param x x size of the map
 * @param y y size of the map
 * @return map_t* the map object
 */
map_t *create_map(size_t x, size_t y);

/**
 * @brief Fill the map with random values
 *
 * @param map the map object
 */
void fill_map(map_t *map);

/**
 * @brief Destroy the map object
 *
 * @param map the map object
 */
void destroy_map(map_t *map);

/**
 * @brief Take an item on a tile
 *
 * @param map the map object
 * @param x x position of the tile
 * @param y y position of the tile
 * @param obj the object to take
 * @return true if the object was taken
 * @return false if the object was not taken
 */
bool take_item(map_t *map, size_t x, size_t y, enum object_e obj);

/**
 * @brief Drop an item on a tile
 *
 * @param map the map object
 * @param x x position of the tile
 * @param y y position of the tile
 * @param obj the object to drop
 */
void drop_item(map_t *map, size_t x, size_t y, enum object_e obj);

/**
 * @brief Display the map in stdout
 *
 * @param map the map object
 * @param width width of the map
 * @param height height of the map
 */
void display_map(map_t *map, size_t width, size_t height);


/**
 * @brief Send informations about a tile in a client with @param fd
 *
 * @param fd File descriptor of the client
 * @param map the map object
 * @param y y coordinates of the tile
 * @param x x coordinates of the tile
 */
void send_info_tile(int fd, map_t *map, size_t y, size_t x);

/**
 * @brief retieves a tile from the map
 *
 * @param map the map object
 * @param x x position of the tile
 * @param y y position of the tile
 * @return struct tile_s* the tile object
 */
struct tile_s *get_tile(map_t *map, size_t x, size_t y);
