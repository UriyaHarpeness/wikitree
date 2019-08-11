#include "LinksResolver.h"

LinksResolver::LinksResolver() : m_running_count(0), m_threads_exited_counter(0), m_thread_is_waiting(false) {
    for (auto &single_thread : m_threads) single_thread = nullptr;
    for (uint8_t &thread_exited : m_threads_exited) thread_exited = 0;
}

LinksResolver::~LinksResolver() = default;

void LinksResolver::wait_until_done() {
    m_running_lock.lock();
    if (!m_running_count) {
        m_running_lock.unlock();
        return;
    }
    m_running_lock.unlock();
    unique_lock<mutex> done(m_done_lock);
    m_done_condition.wait(done);
#if DEBUG_THREADS
    cout << "done condition notified" << endl;
#endif // DEBUG_THREADS
}

void LinksResolver::join_threads() {
    for (uint8_t i = 0; i < thread_num; i++) {
        if (m_threads[i]) {
#if DEBUG_THREADS
            cout << "joining thread " << (int) i << ": " << m_threads[i] << endl;
#endif // DEBUG_THREADS
            m_threads[i]->join();
            m_threads[i] = nullptr;
        }
    }
    m_running_count = 0;
    m_threads_exited_counter = 0;
}

void LinksResolver::resolve_links_thread(Node *node, uint8_t thread_id) {
    // `resolve_links` accesses the disk, and when using multiple threads, normally this may cause collision, but since
    // the links that are resolved are nodes in a tree, and each node has a unique value, no such collision is possible.
    node->resolve_links();
    m_running_lock.lock();
    m_running_count--;
    if (!m_running_count && !m_thread_is_waiting) {
        m_done_condition.notify_all();
    }
    m_threads_exited[m_threads_exited_counter++] = thread_id;
    lock_guard<mutex> exiting_guard(m_exiting_lock);
    m_running_lock.unlock();
    m_waiting_condition.notify_one(); // Only one thread should be in wait at a time.
}

void LinksResolver::resolve_links(Node *node) {
    m_running_lock.lock();
    if (m_running_count == thread_num) {
        m_thread_is_waiting = true;
        m_running_lock.unlock();
        unique_lock<mutex> waiting(m_waiting_lock);
        m_waiting_condition.wait(waiting);
        m_running_lock.lock();
        m_thread_is_waiting = false;
    }
    m_exiting_lock.lock();
    if (m_threads_exited_counter) {
        m_threads_exited_counter--;
        if (m_threads[m_threads_exited[m_threads_exited_counter]] &&
            m_threads[m_threads_exited[m_threads_exited_counter]]->joinable()) {
#if DEBUG_THREADS
            cout << "joining thread " << (int) m_threads_exited[m_threads_exited_counter] << ": "
                 << m_threads[m_threads_exited[m_threads_exited_counter]] << endl;
#endif // DEBUG_THREADS
            m_threads[m_threads_exited[m_threads_exited_counter]]->join();
            delete m_threads[m_threads_exited[m_threads_exited_counter]];
        }
        m_threads[m_threads_exited[m_threads_exited_counter]] = new thread(&LinksResolver::resolve_links_thread, this,
                                                                           node,
                                                                           m_threads_exited[m_threads_exited_counter]);
#if DEBUG_THREADS
        cout << "created thread number " << (int) m_running_count << " (reuse): "
             << m_threads[m_threads_exited[m_threads_exited_counter]] << endl;
#endif // DEBUG_THREADS
    } else {
        m_threads[m_running_count] = new thread(&LinksResolver::resolve_links_thread, this, node, m_running_count);
#if DEBUG_THREADS
        cout << "created thread number " << (int) m_running_count << " (new): "
             << m_threads[m_running_count] << endl;
#endif // DEBUG_THREADS
    }
    m_exiting_lock.unlock();
    m_running_count++;
    m_running_lock.unlock();
}
