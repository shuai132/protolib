#!/usr/bin/env bash

PROTO_DIR=$1
PROTO_OUT=$2

cd ${PROTO_DIR} && \
mkdir -p ${PROTO_OUT} && \
protoc *.proto --cpp_out=${PROTO_OUT}
