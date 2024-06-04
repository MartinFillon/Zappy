//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// object
//

use std::collections::HashMap;

use crate::DeserializeTrait;

use super::{JsonValue, Parser, ParserError};

impl<'a> Parser<'a> {
    pub(super) fn parse_object(&mut self) -> Result<JsonValue, ParserError> {
        let mut object = HashMap::new();
        self.buffer.next();
        loop {
            let c = self.buffer.peek();
            match c {
                Some('}') => {
                    self.buffer.next();
                    break;
                }
                Some('"') => {
                    self.key = self.parse_key()?;
                }
                Some(':') => {
                    self.buffer.next();
                    object.insert(self.key.clone(), self.parse_value()?);
                }
                Some(',') => {
                    self.buffer.next();
                    self.skip();
                }
                None => return Err(ParserError::UnexpectedEOF),
                Some(' ' | '\t' | '\n') => self.skip(),
                c => {
                    dbg!(c);
                    return Err(ParserError::InvalidValue(self.buffer_str.clone()));
                }
            }
        }

        Ok(JsonValue::Object(object))
    }

    fn parse_key(&mut self) -> Result<String, ParserError> {
        self.buffer.next();
        let mut key = String::new();

        while let Some(&c) = self.buffer.peek() {
            match c {
                '"' => {
                    self.buffer.next();
                    break;
                }
                _ => {
                    key.push(c);
                    self.buffer.next();
                }
            }
        }

        Ok(key)
    }
}

impl DeserializeTrait for HashMap<String, JsonValue> {
    fn from_value(value: &JsonValue) -> Result<Self, String>
    where
        Self: Sized,
    {
        match value {
            JsonValue::Object(obj) => Ok(obj.clone()),
            _ => Err(String::from("Bad json value")),
        }
    }
}

#[cfg(test)]
pub mod tests {
    use std::collections::HashMap;

    use crate::{JsonDocument, JsonValue, ParserError};

    #[test]
    fn basic_json_object() {
        let result: Result<JsonDocument, ParserError> =
            JsonDocument::try_from(r#"{"key": "value"}"#);
        let mut object = HashMap::new();
        object.insert("key".to_string(), JsonValue::String("value".to_string()));
        assert_eq!(result, Ok(JsonDocument(JsonValue::Object(object))));
    }

    #[test]
    fn json_object_with_multiple_keys() {
        let result: Result<JsonDocument, ParserError> =
            JsonDocument::try_from(r#"{"key1": "value1", "key2": "value2"}"#);
        let mut object = HashMap::new();
        object.insert("key1".to_string(), JsonValue::String("value1".to_string()));
        object.insert("key2".to_string(), JsonValue::String("value2".to_string()));
        assert_eq!(result, Ok(JsonDocument(JsonValue::Object(object))));
    }

    #[test]
    fn json_object_with_nested_objects() {
        let result: Result<JsonDocument, ParserError> =
            JsonDocument::try_from(r#"{"key1": "value1", "key2": {"key3": 33}}"#);
        let mut object = HashMap::new();
        object.insert("key1".to_string(), JsonValue::String("value1".to_string()));
        let mut nested_object = HashMap::new();
        nested_object.insert("key3".to_string(), JsonValue::Number(33f64));
        object.insert("key2".to_string(), JsonValue::Object(nested_object));
        assert_eq!(result, Ok(JsonDocument(JsonValue::Object(object))));
    }
}
