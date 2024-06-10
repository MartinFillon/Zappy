//
// EPITECH PROJECT, 2024
// look_around
// File description:
// look around command
//

#![allow(dead_code)]

use crate::tcp::{
    command_handle::{CommandError, CommandHandler, ResponseResult},
    TcpClient,
};

use log::info;

fn read_output(raw: String) -> Vec<Vec<String>> {
    let tmp = raw.trim_matches(|c| c == '[' || c == ']' || c == '\n');
    let tiles = tmp.split(',').fold(
        Vec::<Vec<String>>::new(),
        |mut acc: Vec<Vec<String>>, tile: &str| {
            acc.push(tile.split(' ').fold(
                Vec::<String>::new(),
                |mut content: Vec<String>, item: &str| {
                    if !item.is_empty() {
                        content.push(item.to_string());
                    }
                    content
                },
            ));
            acc
        },
    );
    info!("Tiles: {:?}", tiles);
    tiles
}

pub async fn look_around(client: &mut TcpClient) -> Result<ResponseResult, CommandError> {
    info!("Looking around...");
    let response = client.check_dead("Look\n").await?;

    Ok(ResponseResult::Tiles(read_output(response)))
}

#[cfg(test)]
pub mod tests {
    use super::read_output;

    #[test]
    fn output_reading() {
        let res: Vec<Vec<String>> = read_output("[player food,,,food]\n".to_string());
        let cmp: Vec<Vec<String>> = vec![
            vec!["player".to_string(), "food".to_string()],
            vec![],
            vec![],
            vec!["food".to_string()],
        ];
        assert_eq!(cmp, res);
    }
}
