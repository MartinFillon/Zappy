FROM epitechcontent/epitest-docker:latest

COPY . /zappy/

WORKDIR /zappy/

RUN make -C server re

EXPOSE 4242

ENTRYPOINT [ "./docker/entrypoint.sh" ]
