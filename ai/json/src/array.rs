//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// array
//

use crate::DeserializeTrait;

use super::{JsonValue, Parser, ParserError};

impl<'a> Parser<'a> {
    pub(super) fn parse_array(&mut self) -> Result<JsonValue, ParserError> {
        let mut array = Vec::new();
        self.buffer.next();
        array.push(self.parse_value()?);
        loop {
            let c = self.buffer.peek();
            match c {
                Some(']') => {
                    self.buffer.next();
                    break;
                }
                Some(',') => {
                    self.buffer.next();
                    self.skip();
                    array.push(self.parse_value()?);
                }
                Some(' ' | '\n' | '\t') => {
                    self.skip();
                }
                _ => array.push(self.parse_value()?),
            }
        }

        Ok(JsonValue::Array(array))
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

                for elem in arr.iter() {
                    vec.push(T::from_value(elem)?)
                }

                Ok(vec)
            }
            _ => Err(String::from("Bad json value")),
        }
    }
}

#[cfg(test)]
mod tests {
    use crate::JsonDocument;

    use super::*;

    #[test]
    fn test_parse_array() {
        let result: Result<JsonDocument, ParserError> = JsonDocument::try_from("[1, 2, 3]");
        let expected = JsonDocument(JsonValue::Array(vec![
            JsonValue::Number(1f64),
            JsonValue::Number(2f64),
            JsonValue::Number(3f64),
        ]));
        assert_eq!(result, Ok(expected));
    }
}
