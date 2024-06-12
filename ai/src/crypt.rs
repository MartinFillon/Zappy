//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// cipher
//

use aes_gcm::aead::{Aead, KeyInit};
use aes_gcm::{Aes256Gcm, Key, Nonce};
use hex::{decode, encode};
use sha2::{Digest, Sha256};

use log::debug;

pub struct Crypt {
    key: String,
    nonce: [u8; 12],
}

impl Crypt {
    fn new(key: String) -> Self {
        let nonce = derive_nonce_from_string("zappy");
        Self { key, nonce }
    }

    fn get_key(key: &str) -> String {
        let mut key = key.to_string();
        key.truncate(32);
        if key.len() < 32 {
            key.extend(std::iter::repeat('0').take(32 - key.len()));
        }
        key
    }

    pub fn encrypt(&self, data: Vec<u8>) -> Option<String> {
        let key_str = Crypt::get_key(&self.key);
        let key_bytes = key_str.as_bytes();
        let key = Key::<Aes256Gcm>::from_slice(key_bytes);
        debug!("Encrypt's key: {}", encode(key_bytes));

        let nonce = Nonce::from_slice(&self.nonce);
        debug!("Encrypt's nonce: {}", encode(self.nonce));

        let cipher = Aes256Gcm::new(key);

        let ciphertext = cipher.encrypt(nonce, data.as_ref()).ok();
        ciphertext.map(encode)
    }

    pub fn decrypt(&self, encrypted_data: &str) -> Option<String> {
        let key_str = Crypt::get_key(&self.key);
        let key_bytes = key_str.as_bytes();
        let key = Key::<Aes256Gcm>::from_slice(key_bytes);
        debug!("Decrypt's key: {}", encode(key_bytes));

        let nonce = Nonce::from_slice(&self.nonce);
        debug!("Decrypt's nonce: {}", encode(self.nonce));

        let cipher = Aes256Gcm::new(key);

        let ciphertext = decode(encrypted_data).expect("decoding failure");
        let decrypted_data = cipher.decrypt(nonce, ciphertext.as_ref()).ok()?;
        String::from_utf8(decrypted_data).ok()
    }
}

fn derive_nonce_from_string(input: &str) -> [u8; 12] {
    let mut hasher = Sha256::new();
    hasher.update(input.as_bytes());
    let result = hasher.finalize();

    let mut nonce = [0u8; 12];
    nonce.copy_from_slice(&result[..12]);
    nonce
}

#[cfg(test)]
mod tests {
    use super::{derive_nonce_from_string, Crypt};

    #[test]
    fn test_encrypt_decrypt() {
        let crypt = Crypt::new("test".to_string());
        let data = "Hello, World!".as_bytes().to_vec();
        let encrypted_data = crypt.encrypt(data.clone()).unwrap();
        let decrypted_data = crypt.decrypt(&encrypted_data).unwrap();
        assert_eq!(data, decrypted_data.as_bytes());
    }

    #[test]
    fn test_encrypt_decrypt_empty() {
        let crypt = Crypt::new("test".to_string());
        let data = "".as_bytes().to_vec();
        let encrypted_data = crypt.encrypt(data.clone()).unwrap();
        let decrypted_data = crypt.decrypt(&encrypted_data).unwrap();
        assert_eq!(data, decrypted_data.as_bytes());
    }

    #[test]
    fn test_encrypt_decrypt_long() {
        let crypt = Crypt::new("Team1".to_string());
        let data = "2 Need Incantationers for Level 2".as_bytes().to_vec();
        let encrypted_data = crypt.encrypt(data.clone()).unwrap();
        let decrypted_data = crypt.decrypt(&encrypted_data).unwrap();
        assert_eq!(data, decrypted_data.as_bytes());
    }

    #[test]
    fn test_derive_nonce_from_string() {
        let nonce = derive_nonce_from_string("zappy");
        assert_eq!(nonce.len(), 12);
    }

    #[test]
    fn test_derive_nonce_from_string_empty() {
        let nonce = derive_nonce_from_string("");
        assert_eq!(nonce.len(), 12);
    }

    #[test]
    fn test_get_key() {
        let key = "test";
        let key = Crypt::get_key(key);
        assert_eq!(key.len(), 32);
    }

    #[test]
    fn test_get_key_empty() {
        let key = "";
        let key = Crypt::get_key(key);
        assert_eq!(key.len(), 32);
    }
}
