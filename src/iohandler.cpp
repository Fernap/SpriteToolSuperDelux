#include "iohandler.h"

void iohandler::set(iotype tp, FILE* newhandle) {
    if (m_replaced[tp])
        fclose(m_handles[tp]);
    m_handles[tp] = newhandle;
    m_replaced[tp] = true;
}

iohandler& iohandler::get_global() {
    static iohandler global_handler{};
    return global_handler;
}

iohandler::iohandler() : m_handles{stdin, stdout, stderr, nullptr}, m_replaced{false, false, false, false} {
}
char iohandler::getc() {
    return static_cast<char>(fgetc(m_handles[in]));
}

iohandler::~iohandler() {
    for (size_t i = 0; i < sizeof(m_handles) / sizeof(m_handles[0]); i++) {
        if (m_replaced[i])
            fclose(m_handles[i]);
    }
}

int iohandler::scanf(const char* fmt, ...) {
    va_list list{};
    va_start(list, fmt);
    int ret = vfscanf(m_handles[in], fmt, list);
    va_end(list);
    return ret;
}

size_t iohandler::read(char* buf, int size) {
    return fread(buf, sizeof(char), size, m_handles[in]);
}
char* iohandler::readline(char* buf, int size) {
    return fgets(buf, size, m_handles[in]);
}