//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// bot
//

#[derive(Debug, Clone)]
pub struct Bot {
    team: String,
    coord: (usize, usize),
    backtrack: Vec<(usize, usize)>
}
