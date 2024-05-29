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

#[cfg(test)]
pub mod tests {
    use crate::json::{JsonDocument, JsonValue, ParserError};

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
