/*
 *	MetaCall Embedding Server Example by Parra Studios
 *	An example of embedding Net Server from NodeJS into C/C++.
 *
 *	Copyright (C) 2016 - 2020 Vicente Eduardo Ferrer Garcia <vic798@gmail.com>
 *
 *	Licensed under the Apache License, Version 2.0 (the "License");
 *	you may not use this file except in compliance with the License.
 *	You may obtain a copy of the License at
 *
 *		http://www.apache.org/licenses/LICENSE-2.0
 *
 *	Unless required by applicable law or agreed to in writing, software
 *	distributed under the License is distributed on an "AS IS" BASIS,
 *	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *	See the License for the specific language governing permissions and
 *	limitations under the License.
 *
 */

#include <metacall/metacall.h>
#include <stdio.h>

static int cleanup(int code)
{
	if (metacall_destroy() != 0)
	{
		return code != 0 ? -code : -255;
	}

	return code;
}

int main(int argc, char *argv[])
{
	struct metacall_log_stdio_type log_stdio = { stdout };

	printf(metacall_print_info());

	// Define log stream
	if (metacall_log(METACALL_LOG_STDIO, (void *)&log_stdio) != 0)
	{
		return cleanup(1);
	}

	// Initialize MetaCall
	if (metacall_initialize() != 0)
	{
		return cleanup(2);
	}

	// NodeJS
	{
		// Array of scripts to be loaded by MetaCall
		const char * js_scripts[] =
		{
			"script.js"
		};

		// Load scripts
		if (metacall_load_from_file("node", js_scripts, sizeof(js_scripts) / sizeof(js_scripts[0]), NULL) != 0)
		{
			return cleanup(3);
		}

		// Execute server function
		void * future = metacall_await("server", metacall_null_args, [](void *, void *) -> void *
		{
			printf("MetaCall server is listening.\n");

			return NULL;
		}, [](void *, void *) -> void *
		{
			printf("MetaCall server failed.\n");

			return NULL;
		}, NULL);

		// Clean future
		metacall_value_destroy(future);
	}

	return cleanup(0);
}
