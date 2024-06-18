//
// EPITECH PROJECT, 2024
// move_to_tile.rs
// File description:
// utility function to move towards a specific tile in player's vision
//

use crate::{
    ai::bot::Bot,
    commands::{
        move_up,
        turn::{self, DirectionTurn},
    },
    tcp::{
        command_handle::{CommandError, ResponseResult},
        TcpClient,
    },
};

use log::info;

fn get_row(tile: usize, lvl: usize) -> Option<i32> {
    let mut tile_count: usize = 0;
    let mut to_add: usize = 1;
    let mut i: usize = 0;

    loop {
        if i > lvl {
            return None;
        }
        tile_count += to_add;
        to_add += 2;
        i += 1;
        if tile_count > tile {
            break;
        }
    }
    Some(i as i32 - 1)
}

fn get_col(tile: usize, lvl: usize) -> Option<i32> {
    let mut row_middle: usize = 0;
    let mut tile_count: usize = 0;
    let mut to_add: usize = 1;
    let mut i: usize = 0;

    loop {
        if i > lvl {
            return None;
        }
        tile_count += to_add;
        row_middle += to_add - 1;
        to_add += 2;
        i += 1;
        if tile_count > tile {
            break;
        }
    }
    Some(tile as i32 - row_middle as i32)
}

fn get_tile_coordinates(tile: usize, lvl: usize) -> Option<(i32, i32)> {
    let y = get_row(tile, lvl)?;
    let x = get_col(tile, lvl)?;
    Some((x, y))
}

pub async fn move_left(client: &mut TcpClient) -> Result<ResponseResult, CommandError> {
    turn::turn(client, DirectionTurn::Left).await?;
    move_up::move_up(client).await?;
    turn::turn(client, DirectionTurn::Right).await?;
    Ok(ResponseResult::OK)
}

pub async fn move_right(client: &mut TcpClient) -> Result<ResponseResult, CommandError> {
    turn::turn(client, DirectionTurn::Right).await?;
    move_up::move_up(client).await?;
    turn::turn(client, DirectionTurn::Left).await?;
    Ok(ResponseResult::OK)
}

impl Bot {
    pub async fn move_ai_to_coords(
        &mut self,
        (x, y): (i32, i32),
    ) -> Result<ResponseResult, CommandError> {
        let mut client = self.info().client().lock().await;
        if x < 0 {
            move_left(&mut client).await?;
        }
        if x > 0 {
            move_right(&mut client).await?;
        }
        for _ in 0..=y {
            move_up::move_up(&mut client).await?;
        }
        Ok(ResponseResult::OK)
    }

    pub async fn move_to_tile(&mut self, tile: usize) -> Result<ResponseResult, CommandError> {
        info!("Moving to tile {}...", tile);
        match get_tile_coordinates(tile, *self.info().level()) {
            Some(coords) => {
                self.update_coord_movement(coords);
                self.move_ai_to_coords(coords).await
            }
            None => Ok(ResponseResult::KO),
        }
    }
}

#[cfg(test)]
pub mod tests {
    use crate::move_to_tile::{get_col, get_row, get_tile_coordinates};

    /* get_row() */
    #[test]
    fn get_row_tile_0_lvl_1() {
        let row = get_row(0, 1);
        assert_eq!(Some(0), row);
    }

    #[test]
    fn get_row_tile_4_lvl_1() {
        let row = get_row(4, 1);
        assert_eq!(None, row);
    }

    #[test]
    fn get_row_tile_3_lvl_1() {
        let row = get_row(3, 1);
        assert_eq!(Some(1), row);
    }

    #[test]
    fn get_row_tile_6_lvl_2() {
        let row = get_row(6, 2);
        assert_eq!(Some(2), row);
    }

    #[test]
    fn get_row_tile_14_lvl_3() {
        let row = get_row(14, 3);
        assert_eq!(Some(3), row);
    }

    #[test]
    fn get_row_tile_1_lvl_3() {
        let row = get_row(1, 3);
        assert_eq!(Some(1), row);
    }
    /* end get_row() */

    /* get_col() */
    #[test]
    fn get_col_tile_0_lvl_1() {
        let col = get_col(0, 1);
        assert_eq!(Some(0), col);
    }

    #[test]
    fn get_col_tile_4_lvl_1() {
        let col = get_col(4, 1);
        assert_eq!(None, col);
    }

    #[test]
    fn get_col_tile_3_lvl_1() {
        let col = get_col(3, 1);
        assert_eq!(Some(1), col);
    }

    #[test]
    fn get_col_tile_6_lvl_2() {
        let col = get_col(6, 2);
        assert_eq!(Some(0), col);
    }

    #[test]
    fn get_col_tile_10_lvl_3() {
        let col = get_col(10, 3);
        assert_eq!(Some(-2), col);
    }

    #[test]
    fn get_col_tile_14_lvl_3() {
        let col = get_col(14, 3);
        assert_eq!(Some(2), col);
    }

    #[test]
    fn get_col_tile_1_lvl_3() {
        let col = get_col(1, 3);
        assert_eq!(Some(-1), col);
    }
    /* end get_col() */

    /* get_tile_coordinates() */
    #[test]
    fn get_tile_coordinates_tile_0_lvl_1() {
        let tile_coordinates = get_tile_coordinates(0, 1);
        assert_eq!(Some((0, 0)), tile_coordinates);
    }

    #[test]
    fn get_tile_coordinates_tile_4_lvl_1() {
        let tile_coordinates = get_tile_coordinates(4, 1);
        assert_eq!(None, tile_coordinates);
    }

    #[test]
    fn get_tile_coordinates_tile_3_lvl_1() {
        let tile_coordinates = get_tile_coordinates(3, 1);
        assert_eq!(Some((1, 1)), tile_coordinates);
    }

    #[test]
    fn get_tile_coordinates_tile_6_lvl_2() {
        let tile_coordinates = get_tile_coordinates(6, 2);
        assert_eq!(Some((0, 2)), tile_coordinates);
    }

    #[test]
    fn get_tile_coordinates_tile_10_lvl_3() {
        let tile_coordinates = get_tile_coordinates(10, 3);
        assert_eq!(Some((-2, 3)), tile_coordinates);
    }

    #[test]
    fn get_tile_coordinates_tile_14_lvl_3() {
        let tile_coordinates = get_tile_coordinates(14, 3);
        assert_eq!(Some((2, 3)), tile_coordinates);
    }

    #[test]
    fn get_tile_coordinates_tile_1_lvl_3() {
        let tile_coordinates = get_tile_coordinates(1, 3);
        assert_eq!(Some((-1, 1)), tile_coordinates);
    }
    /* end get_tile_coordinates() */
}
