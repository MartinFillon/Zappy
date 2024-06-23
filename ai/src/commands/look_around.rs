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

#[allow(unused_imports)]
use log::{debug, error, info, warn};

pub fn read_look_output(raw: String) -> Vec<Vec<String>> {
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

    debug!("Tiles: {:?}", tiles);
    tiles
}

pub async fn look_around(client: &mut TcpClient) -> Result<ResponseResult, CommandError> {
    debug!("Looking around...");

    let mut response = client.check_dead("Look\n").await?;
    loop {
        let res = client.handle_response(response).await?;
        if let ResponseResult::Tiles(_) = res {
            return Ok(res);
        }
        response = client
            .check_response()
            .await
            .ok_or(CommandError::NoResponseReceived)?;
    }
}

#[cfg(test)]
pub mod tests_look {
    use super::read_look_output;

    #[test]
    fn output_reading() {
        let res: Vec<Vec<String>> = read_look_output("[player food,,,food]\n".to_string());
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
        let res: Vec<Vec<String>> = read_look_output("[]\n".to_string());
        let cmp: Vec<Vec<String>> = vec![[].to_vec()];
        assert_eq!(cmp, res);
    }
}
