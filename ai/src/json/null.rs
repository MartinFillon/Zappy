use super::{JsonValue, Parser, ParserError};

impl<'a> Parser<'a> {
    pub(super) fn parse_null(&mut self) -> Result<JsonValue, ParserError> {
        let null = self.buffer.by_ref().take(4).collect::<String>();
        if null == "null" {
            Ok(JsonValue::Null)
        } else {
            Err(ParserError::InvalidValue(self.buffer.clone().collect()))
        }
    }
}

#[cfg(test)]
pub mod tests {
    use crate::json::{JsonDocument, JsonValue, ParserError};

    #[test]
    fn basic_json_null() {
        let result: Result<JsonDocument, ParserError> = JsonDocument::try_from(r#"null"#);
        assert_eq!(result, Ok(JsonDocument(JsonValue::Null)));
    }
}
