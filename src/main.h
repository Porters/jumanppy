#ifdef __cplusplus
extern "C" {
#endif

struct Morpheme
{
    std::string surface;
    std::string reading;
    std::string pos;
    std::string subpos;
    std::string conjForm;
    std::string conjType;
    std::string baseForm;
    std::string pronunciation;
};

const char * analyze(const char * model, const char * text);
void free_memory(const char* ptr);

#ifdef __cplusplus
}
#endif
