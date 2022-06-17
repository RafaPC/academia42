FROM debian:buster

RUN apt update
RUN apt install -y nginx openssl

RUN mkdir /etc/nginx/ssl

COPY conf/server /etc/nginx/conf.d/default.conf

# Creates ssl certificate
RUN mkdir ssl && openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes -out /etc/nginx/ssl/server.pem -keyout /etc/nginx/ssl/server.key \
-subj "/C=ES/ST=Madrid/L=Madrid/O=FT_INCEPTION_SL/OU=IT Department/CN=www.inception.com"

EXPOSE 443/tcp

CMD [ "nginx", "-g", "daemon off;" ]
