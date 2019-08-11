#pragma once

#include "../node/Node.h"
#include "../config.h"
#include "../debug.h"

#include <mutex>
#include <thread>
#include <condition_variable>

using namespace std;

class Node;

/**
 * A class for resolving pages using multi-threading.
 */
class LinksResolver {
public:

    /**
     * Constructor.
     */
    LinksResolver();

    /**
     * Destructor.
     */
    ~LinksResolver();

    /**
     * Wait for the resolving to be done.
     *
     * Waits on the `m_done_condition` that is set when the resolving of pages of all running threads is done.
     */
    void wait_until_done();

    /**
     * Join all running threads.
     *
     * A cleanup function to be called after `wait_until_done`, joins the threads that finished running.
     */
    void join_threads();

    /**
     * Resolve links of a given node.
     *
     * Creates a thread or blocks until one is done, calls `node`'s `Node::resolve_links` in a multi-threaded way, since
     * this is the function that takes up most of the time (especially when the links are resolved through the network).
     *
     * @param node  The node to resolve its links in turn.
     */
    void resolve_links(Node *node);

    /**
     * Resolve links thread function.
     *
     * Supposed to be called in a new thread, interacts with the class and calls `node`'s `Node::resolve_links` in turn,
     * this function's thread is created in `resolve_links`, and calls the node's, every `Node::resolve_links` is called
     * in a new thread, meaning through a call to this function in a new thread.
     *
     * @param node  The node to resolve its links in the new thread.
     * @param thread_id The ID of the thread.
     */
    void resolve_links_thread(Node *node, uint8_t thread_id);


private:

    /// The maximum number of threads for resolving.
    static const uint8_t thread_num = MAXIMUM_RESOLVING_THREAD_NUM;

    /// The number of currently running threads.
    uint16_t m_running_count;

    /// The threads used for resolving.
    thread *m_threads[thread_num]{};

    /// The number of exited threads that are still unused.
    uint8_t m_threads_exited_counter;

    /// The IDs of threads that finished resolving, the ID is the index of the thread in `m_threads`.
    uint8_t m_threads_exited[thread_num]{};

    /// A mutex for controlling access to the running threads' related fields.
    mutex m_running_lock;

    /// A mutex for indicating when a thread has exited and for access to exited thread's related fields.
    mutex m_exiting_lock;

    /// A mutex used for waiting (in association with `m_waiting_condition`), until a thread is done when the limit is
    /// reached.
    mutex m_waiting_lock;

    /// The condition variable corresponding to `m_waiting_lock`.
    condition_variable m_waiting_condition;

    /// A mutex used for waiting (in association with `m_done_condition`), until all threads have done resolving.
    mutex m_done_lock;

    /// The condition variable corresponding to `m_done_lock`.
    condition_variable m_done_condition;

    /// Is there a thread waiting to be run.
    bool m_thread_is_waiting;
};
