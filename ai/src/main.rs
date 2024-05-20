//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// main
//

mod flags;

fn main() {
    let tmp = flags::get_flags();
    match tmp {
        Ok(res) => println!("{}", res),
        Err(e) => println!("{}", e),
    }
}
