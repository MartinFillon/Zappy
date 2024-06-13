//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// ai_create
//

use crate::ai::{empress, fetus, fork_launch, knight, queen, AIHandler, AI};

use std::io::{self};

use log::info;

pub async fn start_empress_ai(from_ai: AI, id: Option<i32>) -> io::Result<AI> {
    info!("Connection ID #{} creates empress...", from_ai.p_id);
    let (address, team) = (from_ai.address.clone(), from_ai.team.clone());
    let ai = fork_launch(address, team, from_ai, id).await?;

    let mut empress = empress::Empress::init(ai.clone());
    if let Err(e) = empress.update().await {
        println!("Error: {}", e);
    }
    Ok(ai)
}

pub async fn start_queen_ai(from_ai: AI, id: Option<i32>) -> io::Result<AI> {
    info!("Connection ID #{} creates queen...", from_ai.p_id);
    let (address, team) = (from_ai.address.clone(), from_ai.team.clone());
    let ai = fork_launch(address, team, from_ai, id).await?;

    let mut queen = queen::Queen::init(ai.clone());
    if let Err(e) = queen.update().await {
        println!("Error: {}", e);
    }
    Ok(ai)
}

pub async fn start_fetus_ai(from_ai: AI, id: Option<i32>) -> io::Result<AI> {
    info!("Connection ID #{} creates fetus...", from_ai.p_id);
    let (address, team) = (from_ai.address.clone(), from_ai.team.clone());
    let ai = fork_launch(address, team, from_ai, id).await?;

    let mut fetus = fetus::Fetus::init(ai.clone());
    if let Err(e) = fetus.update().await {
        println!("Error: {}", e);
    }
    Ok(ai)
}

pub async fn start_knight_ai(from_ai: AI, id: Option<i32>) -> io::Result<AI> {
    info!("Connection ID #{} creates knight...", from_ai.p_id);
    let (address, team) = (from_ai.address.clone(), from_ai.team.clone());
    let ai = fork_launch(address, team, from_ai, id).await?;

    let mut knight = knight::Knight::init(ai.clone());
    if let Err(e) = knight.update().await {
        println!("Error: {}", e);
    }
    Ok(ai)
}
