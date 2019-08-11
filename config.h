#pragma once

/**
 * Defines program behavior configurations.
 */

/// The maximum number of threads to use for resolving pages.
#define MAXIMUM_RESOLVING_THREAD_NUM 10

/// The maximum number of times to receive an `curlpp::LibcurlRuntimeError` before stopping the program, this may occur
/// when using multiple threads.
#define MAXIMUM_RESOLVE_ERRORS 3
