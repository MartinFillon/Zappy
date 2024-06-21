##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## config
##

class Config:
    def __init__(self, args: list, timeout=None |float) -> None:
        self.args = args
        self.timeout = timeout

class ConfigClient:
    def __init__(
        self,
        port: int,
        cmd_line: None | list[str],
        cmds: None | list[str],
        output: None | str,
        host: str="127.0.0.1"
    ) -> None:
        self.port = port
        self.host = host
        self.cmd_line = cmd_line
        self.cmds = cmds
        self.output = output

class ConfigTest:
    def __init__(
        self,
        name: str,
        config: Config,
        success: str,
        failure: str,
        cliConf: ConfigClient,
    ) -> None:
        self.name = name
        self.config = config
        self.success = success
        self.failure = failure
        self.cliConf = cliConf

### CONFIGS ###

timeout_config = ConfigTest(
    name = "[TEST Timeout] ",
    config = Config(
        args=[
            "./zappy_server",
            "-p", "4242",
            "-x", "10",
            "-y", "10",
            "-n", "team1", "team2", "team3",
            "-c", "4",
            "-f", "100",
            "-l", "DEBUG"
        ],
        timeout=2
    ),
    success = "Test has timeout: OK",
    failure = "Test has not timeout: KO",
    cliConf=ConfigClient(
        port=4242,
        cmd_line= None,
        cmds= None,
        output= None,
    )
)


simple_connection = ConfigTest(
    name = "[TEST Client connect] ",
    config = Config(
        args=[
            "./zappy_server",
            "-p", "4242",
            "-x", "10",
            "-y", "10",
            "-n", "team1", "team2", "team3",
            "-c", "4",
            "-f", "100",
            "-l", "DEBUG"
        ]
    ),
    success = "Test connection handled: OK",
    failure = "Test client not handled: KO",

    cliConf=ConfigClient(
        port=4242,
        cmd_line= None,
        cmds= None,
        output= "WELCOME\n",
    )
)

team_connection = ConfigTest(
    name = "[TEST Team connect] ",
    config = Config(
        args=[
            "./zappy_server",
            "-p", "8080",
            "-x", "10",
            "-y", "10",
            "-n", "team1", "team2", "team3",
            "-c", "4",
            "-f", "100",
            "-l", "DEBUG"
        ]
    ),
    success = "Test Team handled: OK",
    failure = "Test Team not handled: KO",

    cliConf=ConfigClient(
        port=8080,
        cmd_line= None,
        cmds= ["team1\n"],
        output= "WELCOME\n3\n10 10\n",
    )
)

cli_simple_cmds = ConfigTest(
    name = "[TEST Simple commands] ",
    config = Config(
        args=[
            "./zappy_server",
            "-p", "8080",
            "-x", "10",
            "-y", "10",
            "-n", "team1", "team2", "team3",
            "-c", "4",
            "-f", "100",
            "-l", "DEBUG"
        ]
    ),
    success = "Test Simple commands handled: OK",
    failure = "Test Simple commands not handled: KO",

    cliConf=ConfigClient(
        port=8080,
        cmd_line= ["echo", "-ne", "team1\nForward\nRight\nLeft"],
        cmds= ["team1\n", "Forward\n", "Left\n", "Right\n"],
        output= "WELCOME\n3\n10 10\nok\nok\nok\n"
    )
)

hard_test = ConfigTest(
    name = "[TEST Hard input] ",
    config = Config(
        args=[
            "./zappy_server",
            "-p", "8080",
            "-x", "10",
            "-y", "10",
            "-n", "team1", "team2", "team3",
            "-c", "4",
            "-f", "100",
            "-l", "DEBUG"
        ]
    ),
    success = "Test Hard input handled: OK",
    failure = "Test Hard input handled: KO",

    cliConf=ConfigClient(
        port=8080,
        cmd_line= ["cat", "/dev/urandom"],
        cmds= None,
        output= "WELCOME\n"
    )
)
