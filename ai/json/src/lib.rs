//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// mod
//

use std::{
    collections::HashMap,
    fmt::{self, Display, Formatter},
    fs::read_to_string,
    iter::Peekable,
    str::Chars,
};

mod array;
mod bool;
mod null;
mod number;
mod object;
mod string;

struct Parser<'a> {
    buffer: Peekable<Chars<'a>>,
    current: JsonValue,
    key: String,
    buffer_str: String,
}

#[derive(Debug, PartialEq)]
pub enum ParserError {
    InvalidValue(String),
    UnexpectedEOF,
    NotANumber(String),
}

impl Display for ParserError {
    fn fmt(&self, f: &mut Formatter) -> fmt::Result {
        match self {
            Self::InvalidValue(s) => write!(f, "Invalid value {}", s),
            Self::UnexpectedEOF => write!(f, "Unexpected EOF"),
            Self::NotANumber(s) => write!(f, "{} not a number", s),
        }
    }
}

impl<'a> Parser<'a> {
    fn new(input: &'a str) -> Self {
        Parser {
            buffer_str: input.to_string(),
            current: JsonValue::default(),
            buffer: input.chars().peekable(),
            key: String::new(),
        }
    }

    fn parse_value(&mut self) -> Result<JsonValue, ParserError> {
        self.skip();
        match self.buffer.peek() {
            Some(&c) => match c {
                'n' => self.parse_null(),
                '0'..='9' => self.parse_number(),
                '"' => self.parse_string(),
                '[' => self.parse_array(),
                '{' => self.parse_object(),
                't' | 'f' => self.parse_bool(),
                _ => Err(ParserError::InvalidValue(self.buffer.clone().collect())),
            },
            None => Err(ParserError::UnexpectedEOF),
        }
    }

    fn parse(&mut self) -> Result<JsonValue, ParserError> {
        self.skip();
        self.current = self.parse_value()?;
        Ok(self.current.clone())
    }

    fn skip(&mut self) {
        while let Some(&c) = self.buffer.peek() {
            if c.is_whitespace() {
                self.buffer.next();
            } else {
                break;
            }
        }
    }
}

#[derive(Debug, PartialEq, Clone, Default)]
pub enum JsonValue {
    Number(f64),
    String(String),
    Bool(bool),
    Array(Vec<JsonValue>),
    Object(HashMap<String, JsonValue>),
    #[default]
    Null,
}

#[derive(Debug, PartialEq)]
pub struct JsonDocument(pub JsonValue);

impl From<JsonValue> for JsonDocument {
    fn from(value: JsonValue) -> Self {
        JsonDocument(value)
    }
}

impl TryFrom<&str> for JsonDocument {
    type Error = ParserError;

    fn try_from(value: &str) -> Result<Self, Self::Error> {
        let mut parser = Parser::new(value);
        Ok(JsonDocument(parser.parse()?))
    }
}

pub fn create_from_file<T: DeserializeTrait>(path: &str) -> Result<T, String> {
    let content = read_to_string(path).map_err(|e| e.to_string())?;
    let json_document = JsonDocument::try_from(content.as_str()).map_err(|e| e.to_string())?;
    T::from_value(&json_document.0)
}

pub fn create_from_file_or_default<T: DeserializeTrait + Default>(path: &str) -> T {
    read_to_string(path)
        .map_err(|e| e.to_string())
        .map(|c| {
            let json_document = JsonDocument::try_from(c.as_str()).map_err(|e| e.to_string());
            match json_document {
                Ok(j) => T::from_value(&j.0),
                Err(_) => Ok(T::default()),
            }
        })
        .unwrap_or_else(|_| Ok(T::default()))
        .unwrap_or_else(|_| T::default())
}

pub trait DeserializeTrait {
    fn from_value(_value: &JsonValue) -> Result<Self, String>
    where
        Self: Sized,
    {
        unimplemented!()
    }
}
