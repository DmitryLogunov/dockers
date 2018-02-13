FROM ubuntu:16.04
COPY ./ /usr/src/app
WORKDIR /usr/src/app
RUN "./build.sh"
CMD ["./bin/api-server" ]
