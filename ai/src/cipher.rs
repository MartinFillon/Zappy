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

struct Cipher {
    key: String,
    nonce: [u8; 12],
}

impl Cipher {
    fn derive_nonce_from_string(input: &str) -> [u8; 12] {
        let mut hasher = Sha256::new();
        hasher.update(input.as_bytes());

        let result = hasher.finalize();

        let mut nonce = [0u8; 12];
        nonce.copy_from_slice(&result[..12]);
        nonce
    }

    fn set_key(&mut self, mut key: String) {
        key.truncate(32);
        if key.len() < 32 {
            key.extend(std::iter::repeat('0').take(32 - key.len()));
        }
        self.key = key;
    }

    fn encrypt(mut key: String, data: Vec<u8>) -> String {
        key.truncate(32);
        if key.len() < 32 {
            key.extend(std::iter::repeat('0').take(32 - key.len()));
        }
        let key_bytes = key.as_bytes();

        let key = Key::<Aes256Gcm>::from_slice(key_bytes);
        debug!("Key: {}", encode(key_bytes));

        let nonce_bytes = Cipher::derive_nonce_from_string("zappy");
        let nonce = Nonce::from_slice(&nonce_bytes);
        debug!("Nonce: {}", encode(&nonce_bytes));

        let cipher = Aes256Gcm::new(key);

        let ciphertext = cipher
            .encrypt(nonce, data.as_ref())
            .expect("encryption failure!");

        encode(&ciphertext)
    }

    fn decrypt(mut key: String, encrypted_data: &str) -> String {
        key.truncate(32);
        if key.len() < 32 {
            key.extend(std::iter::repeat('0').take(32 - key.len()));
        }
        let key_bytes = key.as_bytes();

        let key = Key::<Aes256Gcm>::from_slice(key_bytes);
        debug!("Key: {}", encode(key_bytes));

        let nonce_bytes = Cipher::derive_nonce_from_string("zappy");
        let nonce = Nonce::from_slice(&nonce_bytes);
        debug!("Nonce: {}", encode(&nonce_bytes));

        let cipher = Aes256Gcm::new(key);

        let ciphertext = decode(encrypted_data).expect("decoding failure");
        let decrypted_data = cipher
            .decrypt(nonce, ciphertext.as_ref())
            .expect("decryption failure!");

        String::from_utf8(decrypted_data).expect("invalid UTF-8")
    }
}
