use crate::{connection::Connection, server::ServerOptions, test::Test};

use super::Client;

#[derive(Debug, Default)]
pub(super) struct Unset;

impl Client for Unset {
    fn connect(
        &mut self,
        _sock: &mut Connection,
        _server_options: &ServerOptions,
        _verbose: bool,
    ) -> Result<(), String> {
        Ok(())
    }

    fn test(
        &mut self,
        sock: &mut Connection,
        test: &Test,
        verbose: bool,
    ) -> Result<Vec<String>, String> {
        test.get_commands()
            .iter()
            .try_fold(Vec::new(), |mut acc, t| {
                if verbose {
                    println!("Sending: {}", t.get_command());
                }

                sock.send(t.get_command().to_string())
                    .map_err(|e| e.to_string())?;

                t.get_expected()
                    .iter()
                    .try_for_each(|e| {
                        let line = sock.get_line().map_err(|e| e.to_string())?;
                        let trimmed = line.trim_end().to_string();
                        if verbose {
                            println!("Received: {}", trimmed);
                        }
                        if trimmed != *e {
                            Err(format!("Expected: {}, got: {}", e, trimmed))
                        } else {
                            Ok(())
                        }
                    })
                    .map_err(|e| acc.push(e))
                    .unwrap_or(());

                Ok(acc)
            })
    }
}
