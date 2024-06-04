//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// number
//

use crate::DeserializeTrait;

use super::{JsonValue, Parser, ParserError};

impl<'a> Parser<'a> {
    pub(super) fn parse_number(&mut self) -> Result<JsonValue, ParserError> {
        let mut number = String::new();
        let mut decimal = false;

        while let Some(&c) = self.buffer.peek() {
            match c {
                '0'..='9' => {
                    number.push(c);
                    self.buffer.next();
                }
                '.' => {
                    number.push(c);
                    if decimal {
                        return Err(ParserError::NotANumber(number));
                    }
                    decimal = true;
                    self.buffer.next();
                }
                _ => break,
            }
        }
        Ok(JsonValue::Number(
            number
                .parse()
                .map_err(|_| ParserError::NotANumber(number))?,
        ))
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

impl DeserializeTrait for f32 {
    fn from_value(value: &JsonValue) -> Result<Self, String>
    where
        Self: Sized,
    {
        match value {
            JsonValue::Number(n) => Ok(n.clone() as f32),
            _ => Err(String::from("Bad json value")),
        }
    }
}

impl DeserializeTrait for f64 {
    fn from_value(value: &JsonValue) -> Result<Self, String>
    where
        Self: Sized,
    {
        match value {
            JsonValue::Number(n) => Ok(n.clone() as f64),
            _ => Err(String::from("Bad json value")),
        }
    }
}

impl DeserializeTrait for i64 {
    fn from_value(value: &JsonValue) -> Result<Self, String>
    where
        Self: Sized,
    {
        match value {
            JsonValue::Number(n) => Ok(n.clone() as i64),
            _ => Err(String::from("Bad json value")),
        }
    }
}

#[cfg(test)]
pub mod tests {
    use crate::{JsonDocument, JsonValue, ParserError};

    #[test]
    fn basic_json_number() {
        let result: Result<JsonDocument, ParserError> = JsonDocument::try_from(r#"123"#);
        assert_eq!(result, Ok(JsonDocument(JsonValue::Number(123.0))));
    }

    #[test]
    fn basic_json_number_with_decimal() {
        let result: Result<JsonDocument, ParserError> = JsonDocument::try_from(r#"123.456"#);
        assert_eq!(result, Ok(JsonDocument(JsonValue::Number(123.456))));
    }

    #[test]
    fn json_number_error_multiple_decimal() {
        let result: Result<JsonDocument, ParserError> = JsonDocument::try_from(r#"2..3"#);
        assert_eq!(result, Err(ParserError::NotANumber("2..".to_string())));
    }
}
