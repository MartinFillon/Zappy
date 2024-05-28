//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// json
//

use std::collections::HashMap;

use std::fs::File;
use std::io::{self, Read};

#[derive(Debug)]
struct ConfigFile {
    file_path: String,
    file: Option<File>,
}

impl ConfigFile {
    fn new(file_path: String) -> Self {
        Self {
            file_path,
            file: None,
        }
    }

    fn open_file(&mut self) -> io::Result<()> {
        self.file = Some(File::open(self.file_path.clone())?);
        Ok(())
    }

    fn read_file(&mut self) -> io::Result<String> {
        let mut contents = String::new();
        if let Some(mut file) = self.file {
            file.read_to_string(&mut contents)?;
        }
        Ok(contents)
    }
}

#[derive(Debug, PartialEq)]
pub enum JsonValue {
    Object(HashMap<String, JsonValue>),
    Array(Vec<JsonValue>),
    String(String),
    Number(f64),
    Bool(bool),
    Null,
}

pub enum ParseError {
    // to implement
    UnexpectedEOF,
    InvalidToken(char),
    InvalidNumber,
    InvalidEscape,
    InvalidUnicode,
    InvalidCharacter(char),
}

pub fn parse(input: &str) -> Result<JsonValue, String> {
    let mut chars = input.chars().peekable();

    parse_value(&mut chars)
}

fn parse_value<I>(chars: &mut std::iter::Peekable<I>) -> Result<JsonValue, String>
where
    I: Iterator<Item = char>,
{
    skip_whitespace(chars);
    match chars.peek() {
        Some(&c) => match c {
            // '{' => JsonValue::parse_object(chars),
            '[' => JsonValue::parse_array(chars),
            '"' => JsonValue::parse_string(chars),
            '0'..='9' | '-' => JsonValue::parse_number(chars),
            't' | 'f' => JsonValue::parse_bool(chars),
            'n' => JsonValue::parse_null(chars),
            _ => Err(format!("Unexpected character: {}", c)),
        },
        None => Err(String::from("Unexpected EOF")),
    }
}

fn skip_whitespace<I>(chars: &mut std::iter::Peekable<I>)
where
    I: Iterator<Item = char>,
{
    while chars.peek().map_or(false, |c| c.is_whitespace()) {
        chars.next();
    }
}

fn parse_digits<I>(chars: &mut std::iter::Peekable<I>, number_str: &mut String) -> bool
where
    I: Iterator<Item = char>,
{
    let digits: String = chars.take_while(|c| c.is_digit(10)).collect();

    if !digits.is_empty() {
        number_str.push_str(&digits);
        true
    } else {
        false
    }
}

impl JsonValue {
    fn parse_array<I>(chars: &mut std::iter::Peekable<I>) -> Result<JsonValue, String>
    where
        I: Iterator<Item = char>,
    {
        let mut array = Vec::new();
        chars.next();
        loop {
            skip_whitespace(chars);
            match chars.peek() {
                Some(']') => {
                    chars.next();
                    break;
                }
                Some(_) => {
                    let value = parse_value(chars)?;
                    array.push(value);
                    skip_whitespace(chars);
                    match chars.peek() {
                        Some(',') => {
                            chars.next();
                        }
                        Some(']') => continue,
                        Some(_) => return Err(String::from("Expected ',' or ']'")),
                        None => return Err(String::from("Unexpected EOF")),
                    }
                }
                None => return Err(String::from("Unexpected EOF")),
            }
        }
        Ok(JsonValue::Array(array))
    }

    fn parse_string<I>(chars: &mut std::iter::Peekable<I>) -> Result<JsonValue, String>
    where
        I: Iterator<Item = char>,
    {
        let mut result = String::new();
        chars.next();
        while let Some(c) = chars.next() {
            match c {
                '"' => return Ok(JsonValue::String(result)),
                '\\' => {
                    if let Some(escaped) = chars.next() {
                        match escaped {
                            '"' | '\\' | '/' => result.push(escaped),
                            'n' => result.push('\n'),
                            'r' => result.push('\r'),
                            't' => result.push('\t'),
                            _ => return Err(String::from("Invalid escape sequence")),
                        }
                    }
                }
                _ => result.push(c),
            }
        }
        Err(String::from("Unexpected EOF"))
    }

    fn parse_number<I>(chars: &mut std::iter::Peekable<I>) -> Result<JsonValue, String>
    where
        I: Iterator<Item = char>,
    {
        let mut number_str = String::new();

        if let Some('-') = chars.peek() {
            number_str.push('-');
            chars.next();
        }

        if !parse_digits(chars, &mut number_str) {
            return Err(String::from("Invalid number"));
        }

        if let Some('.') = chars.peek() {
            number_str.push('.');
            chars.next();
            if !parse_digits(chars, &mut number_str) {
                return Err(String::from("Invalid number"));
            }
        }

        if let Some('e') | Some('E') = chars.peek() {
            number_str.push('e');
            chars.next();
            if let Some('+') | Some('-') = chars.peek() {
                number_str.push(chars.next().unwrap());
            }
            if !parse_digits(chars, &mut number_str) {
                return Err(String::from("Invalid number"));
            }
        }

        match number_str.parse::<f64>() {
            Ok(number) => Ok(JsonValue::Number(number)),
            Err(_) => Err(String::from("Invalid number")),
        }
    }

    fn parse_bool<I>(chars: &mut std::iter::Peekable<I>) -> Result<JsonValue, String>
    where
        I: Iterator<Item = char>,
    {
        if let Some('t') = chars.peek() {
            for expected in "true".chars() {
                if chars.next() != Some(expected) {
                    return Err(String::from("Invalid boolean value"));
                }
            }
            return Ok(JsonValue::Bool(true));
        }
        if let Some('f') = chars.peek() {
            for expected in "false".chars() {
                if chars.next() != Some(expected) {
                    return Err(String::from("Invalid boolean value"));
                }
            }
            return Ok(JsonValue::Bool(false));
        }
        Err(String::from("Invalid boolean value"))
    }

    fn parse_null<I>(chars: &mut std::iter::Peekable<I>) -> Result<JsonValue, String>
    where
        I: Iterator<Item = char>,
    {
        if let Some('n') = chars.peek() {
            for expected in "null".chars() {
                if chars.next() != Some(expected) {
                    return Err(String::from("Invalid null value"));
                }
            }
            return Ok(JsonValue::Null);
        }
        Err(String::from("Invalid null value"))
    }
}
