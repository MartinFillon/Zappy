use std::{collections::HashMap, iter::Peekable, str::Chars};

mod null;
mod number;
mod string;

struct Parser<'a> {
    buffer: Peekable<Chars<'a>>,
    current: JsonValue,
    key: String,
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
            current: JsonValue::default(),
            buffer: input.chars().peekable(),
            key: String::new(),
        }
    }

    fn parse_value(&mut self) -> Result<JsonValue, ParserError> {
        match self.buffer.peek() {
            Some(&c) => match c {
                'n' => self.parse_null(),
                '0'..='9' => self.parse_number(),
                '"' => self.parse_string(),
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

#[derive(Debug, PartialEq, Clone)]
pub enum JsonValue {
    Number(f64),
    String(String),
    Bool(bool),
    Array(Vec<JsonValue>),
    Object(HashMap<String, JsonValue>),
    Null,
}

impl Default for JsonValue {
    fn default() -> Self {
        JsonValue::Object(HashMap::new())
    }
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
