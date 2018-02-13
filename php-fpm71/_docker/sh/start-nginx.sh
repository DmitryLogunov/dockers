#!/bin/bash
rm /etc/nginx/nginx.conf
cp /usr/src/_docker/nginx/nginx.conf /etc/nginx/nginx.conf
mkdir /etc/nginx/hosts
cp /usr/src/_docker/nginx/hosts/api.conf /etc/nginx/hosts/api.conf
nginx -g "daemon off;"
