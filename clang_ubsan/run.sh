#!/bin/bash

mkdir -p share

docker run -it --name clanger --mount src="$(pwd)/share",target=/share,type=bind djan/clanger

