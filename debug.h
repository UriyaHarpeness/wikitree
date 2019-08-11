#pragma once

/**
 * Defines logging configurations.
 */

/// Defines debug config as on.
#define DEBUG_ON 0x1

/// Defines debug config as off.
#define DEBUG_OFF 0x0

/***********************/
/******DEFINE*HERE******/
/***********************/

#define DEBUG_DEPTH DEBUG_ON
#define DEBUG_PROGRESS DEBUG_ON

/***********************/
/*******END*DEFINE******/
/***********************/

#ifdef DEBUG_ALL

/// Log threads related messages.
#define DEBUG_THREADS DEBUG_ON

/// Log search depth related messages.
#define DEBUG_DEPTH DEBUG_ON

/// Log pages resolving related messages.
#define DEBUG_PAGES_RESOLVE DEBUG_ON

/// Log search progress related messages.
#define DEBUG_PROGRESS DEBUG_ON

#endif // DEBUG_ALL
