//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// utils
//

pub fn wrap_coordinate(coord: i32, max: i32) -> i32 {
    let mut wrapped = (coord % max + max) % max;
    if coord > max {
        wrapped = -(max - (wrapped - 1));
    } else if coord < -max {
        wrapped += 1;
    }
    wrapped
}
