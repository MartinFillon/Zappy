FROM epitechcontent/epitest-docker:latest

COPY . /zappy/

WORKDIR /zappy/

RUN make -C server re

EXPOSE 4242

CMD ["./zappy_server", "-p", "4242", "-n", "team1", "team2", "-l", "INFO", "--docker"]
