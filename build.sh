#!/usr/bin/bash

r="$(git rev-parse --show-toplevel)"

if [[ ! -f "$r/src/rpc/list.h"  ]]; then
	if [[! -d /usr/bin/rpcgen ]]; then
		echo "Missing rpcgen, try copy-pasting the following:"
		echo "> sudo apt-get install rpcgen"
		exit
	fi

	cd "$r/src/rpc/"
	rpcgen -C list.x
fi

if [[ ! -f /usr/bin/cmake ]]; then
	echo "Missing cmake, try copy-pasting the following:"
	echo "> sudo apt-get install build-essentials cmake"
	exit
fi

cd "$r"
cmake . && make
