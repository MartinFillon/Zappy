//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// array
//

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
                _ => array.push(self.parse_value()?),
            }
        }

        Ok(JsonValue::Array(array))
    }
}

#[cfg(test)]
mod tests {
    use crate::json::JsonDocument;

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
