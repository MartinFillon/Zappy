//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// bool
//

use super::{JsonValue, Parser, ParserError};

impl<'a> Parser<'a> {
    pub(super) fn parse_bool(&mut self) -> Result<JsonValue, ParserError> {
        let bool_str = self.buffer.by_ref().take(4).collect::<String>();
        if bool_str == "true" {
            Ok(JsonValue::Bool(true))
        } else if bool_str == "fals" {
            match self.buffer.next() {
                Some('e') => {}
                _ => return Err(ParserError::InvalidValue(self.buffer_str.clone())),
            }
            Ok(JsonValue::Bool(false))
        } else {
            Err(ParserError::InvalidValue(self.buffer_str.clone()))
        }
    }
}

#[cfg(test)]
pub mod tests {
    use crate::json::{JsonDocument, JsonValue, ParserError};

    #[test]
    fn basic_json_bool() {
        let result: Result<JsonDocument, ParserError> = JsonDocument::try_from(r#"true"#);
        assert_eq!(result, Ok(JsonDocument(JsonValue::Bool(true))));
    }

    #[test]
    fn basic_json_false() {
        let result: Result<JsonDocument, ParserError> = JsonDocument::try_from(r#"false"#);
        assert_eq!(result, Ok(JsonDocument(JsonValue::Bool(false))));
    }

    #[test]
    fn json_bool_error() {
        let result: Result<JsonDocument, ParserError> = JsonDocument::try_from(r#"tru"#);
        assert_eq!(result, Err(ParserError::InvalidValue("tru".to_string())));
    }

    #[test]
    fn json_bool_error_false() {
        let result: Result<JsonDocument, ParserError> = JsonDocument::try_from(r#"falsa"#);
        assert_eq!(result, Err(ParserError::InvalidValue("falsa".to_string())));
    }
}
