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

use log::{debug, warn};

fn read_output(raw: String) -> Option<Vec<Vec<String>>> {
    if !raw.starts_with('[') || !raw.ends_with("]\n") {
        warn!("Attempted to read invalid string as tiles.");
        return None;
    }
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
    if tiles.len() < 4 {
        return None;
    }

    debug!("Tiles: {:?}", tiles);
    Some(tiles)
}

pub async fn look_around(client: &mut TcpClient) -> Result<ResponseResult, CommandError> {
    debug!("Looking around...");

    let response = client.check_dead("Look\n").await?;
    if client.handle_response(response.clone()).await.is_err() {
        warn!("Detected Err, parsing as tile(s) output...");
        return match read_output(response) {
            Some(output) => Ok(ResponseResult::Tiles(output)),
            None => Err(CommandError::InvalidResponse),
        };
    }
    Err(CommandError::InvalidResponse)
}

#[cfg(test)]
pub mod tests_look {
    use super::read_output;

    #[test]
    fn output_reading() {
        let res: Vec<Vec<String>> = read_output("[player food,,,food]\n".to_string()).unwrap();
        let cmp: Vec<Vec<String>> = vec![
            vec!["player".to_string(), "food".to_string()],
            vec![],
            vec![],
            vec!["food".to_string()],
        ];
        assert_eq!(cmp, res);
    }

    #[test]
    fn output_reading_empty() {
        let res = read_output("[]\n".to_string());
        assert_eq!(None, res);
    }

    #[test]
    fn output_reading_message() {
        let res: Vec<Vec<String>> = read_output("[player food,,,food]\n".to_string()).unwrap();
        let cmp: Vec<Vec<String>> = vec![
            vec!["player".to_string(), "food".to_string()],
            vec![],
            vec![],
            vec!["food".to_string()],
        ];
        assert_eq!(cmp, res);
    }
}
