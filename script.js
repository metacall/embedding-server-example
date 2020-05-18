#!/usr/bin/env node

'use strict';

const net = require('net');

async function server() {
	const server = await net.createServer(socket => {
		socket.on('end', () => console.log('Client disconnected.'));
		socket.on('data', data => console.log(`Server recieved:\n${data}`));
		socket.write('Hello World.\r\n');
		socket.end();
	});

	server.on('error', err => console.log(`Error: ${err.message}.`));
	server.listen(8124, () => console.log('Server listening.'));
}

module.exports = {
	server,
};
