//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// ai_create
//

use crate::ai::{fork_launch, AI};

use std::io::{self};

use log::info;

pub async fn start_empress_ai(from_ai: AI) -> io::Result<AI> {
    info!("Connection ID #{} creates empress...", from_ai.p_id);
    let (address, team) = (from_ai.address.clone(), from_ai.team.clone());
    let ai = fork_launch(address, team, from_ai).await?;
    Ok(ai)
}

pub async fn start_queen_ai(from_ai: AI) -> io::Result<AI> {
    info!("Connection ID #{} creates queen...", from_ai.p_id);
    let (address, team) = (from_ai.address.clone(), from_ai.team.clone());
    let ai = fork_launch(address, team, from_ai).await?;
    Ok(ai)
}

pub async fn start_fetus_ai(from_ai: AI) -> io::Result<AI> {
    info!("Connection ID #{} creates fetus...", from_ai.p_id);
    let (address, team) = (from_ai.address.clone(), from_ai.team.clone());
    let ai = fork_launch(address, team, from_ai).await?;
    Ok(ai)
}

pub async fn start_knight_ai(from_ai: AI) -> io::Result<AI> {
    info!("Connection ID #{} creates knight...", from_ai.p_id);
    let (address, team) = (from_ai.address.clone(), from_ai.team.clone());
    let ai = fork_launch(address, team, from_ai).await?;
    Ok(ai)
}
