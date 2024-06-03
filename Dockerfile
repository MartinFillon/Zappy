# This file is to be run in order to build the project in a github action

FROM epitechcontent/epitest-docker:latest
RUN echo -e "max_parallel_downloads=10\nfastestmirror=True" >> sudo cat /etc/dnf/dnf.conf
RUN dnf -y install raylib-devel
RUN dnf -y install asio-devel
RUN adduser -G wheel student
USER student
RUN mkdir -p /home/student/dev
RUN chmod 777 /home/student/dev
WORKDIR /home/student/dev
CMD ["bash"]
