FROM ubuntu:latest

LABEL maintainer="lsm1998 <487005831@qq.com>"

RUN mkdir -p /opt/blog
WORKDIR /opt/blog

COPY blog-backend /opt/blog/blog-backend
COPY config.ini /opt/blog/config.ini

EXPOSE 10040

ENTRYPOINT ["./blog-backend", "-c", "config.ini"]