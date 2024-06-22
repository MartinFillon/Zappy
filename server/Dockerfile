FROM epitechcontent/epitest-docker:latest

COPY . /zappy/server/

WORKDIR /zappy/server/

RUN make re

CMD ["../zappy_server", "-p", "4242", "-n", "team1", "team2"]
