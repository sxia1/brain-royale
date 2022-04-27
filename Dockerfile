FROM ubuntu:20.04
ENV DEBIAN_FRONTEND=noninteractive
ENV PORT=8080

RUN apt-get update -qq
RUN apt-get upgrade -qq

RUN apt install make -qq

# BOOST
RUN apt install libboost-all-dev -y -qq

# NODE JS
CMD ["curl", "-sL", "https://deb.nodesource.com/setup_16.x -o", "/tmp/nodesource_setup.sh"]
CMD ["bash", "/temp/nodesource_setup.sh"]
RUN apt install nodejs -y -qq

WORKDIR /brain-royale
COPY . /brain-royale

CMD ["make"]
CMD ["make", "run"]
EXPOSE 8080
