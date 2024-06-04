//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// mod
//

use std::{collections::HashMap, iter::Peekable, str::Chars};

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
pub struct JsonDocument(JsonValue);

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

pub trait DeserializeTrait {
    fn from_str(_raw: String) -> Result<Self, ParserError>
    where
        Self: Sized,
    {
        unimplemented!()
    }

    fn from_value(_value: &JsonValue) -> Result<Self, String>
    where
        Self: Sized,
    {
        unimplemented!()
    }
}

impl DeserializeTrait for i32 {
    fn from_value(value: &JsonValue) -> Result<Self, String>
    where
        Self: Sized,
    {
        match value {
            JsonValue::Number(n) => Ok(n.clone() as i32),
            _ => Err(String::from("Bad json value")),
        }
    }
}

impl<T: DeserializeTrait> DeserializeTrait for Vec<T> {
    fn from_value(value: &JsonValue) -> Result<Self, String>
    where
        Self: Sized,
    {
        match value {
            JsonValue::Array(arr) => {
                let mut vec: Vec<T> = Vec::new();

                for (_, elem) in arr.iter().enumerate() {
                    vec.push(T::from_value(elem)?)
                }

                Ok(vec)
            }
            _ => Err(String::from("Bad json value")),
        }
    }
}

impl DeserializeTrait for bool {
    fn from_value(value: &JsonValue) -> Result<Self, String>
    where
        Self: Sized,
    {
        match value {
            JsonValue::Bool(b) => Ok(b.clone()),
            _ => Err(String::from("Bad json value")),
        }
    }
}

impl DeserializeTrait for String {
    fn from_value(value: &JsonValue) -> Result<Self, String>
    where
        Self: Sized,
    {
        match value {
            JsonValue::String(s) => Ok(s.clone()),
            _ => Err(String::from("Bad json value")),
        }
    }
}
