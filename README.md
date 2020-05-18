# MetaCall Embedding Server Example

This example shows how to embed Net Server from NodeJS into C/C++ source code. The instructions are focused on Linux but it can be ported to other platforms easily.

## Dependencies

For building this example you need NodeJS to be installed in the system (either 8.x and 10.x have been tested) and Python 2.7 available as `python` command (due to NodeJS build system dependency). For debian based distros:

```bash
sudo apt-get install -y --no-install-recommends build-essential cmake ca-certificates git nodejs npm python2.7 node-gyp unzip
sudo npm install -g npm@latest
alias python=/usr/bin/python2.7
```

## Build

Build the project, MetaCall dependency may require root permissions in order to be installed in the system.

```bash
git clone https://github.com/metacall/embedding-server-example.git
mkdir embedding-server-example/build && cd embedding-server-example/build
cmake ..
cmake --build . --target install
```

## Run

From project root directory, run the following commands:

```bash
export LOADER_LIBRARY_PATH="/usr/local/lib"
export LOADER_SCRIPT_PATH="`pwd`"
embedding-server-example
```

## Docker

Building and running with Docker:

```bash
docker build --build-arg DISABLE_CACHE=`date +%s` -t metacall/embedding-server-example .
docker run --rm -p 8124:8124 -e LOADER_LIBRARY_PATH="/usr/local/lib" -e LOADER_SCRIPT_PATH="/root/embedding-server-example" -it metacall/embedding-server-example embedding_server_example
```

Testing if it works:
```bash
curl localhost:8124
```
