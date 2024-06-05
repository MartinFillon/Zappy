//
// EPITECH PROJECT, 2024
// inventory
// File description:
// inventory command
//

#![allow(dead_code)]

use crate::tcp::command_handle::{CommandError, CommandHandler, ResponseResult};
use crate::tcp::TcpClient;

use log::info;

fn read_output(raw: String) -> Vec<(String, i32)> {
    let tmp = raw.trim_matches(|c| c == '[' || c == ']' || c == '\n');
    let inventory: Vec<(String, i32)> = tmp.split(',').fold(
        Vec::<(String, i32)>::new(),
        |mut acc: Vec<(String, i32)>, tile| {
            if let Some(idex) = tile.rfind(' ') {
                let (item, quantity) = tile.split_at(idex);
                acc.push((
                    item.trim().to_string(),
                    quantity.trim().parse::<i32>().unwrap_or(0),
                ));
            }
            acc
        },
    );

    info!("Inventory: {:?}", inventory);
    inventory
}

pub async fn inventory(client: &mut TcpClient) -> Result<ResponseResult, CommandError> {
    info!("Checking inventory...");
    let response = client.check_dead("Inventory\n").await?;
    if client.handle_response(response.clone()).await.is_err() {
        return Ok(ResponseResult::Inventory(read_output(response)));
    }
    Err(CommandError::InvalidResponse)
}

#[cfg(test)]
pub mod tests {
    use super::read_output;

    #[test]
    fn output_reading() {
        let res: Vec<(String, i32)> =
            read_output("[food 10,linemate 0,sibur 0,mendiane 0]\n".to_string());
        let cmp: Vec<(String, i32)> = vec![
            ("food".to_string(), 10),
            ("linemate".to_string(), 0),
            ("sibur".to_string(), 0),
            ("mendiane".to_string(), 0),
        ];
        assert_eq!(cmp, res);
    }
}
