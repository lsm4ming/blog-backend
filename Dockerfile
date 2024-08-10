FROM ubuntu:latest

LABEL maintainer="lsm1998 <487005831@qq.com>"

RUN mkdir -p /opt/blog
WORKDIR /opt/blog
COPY cmake-build-debug/blog-backend /blog-backend
COPY config/config.ini /config.ini

EXPOSE 9090

ENTRYPOINT ["/blog-backend", "-c", "config.ini"]