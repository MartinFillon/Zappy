//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// string
//

use super::{JsonValue, Parser, ParserError};

impl<'a> Parser<'a> {
    pub(super) fn parse_string(&mut self) -> Result<JsonValue, ParserError> {
        let mut string = String::new();
        self.buffer.next();
        while let Some(c) = self.buffer.next() {
            match c {
                '"' => break,
                '\\' => self.parse_escaped(&mut string)?,
                _ => {
                    string.push(c);
                }
            }
        }
        Ok(JsonValue::String(string))
    }

    fn parse_escaped(&mut self, str: &mut String) -> Result<(), ParserError> {
        match self.buffer.next() {
            Some('"') => str.push('"'),
            Some('n') => str.push('\n'),
            Some('r') => str.push('\r'),
            Some('t') => str.push('\t'),
            Some('\\') => str.push('\\'),
            Some(c) => str.push(c),
            None => return Err(ParserError::UnexpectedEOF),
        };
        Ok(())
    }
}

#[cfg(test)]
pub mod tests {
    use crate::{JsonDocument, JsonValue, ParserError};

    #[test]
    fn basic_json_string() {
        let result: Result<JsonDocument, ParserError> = JsonDocument::try_from(r#""hello""#);
        assert_eq!(
            result,
            Ok(JsonDocument(JsonValue::String("hello".to_string())))
        );
    }

    #[test]
    fn json_string_with_escaped_characters() {
        let result: Result<JsonDocument, ParserError> = JsonDocument::try_from(r#""hello\nworld""#);
        assert_eq!(
            result,
            Ok(JsonDocument(JsonValue::String("hello\nworld".to_string())))
        );
    }

    #[test]
    fn json_string_with_escaped_quotes() {
        let result: Result<JsonDocument, ParserError> =
            JsonDocument::try_from(r#""hello \"world\"""#);
        assert_eq!(
            result,
            Ok(JsonDocument(JsonValue::String(
                "hello \"world\"".to_string()
            )))
        );
    }

    #[test]
    fn json_string_with_escaped_backslashes() {
        let result: Result<JsonDocument, ParserError> =
            JsonDocument::try_from(r#""hello \\world""#);
        assert_eq!(
            result,
            Ok(JsonDocument(JsonValue::String("hello \\world".to_string())))
        );
    }
}
