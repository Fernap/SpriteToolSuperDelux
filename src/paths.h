#include <cstring>
#include <filesystem>
#include <string>

#ifdef DEBUGMSG
template <typename... A> void debug_print(const char *msg, A... args) {
    printf(msg, args...);
}
#endif

bool nameEndWithAsmExtension(const char *name);
bool nameEndWithAsmExtension(std::string_view name);
std::string cleanPathTrailFromString(std::string path);
void set_paths_relative_to(const char **path, const char *arg0);